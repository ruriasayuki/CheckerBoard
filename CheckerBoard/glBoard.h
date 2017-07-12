#ifndef __opengl__glBoard__
#define __opengl__glBoard__

#include<gl/freeglut.h>
#include"glDrawBox.h"
class glBoard:public glDrawBox
{
private:
	GLfloat xMin,xMax,zMin,zMax,y;
	int xLinesNum,zLinesNum;
	GLuint  texName[1];
	GLfloat lineR,lineB,lineG;
public:
	glBoard(GLfloat in_xMin=0,GLfloat in_xMax=0,GLfloat in_zMin=0,GLfloat in_zMax=0,GLfloat in_y=0,int in_xLinesNum=0,int in_zLinesNum=0)
	{
		xMin=in_xMin;
		xMax=in_xMax;
		zMin=in_zMin;
		zMax=in_zMax;
		y=in_y;
		xLinesNum=in_xLinesNum;
		zLinesNum=in_zLinesNum;
	};
	~glBoard(){};
	virtual void displayWithTexture();
	virtual void displayWithoutTexture();
	virtual bool setTexture(std::string *tex);
	void setLineColor(GLfloat r,GLfloat g,GLfloat b){lineR=r;lineG=g;lineB=b;};
    GLfloat getzMin()const {return zMin;}
	GLfloat getzMax()const {return zMax;}
	GLfloat getxMin()const {return xMin;}
	GLfloat getxMax()const {return xMax;}
	GLfloat gety()const {return y;}

	void setzMin(GLfloat zmin){ zMin=zmin;}
	void setzMax(GLfloat zmax){ zMax=zmax;}
	void setxMin(GLfloat xmin){ xMin=xmin;}
	void setxMax(GLfloat xmax){ xMax=xmax;}
	void sety(GLfloat in_y){ y=in_y;}

};

#endif