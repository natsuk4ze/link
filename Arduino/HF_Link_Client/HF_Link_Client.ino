#include <VarSpeedServo.h>

VarSpeedServo myServo;

void setup() {
  Serial.begin(9600);

  //サーボのアタッチ
  myServo.attach(9);
  myServo.write(45, 5, true);
}

void loop()
{
  //サーボモータの制御
  char head = Serial.read();

  if (head > 0)
  {
    unsigned char angle = head;
    myServo.write(angle, 5, true);
  }
}
