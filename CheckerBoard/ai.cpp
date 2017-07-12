#include "ai.h"
bool AI::GenOK(Coordinate &t,int size)const{//可以落子的点
	bool flag=false;
	int i=t.x;
	int j=t.y;
	if(AIBoard.getgobang(t)==0)
		{
			for(int m=i;m>=std::max(i-size,0);m--)
				if(AIBoard.getgobang(m,j)!=0)
					flag=true;
			for(int m=i;m<=std::min(i+size,14);m++)
				if(AIBoard.getgobang(m,j)!=0)
					flag=true;
			
			for(int n=j;n>=std::max(j-size,0);n--)
				if(AIBoard.getgobang(i,n)!=0)
					flag=true;
			for(int n=j;n<=std::min(j+size,14);n++)
				if(AIBoard.getgobang(i,n)!=0)
					flag=true;
			
			for(int m=i,n=j;m>=std::max(i-size,0)&&n>=std::max(j-size,0);m--,n--) 
				if(AIBoard.getgobang(m,n)!=0)
					flag=true;
			for(int m=i,n=j;m<=std::min(i+size,14)&&n<=std::min(j+size,14);m++,n++)
				if(AIBoard.getgobang(m,n)!=0)
					flag=true;
			
			for(int m=i,n=j;m<=std::min(i+size,14)&&n>=std::max(j-size,0);m++,n--) 
				if(AIBoard.getgobang(m,n)!=0)
					flag=true;
			for(int m=i,n=j;m>=std::max(i-size,0)&&n<=std::min(j+size,14);m--,n++)
				if(AIBoard.getgobang(m,n)!=0)
					flag=true;
		}
	return flag;
}

