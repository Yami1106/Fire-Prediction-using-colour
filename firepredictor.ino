#include <LiquidCrystal_I2C.h>
#include <dht11.h>
#include <TensorFlowLite.h>
#include <Arduino_APDS9960.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include "model.h"
#include<string>
#define MQ2pin 0
#define DHT11PIN 4

LiquidCrystal_I2C lcd(0x27, 16, 2);
dht11 DHT11;

tflite::AllOpsResolver tflResolver;

const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

constexpr int tensorArenaSize = 24 * 1024;
byte tensorArena[tensorArenaSize];

const char* classes[] = {
  "fire",
  "no fire"
};

int buzz = 2;
int i=0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Serial.println("LCD initialized");
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }
  tflModel = tflite::GetModel(model); 
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (true) {}
  }

  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflResolver, tensorArena, tensorArenaSize);

  tflInterpreter->AllocateTensors();

  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);

  delay(20000);
}

void loop() {
  int r, g, b, c, prox;
  float sum;
  float mq2Value;
  char alert[]="Fire Alert!!!";
  char action[]="Take Action ASAP";
  char safe[]="No Fire Safe :)";

  while (!APDS.colorAvailable() || !APDS.proximityAvailable()) {}

  APDS.readColor(r, g, b, c);
  sum = r + g + b;
  prox = APDS.readProximity();

  mq2Value = analogRead(MQ2pin);

  Serial.print("MQ2 Sensor Value: ");
  Serial.println(mq2Value);

  char t[] = "T(C)=";
  char h[] = "H(%)=";
  int chk = DHT11.read(DHT11PIN);
  int temp,hum;
  temp=DHT11.temperature;
  hum=DHT11.humidity;

  String hstr,tstr;

  lcd.clear();
  hstr=String(hum);
  tstr=String(temp);

  // Display temperature label on the first row
  for (i = 0; i < strlen(t); i++) {
    lcd.setCursor(i, 0);
    lcd.print(t[i]);
  }

  for(i=0;i<2;i++){
  lcd.setCursor(strlen(t)+i, 0);
  lcd.print(tstr[i]);
  }

  // Display humidity label on the second row
  for (i = 0; i < strlen(h); i++) {
    lcd.setCursor(8+i, 0);
    lcd.print(h[i]);
  }

  for(i=0;i<2;i++){
  lcd.setCursor(14+i,0);
  lcd.print(hstr[i]);
  }
  Serial.print("Temperature (C): ");
  Serial.println(DHT11.temperature);

  Serial.print("Humidity (%): ");
  Serial.println(DHT11.humidity);

  if (prox >= 0 && c > 10 && sum > 0) {
    float redRatio = r / sum;
    float greenRatio = g / sum;
    float blueRatio = b / sum;

    tflInputTensor->data.f[0] = redRatio;
    tflInputTensor->data.f[1] = greenRatio;
    tflInputTensor->data.f[2] = blueRatio;

    TfLiteStatus invokeStatus = tflInterpreter->Invoke();
    if (invokeStatus != kTfLiteOk) {
      Serial.println("Invoke failed!");
      while (true) {}
    }

    for (int i = 0; i < 2; i++) {
      Serial.print(classes[i]);
      Serial.print(" ");
      Serial.print(int(tflOutputTensor->data.f[i] * 100));
      Serial.print("%\n");
    }
    Serial.println();

    if (int(tflOutputTensor->data.f[0] * 100) > 90 || mq2Value >= 400) {
      tone(buzz, 15000);
      lcd.clear();
      for(i=0;i<strlen(alert);i++){
        lcd.setCursor(i,0);
        lcd.print(alert[i]);
      }
      for(i=0;i<strlen(action);i++){
        lcd.setCursor(i,1);
        lcd.print(action[i]);
      }
    } else if (int(tflOutputTensor->data.f[1] * 100) > 60) {
      noTone(buzz);
      for(i=0;i<strlen(safe);i++){
      lcd.setCursor(i,1);
      lcd.print(safe[i]);
      }
    }
    delay(1000);
  }
}


