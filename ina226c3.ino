// #define printdebug true
#include "INA226.h"
#include "WiFi.hpp"

#include <Wire.h>
#include "ER_OLEDM1_CH1115.hpp"

// Contrast 00 to FF , 0x80 is default. user adjust
#define OLEDcontrast 0x80

// GPIO 5-wire SPI interface
#define RES 5 // GPIO pin number pick any you want
#define DC 4  // GPIO pin number pick any you want
#define CS 10 // GPIO pin number pick any you want
// GPIO pin number SDA(UNO 11) , HW SPI , MOSI
// GPIO pin number SCK(UNO 13) , HW SPI , SCK

// Buffer setup
#define MYOLEDHEIGHT 64
#define MYOLEDWIDTH 128
#define FULLSCREEN (MYOLEDWIDTH * (MYOLEDHEIGHT / 8))
uint8_t screenBuffer[FULLSCREEN];
ERMCH1115 myOLED(MYOLEDWIDTH, MYOLEDHEIGHT, DC, RES, CS);
// instantiate an Shared buffer object , only one in this case to cover whole screen
ERMCH1115_SharedBuffer fullScreen(screenBuffer, MYOLEDWIDTH, MYOLEDHEIGHT, 0, 0);

INA226 INA(0x40);
double sum = 0.0;
uint8_t delayTime = 100;
uint32_t prevTime = 0;
uint8_t tempSumTime = 0;
float tempSum = 0.0;
float coff = 4.045;
void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  if (!WiFi.softAP(ssid, password))
  {
    log_e("Soft AP creation failed.");
    while (1)
      ;
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  InitServer();

  // delay(5000);
  Wire.begin(2, 3);
  delay(100);
  if (!INA.begin())
  {
    Serial.println("could not connect. Fix and Reboot");
    while (1)
      ;
  }
  Serial.print("Init Res");
  Serial.println(INA.setMaxCurrentShunt(78.6432, 0.001, false));

  myOLED.OLEDbegin(OLEDcontrast); // initialize the OLED
  myOLED.OLEDFillScreen(0x3F, 0); // Splash  screen
  delay(1500);
  myOLED.setTextColor(OLED_WHITE);
  myOLED.setTextSize(1);
  myOLED.setFontNum(CH1115Font_Default);
  myOLED.ActiveBufferPtr = &fullScreen; // Assign Buffer to be the active buffer pointer
  Serial.println("Ready");
}

void loop()
{
  server.handleClient();
  if (millis() > prevTime)
  {
    prevTime += delayTime;
    Reset();
    myOLED.setFontNum(CH1115Font_Default);
    myOLED.setTextSize(2);
    myOLED.setCursor(0, 0);

    myOLED.print(F("V:"));
    myOLED.println(INA.getBusVoltage() * coff, 3);

    float curr = INA.getCurrent();
    if (curr < 0)
    {
      curr = -curr;
    }
    myOLED.print(F("A:"));
    myOLED.println(curr, 3);

    myOLED.print(F("P:"));
    double pwr = coff * curr * INA.getBusVoltage();
    myOLED.println(pwr, 3);

    myOLED.print(F("Sum:"));
    sum += (pwr * (delayTime / 1000.0) / 3600.0);
    myOLED.println(sum, 3);

    myOLED.print(F("Temp:"));
    myOLED.print(tempSum / tempSumTime, 3);
    // display.display();

    // Serial.print(INA.getBusVoltage());
    // Serial.print("\t");
    // Serial.print(INA.getShuntVoltage_mV(), 3);
    // Serial.print("\t");
    // Serial.print(INA.getCurrent() * coff, 3);
    // Serial.print("\t");
    // Serial.print(INA.getPower() * coff, 3);
    // Serial.print("\t");
    // Serial.print(sum, 3);
    // Serial.println();
  }
}
void Reset(void)
{
  myOLED.OLEDupdate(); // Write to the buffer
  delay(100);
  myOLED.OLEDclearBuffer();
}