int AI::Type()const
{
	int COMPUTER,HUMAN,hc,hm;
	hc=0;
	hm=0;
	if(!first)
	{
		COMPUTER=1;
		HUMAN=2;
	}
	else
	{
		COMPUTER=2;
		HUMAN=1;
	}
	for(int i=0;i!=eva.size()-4;i++)//计算机得分 
	{
		if(eva[i]==COMPUTER&&eva[i+1]==COMPUTER&&eva[i+2]==COMPUTER&&eva[i+3]==COMPUTER&&eva[i+4]==COMPUTER)
		{
			hc=50000;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==COMPUTER&&eva[i+2]==COMPUTER&&eva[i+3]==COMPUTER&&eva[i+4]==COMPUTER&&eva[i+5]==0)
		{
			hc=4320;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==COMPUTER&&eva[i+2]==COMPUTER&&eva[i+3]==COMPUTER&&eva[i+4]==0&&eva[i+5]==0)
		{
			hc=720;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==0&&eva[i+2]==COMPUTER&&eva[i+3]==COMPUTER&&eva[i+4]==COMPUTER&&eva[i+5]==0)
		{
			hc=720;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==COMPUTER&&eva[i+2]==COMPUTER&&eva[i+3]==0&&eva[i+4]==COMPUTER&&eva[i+5]==0)
		{
			hc=720;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==COMPUTER&&eva[i+2]==0&&eva[i+3]==COMPUTER&&eva[i+4]==COMPUTER&&eva[i+5]==0)
		{
			hc=720;
			break;
		}
		if(eva[i]==COMPUTER&&eva[i+1]==COMPUTER&&eva[i+2]==COMPUTER&&eva[i+3]==COMPUTER&&eva[i+4]==0)
		{
			hc=720;
			break;
		}
		if(eva[i]==0&&eva[i+1]==COMPUTER&&eva[i+2]==COMPUTER&&eva[i+3]==COMPUTER&&eva[i+4]==COMPUTER)
		{
			hc=720;
			break;
		}
		if(eva[i]==COMPUTER&&eva[i+1]==COMPUTER&&eva[i+2]==0&&eva[i+3]==COMPUTER&&eva[i+4]==COMPUTER)
		{
			hc=720;
			break;
		}
		if(eva[i]==COMPUTER&&eva[i+1]==0&&eva[i+2]==COMPUTER&&eva[i+3]==COMPUTER&&eva[i+4]==COMPUTER)
		{
			hc=720;
			break;
		}
		if(eva[i]==COMPUTER&&eva[i+1]==COMPUTER&&eva[i+2]==COMPUTER&&eva[i+3]==0&&eva[i+4]==COMPUTER)
		{
			hc=720;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==0&&eva[i+2]==COMPUTER&&eva[i+3]==COMPUTER&&eva[i+4]==0&&eva[i+5]==0)
		{
			hc=120;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==0&&eva[i+2]==COMPUTER&&eva[i+3]==0&&eva[i+4]==COMPUTER&&eva[i+5]==0)
		{
			hc=120;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==COMPUTER&&eva[i+2]==0&&eva[i+3]==COMPUTER&&eva[i+4]==0&&eva[i+5]==0)
		{
			hc=120;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==0&&eva[i+2]==0&&eva[i+3]==COMPUTER&&eva[i+4]==0&&eva[i+5]==0)
		{
			hc=20;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==0&&eva[i+2]==COMPUTER&&eva[i+3]==0&&eva[i+4]==0&&eva[i+5]==0)
		{
			hc=20;
			break;
		}
	}
	for(int i=0;i!=eva.size()-4;i++)//人类得分 
	{
		if(eva[i]==HUMAN&&eva[i+1]==HUMAN&&eva[i+2]==HUMAN&&eva[i+3]==HUMAN&&eva[i+4]==HUMAN)
		{
			hm=-50000;
			break;//成五
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==HUMAN&&eva[i+2]==HUMAN&&eva[i+3]==HUMAN&&eva[i+4]==HUMAN&&eva[i+5]==0)
		{
			hm=-4320;//活四
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==HUMAN&&eva[i+2]==HUMAN&&eva[i+3]==HUMAN&&eva[i+4]==0&&eva[i+5]==0)
		{
			hm=-720;//活三
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==0&&eva[i+2]==HUMAN&&eva[i+3]==HUMAN&&eva[i+4]==HUMAN&&eva[i+5]==0)
		{
			hm=-720;//活三
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==HUMAN&&eva[i+2]==HUMAN&&eva[i+3]==0&&eva[i+4]==HUMAN&&eva[i+5]==0)
		{
			hm=-720;//活三
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==HUMAN&&eva[i+2]==0&&eva[i+3]==HUMAN&&eva[i+4]==HUMAN&&eva[i+5]==0)
		{
			hm=-720;//活三
			break;
		}
		if(eva[i]==HUMAN&&eva[i+1]==HUMAN&&eva[i+2]==HUMAN&&eva[i+3]==HUMAN&&eva[i+4]==0)
		{
			hm=-720;//死四
			break;
		}
		if(eva[i]==0&&eva[i+1]==HUMAN&&eva[i+2]==HUMAN&&eva[i+3]==HUMAN&&eva[i+4]==HUMAN)
		{
			hm=-720;//死四
			break;
		}
		if(eva[i]==HUMAN&&eva[i+1]==HUMAN&&eva[i+2]==0&&eva[i+3]==HUMAN&&eva[i+4]==HUMAN)
		{
			hm=-720;//死四
			break;
		}
		if(eva[i]==HUMAN&&eva[i+1]==0&&eva[i+2]==HUMAN&&eva[i+3]==HUMAN&&eva[i+4]==HUMAN)
		{
			hm=-720;//死四
			break;
		}
		if(eva[i]==HUMAN&&eva[i+1]==HUMAN&&eva[i+2]==HUMAN&&eva[i+3]==0&&eva[i+4]==HUMAN)
		{
			hm=-720;//死四
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==0&&eva[i+2]==HUMAN&&eva[i+3]==HUMAN&&eva[i+4]==0&&eva[i+5]==0)
		{
			hm=-120;//活二
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==0&&eva[i+2]==HUMAN&&eva[i+3]==0&&eva[i+4]==HUMAN&&eva[i+5]==0)
		{
			hm=-120;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==HUMAN&&eva[i+2]==0&&eva[i+3]==HUMAN&&eva[i+4]==0&&eva[i+5]==0)
		{
			hm=-120;
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==0&&eva[i+2]==0&&eva[i+3]==HUMAN&&eva[i+4]==0&&eva[i+5]==0)
		{
			hm=-20;//活一
			break;
		}
		if(i!=eva.size()-5&&eva[i]==0&&eva[i+1]==0&&eva[i+2]==HUMAN&&eva[i+3]==0&&eva[i+4]==0&&eva[i+5]==0)
		{
			hm=-20;
			break;
		}
	}
	return hc+hm;
}

