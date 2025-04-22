#define relay1 13

String voice = "";

void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, HIGH);  // Relay OFF by default
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') { // End of command
      processCommand(voice);
      voice = ""; // Reset
    } else if (c != '\r') {
      voice += c;
    }
  }
}

void processCommand(String cmd) {
  cmd.trim();  // Clean command

  if (cmd == "turn on light" || cmd == "LIGHT_ON") {
    digitalWrite(relay1, LOW);
  } else if (cmd == "turn off light" || cmd == "LIGHT_OFF") {
    digitalWrite(relay1, HIGH);
  } else if (cmd == "blink" || cmd == "BLINK") {
    for (int i = 0; i < 3; i++) {
      digitalWrite(relay1, LOW);
      delay(500);
      digitalWrite(relay1, HIGH);
      delay(500);
    }
  }
}
