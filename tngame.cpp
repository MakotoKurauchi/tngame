/*
 TNGame Library
 (c)2014 Makoto Kurauchi
 GNU General Public License
*/

#include "tngame.h"
#include "ttbasic.h"

TNGame::TNGame(){
}

int TNGame::init(int x, int y, int fps ){
  return tb_init(x,y,fps);
}

void TNGame::set_vfunc(void(*func)(unsigned char *)){
  tb_set_vfunc( func ) ;
}

void TNGame::set_inkey(char up, char down, char left, char right , char a, char b){
   tb_set_inkey(up, down, left, right, a, b);
}

void TNGame::run(){
  tb_basic();
  tb_vcount(0);
}


