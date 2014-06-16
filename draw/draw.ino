/*
 * touch.ino example for touch functions
 */

#include <ezLCD.h>
#include <SoftwareSerial.h>


EzLCD3_SW lcd( 10, 11 );

void setup()
{
  Serial.begin(9600);
  lcd.begin( EZM_BAUD_RATE ); 
  lcd.calibrate();
  lcd.font(0); 
  lcd.cls(WHITE); // clear screen to white
  lcd.color(BLACK);
  lcd.println("Draw on the Screen");
}

void loop()
{
    int x = lcd.touchX();
    int y = lcd.touchY();
  /*  while(x == 0 && y == 0)
    {
      int x = lcd.touchX();
      int y = lcd.touchY();
      lcd.xy(x,y);
    }*/
  delay(1);
    //if(x>=4 && y>=4 && x<=316 && y<=236 )//extraneous inputs
    if(/*x>=3 && y>=3 && x<=317 && y<=237*/1==1 )//extraneous inputs
    {
      int x2 = lcd.touchX();
      int y2 = lcd.touchY();//for blips
      if(x-x2 <=2 && y-y2 <=2)
      {
      int x3 = lcd.touchX();
      int y3 = lcd.touchY();//for blips
      if(x2-x3 <=2 && y2-y3 <=2)
      {
       lcd.line(x,y);  //draw line from the previous xy location
       lcd.line(x2,y2);  //draw line from the previous xy location
       lcd.line(x3,y3);  //draw line from the previous xy location
      }
      }
    }
}


