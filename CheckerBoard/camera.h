#ifndef __OpenGL__CAMERA__
#define __OpenGL__CAMERA__
#include <gl/freeglut.h>
#include "GlobalConst.h"
class Camera
{
	private:
		GLfloat eye[3];
		GLfloat center[3];
		GLfloat up[3];//glulookat���������
		float alpha;//ƽ���
		bool fixed;//�Ƿ�̶��������ӽ�
	public:
		Camera(){}
		~Camera(){}
		void init(){//��ʼ��
			eye[0]=70.0f;
			eye[1]=60.0f;
			eye[2]=-40.0f;
			alpha =90.0f;
			center[0]=eye[0] + 10.0f * cosf(alpha*Pi/180.0f);
			center[1]=53.0f;
			center[2]=eye[2] + 10.0f * sinf(alpha*Pi/180.0f);
			up[0]=0;
			up[1]=1;
			up[2]=0;
			fixed=false;
		}
		void changeProjection(){fixed=!fixed;}//�ı��ӽ�
		bool notfixed(){return !fixed;}
		void lookat(){//����ӽ�
			center[0]=eye[0] + 10.0f * cosf(alpha*Pi/180.0f);
			center[2]=eye[2] + 10.0f * sinf(alpha*Pi/180.0f);
			gluLookAt(eye[0],eye[1],eye[2],center[0],center[1],center[2],up[0],up[1],up[2]);   
		}
		void lookupdown()const{//�����ӽ�
			gluLookAt(80,200,80,80,0,80,0,0,1); 
		}
		//�����������
		void forward(){
			eye[0] += 4.0f*cosf(alpha * Pi / 180.0f);
			eye[2] += 4.0f*sinf(alpha * Pi / 180.0f);
		}
		void down(){
			eye[0] -= 4.0f*cosf(alpha * Pi / 180.0f);
			eye[2] -= 4.0f*sinf(alpha * Pi / 180.0f);
		}
		void right()
		{
			eye[0] -= 4.0f*sinf(alpha * Pi / 180.0f);
			eye[2] += 4.0f*cosf(alpha * Pi / 180.0f);
		}
		void left()
		{
			eye[0] += 4.0f*sinf(alpha * Pi / 180.0f);
			eye[2] -= 4.0f*cosf(alpha * Pi / 180.0f);
		}
		//�������ƽ�潻
		void rightRotate(){
			alpha += 2.0f;
			if(alpha<0.0f) alpha+=360.0f;
			if(alpha>360.0f) alpha-=360.0f;
		}
		void leftRotate(){
			alpha -= 2.0f;
			if(alpha<0) alpha+=360.0f;
			if(alpha>360.0f) alpha-=360.0f;
		}
};
#endif