/*
   プログラム名：Ticker_Blink
   テーマ：Ticker libraryを利用した周期的な割込み
   説明：0.5秒ごとに割込みを掛け、LEDを点灯／消灯させる
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
#define INTERRUPT_INTERVAL  0.5  // 0.5秒

// Tickerインスタンス
Ticker ticker;

// LEDピンの状態
int pin_status = LOW;

// コールバック関数
void func_blink() {
  pin_status = !pin_status;  // LEDを反転
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

  // 割込み処理の設定（間隔：0.5秒、コールバック関数：func_blink）
  ticker.attach(INTERRUPT_INTERVAL, func_blink);
}

void loop() {
  digitalWrite(LED1, pin_status);
}