int AI::Evaluate(){//估值函数 
	//72路得分总和 
	int score=0;
	for(int i=0;i<15;i++)//左-右 
	{
		eva.clear();
		for(int j=0;j<15;j++)
		eva.push_back(AIBoard.getgobang(i,j));
		score+=Type();
	}
	for(int j=0;j<15;j++)//上-下 
	{
		eva.clear();
		for(int i=0;i<15;i++)
		eva.push_back(AIBoard.getgobang(i,j));
		score+=Type();
	}
	for(int i=4;i<14;i++)//左下-右上 
	{
		eva.clear();
		for(int j=0;j<=i;j++)
		eva.push_back(AIBoard.getgobang(i-j,j));
		score+=Type();
	}
	for(int j=0;j<=10;j++)
	{
		eva.clear();
		for(int i=14;i>=j;i--)
		eva.push_back(AIBoard.getgobang(i,j+14-i));
		score+=Type();
	}
	for(int i=10;i>0;i--)//左上-右下 
	{
		eva.clear();
		for(int j=0;j<=14-i;j++)
		eva.push_back(AIBoard.getgobang(i+j,j));
		score+=Type();
	}
	for(int j=0;j<=10;j++)
	{
		eva.clear();
		for(int i=0;i<=14-j;i++)
		eva.push_back(AIBoard.getgobang(i,i+j));
		score+=Type();
	}
	return score;
}

Coordinate AI::AIComputing(const Data &board,const int size,const int depth) {//AI
	int max_val = -INF;
	AIBoard = Data(board);
	Best.clear();
	Best.reserve(225);
	depthnow=depth;
	for(int i=0;i<15;i++)
	for(int j=0;j<15;j++)
	{
		Coordinate t = Coordinate(i,j);
		if(GenOK(t,size))
		{
			AIBoard.setgobang(t);
			int val=AlphaBetaMin(i,j,-INF,INF,depth-1);
			if(val==max_val)
			{
				Best.push_back(t);
			}
			if(val>max_val)
			{
				max_val=val;
				Best.clear();
				Best.push_back(t);
			}
		AIBoard.moveaway(t);
	}
	}
	srand((unsigned)time(0));  
	Coordinate B=Best[rand()%Best.size()];
	return B;
}

int AI::AlphaBetaMax(int x,int y,int alpha,int beta,int depth)//Alpha-Beta剪枝 
{
	if(AIBoard.check(x,y)!=0)
	{
		return -60000*depth;
	}
	if(depth==1)
	{
		return Evaluate();
	}
	for(int i=0;i<15;i++)
	for(int j=0;j<15;j++)
	{
		Coordinate t = Coordinate(i,j);
		if(GenOK(t,1))
		{
			AIBoard.setgobang(t);
			int val=AlphaBetaMin(i,j,alpha,beta,depth-1);
			AIBoard.moveaway(t);
			if(val>alpha)
			{
				alpha=val;
			}
			if(alpha>=beta)
			{
				break;
			}
		
		}
	}
	return alpha;
}
int AI::AlphaBetaMin(int x,int y,int alpha,int beta,int depth)
{
	if(AIBoard.check(x,y)!=0)
	{
		return 60000*depth;
	}
	if(depth==1)
	{
		return Evaluate();
	}
	int size=1;
	if(depthnow-depth==1) size=2;
	for(int i=0;i<15;i++)
	for(int j=0;j<15;j++)
	{
		Coordinate t = Coordinate(i,j);
		if(GenOK(t,size))
		{
			AIBoard.setgobang(t);
			int val=AlphaBetaMax(i,j,alpha,beta,depth-1);
			AIBoard.moveaway(t);
			if(val<beta)
			{
				beta=val;
			}
			if(alpha>=beta)
			{
				break;
			}
		}
		
	}
	return beta;
}