int ledPin = 13, sensorPin = 3;
int threshold = 30;
boolean val = false;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin (9600);
}
  
void loop (){
  int data = digitalRead(sensorPin);
  Serial.println(digitalRead(sensorPin));
  if(data == 1){
    if(val==false){
        val=true;
        digitalWrite(ledPin,HIGH);
    }
    else{
        val=false;
        digitalWrite(ledPin,LOW);
    }
  }
   
  delay(500);
}
