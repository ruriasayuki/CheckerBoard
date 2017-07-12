#ifndef __gobang__DATA__
#define __gobang__DATA__

#include "mytype.h"
#include <vector>
#include "GlobalConst.h"

const static int SI = 15;//棋盘大小 

class Data{
private:
	int gobang[SI][SI];//记录棋盘状况 0 无 1 黑 2 白
	int state;//状态记录参数 1 黑方准备落子 2 白方准备落子
	void changestate(){if(state==BLACK) state=WHITE;else if(state==WHITE) state=BLACK;};
	//每次进行操作后进行黑白转化
public:
	Data(){};
	~Data(){};
	Data(const Data &board);//拷贝构造函数
	void init();//初始化
	//设定和获得棋盘状态 落子或者撤子
	bool setgobang(const Coordinate &t);//坐标范围均为[0,14]
	bool setgobang(const int x,const int y);
	int getgobang(Coordinate &t) const;
	int getgobang(int x,int y) const;
	int getstate()const{return state;}
	std::string getstateStr(){if (state==1) return "BLACK";else return "WHITE";}
	void moveaway(Coordinate &t) {if(gobang[t.x][t.y]!=0){gobang[t.x][t.y]=0; changestate();}}
	const int check(const int x,const int y)const;//检测落子后是否有一方获胜
	const int check(const Coordinate &t)const;//检测落子后是否有一方获胜
};


#endif