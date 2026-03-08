#define BLYNK_TEMPLATE_ID "TMPL3-rLSTAjX"
#define BLYNK_TEMPLATE_NAME "safe vest"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MQUnifiedsensor.h>
#include <BlynkSimpleEsp32.h>

const char *ssid = "YOUR_WIFI_NAME";
const char *pass = "YOUR_WIFI_PASSWORD";

const int sensorPin = 0;
const int led = 14;

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte degree_symbol[8] = {
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

#define MQ_PIN 34
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
MQ2 mq2(MQ_PIN);

char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;
WiFiClient client;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int coLevel = mq2.readCO();
  int smokeLevel = mq2.readSmoke();
  int lpgLevel = mq2.readLPG();

  Blynk.virtualWrite(V4, lpgLevel);
  Blynk.virtualWrite(V3, smokeLevel);
  Blynk.virtualWrite(V2, coLevel);
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  Serial.print("CO Value: ");
  Serial.println(coLevel);

  Serial.print("Smoke level: ");
  Serial.println(smokeLevel);

  Serial.print("Lpg level: ");
  Serial.println(lpgLevel);

  Serial.print("Temperature : ");
  Serial.print(t);

  Serial.print("    Humidity : ");
  Serial.println(h);
}

void display()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int coLevel = mq2.readCO();
  int smokeLevel = mq2.readSmoke();
  int lpgLevel = mq2.readLPG();

  lcd.setCursor(0, 0);
  lcd.print("Temperature ");

  lcd.setCursor(0, 1);
  lcd.print(t);

  lcd.setCursor(6, 1);
  lcd.write(1);

  lcd.setCursor(7, 1);
  lcd.print("C");

  delay(1500);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Humidity ");
  lcd.print(h);
  lcd.print("%");

  delay(1500);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("CO Lvl: ");
  lcd.print(coLevel);

  lcd.setCursor(0, 1);
  lcd.print("Smoke Lvl: ");
  lcd.print(smokeLevel);

  delay(1500);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("LPG Lvl: ");
  lcd.print(lpgLevel);

  delay(1500);
  lcd.clear();
}

void setup()
{
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  dht.begin();
  mq2.begin();

  pinMode(led, OUTPUT);

  lcd.begin();
  lcd.createChar(1, degree_symbol);

  lcd.setCursor(0, 0);
  lcd.print("Safe vest");

  lcd.setCursor(0, 1);
  lcd.print("Monitoring");

  delay(1000);
  lcd.clear();

  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void loop()
{
  Blynk.run();
  timer.run();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int coLevel = mq2.readCO();
  int smokeLevel = mq2.readSmoke();
  int lpgLevel = mq2.readLPG();

  display();

  while (t >= 40 || h >= 90 || coLevel >= 3000 || smokeLevel >= 1000 || lpgLevel >= 500)
  {
    digitalWrite(led, HIGH);
    delay(500);

    digitalWrite(led, LOW);
    delay(500);

    display();
    sendSensor();

    h = dht.readHumidity();
    t = dht.readTemperature();
    coLevel = mq2.readCO();
    smokeLevel = mq2.readSmoke();
    lpgLevel = mq2.readLPG();
  }

  sendSensor();

  if (coLevel > 600 || smokeLevel > 600 || lpgLevel > 600)
  {
    Blynk.logEvent("ALERT", "GAS ALERT");
  }
}
