// C++ code
// author: Ilari Huttula
// program that uses EEPROM-memory to save temperature data.


// including eeprom library
#include <EEPROM.h>


// global variables
long time;
int how_many_values = 0; //variable for how many values has been saved to EEPROM memory. Helps with printing
int time_lasted = 0; // time variable for keeping count of runned time
int address = 0; // address variable for writing into EEPROM memory
int nappiPin = 3; // button1 pin
int pwrOut = 12; // power out pin
int pinVal = 0; // pin value
int tempPin = A0; // temp sensor pin


// setup before main loop
void setup() {
  time = millis();
  pinMode(pwrOut, OUTPUT); // power output from port 12
  attachInterrupt(1,button1Pressed, RISING); // making attachInterrupt for button1
  attachInterrupt(0,button2Pressed, RISING); // making attachInterrupt for button2
  Serial.begin(9600); // Serial port
}


// main loop
// if time has passed more than 5000 millseconds, then go to function checkTemperature
void loop() {
  if (millis() - time > 5000) {
    time = time + 5000; // add 5 secs to time
    checkTemperature(); // go to function every 5 seconds to check the temperature
  }
}


// function that checks if the temperature value has changed
// and if so then saves it and time when measurement appeared to EEPROM
void checkTemperature() {
  time_lasted = time_lasted + 5;
  int curr_ADC_value = analogRead(tempPin) / 4; // getting current ADC-value. Its divided by 4 so it fits to memory. When printed it is multiplied by 4.

  // if EEPROM memory is full then starting address variable over
  if (address + 2 == EEPROM.length()) {
    address = 0;
  }
  
  // checking if current ADC-value differs from one that is at the memort
  // and if so then just return. otherwise save to eeprom
  if (EEPROM.read(address - 1) == curr_ADC_value) {
    return;
  } else {
    EEPROM.write(address + 1, curr_ADC_value); // saving ADC-value
    EEPROM.write(address, time_lasted); // savin time
    address = address + 2; // new address for the next value saving
    how_many_values = how_many_values + 1; // values counter + 1
    return;
  }
}


// attach interrupt function for button1
// prints EEPROM memory values to the serial monitor
void button1Pressed() {
  // if not saved values then just return
  if (how_many_values == 0) {
    return;
  }
  // print all the values to Serial monitor
  for (int i = 0; i < how_many_values * 2; i = i + 2) {
    Serial.print(" Aika: ");
    Serial.print(EEPROM.read(i));
    Serial.print("\tADC: ");
    Serial.print(EEPROM.read(i+1) * 4);
    Serial.print("\t\tLT: ");
    Serial.print(((5 * (EEPROM.read(i+1) * 4) / 1024.0) - 0.5) * 100); // turning ADC-value to celsius
    Serial.println();
  }
}


// attach interrupt function for button2
// emptys EEPROM memory
void button2Pressed() {
  Serial.println("Tyhjennetään EEPROM ....");
  
  // erasing memory
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  
  Serial.println("EEPROM on tyhjä.");
  
  time_lasted = 0; //time counter to zero
  how_many_values = 0; // values counter to zero
  address = 0; // address to zero
}