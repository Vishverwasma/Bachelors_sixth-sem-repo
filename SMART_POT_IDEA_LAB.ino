
/*
  SMART POT
  IDEA LAB BIT DURG

  FACULTY INCHARGE
  PROF. ANUPAM AGRAWAL
 
  BY 
  AYUSH KUMAR GUPTA  CSE     6TH SEM
  PIYUSH KUMAR SAHU  EE      4TH SEM
  DIVYA              IT      4TH SEM
  JAYANT KUMAR       MECH    4TH SEM
  OJASWI SAHU        ETC     6TH SEM
  VISHWAS VERMA      ETC     6TH SEM
  MONIKA SHARMA      MCA     2ND SEM
*/

// Include Libraries
#include "Arduino.h"
#include "SoilMoisture.h"
#include "dht.h"
#define dht_apin A0 // Analog Pin sensor is connected to
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
dht DHT;

// Pin Definitions
#define SOILMOISTURE_5V_PIN_SIG  A3 //SOIL MOISTURE SURE
#define IN1 7      //IN1 MD
#define IN2 3        //IN2 MD 
#define IN3 4          //IN3 MD
#define IN4 5          //IN4 MD
#define POWER_PIN  8
#define SIGNAL_PIN A2
#define greenled 2
#define redled 12

int value = 0;
int show =0;
// Global variables and defines

// object initialization
SoilMoisture soilMoisture_5v(SOILMOISTURE_5V_PIN_SIG);
// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
  pinMode(IN1 , OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
  
    lcd.begin();
  lcd.backlight();
  lcd.clear();
   lcd.setCursor(0,0);
lcd.print("Welcome to ");
lcd.setCursor(0,1);
lcd.print("SMART POT");
delay(3000);lcd.clear();
lcd.setCursor(0,0);
lcd.print("IDEA LAB  ");
lcd.setCursor(0,1);
lcd.print("BIT DURG");
delay(4000);
lcd.clear();             //INITIAL MESSAGE
    
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{  

    
   int soilMoisture_5vVal = soilMoisture_5v.read();
   Serial.print(F("Val: ")); Serial.println(soilMoisture_5vVal); //SOIL SENSOR
    if(soilMoisture_5vVal>600) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

       lcd.clear();
   lcd.setCursor(0,0);
lcd.print("SOIL MOISTURE ");
lcd.setCursor(0,1);
lcd.print("IS LOW");
 delay(2000);
 lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("MOTOR ON...");
   delay(2000);
 lcd.clear();
    

    }


 else {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  lcd.clear();
   lcd.setCursor(0,0);
lcd.print("SOIL MOISTURE");
lcd.setCursor(0,1);
lcd.print("IS GOOD");
 delay(2000);
 lcd.clear();
 }
 digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);  
  // turn the sensor OFF
show = value/5;
if (value>500)
{show =100;}
  
  Serial.print(F("Water sensor.....- ")); Serial.println(value);
  if(value>150)
  {digitalWrite(greenled, HIGH);
  digitalWrite(redled, LOW);
  

  lcd.clear();
   lcd.setCursor(0,0);
lcd.print("WATER TANK");
lcd.setCursor(0,1);
lcd.print("CAPACITY: ");
lcd.print(show);
lcd.print(" %");
   delay(1000);
 lcd.clear();
  
  
  }
  else if (value<200)
  {
  
  lcd.clear();
   lcd.setCursor(0,0);
lcd.print("WATER TANK");
lcd.setCursor(0,1);
lcd.print("CAPACITY: ");
lcd.print(show);
lcd.print(" %");
 delay(1000);
 lcd.clear();
 digitalWrite(greenled, LOW);
  digitalWrite(redled, HIGH);
  delay(1000);
  digitalWrite(greenled, LOW);
  digitalWrite(redled, LOW);
  delay(1000);
  digitalWrite(greenled, LOW);
  digitalWrite(redled, HIGH);
  delay(1000);
  digitalWrite(greenled, LOW);
  digitalWrite(redled, HIGH);
  delay(1000);
  digitalWrite(greenled, LOW);
  digitalWrite(redled, LOW);
  delay(1000);
  digitalWrite(greenled, LOW);
  digitalWrite(redled, HIGH);
  delay(1000);
  digitalWrite(greenled, LOW);
  digitalWrite(redled, LOW);
   delay(1000);
   digitalWrite(greenled, LOW);
  digitalWrite(redled, HIGH);
  
  
  
  }

  DHT.read11(dht_apin);
    
    Serial.print("Current humidity : ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature : ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(2000);

   lcd.clear();
   lcd.setCursor(0,0);
lcd.print("Humidity: ");
lcd.print(DHT.humidity);
lcd.print("%  ");
 lcd.setCursor(0,1);
lcd.print("Temp:     ");
lcd.print(DHT.temperature); 
lcd.println("C");
delay(2000);
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Soil Moisture Sensor"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing Soil Moisture Sensor"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
