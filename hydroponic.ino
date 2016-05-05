#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// LiquidCrystal lcd( RS, E, D4, D5, D6, D7);
int lcd4RS = 10, // Arduino Pin 10. LCD pin 4 is RS.
lcd6E = 9,  // Arduino Pin 9. LCD H/L Enable.
lcd11D4 = 5, // Arduino Pin 5.
lcd12D5 = 4, // Arduino Pin 4.
lcd13D6 = 3, // Arduino Pin 3.
lcd14D7 = 2; // Arduino Pin 2.
LiquidCrystal lcd(lcd4RS, lcd6E, lcd11D4, lcd12D5, lcd13D6, lcd14D7);
int potOut;

//sensor d'humidité..
int waterSensor = A0;    // select the input pin for the potentiometer
int waterValue = 0;  // variable to store the value coming from the sensor

int lightSensor = A1 ; 
int lightValue = 0 ; 

int temperature = A3 ; 
int temValue = 0 ; 

void setup() {
 Serial.begin(9600);
 // set up the LCD's number of rows and columns: 
 lcd.begin(16, 2);
 // Print a message to the LCD.
 lcd.setCursor(0, 0);  
 lcd.print("      Eau    ");
 //lcd.print("Tx D'humidité : ");
 Serial.println("Welcome to Lesson 19: LED Proof.");

  

 
}

void loop() {
potOut = analogRead(A5); // Values of 0-1023.
Serial.print(millis()/1000.); 
Serial.print("  Pot Output = "); Serial.println(potOut);

 // set the cursor to column 0, line 1
 // (note: line 1 is the second row, since counting begins with 0):
 lcd.setCursor(0, 1);
 // print the number of seconds since reset:


 // humidite() ; 
 light() ; 

  delay(1000);
}



void light ()
{

 lightValue = analogRead(lightSensor);    
 lcd.setCursor(0, 0);  
 lcd.print("      Lumiere   ");  
 lcd.setCursor(0, 1);
 lcd.print("      ") ; 
 lcd.print(lightValue); 

}

void humidite ()
{
 // read the value from the sensor:
  waterValue = 1024 - analogRead(waterSensor);        
  Serial.print("sensor = " );  
  lcd.setCursor(0, 0);  
  lcd.print("      eau   ");                       
   Serial.println(waterValue); 
    lcd.setCursor(0, 1);   
   lcd.print("      "); 
   lcd.print(waterValue); 
   lcd.print("%     ");   
 

}




