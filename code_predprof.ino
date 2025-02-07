const int buttonPin = 4;
const int ledPin    = 2;
const int fivePin   = 5;

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

int pressCount = 0;
bool enabled = true;

const unsigned long halfPeriod = 10;
bool acState = LOW;
unsigned long lastToggleTime = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(fivePin, OUTPUT);

  digitalWrite(ledPin, acState);
  digitalWrite(fivePin, acState);
}

void loop() {
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        pressCount++;
        enabled = (pressCount % 2 == 0);
        acState = LOW;
        lastToggleTime = millis();
      }
    }
  }
  
  lastButtonState = reading;
  
  if (enabled) {
    unsigned long currentTime = millis();
    if (currentTime - lastToggleTime >= halfPeriod) {
      acState = (acState == LOW) ? HIGH : LOW;
      lastToggleTime = currentTime;
    }
    digitalWrite(ledPin, acState);
    digitalWrite(fivePin, acState);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(fivePin, LOW);
  }
}
