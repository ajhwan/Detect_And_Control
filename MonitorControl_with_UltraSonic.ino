#include <Keyboard.h>

const int trigPin = 3;
const int echoPin = 4;
const int button1 = 7;
const int button2 = 8;
const int LED1 = 6;
const int LED2 = 9;

float duration, distance;
int input_data;
int cnt = 0;
int state = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  if (digitalRead(button2) == HIGH) {
    cnt = 0;
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }

  if (digitalRead(button1) == HIGH) {
    if (state == 0) {
      delay(10);
      state = 1;
    }
  }

  if (digitalRead(button1) == LOW) {
    if (state == 1) {
      cnt++;
      delay(10);
      state = 0;
    }
  }

  if (cnt % 2 == 1) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    Serial.print("cnt: ");
    Serial.println(cnt);
  }

  if (cnt != 0 && cnt % 2 == 0) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    Serial.print("cnt: ");
    Serial.println(cnt);
  }

  while (Serial.available()) {
    char c = Serial.read();
    if (c == '1') {
      if (distance > 0 && distance < 10) {
        if (cnt == 0) {
          Serial.print("window cnt: ");
          Serial.println(cnt);
          Serial.println(input_data);
          delay(100);
          Keyboard.press(0x83);  // left window
          delay(50);
          Keyboard.press('d');
          delay(500);
          Keyboard.releaseAll();
          delay(500);
        }

        if (cnt % 2 == 1) {
          Serial.print("altTap cnt: ");
          Serial.println(cnt);
          Keyboard.press(0x82);  // left alt
          delay(50);
          Keyboard.press(0xB3);  // Tap
          delay(50);
          Keyboard.releaseAll();
          delay(500);
        }

        if (cnt != 0 && cnt % 2 == 0) {
          Serial.print("Tapwindow cnt: ");
          Serial.println(cnt);
          Keyboard.press(0x83);  // left window
          delay(50);
          Keyboard.press('x');
          delay(50);
          Keyboard.releaseAll();
          delay(10);
          Keyboard.press('u');
          delay(10);
          Keyboard.release('u');
          delay(10);
          Keyboard.press('u');
          delay(500);
          Keyboard.releaseAll();
          delay(500);
        }
      }
    } 
    else {
      return;
    }
  }
}
