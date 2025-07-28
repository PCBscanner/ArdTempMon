#include "max6675.h"

//MAX6675 parameters
int8_t PIN_SO      = 4;  //Serial Out (SO) pin
int8_t PIN_SCK     = 5;  //Clock (SCK) pin
int8_t PIN_CS1     = 6;  //Chip Select (CS) pin
int8_t PIN_CS2     = 7;  //Chip Select (CS) pin
float  T1          = 0;  //initialising the temperature
const float T1_LIM = 30; //temperature limit before the buzzer goes off

//buzzer parameters
const int8_t  PIN_BUZZER      = 9;    //buzzer to arduino pin 9
const int16_t FREQ_BUZZER     = 1000; //tone frequency for the buzzer
const int16_t DURATION_BUZZER = 300;  //duration in ms

MAX6675 thermocouple1(PIN_SCK, PIN_CS1, PIN_SO);
MAX6675 thermocouple2(PIN_SCK, PIN_CS2, PIN_SO);

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BUZZER, OUTPUT);
  Serial.print("Setup complete.\n");
  delay(3000);
}

void buzzer() {
  Serial.print("Buzzing...\n");
  tone(PIN_BUZZER, FREQ_BUZZER);
  delay(DURATION_BUZZER);
  noTone(PIN_BUZZER);
}

void loop() {
  T1 = thermocouple1.readCelsius();
  Serial.print("T1: ");
  Serial.print(T1);
  Serial.print("\xC2\xB0"); //degree symbol
  Serial.print("C\n");
  
  if (T1 > T1_LIM) {
    Serial.print("Temperature limit exceeded!\n");
    buzzer();
  }

  delay(1000);
}
