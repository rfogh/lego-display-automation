#include "MqttClient.h"
#include "config.h"

WiFiClient _espClient = WiFiClient();
PubSubClient _client = PubSubClient(MQTT_SERVER, 1883, _espClient);

MqttClient::MqttClient(void (*handler)(char*, JsonObject&)) {
  setClientId();
  setup_wifi();

  setHandler(handler);
}

void MqttClient::setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
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

void MqttClient::callback(char* topic, unsigned char* payload, unsigned int length) {
  Serial.println(topic);
  Serial.println((char*) payload);

  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& message = jsonBuffer.parseObject(payload);

  _handler(topic, message);
}

long lastReconnectAttempt = 0;

boolean MqttClient::reconnect() {
  if (_client.connect(_clientId)) {
    _client.publish("event/connected", _clientId);

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

boolean MqttClient::publish(const char *topic) {
  Serial.println(topic);
  return _client.publish(topic, "");
}

boolean MqttClient::publish(const char *topic, JsonObject& message) {
  char serializedMessage[200];
  message.printTo((char*) serializedMessage, message.measureLength()+1);

  Serial.println(topic);
  Serial.println((char*) serializedMessage);

  return _client.publish(topic, serializedMessage);
}

boolean MqttClient::subscribe(const char *topic) {
  if (_subscriptionIndex >= MQTT_MAX_SUBSCRIPTIONS) {
    Serial.println("Max subscriptions reached. Not subscribed.");
    return false;
  }

  _subscriptions[_subscriptionIndex++] = topic;
  return _client.subscribe(topic);
}

void MqttClient::setHandler(void (*handler)(char*, JsonObject&)) {
  std::function<void(char*, unsigned char*, unsigned int)> pubsubCallback = [this] (char *topic, unsigned char *payload, unsigned int length) {this -> callback(topic, payload, length);};
  _client.setCallback(pubsubCallback);

  _handler = handler;
}

void MqttClient::setClientId() {
  uint32_t chipid=ESP.getChipId();
  snprintf(_clientId,10,"ESP-%08X",chipid);
}

char* MqttClient::getClientId() {
  return _clientId;
}
