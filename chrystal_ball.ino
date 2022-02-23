// C++ code
// author: Ilari Huttula
// program that uses LCD-screen, tilt sensor and temperature-sensor. When tilt-sensor is used, programm tells chrystall ball -like answers. When temperature button is pressed temperature is shown on LCD-screen

#include <LiquidCrystal.h> // including LCD-library
LiquidCrystal lcd(12,11,5,4,10,9); // setup for LCD, pins
const int switchPin = 6; // pin for tilt sensor
int switchState = 0; // variable for switchstate
int prevSwitchState = 0; // variable for previous switchstate
int reply; // variable for random reply
int tempPin = A0; // temp sensor pin

void setup(){
  lcd.begin(16,2); //start lcd
  pinMode(switchPin, INPUT); //tilt sensor intput
  lcd.print("Ask the");
  lcd.setCursor(0,1); // set cursor for second row
  lcd.print("Crystal Ball!");
  attachInterrupt(0,buttonPressed, RISING); // making attachInterrupt for button
}


// in the main loop: reading switchstate from
// input pin. If differs from last one, then
// randomly choose from answers and print it to lcd-screen
void loop() {
  switchState = digitalRead(switchPin);
  if (switchState != prevSwitchState) {
    if (switchState == LOW) {
      reply = random(8); // random case number for switch case
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("The ball says: ");
      lcd.setCursor(0,1);
      switch(reply) {
        case 0:
        lcd.print("Yes");
        break;
        case 1:
        lcd.print("Most likely");
        break;
        case 2:
        lcd.print("Certainly");
        break;
        case 3:
        lcd.print("Outlook good");
        break;
        case 4:
        lcd.print("Unsure");
        break;
        case 5:
        lcd.print("Ask again");
        break;
        case 6:
        lcd.print("Doubtful");
        break;
        case 7:
        lcd.print("No");
        break;
      }
    }
  }
  prevSwitchState = switchState; // change prev switchstate
}


// when button is pressed, this attachinterrupt function takes action
void buttonPressed() {
  int ADC_value = analogRead(tempPin); // getting ADC-value
  double degrees = ((5 * ADC_value / 1024.0) - 0.5) * 100; // changind ADC-value to degrees celsius
  // printing temperature to lcd-screen
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp is now: ");
  lcd.setCursor(0,1);
  lcd.print(degrees);
}