int motorpin1 = 2;
int motorpin2 = 3;

//OUT 1 minus
//OUT 2 plus

void setup() {
  // put your setup code here, to run once:
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);

  delay(1000); 

  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);

  delay(1000); 

}
