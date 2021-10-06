/*
プログラム名：Touch_Interrupt_To_Led
テーマ：タッチ入力と割込み処理
作成者：k019c1068 石井　恭輔 // 自分の学籍番号と氏名に変えること
説明：T0(GPIO4)に触れる度にLEDが点滅する
*/
// スイッチ用入力ピン（内部プルアップ抵抗使用）
#define PIN_SW 32 // IO32
// LED用出力ピン
#define LED1 13 // 使用するLED
#define LED2 12 // 未使用
#define LED3 5 // 未使用
#define LED4 14 // 未使用
// タッチセンサー
#define TOUCH_SENSOR T0 // 使用するセンサーT0（ティー・ゼロ、GPIO04）
#define THRESHOLD 40 // 閾値（しきいち）
// インターバル
#define INTERVAL 100 // 点滅間隔
// シリアル通信
#define SERIAL_SPEED 115200 // 通信速度
bool touchdetected = false; // タッチの検知:OFF
int LedStatus = 0; // LEDの状態（0:OFF、1:ON）

// 割込み時に実行する処理（関数）
void touchedPin() {
touchdetected = true; // タッチの検知:ON
}
void setup() {
Serial.begin(SERIAL_SPEED);
delay(1000); // give me time to bring up serial monitor
pinMode(PIN_SW, INPUT_PULLUP);
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);
digitalWrite(LED1, LOW);
digitalWrite(LED2, LOW);
digitalWrite(LED3, LOW);
digitalWrite(LED4, LOW);
touchAttachInterrupt(TOUCH_SENSOR, touchedPin, THRESHOLD); // 割込み処理の設定
}
void loop() {
if (touchdetected) {
touchdetected = false;
digitalWrite(LED1, LedStatus);
LedStatus = !LedStatus;
Serial.println("Touch detected");
}
delay(INTERVAL);
}
