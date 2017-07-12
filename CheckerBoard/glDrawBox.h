#ifndef __opengl__glDraw__
#define __opengl__glDraw__
#include<gl/freeglut.h>
#include<string>
class glDrawBox
{
protected:
	int R,G,B;//颜色
public:
	glDrawBox(){};
	~glDrawBox(){};
	virtual void displayWithTexture(){};//带贴图显示
	virtual void displayWithoutTexture(){};//不带贴图显示
	virtual bool setTexture(std::string *tex){return true;};//设置贴图
	bool setRGB(int r,int g,int b){R=r;G=g;B=b;};//设置色彩
	void texload(GLuint& myTexture,std::string filename);//载入贴图
    unsigned char *LoadBitmapFile(std::string filename, BITMAPINFOHEADER *bitmapInfoHeader);//读取位图文件
};

#endif