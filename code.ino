#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define GREEN_LED 8
#define RED_LED 9
#define BUZZER 10

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 11);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  lcd.begin(20, 4);
  dht.begin();
  lcd.setCursor(0, 0);
  lcd.print(" Systeme de ");
  lcd.setCursor(0, 1);
  lcd.print(" Refrigeration ");
  delay(2000);
  lcd.clear();
}
void loop() {
  float temp = dht.readTemperature();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp Frigo: ");
  if (isnan(temp)) {
    lcd.print("Erreur");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Capteur HS !");
    delay(2000);
    return;
  }
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C");
  // Température normale
  if (temp >= 5 && temp <= 8) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
    
    lcd.setCursor(0, 1);
    lcd.print("Etat Normal");
  }
  // Température trop basse
  else if (temp < 5) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Temp Trop Basse");
  }
  // Température trop élevée
  else {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Temp Trop Haute");
  }
  delay(2000);
}
