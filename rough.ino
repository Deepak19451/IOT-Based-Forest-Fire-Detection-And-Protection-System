#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Sensor 2
#define Buzzer 5
#define relay 4

// Initialize the LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(Sensor, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  Serial.println("Temperature Monitor!");

  // Initialize the LCD
  lcd.init();
  lcd.backlight(); // Ensure the backlight is turned on
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DETECTING FIRE");
  delay(2000);

  // Clear the LCD and set cursor position
  lcd.clear();
  lcd.setCursor(0, 0);
  delay(2000);
}

void loop() {
  delay(2000);

  // Custom temperature value (replace with your desired temperature)
  float t = 45.0;
  Serial.print("Temperature:");
  Serial.print(t);
  Serial.println("*C");

  // Display temperature on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(12, 0); // Ensure the cursor position is within the display size
  lcd.print(t);
  delay(2000);

  // Assuming flame sensor reading
  bool value = digitalRead(Sensor);
  Serial.println(value);

  if (value == LOW) {
    if (t > 40.00) {
      digitalWrite(Buzzer, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("*Fire Detected*");
      Serial.println("Fire Detected");
    }
    digitalWrite(relay, LOW);
    delay(10000);
  } else {
    digitalWrite(Buzzer, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Fire");
    Serial.println("No Fire ");
    digitalWrite(relay, HIGH);
    delay(2000);
  }
}
