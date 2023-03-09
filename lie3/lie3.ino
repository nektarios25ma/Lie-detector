#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according


const int GSR=A0;
int sensorValue=0;
int gsr_average=0;
int threshold=3;
const int BUZZER=13;//11;
int previous=0; 


void setup(){
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
                 // this stop the library(LCD_I2C) from calling Wire.begin()
//lcd.begin(false)                 
  lcd.backlight();

  Serial.begin(9600);
  pinMode(2, OUTPUT);//GREEN
	pinMode(3,   OUTPUT);//ORANGE OR YELLOW
	pinMode(4, OUTPUT);//RED
	digitalWrite(2, HIGH);
	delay(500);
	digitalWrite(3,   HIGH);
	delay(500);
	digitalWrite(4, HIGH);
	delay(500);  
 //digitalWrite(2, LOW);
//	delay(500);
//	digitalWrite(3,   LOW);
//	delay(500);
//	digitalWrite(4, LOW);
//	delay(500);  
}
 
void loop(){
  long sum=0;
  for(int i=0;i<10;i++)           //Average the 10 measurements to remove the glitch
      {
      sensorValue=analogRead(GSR);
      sum += sensorValue;
      delay(5);
      }
   gsr_average = sum/10;
  // Serial.write(gsr_average);
   Serial.println(gsr_average);
  lcd.setCursor(0, 0); // Or setting the cursor in the desired position.
  lcd.print("GSR_value:");
  lcd.setCursor(12, 0);  lcd.print(gsr_average);   
  lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
  lcd.print("GEL SOUDAS_MARIA"); 
if (((gsr_average- previous) > 1)){
 
//digitalWrite(BUZZER,LOW);
digitalWrite(2, HIGH);//GREEN   
//   Serial.println("Lie detected");
//digitalWrite(3, LOW);
//digitalWrite(4, LOW);
 }
else {
  digitalWrite(2,   LOW);
}
if ((gsr_average- previous) >= 3){
 
//   digitalWrite(BUZZER,LOW);
  // digitalWrite(2, HIGH);//GREEN   
   digitalWrite(3, HIGH);//YELLOW
  // digitalWrite(4, LOW);  
   Serial.println("Maybe:lie detected");
   lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
   lcd.print("???Lie detected ");
delay(500);
 }
else {
digitalWrite(3,   LOW);  
}
if (((gsr_average- previous) >=4) )  {
 
   digitalWrite(BUZZER,LOW);
   digitalWrite(4, HIGH);
  //digitalWrite(2, HIGH);//GREEN   
  // digitalWrite(3, HIGH);//YELLOW
   Serial.println("Lie detected!!!");
   lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
  lcd.print("!!!Lie detected ");
delay(500);
 } 
 else{
   digitalWrite(4,   LOW);
 }

//delay(500);
 
 previous=gsr_average;

}
