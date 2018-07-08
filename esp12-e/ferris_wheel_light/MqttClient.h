#ifndef MqttClient_h
#define MqttClient_h

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

class MqttClient
{
  public:
    MqttClient(const char *id);
    void initialize(void (*handler)(char*, JsonObject));
    void loop();
    boolean publish(const char *topic, const char *message);
    boolean subscribe(const char *topic);
  private:
    void setup_wifi();
    void callback(char *topic, byte *payload, unsigned int length);
    boolean reconnect();
    const char *_id;
    const char *_subscriptions[10];
    int _subscriptionIndex = 0;
    void (*_handler)(char*, JsonObject);
    WiFiClient _espClient = WiFiClient();
    PubSubClient _client = PubSubClient(_espClient);
};

#endif
