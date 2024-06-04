#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <BMP280_DEV.h>

// iki yo butuh modul jam tapi
LiquidCrystal_I2C layar(0x27, 16,2);
DS3231 jam;

                           // Include the BMP280_DEV.h library

float temperature, pressure, altitude;            // Create the temperature, pressure and altitude variables
BMP280_DEV bmp280;                                // Instantiate (create) a BMP280_DEV object and set-up for I2C operation (address 0x77)


bool CenturyBit;
bool h12;
bool hPM;

int detik;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  bmp280.begin(BMP280_I2C_ALT_ADDR);
  layar.init();
  layar.backlight();
  
  detik = jam.getSecond();
  bmp280.setSeaLevelPressure(1011);
  // pressure kamar = 976.1

}

void loop() {
  // put your main code here, to run repeatedly:

  if(detik != jam.getSecond()){
    detik = jam.getSecond();
  
  layar.setCursor(0,0);
  layar.print(jam.getDate());
  layar.print("-");
  layar.print(jam.getMonth(CenturyBit));
  layar.print("-");
  layar.print(jam.getYear());

  layar.print(" ");
 
  layar.print(jam.getHour(h12, hPM));
  layar.print(":");
  if (jam.getMinute() <10) layar.print("0");
  layar.print(jam.getMinute());
  layar.print(":");
  if (detik <10) layar.print("0");
  layar.print(detik);

  
  layar.setCursor(0,1);
  layar.print("Altitude : ");
  
  bmp280.startForcedConversion();
    if (bmp280.getMeasurements(temperature, pressure, altitude)){
    
      layar.print(altitude);
    

    
    }else{
      bmp280.getCurrentMeasurements(temperature, pressure, altitude);
     
      layar.print(altitude);
     
 
    }
    
  }
}
