#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

void setup()
{
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
}

void   loop()
{
 // Serial.println(analogRead(A0));
  lcd.setCursor(0, 0); // Or setting the cursor in the desired position.
  lcd.print("GSR_value:");
  lcd.setCursor(12, 0);  lcd.print(analogRead(A0));   
  lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
  lcd.print("GEL SOUDAS_MARIA");   
	if (analogRead(A0) > 60)
	{
		digitalWrite(4, HIGH);//RED
Serial.println("Lie detected!!!");
   lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
  lcd.print("!!!Lie detected ");    
	}
	else
	{
		digitalWrite(4,   LOW);
	}
	if (analogRead(A0) > 20)
	{
		digitalWrite(2, HIGH);//GREEN
	}
	else
	{
		digitalWrite(2,   LOW);
	}
	if (analogRead(A0) > 45)
	{
		digitalWrite(3, HIGH);//YELLOW
Serial.println("Maybe:lie detected");
   lcd.setCursor(0, 1); // Or setting the cursor in the desired position.
   lcd.print("???Lie detected ");    
	}
	else
	{
		digitalWrite(3,   LOW);
	}

	Serial.println(analogRead(A0));
	delay(20);
}