/*
   プログラム名：Thermo_1
   テーマ：IC温度センサー
   説明：温度センサーの値をシリアルモニタへ出力する
   備考：アナログ入力は12bit
         0℃のときのセンサーからの出力電圧600mV
         1℃→＋10mV
*/

// スイッチ用ピン
#define PIN_SW1   4					        // 未使用
#define PIN_SW2  32					        // 未使用

// LED用出力ピン
#define LED1  13					          // 未使用
#define LED2  12					          // 未使用
#define LED3   5					          // 未使用
#define LED4  14					          // 未使用

// アナログ入力ピン
#define ANALOG_PIN  A19				      // アナログ入力ピン(GPIO26)

// シリアル通信
#define SERIAL_SPEED  115200		    // 通信速度

// インターバル
#define INTERVAL  500				        // 測定間隔(0.5秒)

// オフセット
#define OFFSET  600					// 0℃のときのセンサー出力電圧

// 温度換算
#define VOL_PER_TEMP  10.0			// +10mv/℃

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
  Serial.begin(SERIAL_SPEED);
}

void loop() {
  unsigned int ADC_Value;
  int thermo;
  float temperature;				// 温度（摂氏）

  ADC_Value = analogRead(ANALOG_PIN);	          // アナログピンの読み取り

  // 温度の算出
  thermo = ADC_Value - OFFSET;
  temperature = (float)(thermo / VOL_PER_TEMP);

  Serial.printf("%d  %d  %3.1f\n", ADC_Value, thermo, temperature);
  delay(INTERVAL);
}
