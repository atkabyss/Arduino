/*
   プログラム名：Switch_Input
   テーマ：スイッチ入力の基本　その3
   説明：スイッチを押している時にLEDが点灯する
*/

#define PIN_SW  32 // スイッチのピン番号:IO32
#define LED1 13    // LED1のピン番号:IO13（点灯させるLED）
#define LED2 12    // LED2のピン番号:IO12
#define LED3 5     // LED3のピン番号:IO5
#define LED4 14    // LED4のピン番号:IO14

int prev = 0;      // スイッチの直前の状態

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  pinMode(PIN_SW, INPUT_PULLUP);	// 指定ピンで内部プルアップ抵抗を有効にする
  Serial.begin(115200);
  Serial.print("HIGH=");
  Serial.println(HIGH); //ピンの状態値HIGHの出力
  Serial.print("LOW=");
  Serial.println(LOW);  //ピンの状態値LOWの出力
}

void loop() {
  int in;

  in = get_sw(prev);				// スイッチからの入力

  if (in == 0) {
    digitalWrite(LED1, 1);		// スイッチON -> LED点燈
  } else {
    digitalWrite(LED1, 0); 		// スイッチOFF -> LED消灯
  }

  /* スイッチの状態が変わった場合に状態をシリアルモニタへ出力し、
     現在の状態を直前の状態として保存する */
  if (in != prev) {
    Serial.println(in);
    prev = in;
  }
}

/* スイッチの状態を取得する関数（簡易的なチャタリング防止機能付き） */
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
