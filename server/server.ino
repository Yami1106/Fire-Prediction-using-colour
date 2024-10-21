#include <WiFi.h>
#include <HTTPClient.h>

// Server URL
String URL = "http://192.168.33.172/esp_data/insert_data.php";  // Update with your actual server IP and path

// WiFi credentials
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
    float temperature = 0.0, humidity = 0.0, mq2_value = 0.0, fire_percent = 0.0, no_fire_percent = 0.0;
    int parsedItems = sscanf(receivedData.c_str(), "%f,%f,%f,%f,%f", &temperature, &humidity, &mq2_value, &fire_percent, &no_fire_percent);

    // Check if all values were successfully parsed
    if (parsedItems == 5) {
      Serial.println("Data parsed successfully:");
      Serial.print("Temperature: "); Serial.println(temperature);
      Serial.print("Humidity: "); Serial.println(humidity);
      Serial.print("MQ2 Value: "); Serial.println(mq2_value);
      Serial.print("Fire Percent: "); Serial.println(fire_percent);
      Serial.print("No Fire Percent: "); Serial.println(no_fire_percent);

      // Create the POST data string
      String postData = "temperature=" + String(temperature) +
                        "&humidity=" + String(humidity) +
                        "&mq2_value=" + String(mq2_value) +
                        "&fire_percent=" + String(fire_percent) +
                        "&no_fire_percent=" + String(no_fire_percent);

      // Initialize HTTPClient object
      HTTPClient http;

      // Start connection to server and set headers
      http.begin(URL);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");  // Set content type
      http.setTimeout(5000);

      // Send HTTP POST request
      int httpCode = http.POST(postData);

      // Check the response
      if (httpCode > 0) {
        // Success, print response payload
        String payload = http.getString();
        Serial.println("Server response:");
        Serial.println(payload);
      } else {
        // If there was an error, print error code
        Serial.print("Error on HTTP request, code: ");
        Serial.println(httpCode);
      }

      // Close the HTTP connection
      http.end();

      // Print the sent data for debugging
      Serial.println("POST Data: " + postData);
      Serial.println("HTTP Code: " + String(httpCode));
    } else {
      Serial.println("Failed to parse the data correctly.");
    }
  }

  delay(1000);  // Wait 1 second before checking for the next data
}
