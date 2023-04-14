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
#define frontTrigger 6
#define frontEcho 10
#define echoPin A5
#define trigPin A4
#define leftEdgeSensor A0
#define rightEdgeSensor A1
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
int backDistance = 0;
int frontDistance = 0;
int fwDist = 0;
long duration;
TYPE_STATE state;
int sensorState;

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
  pinMode(frontTrigger, OUTPUT);
  pinMode(frontEcho, INPUT);
  pinMode(leftEdgeSensor, INPUT);
  pinMode(rightEdgeSensor, INPUT);


  lcd.begin(16,2);
  Serial.begin(9600);

  lcd.print(" check engine! ");


}

void loop() {

  moveForward();



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
  
  fwdSensor();
  moveBackwards(); // ne moze vise napred mora nazad
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
  moveForward(); // ne moze vise nazad
}

void turnRight() {


  while(digitalRead(rightEdgeSensor) == HIGH){
    
      digitalWrite(motorpin1, HIGH);
      digitalWrite(motorpin3, LOW);
      digitalWrite(motorpin2, HIGH);
      digitalWrite(motorpin4, LOW);
      
      //dodati da ne blokira echo senzor
  }
  moveForward();
}

void turnLeft() {
 while(digitalRead(leftEdgeSensor) == HIGH){
    
      digitalWrite(motorpin1, LOW);
      digitalWrite(motorpin3, HIGH);
      digitalWrite(motorpin2, LOW);
      digitalWrite(motorpin4, HIGH);    
    
      //dodati da ne blokira echo senzor

  }
  moveForward();
}

void beeP(int dist){
 
   if(dist >= 12 && dist <= 15){
      currentMillis = millis();
  
      if (currentMillis - previousMillis >= slowBeepInterval) {
        previousMillis = currentMillis;
        tone(buzzer, 1000);
        delay(10);
        noTone(buzzer);

      }
   }else if(dist < 12 && dist >= 8){
      currentMillis = millis();
  
      if (currentMillis - previousMillis >= mediumBeepInterval) {
        previousMillis = currentMillis;
        tone(buzzer, 1250);
        delay(10);
        noTone(buzzer);
      }
   }else if(dist <= 7){
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
  backDistance = duration * 0.034 / 2; // brzina zvuka podeljena sa 2 (tamo i nazad)


  while (backDistance > 4) {

    beeP(backDistance);
    digitalWrite(reverseLight, HIGH);
    currentMillis = millis();
    
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH); 
    backDistance = duration * 0.034 / 2;
    lcd.setCursor(0,1); 
    lcd.print("Distance: ");
    lcd.print(backDistance);
    lcd.println(" cm");


  }
}


void fwdSensor() {
  // merenje prvi put ako je preblizu zida nece upasti u while vec ce odmah iskociti
  digitalWrite(frontTrigger, LOW); //vrati na default
  delayMicroseconds(2);
  digitalWrite(frontTrigger, HIGH); //aktivira trigger na 10 microseconds
  delayMicroseconds(10);
  digitalWrite(frontTrigger, LOW); //ugasi trigger

  duration = pulseIn(frontEcho, HIGH); //cita talase sa echo pina i vraca vreme trajanja zvucnog talasa u mikrosekundama
  frontDistance = duration * 0.034 / 2; // brzina zvuka podeljena sa 2 (tamo i nazad)


  while (frontDistance > 5) {

    if(digitalRead(leftEdgeSensor) == HIGH){
      turnLeft();
    }else if(digitalRead(rightEdgeSensor) == HIGH){
      turnRight();
    }        

    currentMillis = millis();

    digitalWrite(frontTrigger, LOW); 
    delayMicroseconds(2);
    digitalWrite(frontTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(frontTrigger, LOW);

    duration = pulseIn(frontEcho, HIGH); 
    frontDistance = duration * 0.034 / 2;
    lcd.setCursor(0,1); 
    lcd.print("Distance: ");
    lcd.print(frontDistance);
    lcd.println(" cm");


  }
}

