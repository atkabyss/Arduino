#include "pitches.h"
#include "melody.h"

#define bluesw 4
#define brownsw 32
#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_13_BIT  13
#define LEDC_BASE_FREQ  5000
#define RedLed 14
#define GreenLed 5
#define bzz 16


int arrayS = sizeof melody / sizeof melody[0];

int d[] = {261, 293, 329, 349, 391, 440, 493, 523};
void setup() {
  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(bluesw, INPUT_PULLUP);
  pinMode(brownsw, INPUT_PULLUP);
  pinMode(bzz, OUTPUT);
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(bzz, LEDC_CHANNEL_0);

  digitalWrite(GreenLed, HIGH);

  ledcWriteTone(LEDC_CHANNEL_0, 100);
  ledcWriteTone(LEDC_CHANNEL_0, 0);
}

void loop() {
  while(digitalRead(bluesw) == HIGH){
    digitalWrite(GreenLed, HIGH);
  }
  ra();
}

void ra() {
  delay(980);
  digitalWrite(GreenLed, LOW);
  for (int i = 0; i <= 7; i++) {
    ledcWriteTone (LEDC_CHANNEL_0, d[i]);
    digitalWrite(RedLed, HIGH);
    delay(20);
    ledcWriteTone (LEDC_CHANNEL_0, 0);
    digitalWrite(RedLed, LOW);
    for(int i = 0; i <= 980; i++) {
      delay(1);
      if(digitalRead(brownsw) == LOW)break;
    }
    if(digitalRead(brownsw) == LOW)break;
  }
  if(digitalRead(brownsw) == LOW){goto bailout;}
  digitalWrite(GreenLed, HIGH);
  for (int n = 0; n < arrayS; n++) {
    ledcWriteTone(LEDC_CHANNEL_0, melody[n]);
    delay(tempo[n]);
    ledcWriteTone (LEDC_CHANNEL_0, 0);
  }
  bailout:;
}
