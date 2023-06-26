#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);                 // Set the LCD I2C address and the number of columns and rows

const int sensorPin = A0;                           // Analog pin connected to the CO2 sensor

void setup() {
  Serial.begin(9600);                               // Initialize the Serial Monitor
  lcd.begin(16, 2);                                 // Initialize the LCD
  lcd.backlight();                                  // Turn on the backlight
  lcd.print("CO2: ");                               // Initial display message
  
  delay(2000);                                      // Wait for the sensor to warm up
}

void loop() {
  int co2Level = analogRead(sensorPin);             // Read CO2 level from the sensor

  lcd.setCursor(5, 0);                              // Set cursor to the second row, sixth column
  lcd.print("     ");                               // Clear the previous CO2 reading
  lcd.setCursor(5, 0);                              // Set cursor back to the same position
  lcd.print(co2Level);                              // Display the current CO2 level
  
                                                    // Check CO2 level and display appropriate alerts
  if (co2Level > 1000) {
    lcd.setCursor(0, 1);
    lcd.print("ALERT: TAKE A BREAK");
    Serial.println("ALERT: TAKE A BREAK");
    Serial.println();                               // line break in the Serial Monitor
  } else if (co2Level > 700 && co2Level <= 999) {
    lcd.setCursor(0, 1);
    lcd.print("ALERT: OPEN WINDOWS");
    Serial.println("ALERT: OPEN WINDOWS");
    Serial.println();                               // line break in the Serial Monitor
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Air is safe");
    Serial.println("Air is safe");
    Serial.println();                               // line break in the Serial Monitor
  }

                                                    // Print CO2 level to Serial Monitor
  Serial.print("CO2 Level: ");
  Serial.println(co2Level);

  delay(3000);                                      // Wait for 3 seconds before taking the next reading
}
