#ifndef __gobang__AI__
#define __gobang__AI__
#include <vector>
#include "mytype.h"
#include "data.h"
#include <time.h>  
class AI{
	private:
		std::vector<Coordinate> Best; //记录最佳得分落子点
		std::vector<int> eva; //计算棋盘分值用
		const static int INF=1000000; //INF定义
		bool GenOK(Coordinate &t,int size)const;//判断是否可落子 私有
		int Evaluate(); //计分 私有
		int Type()const; //计分分类器
		int AlphaBetaMax(int x,int y,int alpha,int beta,int depth);//alphabeta剪枝搜索
		int AlphaBetaMin(int x,int y,int alpha,int beta,int depth);
		Data AIBoard;//推演用棋盘
		bool first;//先手
		int depthnow;//当前搜索深度
		int initdepth;//初始设定搜索深度
	public:
		AI(){};
		~AI(){};
		void init(bool b,int depth){first=b;initdepth=depth;}//初始化函数
		const int getinitdepth()const{return initdepth;}//返回当前设定的初始设定深度
		Coordinate AIComputing(const Data &board,const int size,const int depth);//AI函数
};
#endif