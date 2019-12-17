#include <VarSpeedServo.h>

VarSpeedServo myServo;

void setup() {
  Serial.begin(9600);

  //サーボのアタッチ
  myServo.attach(9);
  myServo.write(90, 5, true);
}

void loop()
{
  //サーボモータの制御
  if (Serial.available() > 0)
  {
    char head = Serial.read();
    unsigned char angle = head;
    myServo.write(angle, 5, true);
  }
}
