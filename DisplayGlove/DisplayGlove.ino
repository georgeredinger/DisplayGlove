
#define ADXL345_POWER A3
#define OLED_RESET 13
#define OLED_POWER 12
#define VIBRATOR 3
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
Adafruit_SSD1306 display(OLED_RESET);


extern int freeMemory();

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 


#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define CAPTURE_SIZE 140
static long capture[CAPTURE_SIZE];



void setup()   {                
  Serial.begin(115200);               //initial the Serial
  pinMode(OLED_POWER,OUTPUT);
  pinMode(ADXL345_POWER,OUTPUT);
  pinMode(VIBRATOR,OUTPUT);
  
  digitalWrite(ADXL345_POWER,HIGH);
if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }
  digitalWrite(OLED_POWER,HIGH);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Swingizer");
  display.display();
  delay(1000);
  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
  // displaySetRange(ADXL345_RANGE_8_G);
  // displaySetRange(ADXL345_RANGE_4_G);
  // displaySetRange(ADXL345_RANGE_2_G);
}


int index = 0;
void loop() {
  sensors_event_t event; 
  accel.getEvent(&event);
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print(event.acceleration.x);
  display.setCursor(40,0);
  display.print(event.acceleration.y);
  display.setCursor(80,0);
  display.println(event.acceleration.z);
  display.setCursor(0,20);
  display.print(freeMemory());
  display.display();
 // Serial.println(buff);    //send what has been received
 if(event.acceleration.z < -9.0) {
     digitalWrite(VIBRATOR,HIGH);
     delay(500);
     digitalWrite(VIBRATOR,LOW);
     capture[index % CAPTURE_SIZE] = event.acceleration.z;
     index++;
 }
}



