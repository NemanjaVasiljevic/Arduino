// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 5; 
// Create a servo object 
Servo servo; 
int angle = 10;
void setup() { 
   // We need to attach the servo to the used pin number 
   servo.attach(servoPin); 
   servo.write(angle);
   delay(1500);
}
void loop(){ 
  servo.write(0);
  delay(1000);
   // Make servo go to 0 degrees 
   /*for(angle = 10; angle < 180; angle++){
     servo.write(angle);
     delay(10);
   }*/
   servo.write(180);
   delay(1000);
}