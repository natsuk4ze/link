#include <Adafruit_NeoPixel.h>
#include <VarSpeedServo.h>

/*******************************************************
   マクロ定義
 *******************************************************/
#define LED_PIN 6
#define INPUT_PIN 2
#define OUTPUT_PIN 3
#define SERVO_PIN 9

#define LED_NUM 30
#define DELAYVAL 10

#define TRUE 1
#define FALSE 0

#define LOOP_PERIOD 1000


/*******************************************************
   RGB設定
 *******************************************************/
int colorMinus[3] = {255, 0, 0};
int colorPlus[3] = {0, 150, 255};

/*******************************************************
   プロトタイプ宣言
 *******************************************************/
void EventBlinkTape(int r, int g, int b);
void IdleBlinkTape();

/*******************************************************
  グローバル変数
 *******************************************************/
Adafruit_NeoPixel pixels(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);
VarSpeedServo myServo;

char inBlink;       //イベントの点滅中か
char isLightup;     //ライトアップするかどうか
int cntFrame;       //フレームカウント

/*******************************************************
   セットアップ
 *******************************************************/
void setup() {
  //シリアル通信開始
  Serial.begin(9600);

  //LED制御の初期化
  pixels.begin();
  pixels.clear();

  //LED制御変数の初期化
  inBlink = FALSE;
  isLightup = TRUE;
  cntFrame = 0;

  //サーボモータの初期化
  myServo.attach(SERVO_PIN);

  //入出力ピンの初期化
  pinMode(INPUT_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);
}

/*******************************************************
   ループ
 *******************************************************/
void loop()
{
  //シリアルポートからの読み込みを確認
  if (Serial.available() > 0)
  {
    char head = Serial.read();
    //'p'を受信したらプラスイベントのLED制御
    if (head == 'p' && !digitalRead(INPUT_PIN))
    {
      EventBlinkTape(colorPlus[0], colorPlus[1], colorPlus[2]);
    }
    //'m'を受信したらマイナスイベントのLED制御
    else if (head == 'm' && !digitalRead(INPUT_PIN))
    {
      EventBlinkTape(colorMinus[0], colorMinus[1], colorMinus[2]);
    }
    //'r'を受信したらサーボの回転
    else if (head == 'r')
    {
      unsigned char angle = Serial.read();
      myServo.write(angle, 5, true);
    }
  }
}

/*******************************************************
   イベント時の点滅処理
 *******************************************************/
void EventBlinkTape(int r, int g, int b)
{
  inBlink = TRUE;
  digitalWrite(OUTPUT_PIN, HIGH);

  pixels.clear();

  for (int j = 0; j < 5; j++)
  {
    for (int i = 0; i < LED_NUM; i++)
    {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
      pixels.show();
      delay(DELAYVAL);
    }
    for (int i = 0; i < LED_NUM; i++)
    {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      delay(DELAYVAL);
    }
  }

  inBlink = FALSE;
  pixels.clear();

  cntFrame = 0;
  isLightup = FALSE;
  digitalWrite(OUTPUT_PIN, LOW);
}

/*******************************************************
   通常時の点滅処理
 *******************************************************/
void IdleBlinkTape()
{
  cntFrame++;
  if (cntFrame > LOOP_PERIOD)
  {
    cntFrame = 0;
    isLightup = 1 - isLightup;
  }

  int color = isLightup == TRUE ? 200 : 0;

  for (int i = 0; i < LED_NUM; i++)
  {
    pixels.setPixelColor(i, pixels.Color(color, color, color));
  }
  pixels.show();
}
