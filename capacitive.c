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
    else if (csv[i] < sensitivity) {
      noteOff(0x90, note + i, 0);
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
