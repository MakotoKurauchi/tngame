/*
 TNGame Library
 (c)2014 Makoto Kurauchi
 GNU General Public License
*/

#include "tngame.h"
#include <SD.h>
#include <SPI.h>

TNGame game ;

#ifdef BETA

#define BTN_A 15
#define BTN_B 24
#define BTN_UP 6
#define BTN_DOWN 7
#define BTN_LEFT 5
#define BTN_RIGHT 22

#define LED 23
#define SP 3
#define SDCS 2
#define SRCS 8
#define MOSI 11
#define SCK 13

int COL[] = {9,10,16,17,18,19,20,21};

#else

#define BTN_A 2
#define BTN_B 24
#define BTN_UP 6
#define BTN_DOWN 7
#define BTN_LEFT 5
#define BTN_RIGHT 22

#define LED 23
#define SP 3
#define SDCS 15
#define SRCS 8
#define MOSI 11
#define SCK 13

int COL[] = {21,17,18,16,19,10,9,20};

#endif

int BtnSst[] = {BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, BTN_A, BTN_B};

unsigned char vbuf[64];

unsigned int counter;

void test(unsigned char *buf){
  for(int i=0;i<sizeof(vbuf)/sizeof(vbuf[0]);i++){
    vbuf[i] = buf[i];
  }
}

void display(unsigned long t){
  int i;

  if( game.iomode() == IO_SERIAL ){
    counter ++;

    for(i=0;i<8;i++){
      digitalWrite(COL[i],HIGH);
    }

    digitalWrite(SRCS,LOW);
    SPI.transfer(1<<(counter%8));
    digitalWrite(SRCS,HIGH);

    for(i=0;i<8;i++){
      digitalWrite(COL[i],!vbuf[i+(counter%8)*8]);
    }
  }
}


void setup(void){
  int i;
  
  for(i=0;i<sizeof(BtnSst)/sizeof(BtnSst[0]);i++){
    pinMode(BtnSst[i],INPUT_PULLUP);
  }
  
  for(i=0;i<sizeof(COL)/sizeof(COL[0]);i++){
    pinMode(COL[i],OUTPUT);
  }
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);

  pinMode(LED,OUTPUT);
  pinMode(SDCS,OUTPUT);
  pinMode(SRCS,OUTPUT);
  
  Serial.begin(9600);
  
  // TNGAMEライブラリを初期化
  if ( !game.init(8,8,30,SDCS) ) { // 画像サイズX、画像サイズY、フレームレート、SDカードのCSピン番号
    Serial.println("Initialize error.");
    while(1);
  }
  game.set_vfunc(test); // 画面データを受け取る関数を登録
  game.set_inkey(BTN_UP,BTN_DOWN,BTN_LEFT,BTN_RIGHT,BTN_A,BTN_B); // 入力ボタンを登録

  // 表示用割り込み関数登録
  attachIntervalTimerHandler(display);
  
  // 電源ランプ点灯
  digitalWrite(LED, HIGH); 
  
  // Basicコマンド
  game.command("load 0");
  game.command("run");
}


void loop(void){
  // 入力受付
   game.run();
}



