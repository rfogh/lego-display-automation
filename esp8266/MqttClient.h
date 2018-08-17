#ifndef MqttClient_h
#define MqttClient_h

#define MQTT_MAX_SUBSCRIPTIONS    10

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

class MqttClient
{
  public:
    MqttClient(void (*handler)(String, ArduinoJson::JsonObject&));
    void begin();
    boolean publish(const char *topic);
    boolean publish(const char *topic, JsonObject& message);
    boolean subscribe(const char *topic);
    void loop();
    char* getClientId();
  private:
    void setup_wifi();
    void callback(char *topic, unsigned char *payload, unsigned int length);
    boolean reconnect();
    void setHandler(void (*handler)(String, JsonObject&));
    void setClientId();
    char _clientId[12];
    const char *_subscriptions[MQTT_MAX_SUBSCRIPTIONS];
    int _subscriptionIndex = 0;
    void (*_handler)(String, JsonObject&);
};

#endif
