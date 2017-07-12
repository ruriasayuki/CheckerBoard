#include"glSkyBox.h"

void glSkyBox::displayWithTexture()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texName[0]);
	glBegin(GL_QUADS);//底面
	glTexCoord2f(0,1);glVertex3f(xMin,yMin,zMin);
	glTexCoord2f(1,1);glVertex3f(xMax,yMin,zMin);
	glTexCoord2f(1,0);glVertex3f(xMax,yMin,zMax);
	glTexCoord2f(0,0);glVertex3f(xMin,yMin,zMax);
	glEnd();

	    glBindTexture(GL_TEXTURE_2D,texName[1]);
	glBegin(GL_QUADS);//天空
	glTexCoord2f(0,1);glVertex3f(xMin,yMax,zMin);
	glTexCoord2f(1,1);glVertex3f(xMax,yMax,zMin);
	glTexCoord2f(1,0);glVertex3f(xMax,yMax,zMax);
	glTexCoord2f(0,0);glVertex3f(xMin,yMax,zMax);
	glEnd();

	    glBindTexture(GL_TEXTURE_2D,texName[2]);
	glBegin(GL_QUADS);//侧面
	glTexCoord2f(1,0);glVertex3f(xMin,yMin,zMin);
	glTexCoord2f(1,1);glVertex3f(xMin,yMax,zMin);
	glTexCoord2f(0,1);glVertex3f(xMin,yMax,zMax);
	glTexCoord2f(0,0);glVertex3f(xMin,yMin,zMax);
	glEnd();
	

		glBindTexture(GL_TEXTURE_2D,texName[3]);
	glBegin(GL_QUADS);//侧面
	glTexCoord2f(1,0);glVertex3f(xMax,yMin,zMin);
	glTexCoord2f(1,1);glVertex3f(xMax,yMax,zMin);
	glTexCoord2f(0,1);glVertex3f(xMax,yMax,zMax);
	glTexCoord2f(0,0);glVertex3f(xMax,yMin,zMax);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texName[4]);
	glBegin(GL_QUADS);//侧面
	glTexCoord2f(0,0);glVertex3f(xMin,yMin,zMin);
	glTexCoord2f(0,1);glVertex3f(xMin,yMax,zMin);
	glTexCoord2f(1,1);glVertex3f(xMax,yMax,zMin);
	glTexCoord2f(1,0);glVertex3f(xMax,yMin,zMin);
	glEnd();
	
		glBindTexture(GL_TEXTURE_2D,texName[5]);
	glBegin(GL_QUADS);//侧面
	glTexCoord2f(0,0);glVertex3f(xMin,yMin,zMax);
	glTexCoord2f(0,1);glVertex3f(xMin,yMax,zMax);
	glTexCoord2f(1,1);glVertex3f(xMax,yMax,zMax);
	glTexCoord2f(1,0);glVertex3f(xMax,yMin,zMax);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void glSkyBox::displayWithoutTexture()
{
	glPushMatrix();
	glColor3ub(R,B,G);
	glBegin(GL_QUADS);//底面
	glTexCoord2f(0,1);glVertex3f(xMin,yMin,zMin);
	glTexCoord2f(1,1);glVertex3f(xMax,yMin,zMin);
	glTexCoord2f(1,0);glVertex3f(xMax,yMin,zMax);
	glTexCoord2f(0,0);glVertex3f(xMin,yMin,zMax);
	glEnd();
	glBegin(GL_QUADS);//天空
	glTexCoord2f(0,1);glVertex3f(xMin,yMax,zMin);
	glTexCoord2f(1,1);glVertex3f(xMax,yMax,zMin);
	glTexCoord2f(1,0);glVertex3f(xMax,yMax,zMax);
	glTexCoord2f(0,0);glVertex3f(xMin,yMax,zMax);
	glEnd();

	glBegin(GL_QUADS);//侧面
	glTexCoord2f(1,0);glVertex3f(xMin,yMin,zMin);
	glTexCoord2f(1,1);glVertex3f(xMin,yMax,zMin);
	glTexCoord2f(0,1);glVertex3f(xMin,yMax,zMax);
	glTexCoord2f(0,0);glVertex3f(xMin,yMin,zMax);
	glEnd();

	glBegin(GL_QUADS);//侧面
	glTexCoord2f(1,0);glVertex3f(xMax,yMin,zMin);
	glTexCoord2f(1,1);glVertex3f(xMax,yMax,zMin);
	glTexCoord2f(0,1);glVertex3f(xMax,yMax,zMax);
	glTexCoord2f(0,0);glVertex3f(xMax,yMin,zMax);
	glEnd();

	glBegin(GL_QUADS);//侧面
	glTexCoord2f(0,0);glVertex3f(xMin,yMin,zMin);
	glTexCoord2f(0,1);glVertex3f(xMin,yMax,zMin);
	glTexCoord2f(1,1);glVertex3f(xMax,yMax,zMin);
	glTexCoord2f(1,0);glVertex3f(xMax,yMin,zMin);
	glEnd();

	glBegin(GL_QUADS);//侧面
	glTexCoord2f(0,0);glVertex3f(xMin,yMin,zMax);
	glTexCoord2f(0,1);glVertex3f(xMin,yMax,zMax);
	glTexCoord2f(1,1);glVertex3f(xMax,yMax,zMax);
	glTexCoord2f(1,0);glVertex3f(xMax,yMin,zMax);
	glEnd();
	glColor3f(1,1,1);
}
bool glSkyBox::setTexture(std::string *tex)
{
	glEnable(GL_TEXTURE_2D);   
	for(int i=0;i<6;i++)
	{
	if(tex[i]==" ") return false;
	else
	{
		glGenTextures(1, &texName[i]);
	    texload(texName[i], tex[i]);
	}   
	}
	return true;
}
