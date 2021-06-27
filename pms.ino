//AD8232 Heart Rate sensor

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(2, INPUT); // Setup for leads off detection LO +
  pinMode(3, INPUT); // Setup for leads off detection LO -

}

void loop() {
  
  if((digitalRead(2) == 1)||(digitalRead(3) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 2:
      Serial.println(analogRead(A0));
  }
  //Wait for a bit to keep serial data from saturating
  delay(1);

  //Ultrasonic, LM35, Bluetooth module, Heart rate sensor, LCD ,Bluetooth
#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX | TX

// Ultrasonic
const int trigPin = 7;
const int echoPin = 6;
const int buzzer = 5;
const int led = 4;
long duration;
int distance;
int safetyDistance;



//LM35 temperature sensor
#define sensor A0
byte degree[8] =
{
  0b00011,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

// LCD Display
#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//The Pulse Sensor
#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM math
#include <PulseSensorPlayground.h>
const int PulseWire = 1; // PulseSensor PURPLE WIRE connected to ANALOG PIN 1
const int LED13 = 13; // The on-board Arduino LED, close to PIN 13.
int Threshold = 550; // Determine which Signal to "count as a beat" and which to ignore
PulseSensorPlayground pulseSensor;

void setup() {
  Serial.begin(9600); // begin serial communitication
  //Bluetooth
  BTserial.begin(9600);

//ultrasonic sensor
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(buzzer, OUTPUT);
pinMode (led, OUTPUT);



//LCD Display
lcd.begin(16, 2);

//The Pulse Sensor
pulseSensor.analogInput(PulseWire);
pulseSensor.blinkOnPulse(LED13); //auto-magically blink Arduino's LED with heartbeat.
pulseSensor.setThreshold(Threshold);
if (pulseSensor.begin()) {
  Serial.println(" Initialising !"); //This prints one time at Arduino power-up, or on Arduino reset.
}
}

void loop() {
  //temperature sensor
  float reading = analogRead(sensor);
  float temperature = reading * (5.0 / 1023.0) * 100;
  delay(20);
   Serial.println("Wait"); //This prints one time at Arduino power-up, or on Arduino reset.

  //The Pulse Sensor
  int myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) {
    Serial.println(" HeartBeat found! "); // If test is "true", print a message "a heartbeat happened".
    Serial.print("BPM: "); // Print phrase "BPM: "
    Serial.println(myBPM); // Print the value inside of myBPM.
    lcd.setCursor(0, 0);          //sets the cursor at row 0 column 0
    lcd.print("Pulse:" + String(myBPM) + "BPM"); // prints 16x2 LCD MODULE
    Serial.print("Pulse:" + String(myBPM) + "BPM"); // prints 16x2 LCD MODULE
    lcd.setCursor(0, 1);          //sets the cursor at row 0 column 0
    lcd.print(String("Temp.: ") + temperature + ("C")); // prints 16x2 LCD MODULE
    Serial.print("Temp.: " + String(temperature)); // prints 16x2 LCD MODULE
    BTserial.print(String(myBPM) + "BPM");
  }
  delay(40); // considered best practice in a simple sketch.






   //ultrasonic sensor
    long duration, distance; // start the scan
    digitalWrite(trigPin, LOW);
    delayMicroseconds(20); // delays are required for a succesful sensor operation.
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); //this delay is required as well!
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); //defining variables
    distance = (duration / 2) / 29.1; // convert the distance to centimeters.
    if (distance >= 8) {
      tone(buzzer, 1000, 500);
      digitalWrite(led, HIGH); // Turn the LED on
      Serial.println("ALERT! LOW GLUCOSE LEVELS DETECTED");
    }
    else {
      digitalWrite(led, LOW); // Keep the LED off
    }
  }
