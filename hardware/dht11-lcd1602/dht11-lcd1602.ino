/*
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor (potentiometer)
 * ends to +5V through a 220 ohm resitor to provide and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.
 http://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay

*/

/*
  DH11 
*/

// include the library code:
#include <LiquidCrystal.h>

#include <dht.h>

#include <Arduino.h>

dht DHT;

// can use digital pin
#define DHT11_PIN 7

typedef struct {
    char humidity[16];
    char temperature[16];
} SensorData;


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(115200);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.display();
}

void loop() {
  SensorData result = getHumiAndTemp();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(result.humidity);
  lcd.setCursor(0,1);
  lcd.print(result.temperature);
  delay(2000);
}

SensorData getHumiAndTemp() {
  SensorData data;
   // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default: 
    Serial.print("Unknown error,\t");
    break;
  }

  
  char humiStr[10], tempStr[10];
  dtostrf(DHT.humidity, 6, 1, humiStr);
  dtostrf(DHT.temperature, 6, 1, tempStr);

  snprintf(data.humidity, sizeof(data.humidity), "HUM: %s %%", humiStr);
  snprintf(data.temperature, sizeof(data.temperature), "Temp:%s C", tempStr);

  Serial.print(DHT.humidity);
  Serial.print(",\t");
  Serial.println(DHT.temperature);
  return data;
}

