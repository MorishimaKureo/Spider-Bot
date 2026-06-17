// ==========================================
// KODE UNTUK ROBOT (RECEIVER + PCA9685)
// ==========================================

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50 

// Pemetaan Channel Servo di PCA9685
const int FR1_CH = 0;  
const int FR2_CH = 1;  
const int FL1_CH = 2;  
const int FL2_CH = 3;  
const int BR1_CH = 4;  
const int BR2_CH = 5;  
const int BL1_CH = 6;  
const int BL2_CH = 7;  

struct DataPaket {
  char perintah;
};

DataPaket dataMasuk;
volatile char perintahAktif = 'S'; // Menyimpan perintah aktif saat ini

void setServoAngle(int channel, int angle) {
  if(angle < 0) angle = 0;
  if(angle > 180) angle = 180;
  int pulse = map(angle, 0, 180, 150, 600);
  pwm.setPWM(channel, 0, pulse);
}

// Variable Posisi asli
int fr1;
int fr2;
int fl1;
int fl2;
int br1;
int br2;
int bl1;
int bl2;

// Prototipe Fungsi
void down();
void up();
void dance();
void STRECHING();
void dance_queen();
void step1();
void step2();
void i_dont_now();

// Prototipe Fungsi Gerakan Baru dari Remote
void maju_terus();
void mundur_terus();
void strafe_kiri();
void strafe_kanan();
void putar_kiri();
void putar_kanan();
void jump();

// Callback ESP-NOW ketika menerima data dari remote
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&dataMasuk, incomingData, sizeof(dataMasuk));
  perintahAktif = dataMasuk.perintah;
  
  Serial.print("Menerima: ");
  Serial.println(perintahAktif);
}

