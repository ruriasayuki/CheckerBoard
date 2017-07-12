#ifndef __gobang__GAME__
#define __gobang__GAME__
#include <string>
#include <iostream>
#include "data.h"
#include "RecordManager.h"
#include "mytype.h"
#include "camera.h"
#include "ai.h"
class Game
{
	private:
		bool state;//游戏进行状态 
		bool mode;//true PVA false PVP
		bool first;//true 玩家先 false AI先
		int initstep;//初始化步骤记录
		int tx;//游标坐标
		int ty;
		int step;//步数记录
		std::string message;//消息
		int inputnum;//输入数字缓存
	public:
		Game(){initstep=0;state=false;}//类的简单初始化
		void start(Data &data,AI &ai,Camera &camera,RecordManager &rm);//开始游戏的过程（配合initstep分步进行）
		void introduction()const;//游戏介绍
		void changeInitStepto(const int t)//控制初始化过程跳转
		{
			initstep=t;
		}
		void input(const int num){inputnum = num;}//向输入数字缓存区存数字
		const int getInitStep() const {return initstep;}//获取当前初始化状况

		void move(const int i,const int j)//移动游标
		{
			if(tx+i>=0 && tx+i<15) tx = tx+i;
			if(ty+j>=0 && ty+j<15) ty = ty+j;
		}
		void moveTo(const Coordinate &t)//移动游标至特定点
		{
			tx=t.x;ty=t.y;
		}
		const Coordinate getCo()const //获得当前游标坐标
		{
			return Coordinate(tx,ty);
		}
		const Coordinate changeCo(const Coordinate &t)const //3维空间和棋盘坐标转化 
		{
			return Coordinate(t.x*10+10,t.y*10+10);
		}
		const bool getstate() const {return state;}//返回当前的游戏进行状态（进行中或者已结束）
		const bool getmode() const {return mode;}//返回当前游戏模式，人人or人机
		void over(){state=false;}//一方胜利后控制
		void incStep(){step++;if(step==225){this->setMessage("The game ended in a draw"); this->over();}}//计步器
		void decStep(){step--;}
		const int getStep()const{return step;}//获得当前步数

		void setMessage(const std::string &a){message=a;}//设定提示信息
		const std::string getMessage()const{return message;}//提取提示信息
		
};
#endif