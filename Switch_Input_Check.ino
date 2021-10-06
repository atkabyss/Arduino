/*
   プログラム名：Switch_Input_Check
   テーマ：スイッチ入力の基本 その1
   備考：簡易チャタリング防止付き
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

  in = digitalRead(PIN_SW); // プルアップ済みの指定ピンからの入力

  if (in != prev) {         // 前の状態値と同じでない場合の処理
    if (in == 0) {
      Serial.println(in);   // スイッチ押下時のピンの状態値の出力
    } else {
      Serial.println(in);   // 上記以外時のピンの状態値の出力
    }
    prev = in;              // 現在のピンの状態値 → 前のピンの状態値
    delay(100);	            // 簡易的なチャタリング軽減処理
  }
}
