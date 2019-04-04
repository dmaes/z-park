#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Watson IoT connection details
#define MQTT_HOST "4p0ycs.messaging.internetofthings.ibmcloud.com"
#define MQTT_PORT 1883
#define MQTT_DEVICEID "d:4p0ycs:MQTT-client:arduino_test"
#define MQTT_USER "use-token-auth"
#define MQTT_TOKEN "testtoken"
#define MQTT_TOPIC "iot-2/evt/status/fmt/json"
#define MQTT_TOPIC_DISPLAY "iot-2/cmd/update/fmt/json"

const int BAUD_RATE = 115200;

// Update these with values suitable for your network.

const char* ssid = "ucll-projectweek-IoT";
const char* password = "Foo4aiHa";
const char* mqtt_server = "4p0ycs.messaging.internetofthings.ibmcloud.com";
const int button = 0;
int buttonState = 0;

// defines pins numbers
const int trigPinLeft = 14;
const int echoPinLeft = 12;
const int trigPinRight = 15;
const int echoPinRight = 13;
 
const int linksRood = 3;
const int linksGroen = 1;
const int linksBlauw = 2;
 
const int rechtsRood = 0;
const int rechtsGroen = 4;
const int rechtsBlauw = 5;
 
// defines variables
long durationLeft;
int distanceLeft;
long durationRight;
int distanceRight;

bool statusLeft = true;
bool statusRight = true;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void connect_setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void distance_setup() {
  pinMode(trigPinLeft, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinLeft, INPUT); // Sets the echoPin as an Input
  pinMode(trigPinRight, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinRight, INPUT); // Sets the echoPin as an Input
}

void setup() {
  Serial.begin(BAUD_RATE);
  connect_setup();
  distance_setup();
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_DEVICEID, MQTT_USER, MQTT_TOKEN)) {
      Serial.println("connected");
      client.subscribe(MQTT_TOPIC_DISPLAY);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  checkDistanceLeft();
  checkDistanceRight();
}

void setLinks(int r, int g, int b){
  analogWrite(linksRood, r);
  analogWrite(linksGroen, g);
  analogWrite(linksBlauw, b);
}
 
void setRechts(int r, int g, int b){
  analogWrite(rechtsRood, r);
  analogWrite(rechtsGroen, g);
  analogWrite(rechtsBlauw, b);
}
 
void checkDistanceRight() {
  bool oldStatus = statusRight;
  // Clears the trigPin
  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationRight = pulseIn(echoPinRight, HIGH);
  // Calculating the distance
  distanceRight = durationRight * 0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("DistanceRight: ");
  Serial.println(distanceRight);
  delay(100);
 
  if (distanceRight > 10) {
    statusRight = true; 
    setRechts(0,255,0);
  }else {
    statusRight = false;
    setRechts(255,0,0);
  }

  if (oldStatus != statusRight) {
    sendParkingStatus("2", statusRight);
  }
 
}

inline const String BoolToString(bool b) {
  return b ? "true" : "false";
}

void sendParkingStatus(String location, bool free) {
  String payload = "{ \"location\": \"" + location + "\",";
  payload += " \"available\": " + BoolToString(free) + "}";
  sendPayload(payload);
}
 
void checkDistanceLeft() {
  bool oldStatus = statusLeft;
  // Clears the trigPin
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinLeft, HIGH);// defines pins numbers
 
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationLeft = pulseIn(echoPinLeft, HIGH);
  // Calculating the distance
  distanceLeft = durationLeft * 0.034/2;
 
  if (distanceLeft > 10) {
    statusLeft = true;
    setLinks(0,255,0);
  }else {
    statusLeft = false;
    setLinks(255,0,0);
  }
  // Prints the distance on the Serial Monitor
  Serial.print("DistanceLeft: ");
  Serial.println(distanceLeft);
  delay(100);

  if (oldStatus != statusLeft) {
    sendParkingStatus("1", statusLeft);
  }
}

void sendPayload(String payload) {
  Serial.println(payload);
  if (client.publish(MQTT_TOPIC, (char*) payload.c_str())) {
    Serial.println("Publish ok");
  } else {
    Serial.println("Publish failed");
  }
}
