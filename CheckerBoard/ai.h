#ifndef __gobang__AI__
#define __gobang__AI__
#include <vector>
#include "mytype.h"
#include "data.h"
#include <time.h>  
class AI{
	private:
		std::vector<Coordinate> Best; //��¼��ѵ÷����ӵ�
		std::vector<int> eva; //�������̷�ֵ��
		const static int INF=1000000; //INF����
		bool GenOK(Coordinate &t,int size)const;//�ж��Ƿ������ ˽��
		int Evaluate(); //�Ʒ� ˽��
		int Type()const; //�Ʒַ�����
		int AlphaBetaMax(int x,int y,int alpha,int beta,int depth);//alphabeta��֦����
		int AlphaBetaMin(int x,int y,int alpha,int beta,int depth);
		Data AIBoard;//����������
		bool first;//����
		int depthnow;//��ǰ�������
		int initdepth;//��ʼ�趨�������
	public:
		AI(){};
		~AI(){};
		void init(bool b,int depth){first=b;initdepth=depth;}//��ʼ������
		const int getinitdepth()const{return initdepth;}//���ص�ǰ�趨�ĳ�ʼ�趨���
		Coordinate AIComputing(const Data &board,const int size,const int depth);//AI����
};
#endif