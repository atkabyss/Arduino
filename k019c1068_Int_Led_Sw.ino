/*
プログラム名：Int_Led_Sw
テーマ：スイッチによる割込み
作成者：k019c1068石井　恭輔
説明：各タクトスイッチを押したときに割込み、
対応するLEDの状態を反転（消灯⇔点灯）させる
GPIO4のスイッチ → GPIO14のLED
GPIO32のスイッチ → GPIO5のLED
*/
// LED用出力ピン
#define LED1 14 // GPIO4スイッチで制御
#define LED2 5 // GPIO32スイッチで制御
#define LED3 12 // 未使用
#define LED4 13 // 点滅用LED
// 割込み関連の関数マクロ
#define DI_1() portENTER_CRITICAL_ISR(&mux_1); //割込み禁止
#define EI_1() portEXIT_CRITICAL_ISR(&mux_1); //割込み許可
#define DI_2() portENTER_CRITICAL_ISR(&mux_2); //割込み禁止
#define EI_2() portEXIT_CRITICAL_ISR(&mux_2); //割込み許可
// シリアル通信
#define SERIAL_SPEED 115200 // 通信速度
// 割込みスイッチ
const byte SW1 = 4; // GPIO14用割込みスイッチ
const byte SW2 = 32; // GPIO5用割込みスイッチ
// LEDの状態（初期状態：消灯）
volatile int status1 = LOW; // LED1の状態
volatile int status2 = LOW; // LED2の状態
// 同期処理
portMUX_TYPE mux_1 = portMUX_INITIALIZER_UNLOCKED; // メインコードとISR1間の同期を処理する
portMUX_TYPE mux_2 = portMUX_INITIALIZER_UNLOCKED; // メインコードとISR2間の同期を処理する
// ISRとして実行する関数1
void IRAM_ATTR handleInterrupt_1() {
DI_1();
status1 = !status1; // LED1の状態反転
EI_1();
}
// ISRとして実行する関数2
void IRAM_ATTR handleInterrupt_2() {
DI_2();
status2 = !status2; // LED2の状態反転
EI_2();
}
void setup() {
Serial.begin(SERIAL_SPEED);
pinMode(SW1, INPUT_PULLUP); // スイッチピン1の内部プルアップ抵抗の有効化
pinMode(SW2, INPUT_PULLUP); // スイッチピン2の内部プルアップ抵抗の有効化
// ピンへの割込み設定（割込みハンドラーの登録とモード（H→Lに変わるとき）の設定）
attachInterrupt (digitalPinToInterrupt(SW1), handleInterrupt_1, FALLING);
attachInterrupt (digitalPinToInterrupt(SW2), handleInterrupt_2, FALLING);
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
Serial.print(status1); Serial.println(status2);
digitalWrite(LED1, status1);
digitalWrite(LED2, status2);
}
