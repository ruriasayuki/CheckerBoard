#include"glDrawText.h"
void glDrawText::DrawString(const std::string &str)
{
	 {
    static int isFirstCall = 1;
    static GLuint lists;

    if( isFirstCall ) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
                         // Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
         isFirstCall = 0;

         // ����MAX_CHAR����������ʾ�б���
         lists = glGenLists(MAX_CHAR);

         // ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
         wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
     }
     // ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
    for (int i=0;i<str.size(); i++) {  
        glCallList(lists + str[i]);  
    }  
}
}
void glDrawText::ShowText(GLfloat X,GLfloat Y,const std::string &str)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(Left, Right, Button, Top);//�ü���Χ(��, ��, ��, ��)
	glMatrixMode(GL_MODELVIEW);//Ȼ��ص�ģ����ͼ����ģʽ
	glLoadIdentity();
    glRasterPos2f(X,Y);
    DrawString(str);

}
