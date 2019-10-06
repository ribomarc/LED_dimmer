/*
  The following sketch is meant to to define dimming value through potentiometer,
  The potentiometer values are changing in range from 0 to 1023
  potentiometer values are converted through the map function to values from 0 to 100% and saved in dimmer.setPower(outVal);
  Serial.begin is used to display dimming values 

  Dimmer is connected to following pins:
  D2 - zero-cross; it's hard-defined because of the use of external interupt 
  dimmerLamp dimmer(4); used to initialize the 4th pin and is defined by the user
  
  void loop()  обработчик потенциометра, вывод информации на серийный порт, задавание значения.
*/

#include <RBDdimmer.h>

dimmerLamp dimmer(4); //initialase port for dimmer: name(PinNumber);

int outVal = 70;

void setup() {
  Serial.begin(9600);
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE) 
  pinMode(13, OUTPUT);      //Define D13 as output to flash status LED
  Serial.println("Dimmer Program is starting...");
  Serial.println("Set value");

  dimmer.setPulseWidth(13); // avoid LED flickering!
}

void printSpace(int val)
{
  if ((val / 100) == 0) Serial.print(" ");
  if ((val / 10) == 0) Serial.print(" ");
}

void loop() {
  int preVal = outVal;

  if (Serial.available())
  {
    int buf = Serial.parseInt();
    if (buf != 0)
    {
      outVal = buf;
    }
    delay(200);
  }

  dimmer.setPower(outVal); // setPower(0-100%);  

  if (preVal != outVal)
  {
    Serial.print("% lampValue -> ");
    printSpace(dimmer.getPower());
    Serial.print(dimmer.getPower());
  }
  delay(50);
  flash_led();
}

void flash_led() {
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
