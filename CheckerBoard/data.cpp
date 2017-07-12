#include "data.h"
#include <iostream>
Data::Data(const Data &board){
	for(int i=0;i<SI;i++)
		for(int j=0;j<SI;j++)
			gobang[i][j]=board.getgobang(i,j);
	state = board.getstate();
};
void Data::init(){
	for(int i=0;i<SI;i++)
		for(int j=0;j<SI;j++)
			gobang[i][j]=0;
	state = BLACK;
};
int Data::getgobang(Coordinate &t) const{
	if(t.x>=0&&t.x<15&&t.y>=0&&t.y<15){
		return gobang[t.x][t.y];
	}
	return 0;
};
int Data::getgobang(int x, int y) const{
	if(x>=0&&x<15&&y>=0&&y<15){
		return gobang[x][y];
	}
	return 0;
};
bool Data::setgobang(const Coordinate &t){
	if(t.x>=0&&t.x<15&&t.y>=0&&t.y<15){
		if(gobang[t.x][t.y]==0){
			gobang[t.x][t.y]=state;
		//	rm.push(Record(state,t));
			changestate();
			return true;
		}
	}
	return false;
};

bool Data::setgobang(const int x,const int y){
	if(x>=0&&x<15&&y>=0&&y<15){
		if(gobang[x][y]==0){
			gobang[x][y]=state;
		//	rm.push(Record(state,Coordinate(x,y)));
			changestate();
			return true;
		}
	}
	return false;
};
const int Data::check(const int x,const int y)const{
	int wb = gobang[x][y];
	int num = 0;
	int tx = x-1;
	while(tx>=0 && gobang[tx][y]==wb)
	{
		num++;
		tx--;
	}
	tx = x+1;
	while(tx<SI && gobang[tx][y]==wb)
	{
		num++;
		tx++;
	}
	if (num>3) return wb;

	num = 0;
	int ty = y-1;
	while(ty>=0 && gobang[x][ty]==wb)
	{
		num++;
		ty--;
	}
	ty = y+1;
	while(ty<SI && gobang[x][ty]==wb)
	{
		num++;
		ty++;
	}
	if (num>3) return wb;
	
	num = 0;
	tx = x-1;
	ty = y-1;
	while(tx>=0 && ty>=0 && gobang[tx][ty]==wb)
	{
		num++;
		tx--;
		ty--;
	}
	tx = x+1;
	ty = y+1;
	while(tx<SI && ty<SI && gobang[tx][ty]==wb)
	{
		num++;
		tx++;
		ty++;
	}
	if (num>3) return wb;

	num = 0;
	tx = x+1;
	ty = y-1;
	while(tx<SI && ty>=0 && gobang[tx][ty]==wb)
	{
		num++;
		tx++;
		ty--;
	}
	tx = x-1;
	ty = y+1;
	while(tx>=0 && ty<SI && gobang[tx][ty]==wb)
	{
		num++;
		tx--;
		ty++;
	}
	if (num>3) return wb;
	return 0;	
}
const int Data::check(const Coordinate &t)const{
	return check(t.x,t.y);
}
/*
void Data::printboard()
{
	for(int i=0;i<15;i++)
		{
		for(int j=0;j<15;j++)//¡ñ¡ð¡õ
		{
			if(gobang[i][j]==1)
			{
				std::cout<<"¡ñ";
			}
			else if(gobang[i][j]==2)
			{
				std::cout<<"¡ð";
			}
			else
			{
				std::cout<<"¡õ";
			}
		}
		std::cout<<std::endl;
	}
}*/

