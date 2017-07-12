#include "glchess.h"
#include <gl\freeglut.h>

void glChess:: DrawChess()  //绘制一颗棋子
{  
    GLfloat fYRotStep = 2.0f * Pi / nStack;                        //沿着Y轴旋转的步长  
    GLfloat fRange = atan(a / (b + c));                            //顶部圆弧的角度(单位为弧度)  
    GLfloat R = sqrt(a * a + (b + c) * (b + c)) + c;            //大圆顶半径  
  
    GLint nSlice1 = nSlice;                                        //底部纵向分片数量  
    GLint nSlice2 = (GLint)(nSlice * (Pi - fRange) * c / a);    //侧面纵向分片数量  
    GLint nSlice3 = (GLint)(nSlice * R * fRange / a);            //顶部纵向分片数量  
  
    GLfloat fStep1 = a / nSlice1;                                //顶部步长  
    GLfloat fStep2 = (Pi - fRange) / nSlice2;                    //侧面步长(弧度)  
    GLfloat fStep3 = fRange / nSlice3;                            //顶部步长(弧度)  
  
    GLfloat dr = -0.5f / (nSlice1 + nSlice2 + nSlice3);            //纹理半径增加的步长  
  
    GLint i = 0, j = 0;  
    for (i=0; i<nStack; i++)  
    {  
        GLfloat fYR = i * fYRotStep;                            //当前沿着Y轴旋转的弧度  
        GLfloat fZ = -sin(fYR);                                    //Z分量比率  
        GLfloat fX = cos(fYR);                                    //X分量比率  
        GLfloat fZ1 = -sin(fYR + fYRotStep);                    //下一列的Z分量比率  
        GLfloat fX1 = cos(fYR + fYRotStep);                        //下一列的X分量比率  
        GLfloat rs = 0.5f;                                        //纹理半径的起点  
  
        glBegin(GL_TRIANGLE_STRIP);  
  
        //底部  
        for (j=0; j<nSlice1; j++)  
        {  
            GLfloat r = fStep1 * j;  
  
            glTexCoord2f(0.5f + rs * fX, 0.5f + rs * fZ);  
            glNormal3f(0.0f, -1.0f, 0.0f);  
            glVertex3f(r * fX, b, r * fZ);  
  
            glTexCoord2f(0.5f + rs * fX1, 0.5f + rs * fZ1);  
            glNormal3f(0.0f, -1.0f, 0.0f);  
            glVertex3f(r * fX1, b, r * fZ1);  
  
            rs += dr;  
        }  
  
        //侧面  
        for (j=0; j<nSlice2; j++)  
        {  
            GLfloat r = a + c * sin(fStep2 * j);  
            GLfloat y = b + c - c * cos(fStep2 * j);  
            GLfloat nr = sin(fStep2 * j);  
            GLfloat nY = -cos(fStep2 * j);  
  
            glTexCoord2f(0.5f + rs * fX, 0.5f + rs * fZ);  
            glNormal3f(nr * fX, nY, nr * fZ);  
            glVertex3f(r * fX, y, r * fZ);  
  
            glTexCoord2f(0.5f + rs * fX1, 0.5f + rs * fZ1);  
            glNormal3f(nr * fX1, nY, nr * fZ1);  
            glVertex3f(r * fX1, y, r * fZ1);  
  
            rs += dr;  
        }  
  
        //顶部  
        for (j=0; j<=nSlice3; j++)  
        {  
            GLfloat r = R * sin(fRange - j * fStep3);  
            GLfloat y = R * cos(fRange - j * fStep3);  
            GLfloat nr = sin(fRange - j * fStep3);  
            GLfloat nY = cos(fRange - j * fStep3);  
  
            glTexCoord2f(0.5f + rs * fX, 0.5f + rs * fZ);  
            glNormal3f(nr * fX, nY, nr * fZ);  
            glVertex3f(r * fX, y, r * fZ);  
  
            glTexCoord2f(0.5f + rs * fX1, 0.5f + rs * fZ1);  
            glNormal3f(nr * fX1, nY, nr * fZ1);  
            glVertex3f(r * fX1, y, r * fZ1);  
  
            rs += dr;  
        }  
  
        glEnd();  
    }  
}  
void glChess::DrawChessPos(const Coordinate &t,int color)//根据点的坐标以及颜色绘制棋子
{
   if(color==BLACK)
   {
	   glPushMatrix();
	   glTranslatef(t.x,0,t.y);
	   glColor3f(0,0,0);
	   DrawChess();
	   glPopMatrix();
   }
   else if (color==WHITE)
   {
	   glPushMatrix();
	   glTranslatef(t.x,0,t.y);
	   glColor3f(1,1,1);
	   DrawChess();
	   glPopMatrix();
   }
   glColor3f(1,1,1);
}
void glChess::DrawChessCursor(const Coordinate &t)//根据点的坐标以及颜色绘制棋子
{
	glPushMatrix();
	glTranslatef(t.x,0.1f,t.y);	
	glColor3f(0.8f,0.8f,1.0f);
	DrawChess();
	glPopMatrix();
	glColor3f(1,1,1);
}
