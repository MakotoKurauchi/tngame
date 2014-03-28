TNGame Library
======
Basic でゲームを作るためのライブラリです。


言語仕様

変数型　INTのみ（アルファベットA - Z）
配列　１次配列のみ（@）

ステートメント
　IF 
　FOR TO STEP NEXT
　GOTO
　GOSUB RETURN
　REM
　STOP
　LET

標準入出力
　INPUT PRINT

関数
　RND ABS SIZE BUTTON 

グラフィック
　GPSET
　GPRESET
　GSPOIT
　GCLS

時間
　VSYNC
　WAIT

コマンド
　NEW
　LIST
　RUN

   
演算子（優先順位順）
　( )
　* / %
　- +
　<< >>
　>= <= > <
　== !=
　&
　^
　|
　&&
　||


サンプルプログラム


ドットが上から下に
10 FOR Y=0 TO 7
20 FOR X=0 TO 7
30 GPSET X,Y
40 WAIT 1
50 NEXT X
60 NEXT Y
70 GCLS
80 GOTO 10

ボタン入力
10 for i=0 to 5
20 gpset i,0,button(i)
30 next i
40 goto 10
