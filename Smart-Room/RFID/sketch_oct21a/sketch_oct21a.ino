#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define echoPin 3
#define trigPin 4

MFRC522 mfrc522(SS_PIN, RST_PIN);  
int diode = 2;
long duration;
int distance;

void setup() {
  pinMode(diode,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(trigPin, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  digitalWrite(diode,LOW);
  Serial.print("Poceo je kod");
}

void loop() {
  int distance = 451;   // za 1cm veci od max za svaki slucaj
  if(Authorize()){

      while(distance >= 60){
        distance = Scan();
        delay(500);  
      }
      digitalWrite(diode,HIGH);
      delay(1000);
      digitalWrite(diode,LOW);
  }else{
      digitalWrite(diode,LOW);
      
    }

  delay(100);
}

int Scan(){
    digitalWrite(trigPin,LOW); //vrati na default
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH); //aktivira trigger na 10 microseconds 
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW); //ugasi trigger

    duration = pulseIn(echoPin, HIGH); //cita talase sa echo pina i vraca vreme trajanja zvucnog talasa u mikrosekundama
    Serial.println(duration);
    distance = duration * 0.034 / 2; // brzina zvuka podeljena sa 2 (tamo i nazad)
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    return distance;  
}

bool Authorize(){
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      //Serial.println("Waiting for card");
      return false;
    }
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      Serial.println("Selected");
      return false;
    }
    Serial.print("UID tag :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == "C9 60 31 C3") 
    {
      Serial.println("Authorized access");
      Serial.println();
      return true;
    }
   
   else   {
    
      Serial.println(" Access denied");
      return false;
    
    }    
}
