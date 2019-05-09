#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
// Main questions:
// how does mass determine resonance, hence frequency?

typedef struct Element {
    char *name;
    int Atomic_number;
    double mass;
}Element;
int main() {


///////////////////////////     Filling ElementArray     //////////////////////////////
    Element *ElementArray;
    int e;
    ElementArray = (Element *) calloc (118, sizeof(Element));
    //int n,
    // strcpy(ElementArray[0].name,"Hydrogen");
    ElementArray[0].name = "Hydrogen";
    ElementArray[0].Atomic_number = 2;
    ElementArray[0].mass = 4.002602;

    ElementArray[1].name = "Helium"; 
    ElementArray[1].Atomic_number = 2;
    ElementArray[1].mass = 5.002602; //WRONG MASS!!!!!!!!!

    ElementArray[2].name = "Lithium";
    ElementArray[2].Atomic_number = 3;
    ElementArray[2].mass = 6.941;

    ElementArray[3].name = "Berylium";
    ElementArray[3].Atomic_number = 4;
    ElementArray[3].mass = 9.012182;

    ElementArray[4].name = "Boron";
    ElementArray[4].Atomic_number = 5;
    ElementArray[4].mass = 10.811;

    ElementArray[5].name = "Carbon";
    ElementArray[5].Atomic_number = 6;
    ElementArray[5].mass = 12.0107;

     ElementArray[6].name = "Nitrogen";
    ElementArray[6].Atomic_number = 7; 
    ElementArray[6].mass = 14.0067;
    
     ElementArray[7].name = "Oxygen";
    ElementArray[7].Atomic_number = 8;
    ElementArray[7].mass = 15.9994;

    ElementArray[8].name = "Flourine";
    ElementArray[8].Atomic_number = 9;
    ElementArray[8].mass = 18.9984032;

    ElementArray[9].name = "Neon";
    ElementArray[9].Atomic_number = 10; 
    ElementArray[9].mass = 20.1797;

    ElementArray[10].name = "Sodium";
    ElementArray[10].Atomic_number = 11;
    ElementArray[10].mass = 22.989770;

    ElementArray[11].name = "Magnesium"; 
    ElementArray[11].Atomic_number = 12;
    ElementArray[11].mass = 24.3050;  

    ElementArray[12].name = "Aluminum";
    ElementArray[12].Atomic_number = 13;
    ElementArray[12].mass = 26.981538;

    ElementArray[13].name = "Silicon";
    ElementArray[13].Atomic_number = 14;
    ElementArray[13].mass = 28.0855; 

    ElementArray[14].name = "Phosphorus";
    ElementArray[14].Atomic_number = 15;
    ElementArray[14].mass = 30.973761;

    ElementArray[15].name = "Sulfur";
    ElementArray[15].Atomic_number = 16;
    ElementArray[15].mass = 32.065;

    ElementArray[15].name = "Sulfur";
    ElementArray[15].Atomic_number = 16;
    ElementArray[15].mass = 32.065;

    ElementArray[16].name = "Cholrine";
    ElementArray[16].Atomic_number = 17;
    ElementArray[16].mass = 35.453;

    ElementArray[17].name = "Argon";
    ElementArray[17].Atomic_number = 18;
    ElementArray[17].mass = 39.948;

    ElementArray[18].name = "Potassium";
    ElementArray[18].Atomic_number = 19;
    ElementArray[18].mass = 39.0983; 

    ElementArray[19].name = "Calcium"; 
    ElementArray[19].Atomic_number = 20;
    ElementArray[19].mass = 40.078;

    ElementArray[20].name = "Scandium"; 
    ElementArray[20].Atomic_number = 21;
    ElementArray[20].mass = 44.955910;

    ElementArray[21].name = "Titanium";
    ElementArray[21].Atomic_number = 22;
    ElementArray[21].mass = 47.867;

    ElementArray[22].name = "Vanadium"; 
    ElementArray[22].Atomic_number = 23;
    ElementArray[22].mass = 50.9415;

    ElementArray[23].name = "Chromium"; 
    ElementArray[23].Atomic_number = 24;
    ElementArray[23].mass = 51.9961;

    ElementArray[24].name = "Manganese";
    ElementArray[24].Atomic_number = 25;
    ElementArray[24].mass = 54.938049;

    ElementArray[25].name = "Iron";
    ElementArray[25].Atomic_number = 26; 
    ElementArray[25].mass = 55.845;

    ElementArray[26].name = "Cobalt";
    ElementArray[26].Atomic_number = 27;
    ElementArray[26].mass = 58.933200;

    ElementArray[27].name = "Nickel";
    ElementArray[27].Atomic_number = 28;
    ElementArray[27].mass = 58.6934;

    ElementArray[28].name = "Copper"; 
    ElementArray[28].Atomic_number = 29;
    ElementArray[28].mass = 63.546;

    ElementArray[29].name = "Zinc"; 
    ElementArray[29].Atomic_number = 30; 
    ElementArray[29].mass = 65.409;

    ElementArray[30].name = "Gallium"; 
    ElementArray[30].Atomic_number = 31;
    ElementArray[30].mass = 69.723;

    ElementArray[31].name = "Germanium";
    ElementArray[31].Atomic_number = 32;
    ElementArray[31].mass =  72.64;

    ElementArray[32].name = "Arsenic";
    ElementArray[32].Atomic_number = 33;
    ElementArray[32].mass = 74.92160;

    ElementArray[33].name = "Selenium"; 
    ElementArray[33].Atomic_number = 34;
    ElementArray[33].mass = 78.96;

    ElementArray[34].name = "Bromine";
    ElementArray[34].Atomic_number = 35;
    ElementArray[34].mass = 79.904;

    ElementArray[35].name = "Krypton"; 
    ElementArray[35].Atomic_number = 36;
    ElementArray[35].mass =  83.798;

    ElementArray[36].name = "Rubidium";
    ElementArray[36].Atomic_number = 37; 
    ElementArray[36].mass = 85.4678;

    ElementArray[37].name = "Strontium";
    ElementArray[37].Atomic_number = 38;
    ElementArray[37].mass = 87.62;

    ElementArray[38].name = "Yttrium";
    ElementArray[38].Atomic_number = 39;
    ElementArray[38].mass = 88.90585;

    ElementArray[39].name = "Zicronium"; 
    ElementArray[39].Atomic_number = 40;
    ElementArray[39].mass = 91.224;

    ElementArray[40].name = "Niobium";
    ElementArray[40].Atomic_number = 41;
    ElementArray[40].mass = 92.90638;

    ElementArray[41].name = "Molybdenum"; 
    ElementArray[41].Atomic_number = 42;
    ElementArray[41].mass = 95.94;

    ElementArray[42].name = "Technetium"; // WHOLE NUMBER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ElementArray[42].Atomic_number = 43;
    ElementArray[42].mass = 98.0;

    ElementArray[43].name = "Ruthenium"; 
    ElementArray[43].Atomic_number = 44;
    ElementArray[43].mass = 101.07;

    ElementArray[44].name = "Rhodium";
    ElementArray[44].Atomic_number = 45;
    ElementArray[44].mass = 102.90550;

    ElementArray[45].name = "Palladium"; 
    ElementArray[45].Atomic_number = 46;
    ElementArray[45].mass = 106.42;

    ElementArray[46].name = "Silver";
    ElementArray[46].Atomic_number = 47;
    ElementArray[46].mass = 107.8682;

    ElementArray[47].name = "Cadmium";
    ElementArray[47].Atomic_number = 48;
    ElementArray[47].mass = 112.411;

    ElementArray[48].name = "Indium";
    ElementArray[48].Atomic_number = 49;
    ElementArray[48].mass = 114.818;

    ElementArray[49].name = "Tin";
    ElementArray[49].Atomic_number = 50; 
    ElementArray[49].mass = 118.710;

    ElementArray[50].name = "Antimony"; 
    ElementArray[50].Atomic_number = 51;
    ElementArray[50].mass = 121.760;

    ElementArray[51].name = "Tellurium";
    ElementArray[51].Atomic_number = 52;
    ElementArray[51].mass = 127.60;

    ElementArray[52].name = "Iodine";
    ElementArray[52].Atomic_number = 53;
    ElementArray[52].mass = 126.90447;

    ElementArray[53].name = "Xenon";
    ElementArray[53].Atomic_number = 54; 
    ElementArray[53].mass = 131.293;
 

    printf("Enter Atomic Number 1-54\n\n");
    scanf("%d",&e);
    printf("%s\n%d\n%f\n",ElementArray[e-1].name, ElementArray[e-1].Atomic_number,ElementArray[e-1].mass);
  
   



    free(ElementArray);
    return 0;
   

}


