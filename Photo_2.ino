/*
   プログラム名：Photo_2
   テーマ：フォトトランジスタ
   説明：周囲の明るさによって点灯するLEDを変える
   備考：フォトトランジスタの値　＞　100　→　緑のLEDを点灯する
   　　　フォトトランジスタの値　≦　100　→　赤のLEDを点灯する
         通常、照度を表す単位は、ルクスであるが、このプログラムでは、
         単位変換を行わずにフォトトランジスタの値をそのまま使用する
*/

// スイッチ用ピン
#define PIN_SW1   4             // 未使用
#define PIN_SW2  32             // 未使用

// LED用出力ピン
#define LED1  13                // 未使用
#define LED2  12                // 未使用
#define LED3   5                // 使用（緑）
#define LED4  14                // 使用（赤）

// アナログ入力ピン
#define ANALOG_PIN  A0          // アナログ入力ピン(GPIO36 表記はSVP)

// シリアル通信
#define SERIAL_SPEED  115200    // 通信速度

int led_hi = LED3;              // GPIO5  GOOD
int led_lo = LED4;              // GPIO14 LOW

int good_brightness = 100;      // 既定の明るさ

void setup() {
  pinMode(PIN_SW1, INPUT_PULLUP);
  pinMode(PIN_SW2, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(led_hi, OUTPUT);
  pinMode(led_lo, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(led_hi, LOW);
  digitalWrite(led_lo, LOW);
  Serial.begin(SERIAL_SPEED);
}

void loop() {
  unsigned int ADC_Value;
  
  ADC_Value = analogRead(ANALOG_PIN);
  
  Serial.println(ADC_Value);
  if (ADC_Value  > good_brightness) {
    digitalWrite(led_hi, HIGH);   // 明るいとき
    digitalWrite(led_lo, LOW);
  } else {
    digitalWrite(led_hi, LOW);
    digitalWrite(led_lo, HIGH);   // 暗いとき
  }
}
