// This file is an Insteon "hello world"... 
// Not pretty, but may be useful for initial testing 
// Before running this, you should ensure you have linked your Insteon device to your Insteon Serial modem.
// Also ensure that you substitute the Insteon switch ID's below (three hex bytes) with your own.


#include <ezLCD.h>
//#include <SoftwareSerial.h>


EzLCD3_SW lcd( 10, 11 );
#include "SoftwareSerial.h"
SoftwareSerial insteonSerial(2, 3);

int inByte = 0;         // incoming serial byte
int zeroByte = 0x00;    // I use this because if I do "insteonSerial.write (0);" instead I get a compile error
boolean status = 0;
int d = 50;
//int d2 = 150;



boolean type = 0; //0 = analog. 1 = digital



int xPos = 25;  // horizontal position
int yPos = 150;   // vertical position
int width = 250;
int height = 35;
int option = 5; // 1=draw horizontal, 2=horizontal disabled, 3=vertical,
                // 4=vertical disabled, 5=horizontal slider,
                // 6=horizontal slider disabled, 7=vertical slider,
                //  8=vertical slider disabled
int max= 500;
int resolution = 5;
int value = 200;
int rate = 0;
void setup()
{
  Serial.begin(9600);
  // start serial port at 19200 bps (this is the speed for Insteon modem)
  insteonSerial.begin(19200);  // use software serial for pins 2 and 3 to communicate with the Insteon Modem
                               // soft serial lets us keep the arduino's serial port open for debugging if we wish 
                               Serial.println("start");
                               

  
  
  lcd.begin( EZM_BAUD_RATE );
  lcd.fontw( 1, "sans24" );
  lcd.theme( GRAY, BLACK, 3, SILVER, SILVER, SILVER, YELLOW, YELLOW, YELLOW, GRAY, GRAY );
  lcd.cls(BLACK);
  lcd.color(WHITE);  
  
  
  lcd.image("room.gif",0,0); 
  
  
  
  if(type)
  {
    lcd.color(1);//black
    lcd.rect(19,22,50, 75 );
  }
  else
  {
    lcd.slider( 1, xPos, yPos, width, height, option, max, resolution, value,1 );
  }
  
insteon_off();
  
}
void loop()
{
if(type)
{
  if(lcd.touchS() == 1)
  {
    int x = lcd.touchX();
    int y = lcd.touchY();
    
    if(x>=0 && x<=89 && y>=0 &&y<=117)
    {
    if(status)
    {
      lcd.color(1);//black
      lcd.rect(19,22,50, 75 );
      insteon_off();
      status = 0;
      //delay(d2);
    }
    else
    {
      lcd.color(YELLOW);//white
      lcd.rect(19,22,50, 75 );
      insteon_on();
      status = 1;    
      //delay(d2);
    }
    }
  }
}
else
{
  rate = lcd.getWidgetValue(1); 
  insteon_var(map(rate,0,500,0,255));
} 
}


void insteon_on()
{
  
 // Turn the Living:Lamp on using HEX command:
 // 02 62 19 08 52 05 11 FF            (NOTE: replace the "19 08 52" with your own Insteon ID)
 // Note, each hex value is converted to decimal (below) before it is written via serial.
 
  insteonSerial.write (2);   // 02 hex 
  delay (d); 
  insteonSerial.write (98);  // 62 hex
  delay (d); 
  insteonSerial.write (24);  // 19 hex (1st byte of Insteon ID) 18
  delay (d); 
  insteonSerial.write (194);   // 08 hex (2nd byte of InsteonID) c2
  delay (d); 
  insteonSerial.write (49);  // 52 hex (3rd byte of InsteonID) 31
  delay (d); 
  insteonSerial.write (5);   // 05 hex
  delay (d); 
  insteonSerial.write (17);  // 11 hex (ON command)
  delay (d); 
  insteonSerial.write (255); // FF hex (ON command)
  
}

void insteon_off()
{
    // Turn off Living:Lamp using HEX command
  // 02 62 19 08 52 05 13 00   (note: replace "19 08 52" with your own insteon ID)
    
  insteonSerial.write (2);   // 02 hex
  delay (d); 
  insteonSerial.write (98);  // 62 hex
  delay (d); 
  insteonSerial.write (24);  // 19 hex  (1st byte of Insteon ID)
  delay (d); 
  insteonSerial.write (194);   // 08 hex  (2nd byte of Insteon ID)
  delay (d); 
  insteonSerial.write (49);  // 52 hex  (3rd byte of Insteon ID)
  delay (d); 
  insteonSerial.write (5);   // 05 hex
  delay (d); 
  insteonSerial.write (19);  // 13 hex  (OFF command)
  delay (d); 
  insteonSerial.write (zeroByte);   // 00 hex   (OFF command)
}

void insteon_var(int var)
{
  
 // Turn the Living:Lamp on using HEX command:
 // 02 62 19 08 52 05 11 FF            (NOTE: replace the "19 08 52" with your own Insteon ID)
 // Note, each hex value is converted to decimal (below) before it is written via serial.
 
  insteonSerial.write (2);   // 02 hex 
  delay (d); 
  insteonSerial.write (98);  // 62 hex
  delay (d); 
  insteonSerial.write (24);  // 19 hex (1st byte of Insteon ID) 18
  delay (d); 
  insteonSerial.write (194);   // 08 hex (2nd byte of InsteonID) c2
  delay (d); 
  insteonSerial.write (49);  // 52 hex (3rd byte of InsteonID) 31
  delay (d); 
  insteonSerial.write (5);   // 05 hex
  delay (d); 
  insteonSerial.write (17);  // 11 hex (ON command)
  delay (d); 
  insteonSerial.write (var); // FF hex (ON command)
  
}
