#include "MIDI.h"
#include "Audio.h"
#include "Wavetable.h"

//Compile with:
//gcc Synth.c -o Synth -lportaudio -lportmidi
//Run with:
//./Synth

#define kMIDIAmpIncrement 0.007874016f

typedef struct Synth {
  Wavetable *wavetable;
  MIDIStream *midiStream;
  MIDIEvent midiEvent;
} Synth;

void getMIDIInput(Synth *synth);
void process(float *buffer, unsigned long numFrames, Wavetable *wavetable);

int main(void){
  Synth *synth;
  synth = (Synth *) malloc(sizeof(Synth));
  
  synth->wavetable = (Wavetable *) malloc(sizeof(Wavetable));
  initWavetable(synth->wavetable);

  synth->midiStream = (MIDIStream *) malloc(sizeof(MIDIStream));
  if(initPortMIDI(synth->midiStream, true, false)) return 1;

  //Open audio stream
  AudioStream *audioStream;
  audioStream = (AudioStream *) malloc(sizeof(AudioStream));

  if(initPortAudio()) return 1;
  //printPaDevices();
  if(openAudioStream(audioStream, renderCallback, synth)) return 1;
  if(startAudioStream(audioStream)) return 1;
  
  if(closePortAudio()) return 1;

  //Close MIDI stream
  if(closePortMIDI(synth->midiStream)) return 1;

  //Clean up
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

  //Samples are interleaved so increment by two with kNumChannels
  for(unsigned long n=0; n < numFrames; n+=kNumChannels){//iterate over samples in channels
    for(int c=0;c<kNumChannels;c++){//Iterate over number of channels
      outBuffer[n+c] = inBuffer[n+c]; //Copy input to output
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
