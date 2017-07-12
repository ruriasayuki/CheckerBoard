#ifndef __opengl__glChess__
#define __opengl__glChess__
#include<gl/freeglut.h>
#include<iostream>
#include <math.h> 
#include "mytype.h"
#include "GlobalConst.h"
class glChess{

private:
	GLfloat a;
	GLfloat b;
	GLfloat c;
	GLint nSlice;
	GLint nStack;
	GLfloat x;
	GLfloat z;
	bool black;
	bool cursorFlash;

public:
	glChess(GLfloat a, GLfloat b, GLfloat c, GLint nSlice, GLint nStack){
	
	    this->a=a;
		this->b=b;
		this->c=c;
		this->nSlice=nSlice;
		this->nStack=nStack;
		cursorFlash=false;
	}
	const bool getCursorFlash()const{return cursorFlash;}
	void changeCursorFlash(){cursorFlash=!cursorFlash;}
	void DrawChess(); 
	void DrawChessPos(const Coordinate &t,int color);
	void DrawChessCursor(const Coordinate &t);
};
#endif