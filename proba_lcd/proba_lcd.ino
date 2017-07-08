
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/*
  Program prebere sporocilo do 63 znakov s serijske konzole
  Sporocilo izpise v zgornjo vrstico
  V spodnji vrstici je stevec sekund, indikator za gumb, pozicija in dolzina sporocila
*/


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3f, 16, 2);

char *letters;
int len = 0;
int pos = 0;
int btn = 0;

int seconds = 0;
int lucka = 0;

void setup()
{
  // initialize the LCD
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.cursor_on();
  lcd.printstr("Hello, world!");

  Serial.begin(9600);

  letters = (char*) malloc (64 * sizeof(char));
  sprintf(letters, "Tole je eno dolgo sporocilo.");
  len = 28;

  pinMode(2, INPUT);
  pinMode(10, OUTPUT);

}

void loop() {
  if (Serial.available()) {
    lcd.clear();
    lcd.setCursor(0,0);

    int i=0;
    while(Serial.available() > 0) {
      letters[i] = Serial.read();
      i++;
      if (i >= 63) {
        // too many chars
        break;
      }
    }
    len = i;
    letters[i] = 0; // null terminator
    pos = 0;
  }

  // preberi gumb na pinu 2, ob fronti premakni display
  if (btn == 0 && digitalRead(2) == HIGH) {
    btn = 1;
    pos = (pos + 1) % len;
  } else if (btn == 1 && digitalRead(2) == LOW) {
    btn = 0;
  }

  print16();
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  int sec_tmp = millis() / 1000;
  if (sec_tmp > seconds) {
    lucka = (lucka + 1) % 2;
    if (lucka)
      digitalWrite(10, HIGH); // ledica na pinu 10
    else
      digitalWrite(10, LOW);
  }
  seconds = sec_tmp;
  lcd.print(seconds);

  
  lcd.print(" ");
  lcd.print(btn);
  lcd.print(" ");
  lcd.print(pos);
  lcd.print(" ");
  lcd.print(len);
  lcd.print(" ");
}

// izpise 16 znakov naprej od 'pos', potem pa zacne od zadaj
void print16() {  
  if (len <= 16) {
    lcd.setCursor(0,0);
    lcd.print(letters);
  } else {
    for (int i=0; i<16; i++) {
        lcd.setCursor(i,0);
        if (pos + i < len) {
          lcd.write(letters[pos+i]);
          Serial.print(letters[i]);
        } else if (pos + i == len) {
          lcd.write(' ');
          Serial.print(' ');
        } else {
          lcd.write(letters[(pos + i - 1) % len]);
          Serial.print(letters[(pos + i - 1) % len]);
        }
    }
    Serial.println("");
  }
}

