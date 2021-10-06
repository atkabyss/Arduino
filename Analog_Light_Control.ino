/*
   プログラム名：Analog_Light_Control
   作成者：k019c1068 石井恭輔
   テーマ：ボリュームによるアナログ入力1
   説明：ボリュームの値によってLEDの明るさを変える
   備考：ADCの入力はMAX3.3(V)だが、defaultで11db(1/3.55)の
         アッテネータ（Attenuator、減衰器）が入っており、
         過電圧でも適切な調整が行われるために壊れない
         ・アナログ入力 12bit(4096段階) 戻り値 0～4095
         ・アナログ出力　8bit(256段階)
*/

// LEDC
#define LEDC_CHANNEL_0     0		// 使用チャネル
#define LEDC_TIMER_13_BIT  13		// 分解能
#define LEDC_BASE_FREQ     5000		// 基本周波数

// スイッチ用ピン
#define PIN_SW1   4					// 未使用
#define PIN_SW2  32					// 未使用

// LED用出力ピン
#define LED1  13					// 使用するLED
#define LED2  12					// 未使用
#define LED3   5					// 未使用
#define LED4  14					// 未使用

// アナログ入力ピン
#define ANALOG_PIN  A6				// アナログ入力ピン(GPIO34)

// シリアル通信
#define SERIAL_SPEED  115200		// 通信速度

// PWM出力（duty比256段階での明るさの設定）
void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 255) {
  // タイマーの分解能の算出（13ビットのパターン:2^13 ＝ 8192 → 13ビットで表せる最大値:8191（分解能）
  uint32_t dutybase = ( 1 << LEDC_TIMER_13_BIT ) - 1;   // 1を13回左シフト（2^13と同じ）後に１を引く
  // dutyの算出（duty：0～8191、※ただし、duty比256段階で設定できるようにする）
  uint32_t duty = (dutybase / valueMax) * min(value, valueMax);
  // 指定したdutyでのPWM出力
  ledcWrite(channel, duty);
}

void setup() {
  // チャネルや周波数とタイマーの設定とLEDへの関連付け
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(LED1, LEDC_CHANNEL_0);	// チャネル0へのLEDの接続
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
  uint32_t ADC_Value = analogRead(ANALOG_PIN);  // 指定されたアナログピンから値を読み取る
  Serial.println(ADC_Value);			// デバッグ用
  // アナログピンから読み取った分解能4096の値を分解能256の値へ変換する
  uint32_t ADC_NewValue = map(ADC_Value, 0, 4095, 0, 255);
  ledcAnalogWrite(LEDC_CHANNEL_0, ADC_NewValue);
}
