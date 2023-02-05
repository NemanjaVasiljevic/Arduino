
void moveForward();
void moveBackwards();

int motorpin1 = 2;
int motorpin2 = 3;
int motorpin3 = 4;
int motorpin4 = 5;
int reverseLight = 6;

//OUT 1 minus
//OUT 2 plus

void setup() {
  // put your setup code here, to run once:
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(motorpin3, OUTPUT);
  pinMode(motorpin4, OUTPUT);
  pinMode(reverseLight, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  moveForward();

  delay(1000); 

  moveBackwards();

  delay(2000); 

}

void moveForward(){
  digitalWrite(reverseLight, LOW);

  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
}
void moveBackwards(){
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);

  digitalWrite(reverseLight,HIGH);
}