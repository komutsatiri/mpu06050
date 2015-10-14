//Accel ve gyro degerleri ile olcum
#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int16_t tempAcX,
        tempAcY,
        tempAcZ,
        tempGyX,
        tempGyY,
        tempGyZ;
boolean getFirstValues;
boolean flag;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  getFirstValues = true;
  
}
void loop(){
  flag = false;
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
 
  if(getFirstValues)
  {
    Serial.print("AcX = "); Serial.print(AcX);
    Serial.print(" | AcY = "); Serial.print(AcY);
    Serial.print(" | AcZ = "); Serial.print(AcZ);
    
    Serial.print(" | GyX = "); Serial.print(GyX);
    Serial.print(" | GyY = "); Serial.print(GyY);
    Serial.print(" | GyZ = "); Serial.println(GyZ);
  }
  getFirstValues = false;
  
   if(!getFirstValues)
  {
    if( ((AcX > tempAcX + tempAcX *0.1)| (AcX < tempAcX - tempAcX *0.1)) & ((GyX > tempGyX + tempGyX *0.1)| (GyX < tempGyX - tempGyX *0.1)) )
    {
      Serial.print("AcX = "); Serial.print(AcX);
      Serial.print(" | GyX = "); Serial.print(GyX);
      flag = true;
    }
    if( ((AcY > tempAcY + tempAcY *0.1)| (AcY < tempAcY - tempAcY *0.1)) & ((GyY > tempGyY + tempGyY *0.1)| (GyY < tempGyY - tempGyY *0.1)) )
    {
      Serial.print(" | AcY = "); Serial.print(AcY);
      Serial.print(" | GyY = "); Serial.print(GyY);
      flag = true;
    }
    if( ((AcZ > tempAcZ + tempAcZ *0.1)| (AcZ < tempAcZ - tempAcZ *0.1)) & ((GyY > tempGyY + tempGyY *0.1)| (GyY < tempGyY - tempGyY *0.1)) )
    {
     Serial.print(" | AcZ = "); Serial.print(AcZ);
     Serial.print(" | GyZ = "); Serial.print(GyZ);
     flag = true;
    }
     if(flag)
       Serial.println();
    
    
  }
   if(!flag)
       Serial.println("Veri yok.");
  
  tempAcX=AcX;   tempGyX = GyX;
  tempAcY=AcY;   tempGyY = GyY;
  tempAcZ=AcZ;   tempGyZ = GyZ;
  delay(333);
  
}
