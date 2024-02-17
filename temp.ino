#include <splash.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <gfxfont.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HIEGHT 64
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HIEGHT, &Wire, -1);
int button = 26;
int button_state = false;
int speaker = 14;
float current_time_c,prev_time_c;
float current_time=0,prev_time = 0;
float current_time_b=0,prev_time_b = 0; 
float current_time_st=0,prev_time_st = 0;
float bpm = 0.5454;
int sec,minute = 0;
int hour_c= 20;
int min_c = 43;
int sec_c = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(speaker,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  attachInterrupt(button,statechange,RISING);
  Serial.begin(115200);
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    while(true);
  }
  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());
  delay(5000);
   oled.clearDisplay(); // clear display
  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
//  oled.setCursor(0, 10);        // position to display
//  oled.println("press to start"); // text to display
//  oled.display();               // show on OLED
//  delay(1000);
  oled.clearDisplay();
  Serial.println(digitalRead(button));
  
}

void loop() {
// oled.clearDisplay();
  Serial.println("Inside the Loop");
  clockd();
  minute=0;
  sec=0;
//  if(digitalRead(button) == false){
//    statechange();
//  }
  while(button_state == true){
    current_time_b = millis();
    if(current_time_b - prev_time_b >= bpm*1000){
      buzz();
    }
    
 
    current_time_st = millis();
   // Serial.println(current_time_st);
     if(current_time_st - prev_time_st >= 1000){
      sec += 1;
      prev_time_st = millis();
      
      if(sec >= 60){
        minute += 1;
        sec = sec-60; 
      }
      oled.clearDisplay();
      oled.setCursor(0,10);
      oled.print(minute);
      oled.print("  min :  ");
      oled.print(sec);
      oled.println(" seconds");
      oled.display();
    }
      // Serial.print("min:");
      // Serial.print(minute);
      // Serial.print("        sec:");
      // Serial.println(sec);
    

   // Serial.println(prev_time_st);    
    current_time = millis();
   // Serial.println(current_time);
    if(current_time - prev_time >= 120000)
    { buzz_2min();
      // Serial.println("check pulse");
      oled.clearDisplay();  
      oled.setCursor(0, 10);        // position to display
      oled.println("Check Pulse"); // text to display
      oled.display();
      delay(5000);
      prev_time = millis();
      sec = sec+ 5;
    }
    prev_time_c = millis();
}
    sec_c = sec_c +sec;
    min_c = min_c + minute;

}
void statechange(){
  button_state = !button_state;
  prev_time = millis();
 // Serial.println(prev_time);
  prev_time_st = millis();
 // Serial.println(button_state);
  //Serial.println("Button pressed");
}
void clockd(){
    current_time_c = millis();
    Serial.println(current_time_c);
    if(current_time_c - prev_time_c >= 1000){
       sec_c += 1;
      prev_time_c = millis();
      
      if(sec_c >= 60){
        min_c += 1;
        sec_c= sec_c-60; 
      }
      
      if(min_c >= 60){
        hour_c += 1;
        min_c= min_c-60; 
      }
      if(hour_c >= 24){
        hour_c  = 0; 
      }
      oled.clearDisplay();
      oled.setCursor(0,10);
      oled.print(hour_c);
      oled.print(":  ");
      oled.print(min_c);
      oled.println("min");
      oled.display();
    }
      // Serial.print("hour:");
      // Serial.print(hour_c);
      // Serial.print("        min:");
      // Serial.println(min_c);
    
}
void buzz(){
  digitalWrite(speaker,HIGH);
  delay(10);
  digitalWrite(speaker,LOW);
  prev_time_b = millis();
  
  }
void buzz_2min(){
  digitalWrite(speaker,HIGH);
  delay(1000);
  digitalWrite(speaker,LOW);
  }
