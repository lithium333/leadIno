#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

#define K 16.93

#include <LiquidCrystal.h>

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

const float levels[3][11] = {
  // 0,10%,20%...100% voltages
  {11.59E+3, 11.63E+3, 11.76E+3, 11.87E+3, 11.97E+3, 12.07E+3, 12.18E+3, 12.29E+3, 12.41E+3, 12.53E+3, 12.64+3}, // Flooded Pb-Acid
  {11.63E+3, 11.7E+3, 11.81E+3, 11.96E+3, 12.11E+3, 12.23E+3, 12.41E+3, 12.51E+3, 12.65E+3, 12.78E+3, 12.89E+3}, // Sealed Pb-Acid
  {10.50E+3, 11.51E+3, 11.66E+3, 11.81E+3, 11.95E+3, 12.05E+3, 12.15E+3, 12.30E+3, 12.50E+3, 12.75E+3, 13E+3} // AGM
};

const char* types[3] = {
  "Flooded Lead",
  "Sealed Lead",
  "AGM"
};

void setup() {
  analogReference(INTERNAL);
  lcd.begin(16, 2);
}

void loop() {
  uint16_t sel = analogRead(A1)>>8; // take 2MSB as mode selector
  if(sel==3) sel=0; // avoid 4th state
  uint16_t val = analogRead(A0);
  float val_f = (float)val;
  val_f*=K;
  int it=0;

  while((it<11)&&(val_f>levels[sel][it])) it++; // test all levels

  lcd.clear();
  lcd.print(types[sel]);
  lcd.setCursor(0, 1);
  if(it>0) {
    if(it>10) {
      lcd.print(">100");
    } else {
      lcd.print(it*10);
    }
  } else {
    lcd.print("<0");
  }
  lcd.print("% ("+String(val_f*1E-3)+"V)");
  delay(1000);
}

