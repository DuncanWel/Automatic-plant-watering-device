const int sensorPwrPin = 7;

const int AirValue = 504;
const int WaterValue = 270;
int intervals = (AirValue - WaterValue) / 3;
int soilMoistureValue = 0;

unsigned int readInterval = 60000;

unsigned int lastReadTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(sensorPwrPin, OUTPUT);
  digitalWrite(sensorPwrPin, LOW);
}

void loop() {
  int elapsedTime = millis() - lastReadTime;
  if (elapsdTime >= readInterval) {
    lastReadTime = millis();
    soilMoistureValue = readSoil();

    if (soilMoistureValue < WaterValue) {
      Serial.print("Soaked: ");
      Serial.println(soilMoistureValue);
      Serial.print(elapsedTime);
    } else if (soilMoistureValue >= WaterValue && soilMoistureValue < (WaterValue + intervals)) {
      Serial.print("Wet: ");
      Serial.println(soilMoistureValue);
      Serial.print(elapsedTime);
    } else if (soilMoistureValue >= (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals)) {
      Serial.print("Damp: ");
      Serial.println(soilMoistureValue);
      Serial.print(elapsedTime);
    } else if (soilMoistureValue <= AirValue && soilMoistureValue > (AirValue - intervals)) {
      Serial.print("Dry: ");
      Serial.println(soilMoistureValue);
      Serial.print(elapsedTime);
    } else if (soilMoistureValue >= AirValue) {
      Serial.print("Very dry: ");
      Serial.println(soilMoistureValue);
      Serial.print(elapsedTime);
    }
  }
}

int readSoil() {
  digitalWrite(sensorPwrPin, HIGH);

  int total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(A0);
    delay(10);
  }

  digitalWrite(sensorPwrPin, LOW);

  return total / 10;
}