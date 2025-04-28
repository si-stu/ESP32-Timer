#include <Arduino.h>
#include <LiquidCrystal.h>
#include "modeController.h"

#define BOARD_LED 2
#define PIEZO 23 //labled D23 on the board, 15 on breadboard. Broken pin to ground
#define SWITCH 22 //labled D22 on the board, 14 on breadboard

//ESP32 DO NOT USE PINS 34, 35, 36, 39 as OUTPUT - they are INPUT ONLY
//ESP32 DO NOT USE PINS GPIO12-14 as these are used to write to flash

//LCD pins
#define D7 21 //D7 on LED is GPIO14 on ESP32
#define D6 19 //D6 on LED is GPIO12 on ESP32
#define D5 32 //D5 on LED is GPIO32 on ESP32
#define D4 33 //D4 on LED is GPIO33 on ESP32
#define EN 25 //EN on LED is GPIO25 on ESP32
#define RS 26 //RS on LED is GPIO26 on ESP32
#define V0 27 //V0 on LED is GPIO27 on ESP32, controls contrast

// put function declarations here:
//int myFunction(int, int);

//variable declarations
bool timerGoing = false;
int timeout = 5000; //5 seconds
int endTime = 0;
ModeController* modeController; // Create an instance of ModeController
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); // Create an instance of the LiquidCrystal class

void setup() {
  Serial.begin(115200);

  //setup GPIOs
  pinMode(BOARD_LED, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(SWITCH, INPUT); 
  pinMode(V0, OUTPUT);
  analogWrite(V0, 0);

  //initialize the mode controller
  modeController = new ModeController();
  modeController->setMode(Mode::STANDBY);

  lcd.backlight();
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.home();
  lcd.print("Press me"); // Print a message to the LCD
  lcd.setCursor(0,1);
  lcd.print(";)");

}

void loop() {

  //read the switch
  int switchState = digitalRead(SWITCH);

  if(switchState == HIGH){
    Serial.println("Switch is pressed");
    lcd.clear();
    lcd.home();
    lcd.print("Timer"); 
    lcd.setCursor(0, 1);
    lcd.print("Started!");

    //restart timer
    int currentTime = millis();
    endTime = currentTime + timeout;
    timerGoing = true;
  }

  //if timer is started, check if it has expired
  if (timerGoing){
    digitalWrite(BOARD_LED, HIGH);
    int currentTime = millis();
    if(currentTime >= endTime){
      //play piezo
      timerGoing = false;
      tone(PIEZO, 291, 500); //play tone at 291Hz for 500ms
      delay(500);
      noTone(PIEZO);
      digitalWrite(BOARD_LED, LOW);
      Serial.print("Timer expired");
      lcd.clear();
      lcd.home();
      lcd.print("Timer expired!!");
    }
  } else {
    digitalWrite(BOARD_LED, LOW);
  }

}



