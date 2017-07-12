#ifndef __OpenGL__CAMERA__
#define __OpenGL__CAMERA__
#include <gl/freeglut.h>
#include "GlobalConst.h"
class Camera
{
	private:
		GLfloat eye[3];
		GLfloat center[3];
		GLfloat up[3];//glulookat的三组参数
		float alpha;//平面角
		bool fixed;//是否固定至俯视视角
	public:
		Camera(){}
		~Camera(){}
		void init(){//初始化
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
		void changeProjection(){fixed=!fixed;}//改变视角
		bool notfixed(){return !fixed;}
		void lookat(){//鸟瞰视角
			center[0]=eye[0] + 10.0f * cosf(alpha*Pi/180.0f);
			center[2]=eye[2] + 10.0f * sinf(alpha*Pi/180.0f);
			gluLookAt(eye[0],eye[1],eye[2],center[0],center[1],center[2],up[0],up[1],up[2]);   
		}
		void lookupdown()const{//俯视视角
			gluLookAt(80,200,80,80,0,80,0,0,1); 
		}
		//控制相机坐标
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
		//控制相机平面交
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