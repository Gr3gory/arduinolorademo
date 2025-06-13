//Required MKR WAN 1310 driver in order to work

#include <SPI.h>

// https://github.com/sandeepmistry/arduino-LoRa
#include <LoRa.h>

const int RED_LED_PIN = 1;
const int YELLOW_LED_PIN = 3;
const int GREEN_LED_PIN = 5;

/*
 * This code is in the public domain
 * Anyone can use this code to learn and develop
 * with Arduino MKR WAN 1310 and LoRa
 * 
 * This project handles communication of data 
 * collected from a motion sensor to a LoRa receiver.
 * 
 * Made in I.T.T. Montani - Fermo by Gregorio and Federico
 */

/* configuring pins, Serial Monitor and LoRa*/ 
void setup() {
  Serial.begin(9600);
  while (!Serial);
	pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  Serial.println("LoRa Receiver");

  

  if (!LoRa.begin(868E6)) {
		Serial.println("Starting LoRa failed!");
  	while (1);
	}

}

/* function to update leds view */
void updateLEDs(int value) {
  if (value == 0) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
  }
  if (value > 420) {
    /* green case */
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
  } else if (value < 420 && value > 30) {
    /* yellow case */
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  } else if (value < 30){
    /* red case */
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  }
}

/* Arduino loop() */
void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String data = "";
    while (LoRa.available()) {
      char k = (char)LoRa.read();
      data += k;
    }

    int distance = data.toInt(); 
    Serial.println(distance);

    updateLEDs(distance);  // <== Move this here
  }

  delay(50);
}
