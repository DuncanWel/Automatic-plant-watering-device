const int sensorPwrPin = 7;
const int soilSensorPin = A0;
const int relayPin = 8;
const int ledPin = 10;
const int powerPin = 11;

bool lastButtonState = HIGH;
bool buttonState = HIGH;

const int airValue = 504;
const int waterValue = 270;
int soilMoistureValue = 0;

float moisture;

String soilCondition = "";

enum State {
  STANDBY,
  IDLE,
  MEASURE,
  CLASSIFY,
  WATER
};

State currentState = IDLE;

State lastState = IDLE;

unsigned long readInterval = 60000;

unsigned long lastReadTime = 0;

unsigned long waterStartTime = 0;

unsigned long setWaterTime = 5000;

void setup() {
  Serial.begin(9600);

  pinMode(sensorPwrPin, OUTPUT);
  digitalWrite(sensorPwrPin, LOW);
  pinMode(soilSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(powerPin, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(powerPin);

  if (lastButtonState == HIGH && buttonState == LOW) {
    Serial.print("Button: ");
    Serial.println(buttonState);
    if (currentState == STANDBY) {
      currentState = IDLE;
    }
    else {
      currentState = STANDBY;
    }
  }

  lastButtonState = buttonState;

  switch (currentState) {
    case STANDBY:
    standby();
    break;

    case IDLE:
    idle();
    break;

    case MEASURE:
    measureSoilMoisture();
    break;

    case CLASSIFY:
    classifySoil();
    break;

    case WATER:
    water();
    break;
  }
  
  monitor();

} 

void standby() {
  digitalWrite(relayPin, LOW);
  digitalWrite(sensorPwrPin, LOW);
  digitalWrite(ledPin, LOW);

  if (waterStartTime) {
    waterStartTime = 0;
  }
}

void idle() {
  unsigned long elapsedTime = millis() - lastReadTime;
  if (elapsedTime  >= readInterval) {
    lastReadTime = millis();
    currentState = MEASURE;
  }
}

void measureSoilMoisture() {
  soilMoistureValue = readSoil();
  float soilMoisturePercentage = (float)(soilMoistureValue - airValue) * 100.0/(waterValue - airValue);
  float clampedSMP = constrain(soilMoisturePercentage, 0, 100);
  moisture = clampedSMP;

  currentState = CLASSIFY;
}

void classifySoil() {
  if (moisture < 50) {
    soilCondition = "Dry";
    currentState = WATER;
  }
  else {
    soilCondition = "wet";
    currentState = IDLE;
  }
}

void water() {
  if (waterStartTime == 0) {
    waterStartTime = millis();
  }
  digitalWrite(relayPin, HIGH);
  unsigned long waterTimer = millis() - waterStartTime;
  if (waterTimer >= setWaterTime) {
    waterStartTime = 0;
    digitalWrite(relayPin, LOW);
    currentState = IDLE;
  }
}

int readSoil() {
  digitalWrite(sensorPwrPin, HIGH);
  delay(100);

  int total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(soilSensorPin);
    delay(10);
  }

  digitalWrite(sensorPwrPin, LOW);

  return total / 10;
}

void monitor() {
  if (currentState != lastState) {
    Serial.print("Current state: ");
    Serial.println(currentState);

    lastState = currentState;
  }

  if (currentState == MEASURE) {
    Serial.print("Raw soil value: ");
    Serial.println(soilMoistureValue);

    Serial.print("Moisture percentage: ");
    Serial.print(moisture);
    Serial.println("%");
    }
}