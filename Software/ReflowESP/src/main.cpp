#include <Arduino.h>

#include "main.h"

// Macros / config
#include "core/macros.h"
#include "config/Config.h"

// Persist
#include <Preferences.h>
#include <SPIFFS.h>

// OTA
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

#include <ArduinoJson.h>

#include "core/pwm.h"

const char* ssid = "SSID";
const char* password = "PASSWORD";

AsyncWebServer server(80);

// Menu
#include "core/menu.h"

// Preferences
Preferences preferences;

void IRAM_ATTR onTimer(); // Start the timer to read the clickEncoder every 1 ms

float pwmState = 0;
int pwmPeriodSec = 5;

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

pwm::PWMOutput pwmout;

/* -------------------------------------------------------------------------- */
/*                                    SETUP                                   */
/* -------------------------------------------------------------------------- */

bool initSPIFFS() {
  if(!SPIFFS.begin(true)) {
    Serial.println("Error mounting SPIFFS.");
    return false;
  }
  Serial.println("SPIFFS mounted");
  return true;
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void initPins() {
  pinMode(BUZZ, OUTPUT);
  pinMode(SSR1, OUTPUT);
  pinMode(SSR2, OUTPUT);
}

void initPWM() {
  pwmout.set_pin(BUZZ);
  pwmout.set_period(PWM_PERIOD);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Serial Start");

  if (!initSPIFFS()) {
    return;
  }

  initWiFi();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32.");
  });
  server.serveStatic("/", SPIFFS, "/");

  AsyncElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started.");

  clickEncoder.setAccelerationEnabled(false);
  clickEncoder.setDoubleClickEnabled(false);

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000, true);
  timerAlarmEnable(timer);

  preferences.begin("reflowesp", false);

  gfx.init();
  gfx.setRotation(1);
  gfx.fillScreen(TFT_BLACK);
  Serial.println("Done");

  initPins();
  initPWM();

  delay(500);
}

/* -------------------------------------------------------------------------- */
/*                                  MAIN LOOP                                 */
/* -------------------------------------------------------------------------- */

void loop() {
  constexpr int menuFPS = 1000 / 30;
  static unsigned long lastMenuFrame = -menuFPS;
  unsigned long now = millis();

  switch(exitMenuOptions) {
    // case 1: {
    //   delay (500);
    //   digitalWrite(BUZZ, HIGH);
    //   delay(buzzTimeOn * 1000);
    //   digitalWrite(BUZZ, LOW);
    //   exitMenuOptions = 0;
    // }
    default:
      if (now - lastMenuFrame >= menuFPS) {
        lastMenuFrame = millis();
        nav.poll();
      }
  }

  pwmout.set_level(pwmState);
  pwmout.poll();
}

/* -------------------------------------------------------------------------- */
/*                                 INTERRUPTS                                 */
/* -------------------------------------------------------------------------- */

void IRAM_ATTR onTimer() {
  clickEncoder.service();
}
