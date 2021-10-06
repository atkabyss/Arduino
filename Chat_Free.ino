/*
   プログラム名：Chat_Free
   テーマ：スイッチ入力の基本 その2
   備考：少々本格的なチャタリング防止付き
*/

#define PIN_SW  32 // スイッチのピン番号:IO32
#define LED1 13    // LED1のピン番号:IO13
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
  pinMode(PIN_SW, INPUT_PULLUP); // 指定ピンの内部プルアップ抵抗の有効化
  Serial.begin(115200);
  Serial.print("HIGH=");
  Serial.println(HIGH); //ピンの状態値HIGHの出力
  Serial.print("LOW=");
  Serial.println(LOW);  //ピンの状態値LOWの出力
}

void loop() {
  int in;

  in = get_sw(prev);	// ピンの状態を取得する関数の呼び出し

  if (in != prev) {
    if (in == 0) {
      Serial.println(in);
    } else {
      Serial.println(in);
    }
    prev = in;
  }
}

// ピンの状態を取得する関数
int get_sw(int sw_out) {
  int in1, in2, in3;			// ピンの状態

  // 0.1秒の間隔をあけて指定ピンから3回状態を取得
  in1 = digitalRead(PIN_SW);
  delay(100);
  in2 = digitalRead(PIN_SW);
  delay(100);
  in3 = digitalRead(PIN_SW);

  if ((in1 == in2) && (in1 == in3)) {
    sw_out = in3;
  }
  return (sw_out);
}
