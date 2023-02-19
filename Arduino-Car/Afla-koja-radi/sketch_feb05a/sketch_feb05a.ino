//sudo chmod a+rw /dev/ttyUSB0 za permsije pristupa ako ne radi kako treba
//OUT 1 minus
//OUT 2 plus
// kontrola brzine https://www.youtube.com/watch?v=tsntmgA65Qw
#define motorpin1 2
#define motorpin2 3
#define motorpin3 8
#define motorpin4 9
#define ena A4
#define RS 12
#define EN 11
#define D4 4
#define D5 5
#define D6 13
#define D7 7
#define reverseLight A3
#define buzzer A2
#define echoPin 6
#define trigPin 10
#include <LiquidCrystal.h>

enum DIRECTION {FORWARD, BACKWARDS};

typedef struct {
  DIRECTION dir  ;

} TYPE_STATE;

unsigned long previousMillis = 0;
unsigned long currentMillis;
const long interval = 100;
const long slowBeepInterval = 500;
const long mediumBeepInterval = 300;
const long panickBeepInterval = 150;
int distance = 0;
long duration;
TYPE_STATE state;

void moveForward();
void moveBackwards();
void turnLeft();
void turnRight();
void beeP();

LiquidCrystal lcd(RS,EN,D4,D5,D6,D7);


void setup() {
  
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(motorpin3, OUTPUT);
  pinMode(motorpin4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16,2);
  Serial.begin(9600);

  lcd.print(" check engine! ");
  analogWrite(ena, 255);
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);

}

void loop() {
  
  
  /*moveForward();
  delay(1000);
  moveBackwards();
  delay(10);*/
  
}

void moveForward() {
  state.dir = FORWARD;
  lcd.setCursor(0,0);
  lcd.print("State:   FORWARD");

  digitalWrite(reverseLight, LOW);
  
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);
}

void moveBackwards() {
  state.dir = BACKWARDS;
  lcd.setCursor(0,0);
  lcd.print("State: BACKWARDS");

  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);

  parkingSensor();
}

void turnRight() {

  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);

}

void turnLeft() {
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);

}

void beeP(int dist){
 
   if(dist >= 10 && dist <= 13){
      currentMillis = millis();
  
      if (currentMillis - previousMillis >= slowBeepInterval) {
        previousMillis = currentMillis;
        tone(buzzer, 1000);
        delay(10);
        noTone(buzzer);

      }
   }else if(dist < 10 && dist >= 6){
      currentMillis = millis();
  
      if (currentMillis - previousMillis >= mediumBeepInterval) {
        previousMillis = currentMillis;
        tone(buzzer, 1250);
        delay(10);
        noTone(buzzer);
      }
   }else if(dist <= 5){
      currentMillis = millis();
  
      if (currentMillis - previousMillis >= panickBeepInterval) {
        previousMillis = currentMillis;
        tone(buzzer, 1500);
        delay(10);
        noTone(buzzer);
       
      }
   }
  
}

void parkingSensor() {
  // merenje prvi put ako je preblizu zida nece upasti u while vec ce odmah iskociti
  digitalWrite(trigPin, LOW); //vrati na default
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //aktivira trigger na 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //ugasi trigger

  duration = pulseIn(echoPin, HIGH); //cita talase sa echo pina i vraca vreme trajanja zvucnog talasa u mikrosekundama
  distance = duration * 0.034 / 2; // brzina zvuka podeljena sa 2 (tamo i nazad)


  while (distance > 3) {
    beeP(distance);
    digitalWrite(reverseLight, HIGH);
    currentMillis = millis();

    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH); 
    distance = duration * 0.034 / 2;
    lcd.setCursor(0,1); 
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.println(" cm");


  }
}
