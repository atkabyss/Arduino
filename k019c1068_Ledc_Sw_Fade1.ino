/*
プログラム名：Ledc_Sw_Fade1
テーマ：LED FADEとスイッチ その1
作成者：k019c1068 石井　恭輔 // 自分の学籍番号と氏名に変えること
説明：スイッチを押す度にLEDが暗点灯→全灯→消灯を繰り返す
*/
// LEDCで使用する値
#define LEDC_CHANNEL_0 0 // チャネル
#define LEDC_TIMER_13_BIT 13 // 分解能
#define LEDC_BASE_FREQ 5000 // 基本周波数
// LED用出力ピン
#define PIN_SW 32 // スイッチのピン番号:IO32
#define LED1 13 // 使用するLED
#define LED2 12 // 未使用
#define LED3 5 // 未使用
#define LED4 14 // 未使用
// LEDの明るさ（3段階の設定）
#define LED_OFF 0 // 消灯
#define LED_MID 20 // 暗点灯
#define LED_MAX 255 // 全灯（光量100%）
#define READ_INTERVAL 100 // チャタリング防止対応用読み取り間隔
int in; // 現在のスイッチの状態
int prev = 0; // 直前のスイッチの状態
int counter = 0; // LEDの明るさを変更するカウンタ

// PWM出力（duty比256段階での明るさの設定）
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
uint32_t dutybase = ( 1 << LEDC_TIMER_13_BIT ) - 1;
uint32_t duty = (dutybase / valueMax) * min(value, valueMax);
ledcWrite(channel, duty);
}
// スイッチの状態を取得する関数（チャタリング防止対応）
int get_sw(int sw_out) {
int in1, in2;
in1 = digitalRead(PIN_SW);
delay(READ_INTERVAL);
in2 = digitalRead(PIN_SW);
if (in1 == in2 ) {
sw_out = in2;
}
return (sw_out);
}
void setup() {
// チャネルや周波数とタイマーの設定とLEDへの関連付け
ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
ledcAttachPin(LED1, LEDC_CHANNEL_0); // チャネル0へのLEDの接続
pinMode(PIN_SW, INPUT_PULLUP);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);
digitalWrite(LED2, LOW);
digitalWrite(LED3, LOW);
digitalWrite(LED4, LOW);
Serial.begin(115200); // デバッグ用のコード
}
void loop() {
in = get_sw(prev); // スイッチ状態の読み取り
if ( in != prev) { // スイッチの状態が変わった場合
prev = in;
if (in == 0) { // スイッチが押されている場合
counter++; // カウントアップ
}
}
Serial.println(counter); // デバッグ用

// LEDの明るさの変更
switch ( counter ) {
case 0: // カウンタ=0のとき、LED消灯
ledcAnalogWrite(LEDC_CHANNEL_0, LED_OFF);
break;
case 1: // カウンタ=1のとき、LED暗点灯
ledcAnalogWrite(LEDC_CHANNEL_0, LED_MID);
break;
case 2: // カウンタ=2のとき、LED全灯
ledcAnalogWrite(LEDC_CHANNEL_0, LED_MAX);
break;
default: //カウンタが上記以外のとき、カウンタリセット
counter = 0;
}
}
