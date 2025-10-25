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
bool buttonPressed = false;   // Prevents multiple triggers from single press


int mood = 0;
const int neutralMood = 10;
unsigned long touchedTimer = 0;
unsigned long reducedTimer = 0;
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


  mood = moodChangeWhenPressed(mood);

  mood = moodChangeWhenIgnored(mood);

  changeLEDMood(mood);
  
}


int moodChangeWhenPressed(int mood){
  
  // Invert button state because hardware module gives opposite logic
  pushButtonState = !digitalRead(pushButton);
  delay(5); //Debounce

  if (pushButtonState == HIGH && !buttonPressed){
    mood++;
    if (mood > 20) {
      mood = 20;
    }
    touchedTimer = millis();
    buttonPressed = true;
  }

  if (pushButtonState == LOW && buttonPressed){
    buttonPressed = false;
  }
  
  return mood;

}



int moodChangeWhenIgnored(int mood){
  
  unsigned long currentTimer = millis();
  if ((currentTimer - touchedTimer) > unTouchInterval) {

    if ((currentTimer - reducedTimer) > reducedInterval) {
      mood--;
    
    if (mood < 0) {
      mood = 0;
    }
    reducedTimer = currentTimer;
    } 
  }
  
  return mood;
}



void changeLEDMood(int mood){

  float brightnessInterval = 255 /10;

  if (mood >= neutralMood){
    analogWrite(RedLEDPin, 255);
    analogWrite(GreenLEDPin, brightnessInterval * (mood - neutralMood));
    analogWrite(BlueLEDPin, 255 - brightnessInterval * (mood - neutralMood));
  }

  else {
    analogWrite(RedLEDPin, 255 - brightnessInterval * (neutralMood - mood));
    analogWrite(GreenLEDPin, brightnessInterval * (neutralMood - mood));
    analogWrite(BlueLEDPin, 255 );
  }

}