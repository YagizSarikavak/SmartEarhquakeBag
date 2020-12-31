
#include <Arduino.h>
#include <TinyMPU6050.h>

float pos_offset = 0.5;
float neg_offset = -0.5;
long angle_x, angle_y, angle_z, offset_x, offset_y, offset_z;
MPU6050 mpu (Wire);

int Buzzer =8;
int Led =9;

void setup() {

  // Initialization
  mpu.Initialize();
  pinMode(Buzzer,OUTPUT);
  digitalWrite(Buzzer,LOW);
  pinMode(Led,OUTPUT);
  digitalWrite(Led,LOW);

  // Calibration
  Serial.begin(9600);
  Serial.println("=====================================");
  Serial.println("Starting calibration...");
  mpu.Calibrate();
  Serial.println("Calibration complete!");
  delay(1000);
  for(int i=0; i<200;i++){
   mpu.Execute();
  offset_x = mpu.GetAccX();
  offset_y = mpu.GetAccY();
  offset_z = mpu.GetAccZ();
  }
  Serial.print("offset_x = ");
  Serial.print(offset_x);
  Serial.print("  /  offsetY = ");
  Serial.print(offset_y);
  Serial.print("  /  offsetZ = ");
  Serial.println(offset_z);
  
}

void loop() {

 for(int i=0; i<5;i++){
  mpu.Execute();
  angle_x = mpu.GetAccX();
  angle_y = mpu.GetAccY();
  angle_z = mpu.GetAccZ();
 }

  Serial.print("AngX = ");
  Serial.print(angle_x - offset_x);
  Serial.print("  /  AngY = ");
  Serial.print(angle_y - offset_y);
  Serial.print("  /  AngZ = ");
  Serial.println(angle_z - offset_z);
  

 if ( pos_offset < angle_x - offset_x || neg_offset > angle_x - offset_x || pos_offset < angle_y - offset_y || neg_offset > angle_y - offset_y || pos_offset < angle_z - offset_z || neg_offset > angle_z - offset_z){
 {
  Serial.println("EARTHQUAKE !!!");
  digitalWrite(Led,HIGH);
  digitalWrite(Buzzer,HIGH);
  delay(100);
  digitalWrite(Buzzer,LOW);
  digitalWrite(Led,LOW);
  }
    
 }  
}
