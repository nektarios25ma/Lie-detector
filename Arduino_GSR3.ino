// Watch video here: https://www.youtube.com/watch?v=O5Ye5xJF44c

/* 
GSR connection pins to Arduino microcontroller

Arduino           GSR

GND               GND
5V                VCC
A2                SIG

D13             RED LED

*/

/*
 GSR, standing for galvanic skin response, is a method of 
 measuring the electrical conductance of the skin. Strong 
 emotion can cause stimulus to your sympathetic nervous 
 system, resulting more sweat being secreted by the sweat 
 glands. Grove – GSR allows you to spot such strong emotions 
 by simple attaching two electrodes to two fingers on one hand,
 an interesting gear to create emotion related projects, like 
 sleep quality monitor. http://www.seeedstudio.com/wiki/Grove_-_GSR_Sensor
 */
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 20, 4); // Default address of most PCF8574 modules, change according

const int LED=13;
const int GSR=A2;
int threshold=0;
int sensorValue;

void setup(){
lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
//lcd.begin(false)                 
  lcd.backlight(); 
  
  long sum=0;
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  delay(1000);
pinMode(2, OUTPUT);//GREEN
	pinMode(3,   OUTPUT);//ORANGE OR YELLOW
	pinMode(4, OUTPUT);//RED
	digitalWrite(2, LOW);
	delay(500);
	digitalWrite(3, LOW);
	delay(500);
	digitalWrite(4, LOW);
	delay(500);  
  
  for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  sum += sensorValue;
  delay(5);
  }
  threshold = sum/500;
   Serial.print("threshold =");
   Serial.println(threshold);
   delay(5000);
 lcd.setCursor(0, 0); // Or setting the cursor in the desired position.
  lcd.print("GSR_threshold:"); 
lcd.setCursor(16, 0);
  lcd.print(threshold);  
    
  }

void loop(){
  lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
  lcd.print("GEL SOUDAS       ");
  int temp;
  sensorValue=analogRead(GSR);
  Serial.print("sensorValue=");
  Serial.println(sensorValue);
 Serial.print("threshold =");
   Serial.println(threshold);
   lcd.setCursor(0,2);
 lcd.print("sensorValue="); 
 lcd.setCursor(16, 2);
lcd.print(sensorValue);   
  temp = threshold - sensorValue;
  if(abs(temp)>30)
  {
    sensorValue=analogRead(GSR);
    temp = threshold - sensorValue;
    if((abs(temp)>30) && (abs(temp)<=55)){
    digitalWrite(LED,HIGH);
    
	digitalWrite(2, HIGH);
//	delay(500);
	digitalWrite(3,   HIGH);
//	delay(500);
//	digitalWrite(4, HIGH);
//	delay(500);
    Serial.println("Emotion Changes Detected!");
lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
   lcd.print("???Lie detected "); 
lcd.setCursor(0,2);
 lcd.print("sensorValue=");
 lcd.setCursor(16, 2);
lcd.print(sensorValue); 
// Serial.print("sensorValue=");
//Serial.println(sensorValue);      
    delay(3000);
    digitalWrite(LED,LOW);
    delay(1000);
  }
 if(abs(temp)>55){
    digitalWrite(LED,HIGH);
digitalWrite(2, HIGH);
	delay(5);
	digitalWrite(3,   HIGH);
	delay(5);
	digitalWrite(4, HIGH);
	delay(5);    
    Serial.println("Emotion Changes Detected!");
Serial.println("!!Lie detected!");    
 lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
  lcd.print("!!!Lie detected "); 
  lcd.setCursor(0,2);
 lcd.print("sensorValue=");
 lcd.setCursor(16, 2);
lcd.print(sensorValue);     
    delay(3000);
    digitalWrite(LED,LOW);
    delay(1000);
  }  
 }
digitalWrite(2, LOW);
	delay(5);
	digitalWrite(3,   LOW);
	delay(5);
	digitalWrite(4, LOW); 
}
