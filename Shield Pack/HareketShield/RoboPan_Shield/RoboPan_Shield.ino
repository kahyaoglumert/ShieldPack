#include<Servo.h>

Servo tilt;
Servo pan;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);

  tilt.attach(8);
  pan.attach(9);

  tilt.write(90);
  pan.write(90);
  delay(2000);
}

int val=0;
int val2=0;
void loop() {
 
    Serial.print("\t button: ");
    Serial.print(digitalRead(12));
    Serial.print("\t X: ");
    Serial.print(analogRead(1));
    Serial.print("\t Y: ");
    Serial.println(analogRead(0));
    
  val=0;
  val = analogRead(1);
  val = map(val, 0, 1023, 0, 180);
  pan.write(val);
  Serial.print("Pan :");
  Serial.print(val);
  delay(30);
  
  val2=0;
  val2 = analogRead(0);
  val2 = map(val2, 0, 1023, 0, 180);
  tilt.write(val2);

  Serial.print("\t Tilt :");
  Serial.println(val2);
  delay(30);


}






