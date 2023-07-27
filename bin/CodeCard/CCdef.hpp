#include<stdio.h>
#include<windows.h>

const int MAXSTATE=1048576; 
const int STATENUM=7;
const int CARDNUM=14;

struct PLAYER{
	int score;
	int state[STATENUM+2];
	bool CE;
	
	PLAYER(){
		state[0]=true;
		state[6]=1;
		state[7]=1;
	}
	
	bool ImProcess(){
		if(state[1]>0){
			score+=state[1];
			state[1]=0;
		}
		
		if(state[2]>0){
			score-=state[2];
			state[2]=0;
		}
		
		if(score>0) return false;
		else{
			state[0]=false;
			return true;
		}
	}
	
	bool BtProcess(){
		if(state[4]>0){
			score-=state[4];
			state[4]=0;
		}
		
		if(state[5]>0){
			CE=true;
			state[5]--;
		}
		
		state[3]/=state[7];
		state[7]=1;
		
		if(score>0) return false;
		else{
			state[0]=false;
			return true;
		}
	}
	
	bool EtProcess(){
		if(state[3]>0){
			score-=state[3];
			state[3]=0;
		}
		
		score/=state[6];
		state[6]=1;
		
		if(score>0) return false;
		else{
			state[0]=false;
			return true;
		}
	}
};

struct CARD{
	int id;
	int lvl;
};

//const int LVL[CARDNUM+2][CARDNUM+2]=\
//{{}}

void reactPause(){
	Sleep(100);
}
