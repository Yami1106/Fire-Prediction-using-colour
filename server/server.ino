#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
const char* ssid = "S23";
const char* password = "viropo2310";

// Google Apps Script Web App URL (for sensor data)
String URL = "https://script.google.com/macros/s/AKfycbyNKBgpTZZRSP0X94Bb8uxDFHSNP84Q00uZPxJTne-Lac9PKEJdHoTl3WrS5vEOIOpc/exec";

// Google API Key (for geolocation)
const char* apiKey = "AIzaSyDrlMN-Sg61sv1TJYqSKIT-VDLkV2PfH3A"; 

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600, SERIAL_8N1, 16, 17);  // Serial for sensor data

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void loop() {
    // Check if sensor data is available
    if (Serial1.available()) {
        String receivedData = Serial1.readStringUntil('\n');
        float temperature, humidity, mq2_value, fire_percent, no_fire_percent;
        sscanf(receivedData.c_str(), "%f,%f,%f,%f,%f", &temperature, &humidity, &mq2_value, &fire_percent, &no_fire_percent);

        // Get GPS location
        String gpsData = getLocation();

        // Construct JSON payload
        String postData = "{";
        postData += "\"temperature\":" + String(temperature) + ",";
        postData += "\"humidity\":" + String(humidity) + ",";
        postData += "\"mq2_value\":" + String(mq2_value) + ",";
        postData += "\"fire_percent\":" + String(fire_percent) + ",";
        postData += "\"no_fire_percent\":" + String(no_fire_percent) + ",";
        postData += gpsData + "}";  // Add GPS data to JSON

        // Send Data to Google Sheets
        HTTPClient http;
        http.begin(URL);
        http.addHeader("Content-Type", "application/json");

        int httpCode = http.POST(postData);
        String payload = http.getString();

        Serial.println("Data: " + postData);
        Serial.println("HTTP Code: " + String(httpCode));
        Serial.println("Response: " + payload);

        http.end();
    }
    delay(10000);  // Send data every 10 seconds
}

// Function to get GPS location
String getLocation() {
    Serial.println("🔎 Scanning WiFi networks...");
    int networksFound = WiFi.scanNetworks();
    if (networksFound == 0) {
        Serial.println("❌ No networks found.");
        return "\"latitude\":0, \"longitude\":0";  // Default values if no WiFi networks are found
    }

    // Construct JSON payload
    String json = "{ \"wifiAccessPoints\": [";
    for (int i = 0; i < networksFound; i++) {
        json += "{ \"macAddress\": \"" + WiFi.BSSIDstr(i) + "\", \"signalStrength\": " + String(WiFi.RSSI(i)) + " }";
        if (i < networksFound - 1) json += ", ";
    }
    json += "] }";

    Serial.println("📡 Sending data to Google API...");

    // Send HTTP request
    HTTPClient http;
    String url = "https://www.googleapis.com/geolocation/v1/geolocate?key=" + String(apiKey);
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(json);
    String latitude = "0", longitude = "0";

    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("✅ Location Response: " + response);

        // Extract latitude and longitude from response
        int latIndex = response.indexOf("\"lat\":");
        int lonIndex = response.indexOf("\"lng\":");

        if (latIndex != -1 && lonIndex != -1) {
            latitude = response.substring(latIndex + 6, response.indexOf(",", latIndex));
            longitude = response.substring(lonIndex + 6, response.indexOf("\n", lonIndex));
        }
    } else {
        Serial.print("❌ Error in HTTP request: ");
        Serial.println(httpResponseCode);
    }

    http.end();
    
    return "\"latitude\":" + latitude + ", \"longitude\":" + longitude;
}
