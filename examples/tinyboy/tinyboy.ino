/*
 TNGame Library
 (c)2014 Makoto Kurauchi
 GNU General Public License
*/

#include "tngame.h"
#include <SD.h>
#include <SPI.h>
#include <EEPROM.h>

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

void vreg(unsigned char *buf){
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
  int i,loaded=0;
  char cmd[10];
  
  // ピン設定
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
  
  // シリアル開始
  Serial.begin(9600);
  
  // TNGAMEライブラリを初期化
  if ( !game.init(8,8,30,SDCS) ) { // 画像サイズX、画像サイズY、フレームレート、SDカードのCSピン番号
    Serial.println("Initialize error.");
    while(1);
  }
  game.set_vfunc(vreg); // 画面データを受け取る関数を登録
  game.set_inkey(BTN_UP,BTN_DOWN,BTN_LEFT,BTN_RIGHT,BTN_A,BTN_B); // 入力ボタンを登録

  // 表示用割り込み関数登録
  attachIntervalTimerHandler(display);
  
  // 電源ランプ点灯
  digitalWrite(LED, HIGH); 

  // Basicコマンド
  if(EEPROM.read(EEPROM_BOOT)==1){ // 起動対象（EEPROM　or　SD）
    if(digitalRead(BTN_A)==0 && digitalRead(BTN_B)==0){ // 起動時にABボタンが押されていたら
      game.command("fclear"); // フラッシュをクリアする
    }else{
      game.command("fload"); // フラッシュからロードする
    }
  }else{
    for(i=0;i<sizeof(BtnSst)/sizeof(BtnSst[0]);i++){ // 起動時に押されているボタンに対応するファイルを読み込む
      if(! digitalRead(BtnSst[i])){
        sprintf(cmd,"load %d",i+1);
        game.command(cmd);
        loaded = 1;
        break;
      }  
    }
    if(!loaded) game.command("load 0"); // デフォルトの読み込みファイル
  }
  game.command("run"); // 実行する
}


void loop(void){
  // 入力受付
   game.run();
}



