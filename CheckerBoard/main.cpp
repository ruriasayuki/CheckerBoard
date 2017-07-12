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

//main.cpp��ȫ�ֱ�������
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
    glClearDepth(1.0f);//ָ����Ȼ����������ֵ(������Ȼ��������ֵ����Ϊ1)
    glDepthFunc(GL_LEQUAL);//ָ��������Ȼ���Ƚ�ֵ(���½��������ֵ��ԭ����1�Ƚϣ�<=��ͨ����������)
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	std::string path1[]={"floor.bmp"};
	Board.setTexture(path1);
	Board.setLineColor(0.90588f,0.70196f,0.14509f);
	std::string path2[6]={"world.bmp","world.bmp","world.bmp","world.bmp","world.bmp","wall2.bmp"};
	SkyBox.setTexture(path2);
	
	game.introduction();//�������
	game.start(data,ai,camera,rm);//��Ϸ��ʼ����ʼ��
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

	if(camera.notfixed())//���״̬
		camera.lookat();
	else
		camera.lookupdown();
   
	SkyBox.displayWithTexture();//��պ�������
	Board.displayWithTexture();

	glPushMatrix();

	//������
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

	//���ӻ���
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
	//ratio�ļ���
}
void SpecialKey(GLint key,GLint x,GLint y)  
{
	//�α����
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
	//һ�����
	switch(key)  
	{
		case 'P'://�����ӽ�
		case 'p':{
			camera.changeProjection();
			break;
		}
		case 'O'://�ؿ�
		case 'o':{
			game.changeInitStepto(0);
			game.start(data,ai,camera,rm);
			break;
		}
		case KEY_EXIT:{//�˳�
					   exit(0);
		}
	}
	//��Ϸ����ʱ�ɽ��еĲ���
	if(game.getstate())
	{
		switch(key)
		{
		case 'R'://����
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
					game.setMessage(std::string(err));//��ּ�¼���Ŀ�ջ�����׳�
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
		case KEY_ENTER://enter������
		{
			if(game.getmode()){//��ҪAI��������
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
						Coordinate res;//��¼AI�������ķ���ֵ
						game.setMessage(std::string("AI is Computing..."));
						if(chess.getCursorFlash()){chess.changeCursorFlash();}
						display();//��AI��ʼ���㿨������ǰ��Ⱦ��һ֡
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
				{//���������ɵ��������
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
	//��ʼ���׶εļ��̽���
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
	//����ڸ����ӽ��µ���������
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
void flash(int id)//һ��һ����
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
