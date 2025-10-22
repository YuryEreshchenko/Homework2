/*
 * Yury Ereshchenko 114012010
 * RGB LED Controller with Button Interface
 * 
 * Single click: Cycle through colors
 * Double click: Toggle LED ON/OFF
 * The LED color and state are indiciated in the serial monitor
 * 
 * Date: 15/10/2025
 */

// Pin configuration
const int RedLEDPin = 9;
const int GreenLEDPin = 10;
const int BlueLEDPin = 11;
const int pushButton = 2;

// Button state variables
int pushButtonState = 0;
int ledCounter = 1;           // Tracks current color (1-7)
bool buttonPressed = false;   // Prevents multiple triggers from single press

String currentColor = "OFF";

// LED state (currently always HIGH since blinking is disabled)
bool ledState = LOW;


unsigned long previousMillis = 0;
const long interval_blink = 1000; 

int mood = 0;
const int neutralMood = 10;
unsigned long touchedTimer = 0;
unsigned reducedTimer = 0;
const long unTouchInterval = 5000;
const long reducedInterval = 1000;


void setup() {
  Serial.begin(9600);

  pinMode(RedLEDPin, OUTPUT);
  pinMode(GreenLEDPin, OUTPUT);
  pinMode(BlueLEDPin, OUTPUT);
  pinMode(pushButton, INPUT);

  mood = neutralMood;

}

void loop() {

  // Invert button state because hardware module gives opposite logic
  pushButtonState = digitalRead(pushButton);

  if (pushButtonState = HIGH && !buttonPressed){
    mood++;
    if (mood > 20) {
      mood = 20;
    }
    touchedTimer = millis();
    buttonPressed = true;
  }

  if (pushButtonState = LOW && buttonPressed){
    buttonPressed = false;
  }

  // if (pushpushButtonState == LOW) {
  //   pushpushButtonState = HIGH;
  // } else if (pushpushButtonState == HIGH) {
  //   pushpushButtonState = LOW;
  // }

  // Blinking functionality (disabled)
  // Uncomment to make LEDs blink at 1-second intervals

  unsigned long currentTimer = millis();
  if (currentTimer - touchedTimer > unTouchInterval) {

    if (currentTimer - reducedTimer > reducedInterval) {
      mood--;
    } 
    if (mood < 0) {
      mood = 0;
    }
    reducedTimer = currentTimer;
  }


  // Color selection - only active if power is ON ()

  
  float brightnessInterval = 255 /10.10;

  if (mood >= neutralMood){
    analogWrite(RedLEDPin, 255);
    analogWrite(GreenLEDPin, brightnessInterval * (mood - neutralMood));
    analogWrite(BlueLEDPin, 255 - brightnessInterval * (mood - neutralMood));
  }

  else {
    analogWrite(RedLEDPin, 255 - brightnessInterval * (mood - neutralMood));
    analogWrite(GreenLEDPin, brightnessInterval * (mood - neutralMood));
    analogWrite(BlueLEDPin, 255 );
  }
  

}

// Functions to Turn ON and OFF led to make code more readable
// Note: Uses LOW to turn ON and HIGH to turn OFF (common anode RGB LED)
void TurnColorON(int color) {
  digitalWrite(color, LOW);
}

void TurnColorOFF(int color) {
  digitalWrite(color, HIGH);
}