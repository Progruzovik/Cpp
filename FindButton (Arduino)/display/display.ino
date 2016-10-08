#include <SindormirSevenSegments.h>
#include <Wire.h>

//Slave Receiver

Sindormir7segs mi7S;

void setup() {
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  mi7S.commonType(CATODO);
  mi7S.attach(14, 15, 4, 5, 6, 7, 8, 9);
}

void loop() {}

void receiveEvent(int howMany) {
  int x = Wire.read();
  mi7S.print(x);
}
