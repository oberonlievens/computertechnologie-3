#include <Wire.h>
#define TMP102_I2C_ADDRESS 72

void setup() {
  Wire.begin(); // start the I2C library
  Serial.begin(9600);
  Serial.println("Arduino Ready");
  setConf();
}

void setConf(){
  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x02);
  Wire.write(28); //TLOW
  Wire.endTransmission();

  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x03); //THIGH
  Wire.write(28);
  Wire.endTransmission();

}

void getTemp(){
  byte firstbyte, secondbyte;
  int val;
  float convertedtemp;
  float correctedtemp;

  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x00);
  Wire.requestFrom(TMP102_I2C_ADDRESS, 2);
  Wire.endTransmission();

  firstbyte = (Wire.read());
  secondbyte = (Wire.read());
    val = ((firstbyte) << 4);
    val |= (secondbyte >> 4);
    convertedtemp = val*0.0625;
    correctedtemp = convertedtemp;

  Serial.print(correctedtemp);
  Serial.println("°C");
}

void loop() {
  getTemp();
  delay(250);
}
