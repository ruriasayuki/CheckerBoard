#ifndef __opengl__glSkyBox__
#define __opengl__glSkyBox__
#include<gl/freeglut.h>
#include <string>
#include"glDrawBox.h"
class glSkyBox:public glDrawBox
{
private:
	GLfloat xMin,xMax,yMin,yMax,zMin,zMax;
	GLuint  texName[6];

public:
	glSkyBox(GLfloat in_xMin=0,GLfloat in_xMax=0,GLfloat in_yMin=0,GLfloat in_yMax=0,GLfloat in_zMin=0,GLfloat in_zMax=0)
	{
		xMin=in_xMin;
		xMax=in_xMax;
		yMin=in_yMin;
		yMax=in_yMax;
		zMin=in_zMin;
		zMax=in_xMax;
	};
	~glSkyBox(){};
	virtual void displayWithTexture();
	virtual void displayWithoutTexture();
	virtual bool setTexture(std::string *tex);
	GLfloat getzMin()const {return zMax;}
	GLfloat getzMax()const {return zMax;}
	GLfloat getxMin()const {return xMin;}
	GLfloat getxMax()const {return xMax;}
	GLfloat getyMin()const {return yMin;}
	GLfloat getyMax()const {return yMax;}

	void setzMin(GLfloat zmin){ zMin=zmin;}
	void setzMax(GLfloat zmax){ zMax=zmax;}
	void setxMin(GLfloat xmin){ xMin=xmin;}
	void setxMax(GLfloat xmax){ xMax=xmax;}
	void setyMin(GLfloat ymin){ yMin=ymin;}
	void setyMax(GLfloat ymax){ yMax=ymax;}
};

#endif
