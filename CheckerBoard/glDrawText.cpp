#include"glDrawText.h"
void glDrawText::DrawString(const std::string &str)
{
	 {
    static int isFirstCall = 1;
    static GLuint lists;

    if( isFirstCall ) { // 如果是第一次调用，执行初始化
                         // 为每一个ASCII字符产生一个显示列表
         isFirstCall = 0;

         // 申请MAX_CHAR个连续的显示列表编号
         lists = glGenLists(MAX_CHAR);

         // 把每个字符的绘制命令都装到对应的显示列表中
         wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
     }
     // 调用每个字符对应的显示列表，绘制每个字符
    for (int i=0;i<str.size(); i++) {  
        glCallList(lists + str[i]);  
    }  
}
}
void glDrawText::ShowText(GLfloat X,GLfloat Y,const std::string &str)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(Left, Right, Button, Top);//裁剪范围(左, 右, 下, 上)
	glMatrixMode(GL_MODELVIEW);//然后回到模型视图矩阵模式
	glLoadIdentity();
    glRasterPos2f(X,Y);
    DrawString(str);

}
