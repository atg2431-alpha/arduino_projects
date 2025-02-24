#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>

// Create BMP3XX object
Adafruit_BMP3XX bmp;

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for serial port to initialize

  // Initialize I2C
  if (!bmp.begin_I2C()) {  // Use `bmp.begin_SPI()` for SPI communication
    Serial.println("Could not find a valid BMP390 sensor, check wiring!");
    while (1);
  }

  // Configure sensor settings
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);

  Serial.println("BMP390 initialized!");
}

void loop() {
  if (!bmp.performReading()) {
    Serial.println("Failed to perform reading!");
    return;
  }

  Serial.print("Temperature = ");
  Serial.print(bmp.temperature);
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(bmp.pressure / 100.0);  // Convert to hPa
  Serial.println(" hPa");

  delay(1000);
}
