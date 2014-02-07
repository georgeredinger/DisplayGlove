/*********************************************************************
 * This is an example for our Monochrome OLEDs based on SSD1306 drivers
 * 
 * Pick one up today in the adafruit shop!
 * ------> http://www.adafruit.com/category/63_98
 * 
 * This example is for a 128x32 size display using I2C to communicate
 * 3 pins are required to interface (2 I2C and one reset)
 * 
 * Adafruit invests time and resources providing this open source code, 
 * please support Adafruit and open-source hardware by purchasing 
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada  for Adafruit Industries.  
 * BSD license, check license.txt for more information
 * All text above, and the splash screen must be included in any redistribution
 *********************************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 


#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Welcome");
  display.display();
  delay(2000);
}

unsigned long count;
int size=3;

void loop() {
  display.clearDisplay();
  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(count++);
  display.display();
  
  if(count % 100 == 0){
    size=count % 3 + 1;
    digitalWrite(12,LOW);
    digitalWrite(12,HIGH);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  } 
  
}



