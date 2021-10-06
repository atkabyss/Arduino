/*
   プログラム名：Photo_1
   テーマ：フォトトランジスタ
   説明：フォトトランジスタの値をシリアルモニタへ出力する
   備考：アナログ入力は12bit
         フォトセンサはコレクタ側（長い方）に1KΩを接続して+3.3Vへ
         エミッタ側（短い方）に4.7KΩを接続しグランドへ接続する
         AD変換ピン(GPIO36,ADC0,SVPの表記)へはエミッタ側から取り出し接続する
*/

// スイッチ用ピン
#define PIN_SW1   4					// 未使用
#define PIN_SW2  32					// 未使用

// LED用出力ピン
#define LED1  13					// 未使用
#define LED2  12					// 未使用
#define LED3   5					// 未使用
#define LED4  14					// 未使用

// アナログ入力ピン
#define ANALOG_PIN  A0				// アナログ入力ピン(GPIO36 表記はSVP)

// シリアル通信
#define SERIAL_SPEED  115200		// 通信速度

void setup()
{
  pinMode(PIN_SW1, INPUT_PULLUP);
  pinMode(PIN_SW2, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  Serial.begin(SERIAL_SPEED);
}

void loop() {
  unsigned int ADC_Value;

  ADC_Value = analogRead(ANALOG_PIN);	// アナログピンの読み取り
  Serial.println(ADC_Value);
}
