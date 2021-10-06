/*
   プログラム名：Led_Normal_Sw
   テーマ：スイッチ入力の基本　その5
   説明：スイッチの状態を読み、押すごとにLEDが点灯・消灯する
*/

#define PIN_SW  32 // スイッチのピン番号:IO32
#define LED1 13    // LED1のピン番号:IO13（点灯するLED）
#define LED2 12    // LED2のピン番号:IO12
#define LED3 5     // LED3のピン番号:IO5
#define LED4 14    // LED4のピン番号:IO14

int in;            // 現在のswの状態
int last_led;      // LEDの状態
int prev = 0;      // スイッチの直前の状態

void setup() {
  pinMode(PIN_SW, INPUT_PULLUP);    // スイッチピンの内部プルアップ抵抗の有効化
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void loop() {

  in = digitalRead(PIN_SW);  // スイッチの状態の取得

  if (in != prev) {          // スイッチの状態が変わった場合
    if (in == 0) {           // スイッチが押された場合
      last_led = !last_led;  // LEDの状態の反転
      digitalWrite(LED1, last_led);	// LEDの状態の設定
    }
    prev = in;               // スイッチの前の状態を更新
    delay(100);              // チャタリング軽減
  }
}
