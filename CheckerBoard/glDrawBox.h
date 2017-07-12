#ifndef __opengl__glDraw__
#define __opengl__glDraw__
#include<gl/freeglut.h>
#include<string>
class glDrawBox
{
protected:
	int R,G,B;//��ɫ
public:
	glDrawBox(){};
	~glDrawBox(){};
	virtual void displayWithTexture(){};//����ͼ��ʾ
	virtual void displayWithoutTexture(){};//������ͼ��ʾ
	virtual bool setTexture(std::string *tex){return true;};//������ͼ
	bool setRGB(int r,int g,int b){R=r;G=g;B=b;};//����ɫ��
	void texload(GLuint& myTexture,std::string filename);//������ͼ
    unsigned char *LoadBitmapFile(std::string filename, BITMAPINFOHEADER *bitmapInfoHeader);//��ȡλͼ�ļ�
};

#endif