#include <LiquidCrystal.h>


#include <SoftwareSerial.h>
#include "WiFly.h"

#include "HTTPClient.h"


#define SSID      "beaunes"
#define KEY       "simplice971"
#define AUTH      WIFLY_AUTH_WPA2_PSK     // or WIFLY_AUTH_WPA1, WIFLY_AUTH_WEP, WIFLY_AUTH_OPEN


#define HTTP_GET_URL "http://192.168.1.39/index.php?sun=1&water=1000"

// Pins' connection
// Arduino       WiFly
//  2    <---->    TX
//  3    <---->    RX
SoftwareSerial uart(12, 13);
WiFly wifly(&uart);

HTTPClient http;
char get;


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
 //lcd.setCursor(0, 0);  
 //lcd.print("      Eau    ");
 //lcd.print("Tx D'humidité : ");
 Serial.println("Welcome to hydroponic");

  

//wifi init
uart.begin(9600);

  Serial.begin(9600);
  Serial.println("--------- WIFLY TEST --------");

  lcd.print("hydroponic init ...") ; 
  
  // wait for initilization of wifly
  delay(3000);
  
  uart.begin(9600);     // WiFly UART Baud Rate: 9600
  
  wifly.reset();
  
  Serial.println("Join " SSID );
  if (wifly.join(SSID, KEY, AUTH)) {
    Serial.println("OK");
  } else {
    Serial.println("Failed");
  }
  
  // get WiFly params
  wifly.sendCommand("get everthing\r");
  char c;
  while (wifly.receive((uint8_t *)&c, 1, 300) > 0) {
    Serial.print((char)c);
    
  }
  
  if (wifly.commandMode()) {
    Serial.println("Enter command mode. Send \"exit\"(with \\r) to exit command mode");
  }

int i = 10 ; 
while (i > 0)
{
  lcd.print("*") ; 
   delay(100);
   i--; 
}
  
  lcd.print("                              ") ; 



  while (http.get(HTTP_GET_URL, 10000) < 0) {
  }
  while (wifly.receive((uint8_t *)&get, 1, 1000) == 1) {
    Serial.print(get);
  }

 
}

void loop() {


 
 both() ; 

 while (wifly.available()) {
    Serial.println((wifly.read()) );
    
  }
  
  while (Serial.available()) {
    wifly.write(Serial.read());
  }

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
 // Serial.print("sensor = " );  
  lcd.setCursor(0, 0);  
  lcd.print("      eau   ");                       
   Serial.println(waterValue); 
    lcd.setCursor(0, 1);   
   lcd.print("      "); 
   lcd.print(waterValue); 
   lcd.print("%     ");   
 

}

void both ()
{
  
lightValue = analogRead(lightSensor);    
waterValue = 1024 - analogRead(waterSensor); 
 lcd.setCursor(0, 0);  
 lcd.print("Sun level ");  
 lcd.setCursor(13, 0);
 //lcd.print("    ") ; 
 lcd.print(lightValue); 

 
     
  
  lcd.setCursor(0, 1);  
  lcd.print("Water level ");                       
    lcd.setCursor(13, 1);   
   //lcd.print("   "); 
   lcd.print(waterValue); 
  // lcd.print("%     ");   



}


