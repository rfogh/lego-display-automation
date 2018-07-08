#include "MqttClient.h"
#include "config.h"

#include <Arduino.h>

MqttClient::MqttClient(const char *id)
{
  _id = id;
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  _client.setServer(MQTT_SERVER, 1883);
}

void MqttClient::initialize(void (*handler)(char*, JsonObject)) {
  _handler = handler;
  _client.setCallback([this] (char *topic, byte *payload, unsigned int length) {this -> callback(topic, payload, length);});
}

void MqttClient::setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void MqttClient::callback(char* topic, byte* payload, unsigned int length) {
  StaticJsonDocument<200> doc; //length...?
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    // Serial.print(F("deserializeJson() failed: "));
    // Serial.println(error.c_str());
    return;
  }
  JsonObject message = doc.as<JsonObject>();

  _handler(topic, message);
}

long lastReconnectAttempt = 0;

boolean MqttClient::reconnect() {
  if (_client.connect(_id)) {
    _client.publish("status/connection", _id);

    //Resubscribe
    for (int i=0; i<_subscriptionIndex; i++) {
      _client.subscribe(_subscriptions[i]);
    }
  }
  return _client.connected();
}

void MqttClient::loop() {
  if (!_client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    _client.loop();
  }
}

boolean MqttClient::publish(const char *topic, const char *message) {
  if (_subscriptionIndex >= 10)
    return false;

  _subscriptions[_subscriptionIndex++] = topic;
  return _client.publish(topic, message);
}

boolean MqttClient::subscribe(const char *topic) {
  return _client.subscribe(topic);
}