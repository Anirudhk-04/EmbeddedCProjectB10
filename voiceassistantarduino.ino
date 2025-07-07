#define relay_y 4 // Yellow
#define relay_g 5 // Green
#define relay_b 6 // Blue

String voice = "";

void setup() {
  Serial.begin(9600);
  pinMode(relay_y, OUTPUT);
  pinMode(relay_g, OUTPUT);
  pinMode(relay_b, OUTPUT);

  digitalWrite(relay_y, HIGH);  // Default OFF
  digitalWrite(relay_g, HIGH);
  digitalWrite(relay_b, HIGH);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      processCommand(voice);
      voice = "";
    } else if (c != '\r') {
      voice += c;
    }
  }
}

void processCommand(String cmd) {
  cmd.trim();

  // Yellow Light Commands
  if (cmd == "turn on yellow light" || cmd == "Turn on the yellow light." || cmd == "turn on the yellow light") {
    digitalWrite(relay_y, LOW);
  } else if (cmd == "turn off yellow light" || cmd == "Turn off the yellow light." || cmd == "turn off the yellow light") {
    digitalWrite(relay_y, HIGH);
  } else if (cmd == "blink yellow light") {
    for (int i = 0; i < 3; i++) {
      digitalWrite(relay_y, LOW);
      delay(500);
      digitalWrite(relay_y, HIGH);
      delay(500);
    }
  }

  // Blue Light Commands
  else if (cmd == "turn on blue light" || cmd == "Turn on the blue light." || cmd == "turn on the blue light") {
    digitalWrite(relay_b, LOW);
  } else if (cmd == "turn off blue light" || cmd == "Turn off the blue light." || cmd == "turn off the blue light") {
    digitalWrite(relay_b, HIGH);
  } else if (cmd == "blink blue light") {
    for (int i = 0; i < 3; i++) {
      digitalWrite(relay_b, LOW);
      delay(500);
      digitalWrite(relay_b, HIGH);
      delay(500);
    }
  }

  // Green Light Commands
  else if (cmd == "turn on green light" || cmd == "Turn on the green light." || cmd == "turn on the green light") {
    digitalWrite(relay_g, LOW);
  } else if (cmd == "turn off green light" || cmd == "Turn off the green light." || cmd == "turn off the green light") {
    digitalWrite(relay_g, HIGH);
  } else if (cmd == "blink green light") {
    for (int i = 0; i < 3; i++) {
      digitalWrite(relay_g, LOW);
      delay(500);
      digitalWrite(relay_g, HIGH);
      delay(500);
    }
  }
}
