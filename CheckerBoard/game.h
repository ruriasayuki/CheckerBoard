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
		bool state;//��Ϸ����״̬ 
		bool mode;//true PVA false PVP
		bool first;//true ����� false AI��
		int initstep;//��ʼ�������¼
		int tx;//�α�����
		int ty;
		int step;//������¼
		std::string message;//��Ϣ
		int inputnum;//�������ֻ���
	public:
		Game(){initstep=0;state=false;}//��ļ򵥳�ʼ��
		void start(Data &data,AI &ai,Camera &camera,RecordManager &rm);//��ʼ��Ϸ�Ĺ��̣����initstep�ֲ����У�
		void introduction()const;//��Ϸ����
		void changeInitStepto(const int t)//���Ƴ�ʼ��������ת
		{
			initstep=t;
		}
		void input(const int num){inputnum = num;}//���������ֻ�����������
		const int getInitStep() const {return initstep;}//��ȡ��ǰ��ʼ��״��

		void move(const int i,const int j)//�ƶ��α�
		{
			if(tx+i>=0 && tx+i<15) tx = tx+i;
			if(ty+j>=0 && ty+j<15) ty = ty+j;
		}
		void moveTo(const Coordinate &t)//�ƶ��α����ض���
		{
			tx=t.x;ty=t.y;
		}
		const Coordinate getCo()const //��õ�ǰ�α�����
		{
			return Coordinate(tx,ty);
		}
		const Coordinate changeCo(const Coordinate &t)const //3ά�ռ����������ת�� 
		{
			return Coordinate(t.x*10+10,t.y*10+10);
		}
		const bool getstate() const {return state;}//���ص�ǰ����Ϸ����״̬�������л����ѽ�����
		const bool getmode() const {return mode;}//���ص�ǰ��Ϸģʽ������or�˻�
		void over(){state=false;}//һ��ʤ�������
		void incStep(){step++;if(step==225){this->setMessage("The game ended in a draw"); this->over();}}//�Ʋ���
		void decStep(){step--;}
		const int getStep()const{return step;}//��õ�ǰ����

		void setMessage(const std::string &a){message=a;}//�趨��ʾ��Ϣ
		const std::string getMessage()const{return message;}//��ȡ��ʾ��Ϣ
		
};
#endif