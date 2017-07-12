#include "glchess.h"
#include <gl\freeglut.h>

void glChess:: DrawChess()  //����һ������
{  
    GLfloat fYRotStep = 2.0f * Pi / nStack;                        //����Y����ת�Ĳ���  
    GLfloat fRange = atan(a / (b + c));                            //����Բ���ĽǶ�(��λΪ����)  
    GLfloat R = sqrt(a * a + (b + c) * (b + c)) + c;            //��Բ���뾶  
  
    GLint nSlice1 = nSlice;                                        //�ײ������Ƭ����  
    GLint nSlice2 = (GLint)(nSlice * (Pi - fRange) * c / a);    //���������Ƭ����  
    GLint nSlice3 = (GLint)(nSlice * R * fRange / a);            //���������Ƭ����  
  
    GLfloat fStep1 = a / nSlice1;                                //��������  
    GLfloat fStep2 = (Pi - fRange) / nSlice2;                    //���沽��(����)  
    GLfloat fStep3 = fRange / nSlice3;                            //��������(����)  
  
    GLfloat dr = -0.5f / (nSlice1 + nSlice2 + nSlice3);            //����뾶���ӵĲ���  
  
    GLint i = 0, j = 0;  
    for (i=0; i<nStack; i++)  
    {  
        GLfloat fYR = i * fYRotStep;                            //��ǰ����Y����ת�Ļ���  
        GLfloat fZ = -sin(fYR);                                    //Z��������  
        GLfloat fX = cos(fYR);                                    //X��������  
        GLfloat fZ1 = -sin(fYR + fYRotStep);                    //��һ�е�Z��������  
        GLfloat fX1 = cos(fYR + fYRotStep);                        //��һ�е�X��������  
        GLfloat rs = 0.5f;                                        //����뾶�����  
  
        glBegin(GL_TRIANGLE_STRIP);  
  
        //�ײ�  
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
  
        //����  
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
  
        //����  
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
void glChess::DrawChessPos(const Coordinate &t,int color)//���ݵ�������Լ���ɫ��������
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
void glChess::DrawChessCursor(const Coordinate &t)//���ݵ�������Լ���ɫ��������
{
	glPushMatrix();
	glTranslatef(t.x,0.1f,t.y);	
	glColor3f(0.8f,0.8f,1.0f);
	DrawChess();
	glPopMatrix();
	glColor3f(1,1,1);
}
