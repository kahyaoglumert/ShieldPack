#include<Servo.h>
#include<Wire.h>

Servo tilt;
Servo pan;
const int MPU = 0x68; // I2C address of the MPU-6050
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int val1 = 0;
int val2 = 0;
int secim = 1;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); //seri haberleşme
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Serial.begin(9600);
  pinMode(12, INPUT);
  digitalWrite(12, HIGH);

  tilt.attach(8);
  pan.attach(9);

  tilt.write(90);
  pan.write(90);
  delay(2000);
}

void digitalFiltre() {
  double toplamX = 0;
  double toplamY = 0;

  for (int i = 0; i < 50; i++)
  {
    ivme();
    toplamX = toplamX + AcX;
    toplamY = toplamY + AcY;
  }
  toplamX = toplamX / 50;
  toplamY = toplamY / 50;

  val1 = toplamX;      // reads the value of the potentiometer (value between 0 and 1023)
  val1 = map(val1, -14000, 14000, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  val2 = toplamY;           // reads the value of the potentiometer (value between 0 and 1023)
  val2 = map(val2, -14000, 14000, 0, 180);

  pan.write(val1);
  tilt.write(val2);
  delay(15);

}



void ivme() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)


}

void joystick()
{
  val1 = 0;
  val1 = analogRead(1);
  val1 = map(val1, 0, 1023, 0, 180);
  pan.write(val1);

  delay(30);

  val2 = 0;
  val2 = analogRead(0);
  val2 = map(val2, 0, 1023, 0, 180);
  tilt.write(val2);

  delay(30);

}
 
void loop() {
 

  if (!digitalRead(12)) { // buton ile durum değiştirme
    secim = secim * -1;
    delay(1000);
  }


  if (secim == 1) {
    joystick();   digitalWrite(13, HIGH); }
  else if (secim == -1) {
    digitalFiltre();     digitalWrite(13, LOW);
  }

}




