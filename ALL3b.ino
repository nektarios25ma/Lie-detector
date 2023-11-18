
/* 
GEL SOUDAS 2023
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
#include "DFRobot_BloodOxygen_S.h"

#define I2C_COMMUNICATION  //use I2C for communication, but use the serial port for communication if the line of codes were masked

#define  I2C_COMMUNICATION
#define I2C_ADDRESS    0x57
  DFRobot_BloodOxygen_S_I2C MAX30102(&Wire ,I2C_ADDRESS);

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
while (false == MAX30102.begin())
  {
    Serial.println("init fail!");
    delay(1000);
  }
 
  
  MAX30102.sensorStartCollect();

  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  delay(1000);
pinMode(2, OUTPUT);//GREEN
	pinMode(5,   OUTPUT);//ORANGE OR YELLOW
	pinMode(4, OUTPUT);//RED
	digitalWrite(2, LOW);
	delay(500);
	digitalWrite(5, LOW);
	delay(500);
	digitalWrite(4, LOW);
	delay(500);  
  MAX30102.getHeartbeatSPO2();
  for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  sum += sensorValue;
  delay(5);
  }
  threshold = sum/500;

   delay(5000);
 lcd.setCursor(0, 0); // Or setting the cursor in the desired position.
  lcd.print("  GSR threshold:"); 
lcd.setCursor(17, 0);
  lcd.print(threshold);  
    
  }

void loop(){
  MAX30102.getHeartbeatSPO2();
 float HEARTrate=MAX30102._sHeartbeatSPO2.Heartbeat; 

  int temp;
  sensorValue=analogRead(GSR);
  Serial.println("threshold,sensorValue");
  Serial.print(threshold);Serial.print(",");
  Serial.println(sensorValue);

   lcd.setCursor(0,1);
 lcd.print("sensorValue= "); 
 lcd.setCursor(15, 1);
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
	digitalWrite(5,   HIGH);
  lcd.setCursor(15, 1);
 lcd.print("   ");
lcd.setCursor(0, 2); // Or setting the cursor in the desired position.
   lcd.print("???Lie detected "); 
lcd.setCursor(0,1);
 lcd.print("sensorValue= ");
 lcd.setCursor(15, 1);
lcd.print(sensorValue); 
//Serial.println("threshold,sensorValue");
  Serial.print(threshold);Serial.print(",");
  Serial.println(sensorValue);    
    delay(1000);
    digitalWrite(LED,LOW);
    delay(900);
  }
 if(abs(temp)>55){
    digitalWrite(LED,HIGH);
digitalWrite(2, HIGH);
	delay(5);
	digitalWrite(5,   HIGH);
	delay(5);
	digitalWrite(4, HIGH);
	delay(5);    

  Serial.print(threshold);Serial.print(",");
  Serial.println(sensorValue);
   lcd.setCursor(15, 1);
 lcd.print("   ");     
 lcd.setCursor(0, 2); // Or setting the cursor in the desired position.
  lcd.print("!!!Lie detected "); 
  lcd.setCursor(0,1);
 lcd.print("sensorValue= ");
 lcd.setCursor(15, 1);
lcd.print(sensorValue);     
    delay(1000);
    digitalWrite(LED,LOW);
    delay(900);
  }  
 }
digitalWrite(2, LOW);
	delay(5);
	digitalWrite(4,   LOW);
	delay(5);
	digitalWrite(5, LOW); 
  lcd.setCursor(0, 2);
lcd.print("SPO2 is :   ");
 lcd.setCursor(12, 2);
 lcd.print(MAX30102._sHeartbeatSPO2.SPO2);
 lcd.setCursor(15, 2);
 lcd.print(" %");
  lcd.setCursor(0, 3);
lcd.print("heart rate is:");
if (HEARTrate>99)
 {lcd.setCursor(16, 3);
 lcd.print(MAX30102._sHeartbeatSPO2.Heartbeat);}
 else {
   lcd.setCursor(16, 3);lcd.print(" ");
   lcd.setCursor(17, 3);
 lcd.print(MAX30102._sHeartbeatSPO2.Heartbeat);}


}

