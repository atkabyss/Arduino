/*
   プログラム名：Thermo_2
   テーマ：IC温度センサー
   説明：快適温度帯を設定し、範囲内の温度の場合は緑のLED、そうでない場合は赤のLEDを点灯させる
   備考：アナログ入力は12bit
         0℃のときのセンサーからの出力電圧600mV
         1℃→＋10mV
         快適温度：22℃			※実行環境に応じて値を変更する
         快適温度帯･･･快適温度の前後1度以内
         ・快適温度帯より低い温度の場合	→ 赤のLED（GPIO12）を点灯させる
         ・快適温度帯の温度の場合		→ 緑のLED（GPIO5）を点灯させる
         ・快適温度帯より高い温度の場合	→ 赤のLED（GPIO14）を点灯させる
*/

// スイッチ用ピン
#define PIN_SW1   4				// 未使用
#define PIN_SW2  32				// 未使用

// LED用出力ピン
#define LED1  13				// 未使用
#define LED2  12				// 使用
#define LED3   5				// 使用
#define LED4  14				// 使用

// アナログ入力ピン
#define ANALOG_PIN  A19			// アナログ入力ピン(GPIO26)

// シリアル通信
#define SERIAL_SPEED  115200	// 通信速度

// インターバル
#define INTERVAL  500			// 測定間隔(0.5秒)

// オフセット
#define OFFSET1  600			// 0℃のときのセンサー出力電圧
#define OFFSET2  1				// 快適温度帯（許容範囲）

// 温度換算
#define VOL_PER_TEMP  10.0		// +10mv/℃

// LEDセッティング
int temp_lo_led;				// 快適温度帯より高のときに点灯するLED
int temp_ok_led;				// 快適温度帯のときに点灯するLED
int temp_hi_led;				// 快適温度帯より低いときに点灯するLED

void setup(){
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
  temp_lo_led = LED2;
  temp_ok_led = LED3;
  temp_hi_led = LED4;
  Serial.begin(SERIAL_SPEED);
}

void loop() {
  unsigned int ADC_Value;
  int thermo;
  float temperature;					// 温度（摂氏）
  int cmft_temperature = 22;			// 快適温度

  ADC_Value = analogRead(ANALOG_PIN);	// アナログピンの読み取り

  // 温度の算出
  thermo = ADC_Value - OFFSET1;
  temperature = (float)(thermo / VOL_PER_TEMP);

  Serial.printf("%d  %d  %3.1f\n",
    ADC_Value, thermo, temperature);	// デバッグ用

  // 温度帯によるLEDの状態の設定
  if ( temperature < (float)(cmft_temperature - OFFSET2 ) ) {
    digitalWrite(temp_lo_led, HIGH);	// 点灯
    digitalWrite(temp_ok_led, LOW);		// 消灯
    digitalWrite(temp_hi_led, LOW);		// 消灯
  } else if ( temperature > (float)(cmft_temperature + OFFSET2 ) ) {
    digitalWrite(temp_lo_led, LOW);		// 消灯
    digitalWrite(temp_ok_led, LOW);		// 消灯
    digitalWrite(temp_hi_led, HIGH);	// 点灯
  } else {
    digitalWrite(temp_lo_led, LOW);		// 消灯
    digitalWrite(temp_ok_led, HIGH);	// 点灯
    digitalWrite(temp_hi_led, LOW);		// 消灯
  }

  delay(INTERVAL);
}
