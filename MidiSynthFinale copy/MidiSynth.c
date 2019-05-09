#include "MIDI.h"
#include "Audio.h"
#include "Wavetable.h"


//gcc MidiSynth.c -o MidiSynth -lportaudio -lportmidi
//Run with:
//./MidiSynth

#define kMIDIAmpIncrement 0.007874016f

typedef struct Synth {
  Wavetable *wavetable;
  MIDIStream *midiStream;
  MIDIEvent midiEvent;
} Synth;

void getMIDIInput(Synth *synth);
void process(float *buffer, unsigned long numFrames, Wavetable *wavetable);

int main(void){
  // int n;
  // int numHarmonics;
  Synth *synth;
  synth = (Synth *) malloc(sizeof(Synth));
  
  synth->wavetable = (Wavetable *) malloc(sizeof(Wavetable));
  initWavetable(synth->wavetable);

  // printf("Enter 1 for sine wave, 2 for Square\n");
  // scanf("%d",&n);
  // switch(n){
  //   case 1:
  //     numHarmonics = 1;
  //     break;
  //   case 2:
  //     printf("Type # of harmonics for Square (1-15)\n");
  //     scanf("%d",&numHarmonics);
  //     break;
  //     default:
  //     numHarmonics = 1;
  //     break;
  // }

  synth->midiStream = (MIDIStream *) malloc(sizeof(MIDIStream));
  if(initPortMIDI(synth->midiStream, true, false)) return 1;

  // while(Pt_Time(NULL) < 10000){
  //   if(Pm_Poll(synth->midiStream->input)){
  //     numMIDIEvents = Pm_Read(synth->midiStream->input, synth->midiStream->events, kMaxMIDIEvents);
  //     for(int i=0; i < numMIDIEvents;i++){
  //       printf(" byte1: %d, time: %.3f\n",
         
  //         Pm_MessageData1(synth->midiStream->events[i].message),//Note Number
  //         synth->midiStream->events[i].timestamp/1000.);

  //     }
  //   }
  // }
  AudioStream *audioStream;
  audioStream = (AudioStream *) malloc(sizeof(AudioStream));

  if(initPortAudio()) return 1;
  //printPaDevices();
  if(openAudioStream(audioStream, renderCallback, synth)) return 1;
  if(startAudioStream(audioStream)) return 1;
  
  if(closePortAudio()) return 1;

  if(closePortMIDI(synth->midiStream)) return 1;

  //Free Mallocs
  if(synth){
    free(synth->wavetable);
    free(synth->midiStream);
    free(synth);
  }

  if(audioStream){
    free(audioStream);
  }
}

int renderCallback(
  const void *input,
  void *output,
  unsigned long frameCount,
  const PaStreamCallbackTimeInfo* timeInfo,
  PaStreamCallbackFlags statusFlags,
  void *userData 
){
  float *inBuffer = (float *) input;
  float *outBuffer = (float *) output;
  unsigned long numFrames = frameCount * kNumChannels;
  Synth * synth = (Synth *) userData;

 
  for(unsigned long n=0; n < numFrames; n+=kNumChannels){
    for(int c=0;c<kNumChannels;c++){
      outBuffer[n+c] = inBuffer[n+c]; 
    }
  }

  getMIDIInput(synth);

  if(synth->midiEvent.isOn){
    synth->midiEvent.isOn = false;
    setFrequency(synth->wavetable,synth->midiEvent.note);
    setAmplitude(synth->wavetable,synth->midiEvent.velocity*kMIDIAmpIncrement);
  }

  process(outBuffer, numFrames, synth->wavetable);

  return 0;
}

void process(float *buffer, unsigned long numFrames, Wavetable *wavetable){
  if(wavetable->isPlaying){
    float sample = 0;
    for(unsigned long n=0; n < numFrames; n+=kNumChannels){
      sample = wavetable->amplitude * next(wavetable);

      for(int c=0;c<kNumChannels;c++){
        buffer[n+c] = sample;
      }
    }
  }
}

void getMIDIInput(Synth *synth){
  static int numMIDIEvents;
  static char velocity;
  static char note;
  MIDIStream *midiStream = synth->midiStream;
  
  if(Pm_Poll(midiStream->input)){
    numMIDIEvents = Pm_Read(midiStream->input, midiStream->events, kMaxMIDIEvents);
    for(int i=0; i < numMIDIEvents; i++){
      note = Pm_MessageData1(midiStream->events[i].message);
      velocity = Pm_MessageData2(midiStream->events[i].message);
      if(velocity != 0){
        synth->midiEvent.note = note;
        synth->midiEvent.velocity = velocity;
        synth->midiEvent.isOn = true;
      }
    }
  }
}
