// C++ code
// author: Ilari Huttula
// program that uses attach interrupt when buttons are pressed and then goes to certain function.

// global variables
int luku = 0; // counter value
int nappiPin = 3; // button1 pin
int pwrOut = 12; // power out pin
int pinVal = 0; // pin value
int ledOn = 0; // variable to see if led is on or off
int tempPin = A0; // temp sensor pin

// setup before loop
void setup() {
  pinMode(pwrOut, OUTPUT); // power output from port 12
  pinMode(nappiPin, INPUT); // button 1 in
  attachInterrupt(1,button1Pressed, RISING); // making attachInterrupt for button1
  attachInterrupt(0,button2Pressed, RISING); // making attachInterrupt for button2
  Serial.begin(9600); // Serial port
}

// main loop
void loop() {
}

// attach interrupt function for button1
void button1Pressed() {
  luku = luku + 1; // adding 1 to counter value
  Serial.print("Laskuri: "); // printing
  Serial.println(luku); // printing
  if (ledOn == 0) {
    ledOn = 1;
    digitalWrite(pwrOut, HIGH);
  } else {
    ledOn = 0;
    digitalWrite(pwrOut, LOW);
  }
}

// attach interrupt function for button2
void button2Pressed() {
  int ADC_sum = 0; // variable for sum of all 50 temps.
  for (int i = 0; i < 50; i++) {
    ADC_sum = ADC_sum + analogRead(tempPin); // adding ADC-value to sum
    delay(20); // Wait for 20 millisecond(s)
  }
  int avgADC = ADC_sum / 50; // calculating avgADC
  double LT = ((5 * avgADC / 1024.0) - 0.5) * 100; // calculating temperature
  
  // printing average ADC and LT
  Serial.print("ADC: ");
  Serial.print(avgADC);
  Serial.print(" lt: ");
  Serial.println(LT);
}