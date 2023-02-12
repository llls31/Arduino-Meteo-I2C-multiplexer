#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_SSD1306.h>

#define TCAADDR 0x70            // address  Multiplexer - TCA9548A
#define BMP280_Address 0x76     // address BMP280
#define OLED_Address 0x3C       // address OLED 128x32 IIC I2C Blue OLED LCD Display DIY

Adafruit_BMP280 BMP280;
Adafruit_SSD1306 OLED (1);

void TCA9548A(uint8_t bus) {
    Wire.beginTransmission (TCAADDR);
    Wire.write(1 << bus);
    Wire.endTransmission();
}

double temperature(Adafruit_BMP280 BMP280, int bus) {
    TCA9548A(bus);
    return BMP280.readTemperature();
}

void printValues(double temp, int bus) { // print temp OLED display
    TCA9548A(bus);
    Serial.print("Temperature = ");
    Serial.print(temp);
    Serial.println(" *C");
    OLED.begin();
    OLED.clearDisplay();
    OLED.setTextColor(WHITE);
    OLED.setCursor(0,0);
    OLED.println("Display 3.");
    OLED.setTextSize(2);
    OLED.setCursor(0,16);
    OLED.println(temp);
    OLED.setTextSize(1);
    OLED.display();
    delay(5000); // Wait 10 sec.
}

void setup() {
    Serial.begin(9600);
    TCA9548A(2);
    if(!BMP280.begin(BMP280_Address)) {
        Serial.println("Could not find a valid BME280 sensor on bus 2, check wiring!");
        while (1);
    }

    TCA9548A(3);
    if(!OLED.begin(SSD1306_SWITCHCAPVCC, OLED_Address)) {
        Serial.println("Could not find a valid Display sensor on bus 3, check wiring!");
        while (1);
    }

}

void loop() {
    TCA9548A(2);//Text to OLED display 3
    double temp = temperature(BMP280 , 2);
    TCA9548A(3);//Text to OLED display 3

    printValues(temp,3);


}

