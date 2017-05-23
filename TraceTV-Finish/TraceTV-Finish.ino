#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>

double gak1 = 0;
int valueY = 0;
int carry = 0;
int command = 9;
int onOff = 1;
int mode = 1;
int i=0;

Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

void setupSensor()
{
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
}

void powerON() {
  onOff = ~onOff;
  if(onOff == -2){
    command = 9;
    Serial.print(command);
  }
  else if(onOff == 1){
    command = 8;
    Serial.print(command);
  }
}
void modeSelect() {
  mode = ~mode;
   if(mode == -2){
    command = 7;
    Serial.print(command);
  }
  else if(mode == 1){
    command = 6;
    Serial.print(command);
  }
}

void setup()
{  
  Serial.begin(9600);
  attachInterrupt(0, powerON, RISING);
  attachInterrupt(1, modeSelect, RISING);

  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
}

void loop() // run over and over
{
  lsm.read();
  if(Serial.available());
  gak1 = 0.06 * ((int)lsm.accelData.y / 10) + 90;
  valueY = (int)gak1;
  if(gak1 <0)
    valueY = 0;
  if(gak1>180)
    valueY = 180;

  if(valueY>=0 && valueY<=30){
    carry = 0;
  }
  else if(valueY>30 && valueY<=60){
    carry = 1;
  }
  else if(valueY>60 && valueY<=90){
    carry = 2;
  }
  else if(valueY>90 && valueY<=120){
    carry = 3;
  }
  else if(valueY>120 && valueY<=150){
    carry = 4;
  }
  else if(valueY>150 && valueY<=180){
    carry = 5;
  }

  Serial.print(carry); 
  delay(100);
}

