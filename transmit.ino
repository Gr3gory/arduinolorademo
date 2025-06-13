//Required MKR WAN 1310 driver in order to work

#include <SPI.h>

// https://github.com/sandeepmistry/arduino-LoRa
#include <LoRa.h>

/* sensor pins */
const int trigPin = 4; 
const int echoPin = 5;

/*
 * This code is in the public domain
 * Anyone can use this code to learn and develope 
 * with Arduino MKR WAN 1310 and LoRa
 * 
 * This project handles communication of data 
 * collected from a motion sensor to a LoRa receiver.
 * 
 * Made in I.T.T. Montani - Fermo by Gregorio and Federico
 */

/* configure required pins */
void setup() {
  
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    if (!LoRa.begin(868E6)) {
        Serial.println("Starting LoRa failed!");
        for (;;);
    }
}

/* this function return distance from motion sensor */
float get_distance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    float duration = pulseIn(echoPin, HIGH);
    return (duration * 0.0343) / 2;
}

/* send float value across LoRa */
void send_distance(float distance) {
    LoRa.beginPacket();
    LoRa.print(distance, 0);
    LoRa.endPacket();
}

/* Arduino loop() */
void loop() {
    float distance = get_distance();

    send_distance(distance);

    delay(50);
}
