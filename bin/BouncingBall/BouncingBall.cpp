#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<conio.h>

const int FLht=30,FLwt=100;
char printBuf[FLht+5][FLwt+5];

const int DX[4]={-1,1,1,-1};
const int DY[4]={-1,-1,1,1};

int ballX,ballY,ballD;
int upBoardPos,downBoardPos;
int mapH,mapW,speedX;
bool upFail,downFail;

inline void SP(int x,int y){
	static HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,(COORD){(short)y,(short)x});
}

void hideCursor(){
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

void flushOutput(int x,int y){
	SP(x,y);
	register int i,j;
	
	for(i=1;i<=FLht;i++){
		for(j=1;j<=FLwt;j++)
		putchar(printBuf[i][j]);
		
		SP(x+i,y);
	}
}

void initPrintBuf(){
	register int i,j;
	for(i=0;i<=FLht;i++)
	for(j=0;j<=FLwt;j++)
	printBuf[i][j]=' ';
}

void frameOutput(int x,int y){
	register int i,j;
	printBuf[1][1]='+';
	printBuf[1][y]='+';
	printBuf[x][1]='+';
	printBuf[x][y]='+';
	
	for(i=2;i<y;i++) printBuf[1][i]='-';
	for(i=2;i<y;i++) printBuf[x][i]='-';
	for(j=2;j<x;j++) printBuf[j][1]='|';
	for(j=2;j<x;j++) printBuf[j][y]='|';
}

void ballMove(){
	register int k,c=0;
	register bool f=true;
	
	while(c<=5&&f){
		printBuf[ballX][ballY]=' ';
		ballX+=DX[ballD];
		ballY+=DY[ballD];
		k=ballD,f=false;
		
		if(ballX==mapH) k=((k==1)?0:3),f=1;
		if(ballX==1) k=((k==3)?2:1),f=1;
		if(ballY==mapW) k=((k==2)?1:0),f=1;
		if(ballY==1) k=((k==0)?3:2),f=1;
		if(ballX==1&&abs(ballY-upBoardPos)>1) upFail=true;
		if(ballX==mapH&&abs(ballY-downBoardPos)>1) downFail=true;
		if(f) ballX-=DX[ballD],ballY-=DY[ballD];
		
		printBuf[ballX][ballY]='*';
		ballD=k;
	}
}

void upBoardMove(int x){
	upBoardPos+=x;
	
	if(upBoardPos<2)
}

void downBoardMove(int x){
}

void initGame(){
	initPrintBuf();
	srand(time(NULL));
	
	mapH=23;
	mapW=79;
	ballX=12;
	ballY=40;
	ballD=rand()%4;
	speedX=40;
	upBoardPos=40;
	downBoardPos=40;
	upFail=false;
	downFail=false;
	
	frameOutput(mapH,mapW);
	printBuf[ballX][ballY]='*';
	printBuf[1][upBoardPos]='#';
	printBuf[mapH][downBoardPos]='#';
	printBuf[1][upBoardPos-1]='#';
	printBuf[mapH][downBoardPos-1]='#';
	printBuf[1][upBoardPos-2]='#';
	printBuf[mapH][downBoardPos-2]='#';
	printBuf[1][upBoardPos+1]='#';
	printBuf[mapH][downBoardPos+1]='#';
	printBuf[1][upBoardPos+2]='#';
	printBuf[mapH][downBoardPos+2]='#';
}

signed main(){
	hideCursor();
	initGame();
	flushOutput(2,5);
	fflush(stdout);
	
	while(!(upFail|downFail)){
//		Sleep(speedX);
		ballMove();
		flushOutput(2,5);
		
		if(kbhit()){
			register char ipt;
			ipt=getch();
			
			switch(ipt){
				case 'a':
				case 'A':upBoardMove(-1);break;
				case 'j':
				case 'J':downBoardMove(-1);break;
				case 'd':
				case 'D':upBoardMove(1);break;
				case 'l':
				case 'L':downBoardMove(1);break;
			}
		}
	}
	
	SP(mapH+3,5);
	
	if(upFail) puts("Down Wins!");
	else puts("Up Wins!");
	
	return 0;
}
