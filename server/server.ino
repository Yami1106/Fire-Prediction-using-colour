#include <WiFi.h>
#include <HTTPClient.h>

String URL="http://192.168.33.172/esp_data/insert_data.php";

const char* ssid = "S23";
const char* password = "viropo2310";

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor
  Serial1.begin(9600, SERIAL_8N1, 16, 17);  // Initialize Serial1 for UART (pins 16 as RX and 17 as TX on ESP32)

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (Serial1.available()) {  // Check if data is available on Serial1 (UART)
    String receivedData = Serial1.readStringUntil('\n');  // Read the incoming data
    Serial.print("Received data: ");
    Serial.println(receivedData);  // Print the received data to Serial Monitor

    // Split the data received (which is comma-separated)
    float temperature, humidity, mq2_value, fire_percent, no_fire_percent;
    sscanf(receivedData.c_str(), "%f,%f,%f,%f,%f", &temperature, &humidity, &mq2_value, &fire_percent, &no_fire_percent);
      String postData = "temperature=" + String(temperature) +"&humidity=" + String(humidity) +"&mq2_value=" + String(mq2_value) +"&fire_percent=" + String(fire_percent) +"&no_fire_percent=" + String(no_fire_percent);
      HTTPClient http;

    http.begin(URL);
      // Send HTTP POST request
    int httpCode = http.POST(postData);

    String payload= http.getString();

    http.addHeader("Content-type","application/x-www-form-urlencoded");

    Serial.println("URL: ");
    Serial.print(URL);
    Serial.println("Data: ");
    Serial.print(postData);
    Serial.println("httpcode: ");
    Serial.print(httpCode);
    Serial.println("payload: ");
    Serial.print(payload);
  }
    delay(1000);  // Wait 1 second before checking for the next data
}