void setup(){
  Serial.begin(9600);
  
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("Gagal menginisialisasi ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

  delay(3000);
  up(); // Posisi awal robot berdiri
  Serial.println("Robot Siap.");
}

void loop(){
  // Menangani perintah berdasarkan tombol remote yang ditekan
  switch (perintahAktif){
    case 'U':
      maju_terus(); // Akan looping terus selama perintahAktif == 'U'
      break;
    case 'N':
      mundur_terus(); // Akan looping terus selama perintahAktif == 'N'
      break;
    case 'L':
      strafe_kiri();
      perintahAktif = 'S'; // Kembalikan ke standby setelah sekali eksekusi
      break;
    case 'R':
      strafe_kanan();
      perintahAktif = 'S';
      break;
    case 'Q':
      putar_kiri();
      perintahAktif = 'S';
      break;
    case 'E':
      putar_kanan();
      perintahAktif = 'S';
      break;
    case 'A':
      jump();
      perintahAktif = 'S';
      break;
    case 'B':
      // Mengaktifkan fitur dance asli kamu
      for(int i = 0; i < 2; i++){
        dance();
      }
      up();
      perintahAktif = 'S';
      break;
    case 'C':
      // Mengaktifkan fitur stretch dan dance queen asli kamu
      STRECHING();
      delay(200);
      dance_queen();
      delay(100);
      down();
      perintahAktif = 'S';
      break;
    case 'D':
      up(); // Stand / Berdiri
      perintahAktif = 'S';
      break;
    case 'S':
      // Posisi standby diam (bisa dipanggil up() atau dikosongkan agar menahan posisi terakhir)
      break;
  }
  delay(10);
}

// ==========================================
// TAMBAHAN FUNGSI GERAKAN BARU 
// (Silakan isi logika koordinat servo kamu di sini)
// ==========================================

void maju_terus() {
  // Contoh: kamu bisa pakai gabungan step1() dan step2() kamu di sini agar melangkah maju terus
  step1();
  if(perintahAktif != 'U') return; // Interupsi jika tombol dilepas di tengah langkah
  step2();
}

void mundur_terus() {
  // Isi logika melangkah mundur di sini
}

void strafe_kiri() {
  // Isi logika jalan menyamping ke kiri di sini
}

void strafe_kanan() {
  // Isi logika jalan menyamping ke kanan di sini
}

void putar_kiri() {
  // Isi logika putar di tempat ke kiri di sini
}

void putar_kanan() {
  // Isi logika putar di tempat ke kanan di sini
}

void jump() {
  // Isi logika gerakan melompat singkat di sini
}


// ==========================================
// FUNGSI GERAKAN ASLI (TIDAK ADA YANG DIUBAH)
// ==========================================

void step1(){
  br2 = 125;
  fr2 = 125;
  for(fr1 = 80; fr1 <= 100; fr1 += 2){
    setServoAngle(FR1_CH, fr1);
    setServoAngle(FR2_CH, fr2);
    delay(50);

    fr2 -= 2;
  }
  delay(1000);
  for(br1 = 100; br1 > 80; br1 -= 2){
    setServoAngle(BR1_CH, br1);
    setServoAngle(BR2_CH, br2);

    br2 -= 2;
    delay(50);
  }
}

void step2(){
  bl2 = 125;
  fl2 = 125;
  for(fl1 = 100; fl1 > 80; fl1 -= 2){
    setServoAngle(FL1_CH, fl1);
    setServoAngle(FL2_CH, fl2);
    delay(50);

    fl2 -= 2;
  }
  delay(1000);
  for(bl1 = 80; bl1 < 100; bl1 += 2){
    setServoAngle(BL1_CH, bl1);
    setServoAngle(BL2_CH, bl2);

    bl2 -= 2;
    delay(50);
  }
}

void i_dont_now(){
  fr1 = 80;
  br1 = 80;
  fl1 = 80;
  bl1 = 80;
  fr2 = 110;
  br2 = 110;
  fl2 = 110;
  bl2 = 110;
  
  for(fl2 = 110; fl2 > 55; fl2 -= 2){
    setServoAngle(FL2_CH, fl2);
    setServoAngle(BR2_CH, br2);

    br2 -= 2;
    delay(50);
  }
  for(fr1 = 80; fr1 < 120; fr1 +=2){
    setServoAngle(FR2_CH, fr2);
    setServoAngle(BL2_CH, bl2);
    setServoAngle(FR1_CH, fr1);
    setServoAngle(BL1_CH, bl1);
    
    bl1 += 2;
    fr2 += 2;
    bl2 += 2;  
    delay(50);
  }
  delay(100);
  for(fr1 = 120; fr1 > 80; fr1 -=2){
    setServoAngle(FR2_CH, fr2);
    setServoAngle(BL2_CH, bl2);
    setServoAngle(FR1_CH, fr1);
    setServoAngle(BL1_CH, bl1);
    
    bl1 -= 2;
    fr2 -= 2;
    bl2 -= 2;  
    delay(50);
  }
  //=========================================
  for(fr2 = 110; fr2 > 55; fr2 -= 2){
    setServoAngle(FR2_CH, fr2);
    setServoAngle(BL2_CH, bl2);

    bl2 -= 2;
    delay(50);
  }
  for(fl1 = 50; fl1 < 90; fl1 +=2){
    setServoAngle(FL1_CH, fl1);
    setServoAngle(BR1_CH, br1); 
    setServoAngle(FL2_CH, fl2);
    setServoAngle(BR2_CH, br2);
    
    br1 += 2;
    fl2 += 2;
    br2 += 2;
    delay(50);
  }
  delay(100);
  for(fr1 = 90; fr1 > 50; fr1 -=2){
    setServoAngle(FL1_CH, fl1);
    setServoAngle(BR1_CH, br1); 
    setServoAngle(FL2_CH, fl2);
    setServoAngle(BR2_CH, br2);
    
    br1 -= 2;
    fl2 -= 2;
    br2 -= 2;
    delay(50);
  }
}

void down(){
    setServoAngle(FR1_CH, 90);
    setServoAngle(FR2_CH, 50);
    setServoAngle(FL1_CH, 90);
    setServoAngle(FL2_CH, 50);
    setServoAngle(BR1_CH, 90);
    setServoAngle(BR2_CH, 50);
    setServoAngle(BL1_CH, 90);
    setServoAngle(BL2_CH, 50);
}

void up(){
    setServoAngle(FR1_CH, 90);
    setServoAngle(FR2_CH, 125);
    setServoAngle(FL1_CH, 90);
    setServoAngle(FL2_CH, 125);
    setServoAngle(BR1_CH, 90);
    setServoAngle(BR2_CH, 125);
    setServoAngle(BL1_CH, 90);
    setServoAngle(BL2_CH, 125);
}

void STRECHING(){
  setServoAngle(FL1_CH, 40);
  setServoAngle(FL2_CH, 55);
  setServoAngle(FR1_CH, 130);
  setServoAngle(FR2_CH, 55);
  setServoAngle(BL1_CH, 130);
  setServoAngle(BL2_CH, 55);
  setServoAngle(BR1_CH, 40);
  setServoAngle(BR2_CH, 55);
  delay(100);
}

void dance_queen(){
  fr2 = 100;
  br2 = 100;
  fl2 = 65;
  bl2 = 65;
  
  fr1 = 130;
  br1 = 55;
  fl1 = 55;
  bl1 = 130;
  
  for(int i = 0; i < 5; i++){
    for(br2 = 100; br2 > 65; br2 -= 2){
      setServoAngle(FR2_CH, fr2);
      setServoAngle(BR2_CH, br2);

      fr2 -= 2;
      delay(10);
    }
    for(fl2 = 65; fl2 < 100; fl2 += 2){
      setServoAngle(FL2_CH, fl2);
      setServoAngle(BL2_CH, bl2);

      bl2 += 2;
      delay(10);
    }
    for(fl2 = 100; fl2 > 65; fl2 -= 2){
      setServoAngle(FL2_CH, fl2);
      setServoAngle(BL2_CH, bl2);

      bl2 -= 2;
      delay(10);
    }
    for(br2 = 65; br2 < 100; br2 += 2){
      setServoAngle(FR2_CH, fr2);
      setServoAngle(BR2_CH, br2);

      fr2 += 2;
      delay(10);
    }
  }

  for(fr1 = 130; fr1 > 100; fr1 --){
    setServoAngle(FR1_CH, fr1);
    setServoAngle(BR1_CH, br1);
    setServoAngle(FL1_CH, fl1);
    setServoAngle(BL1_CH, bl1);

    br1 += 2;
    fl1 += 2;
    bl1 -= 2;
    delay(50);
  }
}

void dance(){
  setServoAngle(FL1_CH, 40);
  setServoAngle(FL2_CH, 125);
  setServoAngle(BL1_CH, 40);
  setServoAngle(BL2_CH, 125);
  setServoAngle(FR1_CH, 130);
  setServoAngle(FR2_CH, 125);
  setServoAngle(BR1_CH, 130);
  setServoAngle(BR2_CH, 125);
  bl1 = 40;
  bl2 = 125;
  br1 = 130;
  br2 = 125;
  fl1 = 40;
  fr1 = 130;
  fr2 = 125;
  for(int i = 0; i < 2; i++){
    for(int fl2 = 125; fl2 > 55; fl2 -=5){
      setServoAngle(FL2_CH, fl2);
      setServoAngle(BL2_CH, bl2);
      setServoAngle(BR2_CH, br2);

      bl2 -= 5;
      br2 -= 5;
      delay(15); 
    }
    for(int fl2 = 55; fl2 < 125; fl2 +=5){
      setServoAngle(FL2_CH, fl2);
      setServoAngle(BL2_CH, bl2);
      setServoAngle(BR2_CH, br2);

      bl2 += 5;
      br2 += 5;
      delay(15); 
   }
  }
  delay(100);
  for(int i = 0; i < 2; i++){
    for(int fr2 = 125; fr2 > 55; fr2 -=5){
      setServoAngle(FR2_CH, fr2);
      setServoAngle(BL2_CH, bl2);
      setServoAngle(BR2_CH, br2);

      bl2 -= 5;
      br2 -= 5;
      delay(15); 
    }
    for(int fr2 = 55; fr2 < 125; fr2 +=5){
      setServoAngle(FR2_CH, fr2);
      setServoAngle(BL2_CH, bl2);
      setServoAngle(BR2_CH, br2);

      bl2 += 5;
      br2 += 5;
      delay(15); 
    }
  }
}