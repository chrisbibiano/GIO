#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

#define OLED_RESET 4 // not used / nicht genutzt bei diesem Display
Adafruit_SSD1306 display(OLED_RESET);
SoftwareSerial AllenSerial(5, 6); // RX, TX

char inChar;
String Oled_String;

void setup()   {
 // initialize with the I2C addr 0x3C / mit I2C-Adresse 0x3c initialisieren
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(INVERSE);

  Serial.begin(9600);
  AllenSerial.begin(9600);

  Oled_String.reserve(50);
  Oled_String="";
}

void ToAllenMSG();

void loop()
{
  if (Serial.available()) {
      display.clearDisplay();
      inChar = Serial.read();
      Serial.print(inChar);
      Oled_String+=inChar;
      display.setCursor(0,0);
      display.print(Oled_String);
      display.display();

      if( inChar == '\r'){
          Serial.println("Sending to Allen Bradlay display");
          ToAllenMSG();
          delay(500);
          Oled_String="";
      }
  }
  display.display();
}

void ToAllenMSG(){
    AllenSerial.print("\\14");                     //START
    AllenSerial.print("\\32\\30\\31\\38");         //Message
    AllenSerial.print("\\5C");                     //BackSlash
    AllenSerial.print("\\32");                     //Function
    AllenSerial.print("\\5C");                     //BackSlash
    AllenSerial.print("\\32\\35\\35");             //Address
    AllenSerial.print("\\0D");                     //Return
}
