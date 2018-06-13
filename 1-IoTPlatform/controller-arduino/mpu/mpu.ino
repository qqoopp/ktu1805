#include<Wire.h>

//GPIO******************** 
int pinSCL = A5;
int pinSDA = A4;
//********************GPIO 

//MPU******************** 
#define MPU6050_REG_GYRO_CONFIG       (0x1B) // Gyroscope Configuration
#define MPU6050_REG_ACCEL_CONFIG      (0x1C) // Accelerometer Configuration
#define MPU6050_REG_PWR_MGMT_1        (0x6B) // Power Management 1
const int MPU = 0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float acx, acy, acz, gyx, gyy, gyz;
uint8_t gyroval, accelval;
float gyrodiv, acceldiv;
//********************MPU

typedef enum
{
    MPU6050_GYRO_2000DPS         = 0b11,
    MPU6050_GYRO_1000DPS         = 0b10,
    MPU6050_GYRO_500DPS          = 0b01,
    MPU6050_GYRO_250DPS          = 0b00
} mpu6050_dps_t;

typedef enum
{
    MPU6050_ACCEL_16G             = 0b11,
    MPU6050_ACCEL_8G              = 0b10,
    MPU6050_ACCEL_4G              = 0b01,
    MPU6050_ACCEL_2G              = 0b00,
} MPU6050_ACCEL_t;

void setup(){
  Serial.begin(9600);  
  setup_mpu();
}

void loop(){
  loop_mpu();
  delay(1000);
}

void setup_mpu(){

  Wire.begin();   
  Wire.beginTransmission(MPU); 
  Wire.write(MPU6050_REG_PWR_MGMT_1);  // PWR_MGMT_1 register
  Wire.write(0);     
  Wire.endTransmission(true); 

  gyroval = MPU6050_GYRO_250DPS;
  accelval = MPU6050_ACCEL_2G;
  setSensitivity( gyroval, accelval ); //sensitivity setting
}

void loop_mpu(){

  Wire.beginTransmission(MPU);   
  Wire.write(0x3B);               // register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);   
  Wire.requestFrom(MPU,14,true);  
  
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)   
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  switch(accelval){
    case MPU6050_ACCEL_16G:
        acceldiv = 2048.0;
        break;
      case MPU6050_ACCEL_8G:
        acceldiv = 4096.0;
        break;
      case MPU6050_ACCEL_4G:
        acceldiv = 8192.0;
        break;
      case MPU6050_ACCEL_2G:
        acceldiv = 16384.0;
        break;
  }
   
  acx = AcX / acceldiv;
  acy = AcY / acceldiv; 
  acz = AcZ / acceldiv;

    switch(gyroval){
      case MPU6050_GYRO_2000DPS:
        gyrodiv = 16.4;
        break;
      case MPU6050_GYRO_1000DPS:
        gyrodiv = 32.8;
        break;
      case MPU6050_GYRO_500DPS:
        gyrodiv = 65.5;
        break;
      case MPU6050_GYRO_250DPS:
        gyrodiv = 131.0;
        break;
  }
  
  gyx = GyX / gyrodiv;
  gyy = GyY / gyrodiv; 
  gyz = GyZ / gyrodiv;
  
  Serial.print("ACX = "); Serial.print(acx);
  Serial.print(" AcY = "); Serial.print(acy);
  Serial.print(" AcZ = "); Serial.print(acz);
  //Serial.print(" Tmp = "); Serial.print(Tmp/340.00+36.53);  
  Serial.print(" GyX = "); Serial.print(gyx);
  Serial.print(" GyY = "); Serial.print(gyy);
  Serial.print(" GyZ = "); Serial.println(gyz);
}

void setSensitivity(uint8_t gyro, uint8_t accel){
    Wire.beginTransmission(MPU);
    Wire.write(MPU6050_REG_GYRO_CONFIG);
    Wire.write(gyro);
    Wire.endTransmission();
    Wire.beginTransmission(MPU);
    Wire.write(MPU6050_REG_ACCEL_CONFIG);
    Wire.write(accel);
    Wire.endTransmission();
}

