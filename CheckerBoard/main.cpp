#include<gl/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <string>

#include "ai.h"
#include "data.h"
#include "mytype.h"
#include "RecordManager.h"
#include "resource.h"
#include "glchess.h"
#include "glDrawText.h"
#include "glSkyBox.h"
#include "glDrawBox.h"
#include "glBoard.h"
#include "camera.h"
#include "game.h"

//main.cpp内全局变量声明
const int KEY_ENTER=13;
const int KEY_EXIT=27;
double ratio=0;
Data data;
AI ai;
glDrawText drawText;
glSkyBox SkyBox(-1000.0f,1000.0f,-1000.0f,1000.0f,-1000.0f,1000.0f);
glBoard Board(0,160,0,160,0,16,16);
Camera camera;
Game game;
glChess chess(2.0f,1.0f,0.8f,16,32);
RecordManager rm;

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);//指定深度缓冲区的清除值(即将深度缓冲区里的值设置为1)
    glDepthFunc(GL_LEQUAL);//指定用于深度缓冲比较值(即新进像素深度值与原来的1比较，<=则通过，否则丢弃)
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	std::string path1[]={"floor.bmp"};
	Board.setTexture(path1);
	Board.setLineColor(0.90588f,0.70196f,0.14509f);
	std::string path2[6]={"world.bmp","world.bmp","world.bmp","world.bmp","world.bmp","wall2.bmp"};
	SkyBox.setTexture(path2);
	
	game.introduction();//输出介绍
	game.start(data,ai,camera,rm);//游戏开始，初始化
}	
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawText.ShowText(-95.0f,90.0f,game.getMessage());
	drawText.ShowText(-95.0f,80.0f,std::string("step: ").append(std::to_string(game.getStep())));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 1, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(camera.notfixed())//相机状态
		camera.lookat();
	else
		camera.lookupdown();
   
	SkyBox.displayWithTexture();//天空盒与棋盘
	Board.displayWithTexture();

	glPushMatrix();

	//光标绘制
	if(game.getstate()&&chess.getCursorFlash()){
		glPushMatrix();
		chess.DrawChessCursor(game.changeCo(game.getCo()));
		glPopMatrix();
	}
	else if(game.getstate()&&!chess.getCursorFlash()){
		glPushMatrix();
		chess.DrawChessPos(game.changeCo(game.getCo()),data.getstate());
		glPopMatrix();
	}
	glPushMatrix();

	//棋子绘制
	for(int i=0;i<15;i++)
		{
		for(int j=0;j<15;j++)
		{
			chess.DrawChessPos(game.changeCo(Coordinate(i,j)),data.getgobang(i,j));
		}
	}
	glPopMatrix();
	glutSwapBuffers();
}
void idle()
{
	glutPostRedisplay();
}
void ChangeSize(int width, int height)
{
	glViewport(0, 0, width, height);
	int pwidth=width;
	int pheight=height;
	if(width==0) int pwidth=1;
	if(height==0) int height=1;
	ratio = (1.0*width)/(1.0*height);
	//ratio的计算
}
void SpecialKey(GLint key,GLint x,GLint y)  
{
	//游标控制
	if(game.getstate())
	{
	switch(key)  
	{
	case GLUT_KEY_LEFT:{
		game.move(1,0);
		break;
	}
	case GLUT_KEY_DOWN:{
		game.move(0,-1);
		break;
	}
	case GLUT_KEY_UP:{
		game.move(0,1);
		break;
	}
	case GLUT_KEY_RIGHT:{
		game.move(-1,0);
		break;
	}
	}
	}
}  
void myKeyBoard(unsigned char key, int x, int y)
{
	//一般操作
	switch(key)  
	{
		case 'P'://调整视角
		case 'p':{
			camera.changeProjection();
			break;
		}
		case 'O'://重开
		case 'o':{
			game.changeInitStepto(0);
			game.start(data,ai,camera,rm);
			break;
		}
		case KEY_EXIT:{//退出
					   exit(0);
		}
	}
	//游戏进行时可进行的操作
	if(game.getstate())
	{
		switch(key)
		{
		case 'R'://悔棋
		case 'r':{
			if(!game.getmode())
			{
				try{
					Record laststep = rm.pop();
					game.decStep();
					data.moveaway(laststep.getCo());
					game.moveTo(laststep.getCo());
				}
				catch(char *err)
				{
					game.setMessage(std::string(err));//棋局记录器的空栈错误抛出
				}
			}
			else
			{
				try{
					Record laststep = rm.pop();
					game.decStep();
					data.moveaway(laststep.getCo());
					laststep = rm.pop();
					game.decStep();
					data.moveaway(laststep.getCo());
					game.moveTo(laststep.getCo());
				}
			catch(char *err)
				{
					game.setMessage(std::string(err));
				}
			}
			break;
		}
		case KEY_ENTER://enter键落子
		{
			if(game.getmode()){//需要AI计算的情况
				int tempstate=data.getstate();
				if(data.setgobang(game.getCo()))
					{
						game.incStep();
						rm.push(Record(tempstate,game.getCo()));
						if(data.check(game.getCo())>0) 
						{
							game.over();
							game.setMessage(std::string("Now you win!Congratulation!  push 'o' to restart."));
							break;
						}
						Coordinate res;//记录AI计算结果的返回值
						game.setMessage(std::string("AI is Computing..."));
						if(chess.getCursorFlash()){chess.changeCursorFlash();}
						display();//在AI开始计算卡死画面前渲染出一帧
						if(game.getStep()==1){ res=ai.AIComputing(data,4,4);}
						else{
							res=ai.AIComputing(data,2,ai.getinitdepth());
						}
						game.moveTo(res);
						rm.push(Record(data.getstate(),res));
						data.setgobang(res);
						game.incStep();
						game.setMessage(std::string("Now,it's your turn."));
						if(data.check(res)>0)
						{
							game.over();
							game.setMessage(std::string("You can't beat AI!  push 'o' to restart."));
							break;
						}
						
		  
					}
				}
				else
				{//两个人轻松的下棋代码
					int tempstate=data.getstate();
					if(data.setgobang(game.getCo())){
						game.incStep();
						game.setMessage(data.getstateStr().append(std::string("'s turn.")));
						rm.push(Record(tempstate,game.getCo()));
						if(data.check(game.getCo())!=0)
						{
							game.over();
							if (tempstate==1) game.setMessage(std::string("BLACK wins!Congratulation!  push 'o' to restart."));
							else game.setMessage(std::string("WHITE wins!Congratulation!  push 'o' to restart."));
						}
					}
				}
				break;
			}
		}
	}
	//初始化阶段的键盘交互
	if(game.getInitStep()==0)
	{
		switch(key)
		{
			case '1':{
				game.changeInitStepto(1);
				game.start(data,ai,camera,rm);
				break;
			}
			case '2':{
				game.changeInitStepto(3);
				game.start(data,ai,camera,rm);
				break;
			}
		}
	}
	else if(game.getInitStep()==1)
	{
		switch(key)
		{
			case '1':{
				game.input(1);
				game.changeInitStepto(2);
				game.start(data,ai,camera,rm);
				break;
		}
			case '2':{
				game.input(2);
				game.changeInitStepto(2);
				game.start(data,ai,camera,rm);
				break;
			}
		}
	}
	else if(game.getInitStep()==2)
	{
		switch(key)
		{
			case '1':{
				game.input(1);
				game.changeInitStepto(4);
				game.start(data,ai,camera,rm);
				break;
			}
			case '2':{
				game.input(2);
				game.changeInitStepto(4);
				game.start(data,ai,camera,rm);
				break;
			}
			case '3':{
				game.input(3);
				game.changeInitStepto(4);
				game.start(data,ai,camera,rm);
				break;
			}
		}
	}
	//相机在俯视视角下的锁定工作
	if(camera.notfixed())
	{
		switch(key) 
		{
			case 'A':
			case 'a':{
				camera.left();
				break;
			}
			case 'D':
			case 'd':{
				camera.right();
				break;
			}
			case 'W':
			case 'w':{
				camera.forward();
				break;
			}	
			case 'S':
			case 's':{
				camera.down();
				break;
			}
			case 'Q':
			case 'q':{
				camera.leftRotate();
				break;
			}
			case 'E':
			case 'e':{
				camera.rightRotate();
				break;
			}
		}
	}
}
void flash(int id)//一闪一闪的
{
	chess.changeCursorFlash();
	glutTimerFunc(500, flash ,1);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB );
    glutInitWindowSize (400, 400);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Gobang");
    init();
    glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKeyBoard);
	glutSpecialFunc(SpecialKey);
	glutTimerFunc(500, flash, 1);
    glutMainLoop();
    return 0;
}
