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
int button = 3;
int button_state = false;
int speaker = 4;
float current_time=0,prev_time = 0;
float current_time_b=0,prev_time_b = 0; 
float current_time_st=0,prev_time_st = 0;
float bpm = 0.5454;
int sec,minute = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(speaker,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3),statechange,RISING);
  Serial.begin(9600);
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    while(true);
  }
  delay(2000);
  oled.clearDisplay(); // clear display
  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 10);        // position to display
  oled.println("Hello World!"); // text to display
  oled.display();               // show on OLED
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
minute=0;
sec=0;
  while(button_state == true){
    current_time_b = millis();
    if(current_time_b - prev_time_b >= bpm*1000){
      buzz();
    }
    
 
    current_time_st = millis();
    Serial.println(current_time_st);
    if(current_time_st - prev_time_st >= 975){
      sec += 1;
      prev_time_st = millis();
      if(sec >= 60){
        minute += 1;
        sec = sec-60; 
      }
    }
      Serial.print("min:");
      Serial.print(minute);
      Serial.print("        sec:");
      Serial.println(sec);
    

   // Serial.println(prev_time_st);    
    current_time = millis();
   // Serial.println(current_time);
    if(current_time - prev_time >= 120000)
    { buzz_2min();
      Serial.println("check pulse");
      delay(5000);
      prev_time = millis();
      sec = sec+ 5;
    }
}
}
void statechange(){
  button_state = !button_state;
  prev_time = millis();
 // Serial.println(prev_time);
  prev_time_st = millis();
  Serial.println(button_state);
  Serial.println("Button pressed");
}
int timer(){
  
}
int buzz(){
  digitalWrite(speaker,HIGH);
  delay(10);
  digitalWrite(speaker,LOW);
  prev_time_b = millis();
  }
int buzz_2min(){
  digitalWrite(speaker,HIGH);
  delay(1000);
  digitalWrite(speaker,LOW);
  }
