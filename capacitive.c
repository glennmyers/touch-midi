#include <CapacitiveSensor.h>

const int n = 4;      //number of buttons
int pushButton[n] = {3, 4, 5, 6}; //pin numbers of buttons
int buttonCState[n] = {0};  //current button state
int buttonPState[n] = {0};  //previous button state
int pot = A5;    // potentiometer pin
int sensitivity = 80;
byte note = 36;  //starting note

CapacitiveSensor cs1 = CapacitiveSensor(2, 3); //declaring variables for touch sensing on specific pins
CapacitiveSensor cs2 = CapacitiveSensor(2, 4);
CapacitiveSensor cs3 = CapacitiveSensor(2, 5);
CapacitiveSensor cs4 = CapacitiveSensor(2, 6);
// declaring a variable for 
CapacitiveSensor cs[4] = {cs1, cs2, cs3, cs4};
boolean cs1g = true;
boolean cs2g = true;
boolean cs3g = true;
boolean cs4g = true;
boolean csg[16] = {cs1g, cs2g, cs3g, cs4g};

int prevKnobState;
int knobState;
int offset;
int outputA = 7;
int outputB = 8;

void setup() {
  // knob setup
  pinMode (outputA, INPUT);
  pinMode (outputB, INPUT);
  Serial.begin (9600);
  prevKnobState = digitalRead(outputA);
  offset = 0;

  
  // capacitive setup
  for(int i=0; i<n; i++) {
    cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }
  Serial.begin(115200);
  pinMode(A5,INPUT);
}

void loop() {
  int data, sensitivity;
  data = analogRead(A0);
  sensitivity = map(data,0,1023,50,2000);
  long cs1v = cs1.capacitiveSensor(30);
  long cs2v = cs2.capacitiveSensor(30);
  long cs3v = cs3.capacitiveSensor(30);
  long cs4v = cs4.capacitiveSensor(30);
  long csv[4] = {cs1v, cs2v, cs3v, cs4v};

  // update knob offset
  knobState = digitalRead(outputA); 
  Serial.print("Knob State: ");
  Serial.print(knobState);
  Serial.print("\n")
  if (knobState != prevKnobState){     
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB) != knobState) { 
      offset++;
    } else {
      offset--;
    }
    Serial.print("Offset: ");
    Serial.print(offset);
  } 
  prevKnobState = knobState;

  // read capacitive state
  for (int i = 0; i <= n; i++) {
    if (csg[i]) {
      if (csv[i] > sensitivity) {
        noteOn(0x90, note + offset, 127);
        csg[i] = false;
      }
    }
    else if (csv[i] < sensitivity) {
      noteOff(0x90, note + offset, 0);
      csg[i] = true;
    }

    delay(15);
  }
}

void noteOn(int cmd, int thisPitch, int thisvelocity) //function decleration
{
  //int sensorReading = analogRead(pot);    //read potentiometer pin
  //thisvelocity = map(sensorReading, 0, 1024, 0, 127);    //maping of pot values

  //sending pitch, note and velocity values
  Serial.write(cmd);
  Serial.write(thisPitch);
  Serial.write(thisvelocity);
}
void noteOff(int cmd, int thisPitch, int thisvelocity)    //function decleration
{
  //sending pitch, note and velocity values
  Serial.write(cmd);
  Serial.write(thisPitch);
  Serial.write(0);
}
