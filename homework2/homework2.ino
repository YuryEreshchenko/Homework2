/*
 * Yury Ereshchenko 114012010
 * Interactive Toy
 * 
 * RGB shows the toys mood 
 * The user can pet the toy to make it happier (blue light)
 * The toy becomes sad and devrease its points when untoched for a while (red)
 * When the toy get really unhappy its strats flashing white and blue
 * 
 * Date: 29/10/2025
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

bool blinkState = true;
unsigned long previousMillis = 0;
const long interval = 100;


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

  displayMoodLevel(mood);

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

  else if (mood > 0) {
    analogWrite(RedLEDPin, 255 - brightnessInterval * (neutralMood - mood));
    analogWrite(GreenLEDPin, brightnessInterval * (neutralMood - mood));
    analogWrite(BlueLEDPin, 255 );
  }

  else if (mood == 0){

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (blinkState == true){
    analogWrite(RedLEDPin, 0);
    analogWrite(GreenLEDPin, 0);
    analogWrite(BlueLEDPin, 255 );
    }

    else if (blinkState == false){
    analogWrite(RedLEDPin, 0);
    analogWrite(GreenLEDPin, 0);
    analogWrite(BlueLEDPin, 0 );
    }

    blinkState = !blinkState;

  }


  }

}


void displayMoodLevel(int mood){

  if (mood >=0 && mood <= 5){
      Serial.println("Mood 1-5 : Very Bad Mood! Urgent Pets!!!");
  }

  else if (mood >= 6 && mood <= 10){
      Serial.println("Mood 6-10 : Bad Mood! Needs Pets!");
  }

  else if (mood >= 11 && mood <= 15){
      Serial.println("Mood 11-15 : Neutral Mood! Pets always welcomed!");
  }

  else if (mood >= 16 && mood <= 20){
      Serial.println("Mood 16-20 : Happy Mood!");
  }


}