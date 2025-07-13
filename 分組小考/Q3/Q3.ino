void setup() {
  // 設定數位輸出腳位，用於跑馬燈
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  // 設定數位輸出腳位，用於PWM控制小夜燈
  pinMode(5, OUTPUT);

  // 設定數位輸入腳位，用於按鈕（啟用內部上拉電阻）
  pinMode(2, INPUT);

  // 設定類比輸入腳位，用於光敏電阻
  pinMode(A2, INPUT);

  // 初始化序列埠監視器
  Serial.begin(9600);
}

void loop() {
  // 讀取按鈕狀態（按下時為 LOW，未按下時為 HIGH）
  boolean buttonState = digitalRead(2);
  Serial.println(buttonState);
  // 如果按鈕按下，啟動跑馬燈
  if (buttonState == 1) { // 修正條件為按下（LOW）
    digitalWrite(12, HIGH);
    delay(500);
    digitalWrite(11, HIGH);
    delay(500);
    digitalWrite(10, HIGH);
    delay(500);

    // 關閉所有跑馬燈
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
  } else {
    // 確保 LED 在未按下按鈕時保持關閉
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
  }

  // 讀取光敏電阻的類比值
  int lightValue = analogRead(A2);

  // 印出讀取的類比值到序列埠監視器
  Serial.println(lightValue);

  // 將光敏電阻的值映射為 PWM 值
  byte pwmValue = map(lightValue, 0, 1023, 0, 255);

  // 將 PWM 信號輸出到 LED
  analogWrite(5, pwmValue);

  // 延遲 500 毫秒
  delay(500);
}
