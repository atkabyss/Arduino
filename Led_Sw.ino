/*
   プログラム名：Led_Sw
   テーマ：スイッチ入力の基本　その4
   説明：スイッチを押すとLEDが3秒間点灯する
*/

#define PIN_SW  32            // スイッチのピン番号:IO32
#define LED1 13               // LED1のピン番号:IO13（点灯するLED）
#define LED2 12               // LED2のピン番号:IO12
#define LED3 5                // LED3のピン番号:IO5
#define LED4 14               // LED4のピン番号:IO14
#define DELAYTIME 3000        // 3秒

int in;                       // 現在のスイッチの状態
int prev = 0;                 // 直前のスイッチの状態

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
  in = get_sw(prev);          // スイッチの状態の読み取り

  if (in == 0) {              // スイッチが押されている場合
    digitalWrite(LED1, HIGH);  // LED点灯
    delay(DELAYTIME);         // 停止
    digitalWrite(LED1, LOW);   // LED消灯
  }
}

/* スイッチの状態を読み取る関数 */
int get_sw(int sw_out) {
  int in1, in2;

  in1 = digitalRead(PIN_SW);
  delay(100);
  in2 = digitalRead(PIN_SW);

  if (in1 == in2 ) {
    sw_out = in2;
  }
  return (sw_out);
}
