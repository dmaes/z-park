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
 
void setup() {
  pinMode(trigPinLeft, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinLeft, INPUT); // Sets the echoPin as an Input
  pinMode(trigPinRight, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinRight, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
 
void loop() {
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
    setRechts(0,255,0);
  }else {
    setRechts(255,0,0);
  }
 
}
 
void checkDistanceLeft() {
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
    setLinks(0,255,0);
  }else {
    setLinks(255,0,0);
  }
  // Prints the distance on the Serial Monitor
  Serial.print("DistanceLeft: ");
  Serial.println(distanceLeft);
  delay(100);
}
