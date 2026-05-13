#define HOMEKIT_MINIMAL
#include <HomeSpan.h>

// ── OTA / device identity ─────────────────────
// These are the only values you need to change
// when starting a new project from this template.
#define OTA_HOSTNAME    "my-esp32-device"   // hostname for OTA uploads (no spaces)
#define OTA_PASSWORD    "homekit123"        // password required by arduino-cli / IDE OTA tool
#define SKETCH_VERSION  "1.0"
// ─────────────────────────────────────────────

// ─────────────────────────────────────────────
// Step 1: Define your service struct here.
//         Replace MyService and Service::LightBulb
//         with the HomeKit service you need.
//
// Common services:
//   Service::LightBulb
//   Service::Switch
//   Service::WindowCovering
//   Service::Fan
//   Service::TemperatureSensor
//   Service::HumiditySensor
//   Service::GarageDoorOpener
//   Service::LockMechanism
// ─────────────────────────────────────────────

struct MyService : Service::LightBulb {

  // Step 2: Declare your characteristics here.
  //
  // Common characteristics:
  //   Characteristic::On          — on/off toggle
  //   Characteristic::CurrentPosition  — 0–100
  //   Characteristic::TargetPosition   — 0–100
  //   Characteristic::CurrentTemperature
  //   Characteristic::RotationSpeed
  //
  // Example:
  //   Characteristic::On power{false};

  MyService() {
    // Step 3: Initialize your hardware here.
    // Example: pinMode(PIN, OUTPUT);
  }

  boolean update() override {
    // Step 4: React to HomeKit commands here.
    // Example:
    //   bool on = power.getNewVal();
    //   digitalWrite(PIN, on ? HIGH : LOW);
    return true;
  }
};

// ─────────────────────────────────────────────
// Step 5: Fill in your device identity below.
// ─────────────────────────────────────────────

void setup() {
  Serial.begin(115200);

  homeSpan.setHostNameSuffix("");               // use OTA_HOSTNAME as-is (no auto-appended ID)
  homeSpan.setSketchVersion(SKETCH_VERSION);
  homeSpan.enableOTA(OTA_PASSWORD);             // OTA via ArduinoOTA – upload to OTA_HOSTNAME.local

  homeSpan.setPairingCode("XXXXXXXX");          // Replace with your 8-digit HomeKit PIN
  homeSpan.setLogLevel(0);                      // 0 = minimal, 1 = info, 2 = verbose

  // 3rd arg sets the OTA/mDNS hostname (OTA_HOSTNAME.local)
  homeSpan.begin(Category::Lighting, "My ESP32 Device", OTA_HOSTNAME);  // Change category and name

  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Manufacturer("Your Name");
      new Characteristic::Model("ESP32");
      new Characteristic::SerialNumber("000-000-001");
      new Characteristic::FirmwareRevision("1.0");

  new MyService();
}

void loop() {
  homeSpan.poll();
}
