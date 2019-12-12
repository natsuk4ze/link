#include <Adafruit_NeoPixel.h>

/*******************************************************
   マクロ定義
 *******************************************************/
#define LED_PIN 3

#define LED_NUM 30
#define DELAYVAL 10

#define TRUE 1
#define FALSE 0

#define LOOP_PERIOD 1000


/*******************************************************
   RGB設定
 *******************************************************/
int colorMinus[3] = {255, 0, 0};
int colorPlus[3] = {0, 50, 255};

/*******************************************************
   プロトタイプ宣言
 *******************************************************/
void EventBlinkTape(int r, int g, int b);
void IdleBlinkTape();

/*******************************************************
  グローバル変数
 *******************************************************/
Adafruit_NeoPixel pixels(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);

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
    if (head == 'p')
    {
      EventBlinkTape(colorPlus[0], colorPlus[1], colorPlus[2]);
    }
    //'m'を受信したらマイナスイベントのLED制御
    else if (head == 'm')
    {
      EventBlinkTape(colorMinus[0], colorMinus[1], colorMinus[2]);
    }
  }

  if (inBlink == FALSE)
  {
    IdleBlinkTape();
  }
}

/*******************************************************
   イベント時の点滅処理
 *******************************************************/
void EventBlinkTape(int r, int g, int b)
{
  inBlink = TRUE;

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
    pixels.clear();
  }

  int color = isLightup == TRUE ? 200 : 0;

  for (int i = 0; i < LED_NUM; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, color, 0));
  }
  pixels.show();
}
