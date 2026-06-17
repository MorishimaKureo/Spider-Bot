//  --------                 --------
// |  D9    |               |  D7    |
// | joint9 |               | joint7 |
//  ----- --------     --------- -----
//       |  D8    |   |  D6    |
//       | joint8 |   | joint6 |
//        --------     --------
//       |  D2    |  |   D4    |
//       | joint2 |  |  joint4 |
//  ----- --------    --------- -----
// |  D3    |               |  D5    |
// | joint3 |               | joint5 |
//  --------                 --------
//                Front



#include <Servo.h>

// サーボ宣言
Servo FR1;  // 右前ヒップ
Servo FR2;  // 右前レッグ
Servo FL1;  // 左前ヒップ
Servo FL2;  // 左前レッグ
Servo BR1;  // 左後ヒップ
Servo BR2;  // 左後レッグ
Servo BL1;  // 右後ヒップ
Servo BL2;  // 右後レッグ

// ホームポジション
int fr1;
int fr2;
int fl1;
int fl2;
int br1;
int br2;
int bl1;
int bl2;

void setup(){
  Serial.begin(9600);
  FR1.attach(A4);
  FR2.attach(A5);
  FL1.attach(4);
  FL2.attach(12);
  BR1.attach(7);
  BR2.attach(8);
  BL1.attach(2);
  BL2.attach(3);

  delay(3000);
  Serial.println("1. Down\n2. UP\n3. Queen Dancee\n4 . Sreching\n5. Walk\nPilih [1-5] : "); 
}

void loop(){
  if (Serial.available() > 0) {
    char input = Serial.read();  // Baca input dari Serial Monitor
    
    switch (input){
      case '1':
        down();
        delay(1000);
        break;
      case '2':
        up();
        break;
      case '3':
        up();
        for(int i = 0; i < 2; i++){
          dance();
        }
        up();
        break;
      case '4':
        STRECHING();
        delay(200);
        dance_queen();
        delay(100);
        down();
        break;
      case '5':
        step1();
        break;
      default:
        Serial.println("Input salah");
        break;
    }
  }  
}

void step1(){
  br2 = 125;
  fr2 = 125;
  for(fr1 = 80; fr1 <= 100; fr1 += 2){
    FR1.write(fr1);
    FR2.write(fr2);
    delay(50);

    fr2 -= 2;
  }
  delay(1000);
  for(br1 = 100; br1 > 80; br1 -= 2){
    BR1.write(br1);
    BR2.write(br2);

    br2 -= 2;
    delay(50);
  }
}

void step2(){
  bl2 = 125;
  fl2 = 125;
  for(fl1 = 100; fl1 > 80; fl1 -= 2){
    FL1.write(fl1);
    FL2.write(fl2);
    delay(50);

    fl2 -= 2;
  }
  delay(1000);
  for(bl1 = 80; bl1 < 100; bl1 += 2){
    BL1.write(bl1);
    BL2.write(bl2);

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
    FL2.write(fl2);
    BR2.write(br2);

    br2 -= 2;
    delay(50);
  }
  for(fr1 = 80; fr1 < 120; fr1 +=2){
    FR2.write(fr2);
    BL2.write(bl2);
    FR1.write(fr1);
    BL1.write(bl1);
    
    bl1 += 2;
    fr2 += 2;
    bl2 += 2;  
    delay(50);
  }
  delay(100);
  for(fr1 = 120; fr1 > 80; fr1 -=2){
    FR2.write(fr2);
    BL2.write(bl2);
    FR1.write(fr1);
    BL1.write(bl1);
    
    bl1 -= 2;
    fr2 -= 2;
    bl2 -= 2;  
    delay(50);
  }
  //=========================================
  for(fr2 = 110; fr2 > 55; fr2 -= 2){
    FR2.write(fr2);
    BL2.write(bl2);

    bl2 -= 2;
    delay(50);
  }
  for(fl1 = 50; fl1 < 90; fl1 +=2){
    FL1.write(fl1);
    BR1.write(br1); 
    FL2.write(fl2);
    BR2.write(br2);
    
    br1 += 2;
    fl2 += 2;
    br2 += 2;
    delay(50);
  }
  delay(100);
  for(fr1 = 90; fr1 > 50; fr1 -=2){
    FL1.write(fl1);
    BR1.write(br1); 
    FL2.write(fl2);
    BR2.write(br2);
    
    br1 -= 2;
    fl2 -= 2;
    br2 -= 2;
    delay(50);
  }
}

