#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>z
#include <Adafruit_Sensor.h>

double gak1 = 0;
int valueY = 0;
int carry = 0;
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
    Serial.print('f');
  }
  else if(onOff == 1){
    Serial.print('o');
  }
}
void modeSelect() {
  mode = ~mode;
   if(mode == -2){
    Serial.print('b');
  }
  else if(mode == 1){
    Serial.print('a');
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
  gak1 = 0.06 * ((int)lsm.accelData.y / 10) + 90;
  valueY = gak1;
  
  if(gak1 <0)
    valueY = 0;
  if(gak1>180)
    valueY = 180;


  if(valueY>=0 && valueY<=20){
    carry =0;
  }
  else if(valueY>20 && valueY<=40){
    carry = 1;
  }
  else if(valueY>40 && valueY<=60){
    carry =2;
  }
  else if(valueY>60 && valueY<=80){
    carry = 3;
  }
  else if(valueY>80 && valueY<=100){
    carry = 4;
  }
   else if(valueY>100 && valueY<=120){
    carry =5;
  }
  else if(valueY>120 && valueY<=140){
    carry =6;
  }
  else if(valueY>140 && valueY<=160){
    carry =7;
  }
  else if(valueY>160 && valueY<=180){
    carry = 8;
  }

  Serial.print(carry); 
  delay(100);
}
