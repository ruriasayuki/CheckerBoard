#ifndef __gobang__DATA__
#define __gobang__DATA__

#include "mytype.h"
#include <vector>
#include "GlobalConst.h"

const static int SI = 15;//���̴�С 

class Data{
private:
	int gobang[SI][SI];//��¼����״�� 0 �� 1 �� 2 ��
	int state;//״̬��¼���� 1 �ڷ�׼������ 2 �׷�׼������
	void changestate(){if(state==BLACK) state=WHITE;else if(state==WHITE) state=BLACK;};
	//ÿ�ν��в�������кڰ�ת��
public:
	Data(){};
	~Data(){};
	Data(const Data &board);//�������캯��
	void init();//��ʼ��
	//�趨�ͻ������״̬ ���ӻ��߳���
	bool setgobang(const Coordinate &t);//���귶Χ��Ϊ[0,14]
	bool setgobang(const int x,const int y);
	int getgobang(Coordinate &t) const;
	int getgobang(int x,int y) const;
	int getstate()const{return state;}
	std::string getstateStr(){if (state==1) return "BLACK";else return "WHITE";}
	void moveaway(Coordinate &t) {if(gobang[t.x][t.y]!=0){gobang[t.x][t.y]=0; changestate();}}
	const int check(const int x,const int y)const;//������Ӻ��Ƿ���һ����ʤ
	const int check(const Coordinate &t)const;//������Ӻ��Ƿ���һ����ʤ
};


#endif