void down(){
    FR1.write(90);
    FR2.write(50);
    FL1.write(90);
    FL2.write(50);
    BR1.write(90);
    BR2.write(50);
    BL1.write(90);
    BL2.write(50);
}
void up(){
    FR1.write(90);
    FR2.write(125);
    FL1.write(90);
    FL2.write(125);
    BR1.write(90);
    BR2.write(125);
    BL1.write(90);
    BL2.write(125);
}

void STRECHING(){
  FL1.write(40);
  FL2.write(55);
  FR1.write(130);
  FR2.write(55);
  BL1.write(130);
  BL2.write(55);
  BR1.write(40);
  BR2.write(55);
  delay(100);
}
void dance_queen(){
  // inisialisasi awal servo
  fr2 = 100;
  br2 = 100;
  fl2 = 65;
  bl2 = 65;
  
  fr1 = 130;
  br1 = 55;
  fl1 = 55;
  bl1 = 130;
  // kaki kanan naik
  for(int i = 0; i < 5; i++){
        
    for(br2 = 100; br2 > 65; br2 -= 2){
      FR2.write(fr2);
      BR2.write(br2);

      fr2 -= 2;
      delay(10);
    }
    // kaki kiri naik
    for(fl2 = 65; fl2 < 100; fl2 += 2){
      FL2.write(fl2);
      BL2.write(bl2);

      bl2 += 2;
      delay(10);
    }

  //===================================================
    for(fl2 = 100; fl2 > 65; fl2 -= 2){
      FL2.write(fl2);
      BL2.write(bl2);

      bl2 -= 2;
      delay(10);
    }
    for(br2 = 65; br2 < 100; br2 += 2){
      FR2.write(fr2);
      BR2.write(br2);

      fr2 += 2;
      delay(10);
    }
  }
//  fr1 = 130;
//  br1 = 55;
//  fl1 = 55;
//  bl1 = 130;
  for(fr1 = 130; fr1 > 100; fr1 --){
    FR1.write(fr1);
    BR1.write(br1);
    FL1.write(fl1);
    BL1.write(bl1);

    br1 += 2;
    fl1 += 2;
    bl1 -= 2;
    delay(50);
  }
}

void dance(){
  FL1.write(40);
  FL2.write(125);
  BL1.write(40);
  BL2.write(125);
  FR1.write(130);
  FR2.write(125);
  BR1.write(130);
  BR2.write(125);
  bl1 = 40;
  bl2 = 125;
  br1 = 130;
  br2 = 125;
  fl1 = 40;
  fr1 = 130;
  fr2 = 125;
  for(int i = 0; i < 2; i++){
    for(int fl2 = 125; fl2 > 55; fl2 -=5){
      FL2.write(fl2);
      BL2.write(bl2);
      BR2.write(br2);

      bl2 -= 5;
      br2 -= 5;
      delay(15); 
    }
    for(int fl2 = 55; fl2 < 125; fl2 +=5){
      FL2.write(fl2);
      BL2.write(bl2);
      BR2.write(br2);

      bl2 += 5;
      br2 += 5;
      delay(15); 
   }
  }
  delay(100);
  for(int i = 0; i < 2; i++){
    for(int fr2 = 125; fr2 > 55; fr2 -=5){
      FR2.write(fr2);
      BL2.write(bl2);
      BR2.write(br2);

      bl2 -= 5;
      br2 -= 5;
      delay(15); 
    }
    for(int fr2 = 55; fr2 < 125; fr2 +=5){
      FR2.write(fr2);
      BL2.write(bl2);
      BR2.write(br2);

      bl2 += 5;
      br2 += 5;
      delay(15); 
    }
  }
}




// void step2(){
//   // kaki bergerak maju
//   FL1.write(50);
//   FL2.write(70);
//   BR1.write(130);
//   BR2.write(70);
// }

// void step3(){
//   FR1.write(90);
//   FR2.write(50);
//   BL1.write(90);
//   BL2.write(50);
// }

// void step4(){
//   FR1.write(130);
//   FR2.write(70);
//   BL1.write(40);
//   BL2.write(70);
// }
