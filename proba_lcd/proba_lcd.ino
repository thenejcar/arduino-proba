
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup()
{
  // initialize the LCD
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.cursor_on();
  lcd.printstr("Hello, world!");

  pinMode(1, OUTPUT); //set the speaker as output
   analogWrite(1, HIGH); //turn the speaker on
   delay(500);                     //wait for half a second
   analogWrite(1, LOW); //turn the speaker off
   delay(500);                    //wait for half a second

}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
