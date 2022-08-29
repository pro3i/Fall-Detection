
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <Arduino_LSM6DS3.h>
#include <stdio.h>  
#include <avr/dtostrf.h>

#include "secrets.h"
/*************************
 * Define Constants
 */
char ssid[] = SECRET_SSID;        //network SSID (name)
char pass[] = SECRET_PASS;    //network password (use for WPA, or use as key for WEP)
char token[]= TOKEN;
#define VARIABLE_LABEL_1 "xacc"
#define VARIABLE_LABEL_2 "yacc"
#define VARIABLE_LABEL_3 "zacc"
#define VARIABLE_LABEL_4 "xgyro"
#define VARIABLE_LABEL_5 "ygyro"
#define VARIABLE_LABEL_6 "zgyro"
#define DEVICE_LABEL "arduino"
#define MQTT_CLIENT_NAME "84CCA878C724"
int status = WL_IDLE_STATUS;     // the WiFi radio's status

char mqttBroker[] = "industrial.api.ubidots.com";
char payload[700];
char topic[150];

char str_x_Acc[6];
char str_y_Acc[6];
char str_z_Acc[6];
char str_x_Gyro[6];
char str_y_Gyro[6];
char str_z_Gyro[6];


/***************************
 * Initialise constructors for objects
 */

WiFiClient ubidots;
PubSubClient client(ubidots);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived from [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
   Serial.println();
}
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN,"")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

     // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  
  

   if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);

}

void loop() {

  if (!client.connected()) {
     reconnect();
}
 
  float xacc, yacc, zacc, xgyro, ygyro, zgyro;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(xacc, yacc, zacc);}
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(xgyro, ygyro, zgyro);}
    
    
  dtostrf(xacc,4,2,str_x_Acc);
  dtostrf(yacc,4,2,str_y_Acc);
  dtostrf(zacc,4,2,str_z_Acc);
  dtostrf(xgyro,4,2,str_x_Gyro);
  dtostrf(ygyro,4,2,str_y_Gyro);
  //dtostrf(zgyro,4,2,str_z_Gyro);
  
  
  sprintf(topic, "%s", ""); // Cleans the topic content
  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);

  sprintf(payload, "%s", ""); //Cleans the payload
  
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL_1); // Adds the variable label  
  sprintf(payload, "%s %s ,", payload, str_x_Acc); // Adds the value

  sprintf(payload, "%s \"%s\":", payload, VARIABLE_LABEL_2); // Adds the variable label  
  sprintf(payload, "%s  %s ,", payload, str_y_Acc); // Adds the value

  sprintf(payload, "%s \"%s\":", payload, VARIABLE_LABEL_3); // Adds the variable label  
  sprintf(payload, "%s %s ,", payload, str_z_Acc); // Adds the value

  sprintf(payload, "%s \"%s\":", payload, VARIABLE_LABEL_4); // Adds the variable label  
  sprintf(payload, "%s %s ,", payload, str_x_Gyro); // Adds the value

  sprintf(payload, "%s \"%s\":", payload, VARIABLE_LABEL_5); // Adds the variable label  
  sprintf(payload, "%s %s ,", payload, str_y_Gyro); // Adds the value

  sprintf(payload, "%s \"%s\":", payload, VARIABLE_LABEL_6); // Adds the variable label  
  sprintf(payload, "%s  %.2f ", payload, zgyro); // Adds the value
  
  
  sprintf(payload, "%s }", payload); // Closes the dictionary brackets

  Serial.print(payload);
  Serial.println();

  
  client.publish(topic, payload);
  client.loop();
  delay(2000);


}
