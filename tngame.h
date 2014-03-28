/*
 TNGame Library
 (c)2014 Makoto Kurauchi
 GNU General Public License
*/

class TNGame {
public:
  TNGame();
  int init(int, int, int);
  void run();
  void set_vfunc(void(*func)(unsigned char *));
  void set_inkey(char, char, char, char, char, char);
  
private:

};



