#include "BluetoothSerial.h"
#include<M5Stack.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

//****ディスプレイの初期化作業****
void LcdInit() {
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(0, 0);
}



void setup() {
  M5.begin();
  randomSeed(analogRead(0));
  //Serial.begin(115200);
  SerialBT.begin("M5stack");
  M5.Lcd.println("device start");
  pinMode(13, OUTPUT);
  pinMode(15, INPUT_PULLUP);
}

char databox;
void loop() {
  /*int onof1 = M5.BtnA.read() ;
  int onof2 = M5.BtnB.read() ;
  M5.Lcd.println("M5.BtnA.read()");
  if (onof1 == 1) {
    Serial.println("LED is ON.");
    SerialBT.write('T');
  }
  if ( onof2 == 1) {
   M5.Lcd.println("LED is OFF.");
    SerialBT.write('L');
  }*/



  if (SerialBT.available()) {
    databox = SerialBT.read();
    Serial.println(databox);

    if (databox == 'L') {
      long x = random(0, 320);
      long y = random(0, 240);
      long r = random(10, 200);
      M5.Lcd.drawCentreString("Hello",x - r, y - r, y + r);
      //M5.Lcd.drawCircle(x, y, r, TFT_GREEN);
      delay(1000);
      LcdInit();
      M5.update();
      M5.Lcd.println("ok");
    }
    if (databox == 'T') {
      M5.Lcd.println("dame");
      delay(1000);
      LcdInit();
     // M5.Lcd.fillScreen(BLACK);
    }
  }
  M5.update();
  delay(20);
}
