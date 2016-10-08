#include <Key.h>
#include <Keypad.h>
#include <Wire.h>

//Master Writer

const byte RED = 5;
const byte GREEN = 6;
const byte LINES = 4;

char keys[LINES][LINES] = 
{
  {'a', 'b', 'c', 'd'},
  {'e', 'f', 'g', 'h'},
  {'i', 'j', 'k', 'l'},
  {'m', 'n', 'o', 'p'}
};
byte rowPins[LINES] = {2, 3, 4, 7};
byte colPins[LINES] = {8, 9, 10, 11};
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, LINES, LINES);

bool isNew[LINES * LINES];
byte currentKey;
byte counter;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  randomSeed(analogRead(0));
  reset();
}

void loop()
{
  char key = customKeypad.getKey();
  if (key) {
    if (isNew[key - 'a']) {
      if (key == currentKey) {
        analogWrite(RED, 0);
        analogWrite(GREEN, 100);
        isNew[currentKey - 'a'] = false;
        currentKey = getRand();
        sendNumber(++counter);
      } else {
        analogWrite(RED, 90);
        analogWrite(GREEN, 10);
      }
    } else {
      analogWrite(RED, 100);
      analogWrite(GREEN, 0);
      reset();
      sendNumber(0);
    }
  }
}

void reset()
{
  for (byte i = 0; i < LINES * LINES; i++) {
    isNew[i] = true;
  }
  currentKey = getRand();
  counter = 0;
}

byte getRand()
{
  byte result;
  do {
    result = random('a', 'p');
  } while (!isNew[result - 'a']);
  return result;
}

void sendNumber(byte number)
{
  Wire.beginTransmission(8);
  Wire.write(number);
  Wire.endTransmission();
}

