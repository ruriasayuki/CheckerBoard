#ifndef __opengl__glDrawtext__
#define __opengl__glDrawtext__

#include<gl/freeglut.h>
#define MAX_CHAR 128
#include<string>
class glDrawText
{
private:
	GLdouble Left; 
	GLdouble Right;
	GLdouble Button;
	GLdouble Top;
	glDrawText operator&=(const glDrawText &B)
	{
		this->Button=B.Button;
		this->Left=B.Button;
		this->Right=B.Right;
		this->Top=B.Top;
	}
public:
	glDrawText(GLdouble in_Left=-100.0,GLdouble in_Right=100,GLdouble in_Button=-100.0,GLdouble in_Top=100.0){	
		Left=in_Left;
	    Right=in_Right;
	    Button=in_Button;
	    Top=in_Top;
	};
	~glDrawText(){};
    void glDrawText::ShowText(GLfloat X,GLfloat Y,const std::string &str);
	void glDrawText::DrawString(const std::string &str);
};

#endif