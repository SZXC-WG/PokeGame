#include<stdio.h>
#include<windows.h>

const int FLht=30,FLwt=100;
char flushPrint[FLht+5][FLwt+5];

const int DX[4]={-1,1,1,-1};
const int DY[4]={-1,-1,1,1};

int ballX,ballY,ballD;
int mapH,mapW,speedX;

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
		putchar(flushPrint[i][j]);
		
		SP(x+i,y);
	}
}

void initFlush(){
	register int i,j;
	for(i=0;i<=FLht;i++)
	for(j=0;j<=FLwt;j++)
	flushPrint[i][j]=' ';
}

void frameOutput(int x,int y){
	register int i,j;
	flushPrint[1][1]='+';
	flushPrint[1][y]='+';
	flushPrint[x][1]='+';
	flushPrint[x][y]='+';
	
	for(i=2;i<y;i++) flushPrint[1][i]='-';
	for(i=2;i<y;i++) flushPrint[x][i]='-';
	for(j=2;j<x;j++) flushPrint[j][1]='|';
	for(j=2;j<x;j++) flushPrint[j][y]='|';
}

void ballMove(){
	register int k,c=0;
	register bool f=true;
	
	while(c<=5&&f){
		flushPrint[ballX][ballY]=' ';
		ballX+=DX[ballD];
		ballY+=DY[ballD];
		k=ballD,f=false;
		
		if(ballX==mapH) k=((k==1)?0:3),f=1;
		if(ballX==1) k=((k==3)?2:1),f=1;
		if(ballY==mapW) k=((k==2)?1:0),f=1;
		if(ballY==1) k=((k==0)?3:2),f=1;
		if(f) ballX-=DX[ballD],ballY-=DY[ballD];
		
		flushPrint[ballX][ballY]='*';
		ballD=k;
	}
}

signed main(){
	hideCursor();
	
	mapH=20;
	mapW=80;
	ballX=2;
	ballY=2;
	ballD=0;
	speedX=50;
	
	frameOutput(mapH,mapW);
	flushPrint[ballX][ballY]='*';
	flushOutput(2,5);
	
	while(1){
		Sleep(speedX);
		ballMove();
		flushOutput(2,5);
	}
	
	return 0;
}
