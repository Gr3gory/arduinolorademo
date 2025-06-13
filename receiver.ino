//Required MKR WAN 1310 drivers installed in order to compile and flash

#include <SPI.h>

// https://github.com/sandeepmistry/arduino-LoRa
#include <LoRa.h>

const int RED_LED_PIN = 1;
const int YELLOW_LED_PIN = 3;
const int GREEN_LED_PIN = 5;

/*
 * Anyone can use this code to learn and develop
 * with Arduino MKR WAN 1310 and LoRa
 * 
 * This project handles communication of data 
 * collected from a motion sensor to a LoRa receiver.
 * 
 * Made in I.T.T. Montani - Fermo by Gregorio and Federico
 */

/* configuring pins, Serial Monitor and LoRa */ 
void setup() {
  Serial.begin(9600);
  while (!Serial); //getting stuck here if Serial is not initialized

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
    /* LEDs off */
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
  }
  else if (value > 420) {
    /* green case */
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
  } 
  else if (value < 420 && value > 30) {
    /* yellow case */
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  } 
  else if (value > 0 && value < 30){
    /* red case */
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  }
}

/* Read distance from lora packet and update LEDs */
void loop() {
  /* Get LoRa packet size */
  int packetSize = LoRa.parsePacket();

  /* The value is transmitted one byte at a time
   * We are collecting every byte of the packet 
   * and storing them in a String then we convert
   * the string into an integer
   */
   
  if (packetSize) {
    String data = "";
    while (LoRa.available()) {
      char k = (char)LoRa.read();
      data += k;
    }

    int distance = data.toInt(); 
    Serial.println(distance); //Display the received value to Serial monitor for debugging

    updateLEDs(distance); 
  }

  delay(50);
}
