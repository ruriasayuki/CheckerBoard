#include"glBoard.h"
void glBoard::displayWithoutTexture()
{

   glPushMatrix();
   glColor3ub(R,B,G);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(xMin,y,zMin);
   glTexCoord2f(1,0);glVertex3f(xMax,y,zMin);
   glTexCoord2f(1,1);glVertex3f(xMax,y,zMax);
   glTexCoord2f(0,1);glVertex3f(xMin,y,zMax);
   glEnd();
   glPopMatrix();
   glColor3f(1,1,1);
   
   glColor3f(lineR,lineG,lineB);
   glPushMatrix();
   double xinterval=(xMax-xMin)/(xLinesNum);
   double zinterval=(zMax-zMin)/(zLinesNum);
   for(int i=0;i<xLinesNum-1;i++)
	{	
		glBegin(GL_LINES);
		glVertex3f(xMin+xinterval+i*(xMax-xMin)/(xLinesNum),y+0.1,zMax-zinterval);
		glVertex3f(xMin+xinterval+i*(xMax-xMin)/(xLinesNum),y+0.1,zMin+zinterval);
		glEnd();
	}
   for(int i=0;i<zLinesNum-1;i++)
	{
		glBegin(GL_LINES);
		glVertex3f(xMin+xinterval,y+0.1,zMin+zinterval+i*(zMax-zMin)/(zLinesNum));
		glVertex3f(xMax-xinterval,y+0.1,zMin+zinterval+i*(zMax-zMin)/(zLinesNum));
		glEnd();
	}
	glPopMatrix();
	glColor3f(1,1,1);
}
void glBoard::displayWithTexture()
{
   glPushMatrix();
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,texName[0]);
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);glVertex3f(xMin,y,zMin);
   glTexCoord2f(1,0);glVertex3f(xMax,y,zMin);
   glTexCoord2f(1,1);glVertex3f(xMax,y,zMax);
   glTexCoord2f(0,1);glVertex3f(xMin,y,zMax);
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

   glColor3f(lineR,lineG,lineB);
   double xinterval=(xMax-xMin)/(xLinesNum);
   double zinterval=(zMax-zMin)/(zLinesNum);
   glPushMatrix();
   for(int i=0;i<zLinesNum-1;i++)
	{	
		glBegin(GL_LINES);
		glVertex3f(xMin+xinterval+i*(xMax-xMin)/(zLinesNum),y+1,zMax-zinterval);
		glVertex3f(xMin+xinterval+i*(xMax-xMin)/(zLinesNum),y+1,zMin+zinterval);
		glEnd();
	}
   for(int i=0;i<xLinesNum-1;i++)
	{
		glBegin(GL_LINES);
		glVertex3f(xMin+xinterval,y+1,zMin+i*(zMax-zMin)/(xLinesNum)+zinterval);
		glVertex3f(xMax-xinterval,y+1,zMin+i*(zMax-zMin)/(xLinesNum)+zinterval);
		glEnd();
	}
	glPopMatrix();
	glColor3f(1,1,1);

}
bool glBoard::setTexture(std::string *tex)
{
	glEnable(GL_TEXTURE_2D);   
	if(*tex=="") return false;

	glGenTextures(1, &texName[0]);
	texload(texName[0], tex[0]);
	return true;
}