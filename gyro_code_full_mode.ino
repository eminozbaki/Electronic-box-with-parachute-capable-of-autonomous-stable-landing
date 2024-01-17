#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h>
#include <Servo.h>

Adafruit_MPU6050 mpu;
int x = 0;
int y = 0;
int z = 0;

Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4;

int value  = 0;

void setup(void) {
  Serial.begin(115200);
// Başlatmayı dene!
  if (!mpu.begin()) {
    Serial.println("MPU6050 bulunamadı!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 bulundu!");

  // İvmeölçer aralığını +-8G olarak ayarlandı!
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // Gyro aralığını +- 500 derece/sn olarak ayarlandı!
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // Filtre bant genişliğini 21 Hz olarak ayarlandı!
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
  servo1.attach(7);
  servo2.attach(6); 
  servo3.attach(5); 
  servo4.attach(4); 

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
}

void loop() {
  /* Okumalarla birlikte yeni sensör olaylarını al! */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  x = a.acceleration.x;
  y = a.acceleration.y;
  z = a.acceleration.z;

//Serial.print(x);Serial.print(" ");Serial.println(y);
if (x < 10 && x > 0 && y < 4 && y > -4){
  Serial.println("Yukarı yönde");
   value = map(x,  0, 10, 0, 180);
   servo1.write(value);
   Serial.print(value);
  }
else if (x > -10 && x < 0 && y < 4 && y > -4){
  Serial.println("Aşağı yönde");
  value = map(x,  -10, 0, 180, 0);
  servo2.write(value);
  Serial.print(value);
  }

if (y < 10 && y > 0 && x < 4 && x > -4){
  Serial.println("Sağ yönde");
  value = map(y,  0, 10, 0, 180);
  servo3.write(value);
  Serial.print(value);
  }
else if (y > -10 && y < 0  && x < 4 && x > -4){
  Serial.println("Sol yönde");
  value = map(y,  -10, 0, 180, 0);
  servo4.write(value);
  Serial.print(value);
  }
}
