#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// Wi-Fi credentials
#define WIFI_SSID "ATHAFY NETWORK"
#define WIFI_PASSWORD "9526888917"

// Firebase credentials
#define FIREBASE_HOST "smartweatherstation-460ef-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "0LSadxIyPSVimRXNYOn2vTD8mMvMDrBB3WRY9wUI"

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    Serial.print("Connecting to Wi-Fi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\n✅ Connected to Wi-Fi!");

    // Configure Firebase
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("🔥 Sending test data to Firebase...");

    // Send test data
    if (Firebase.setInt(fbdo, "/test/value", 100)) {
        Serial.println("✅ Data sent successfully!");
    } else {
        Serial.print("❌ Failed to send data: ");
        Serial.println(fbdo.errorReason().c_str());
    }
}

void loop() {
    // Add your main logic here
}
