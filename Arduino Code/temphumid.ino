#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2

#define DHTTYPE DHT22   

DHT dht = DHT(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("% || ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("\xC2\xB0");
  Serial.println("C");
}
