/*
   プログラム名：Ticker_Parameter
   テーマ：2つのTickerインスタンスを利用した周期的な割込み
   説明：250ミリ秒と500ミリ秒ごとに割込み、LEDを点灯／消灯させる
*/

#include "ESP32Ticker.h"

// スイッチ用入力ピン（内部プルアップ抵抗使用）
#define PIN_SW  32          // IO32

// LED用出力ピン
#define LED1  13            // 使用するLED
#define LED2  12            // 未使用
#define LED3  5             // 未使用
#define LED4  14            // 未使用

// インターバル
#define INTRUPT_ITVAL250  250   // 250ミリ秒
#define INTRUPT_ITVAL500  500   // 500ミリ秒
// インターバル
//#define INTRUPT_ITVAL250  25   // 25ミリ秒
//#define INTRUPT_ITVAL500  26   // 26ミリ秒

// Tickerインスタンス
Ticker tickerSetHigh;       // 点灯用インスタンス
Ticker tickerSetLow;        // 消灯用インスタンス

// コールバック関数（引数あり）
void setPin(int state) {
  digitalWrite(LED1, state);
}

void setup() {
  pinMode(PIN_SW, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  // 割込み処理の設定（間隔：250ミリ秒、コールバック関数：setPin、引数：LOW）
  tickerSetLow.attach_ms(INTRUPT_ITVAL250, setPin , LOW);

  // 割込み処理の設定（間隔：500ミリ秒、コールバック関数：setPin、引数：HIGH）
  tickerSetHigh.attach_ms(INTRUPT_ITVAL500, setPin, HIGH);
}

void loop() {
}
