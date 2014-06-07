/*
 TOYOSHIKI Tiny BASIC for Arduino
 (C)2012 Tetsuya Suzuki
 GNU General Public License
 */
/*
 TNGame Library
 (c)2014 Makoto Kurauchi
 GNU General Public License
*/

#include <Arduino.h>

//Prototypes
void newline(void);
char* c_strchr(char *, char);
short c_isspace_f(char c);
void c_puts(const char *);
short c_gets(void);
void gpush(unsigned char*);
unsigned char* gpop(void);
void lpush(unsigned char*);
unsigned char* lpop(void);
void error(void);
void putnum(short, short);
short getnum(void);
short getvalue(unsigned char*);
short getparam(void);
unsigned char* getlp(short);
unsigned char toktoi(void);
void putlist(unsigned char*);
void inslist(void);
short getsize(void);
short getabs(void);
short getrnd(void);
short getarray(void);
short ivalue(void);
short icalc(void);
short iexp(void);
void iprint(void);
void iinput(void);
short iif(void);
void ivar(void);
void iarray(void);
void ilet(void);
void ilist(void);
void inew(void);
unsigned char* iexe(void);
void irun(void);
void icom(void);

void tb_basic(void);
int tb_init(int, int, int);
void ipset(short);
short getinkey(void);
short gspoit(void);
unsigned char* tb_getvbuf(void);
void tb_vcount(unsigned int);
void tb_set_vfunc(void(*func)(unsigned char *));
void tb_set_inkey(char, char, char, char, char, char);
void iwait(void);
void igcls(void);

short idivmul(void);
short iaddsub(void);
short ishift(void);
short icomp(void);
short ieqlieq(void);
short iband(void);
short ibxor(void);
short ibor(void);
short iand(void);
short ior(void);
