#define RMTC_DEFINE_GLOBAL_VARS
#include "dora.h"
#include <Arduino.h>

DORA::DORA() {}

void DORA::setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  initServer();
  initAp();

}

void DORA::loop() {
  static elapsedMillis blink;
  // simple blink to indicate that the device is working
  if (blink > 500) {
    blink = 0;
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  // DNS server is required for captive portal to work
#ifdef DORA_CAPTIVE_PORTAL
  if (apActive) dnsServer.processNextRequest();
#endif

  sendEvents();
}

// reset the device
void DORA::reset() {
  unsigned long dly = millis();
  while (millis() - dly < 450) {
    yield();        // enough time to send response to client
  }
  Serial.println("DORA reset...");
  ESP.restart();
}

void DORA::initAp() {

  WiFi.softAPConfig(IPAddress(10, 1, 2, 3), IPAddress(10, 1, 2, 3), IPAddress(255, 255, 255, 0));
  WiFi.softAP("DORA", "dora1234", 1);

  // start mdns
  if (!MDNS.begin("dora")) {
    Serial.println("Error setting up MDNS responder!");
  }

  // start server and or captive portal if AP not active
  if (!apActive) 
  {
    server.begin();
#ifdef DORA_CAPTIVE_PORTAL
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(53, "*", WiFi.softAPIP());
#endif
  }
  apActive = true;
}
