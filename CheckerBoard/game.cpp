#include "game.h"
void Game::introduction()const
{
	std::cout<<"————————操作说明————————"<<std::endl;
	std::cout<<"w、a、s、d 控制视角移动，q、e控制视角旋转,p键改变视角。"<<std::endl;
	std::cout<<"方向键控制落子位置，回车键落子。"<<std::endl;
	std::cout<<"o键重开游戏，r键悔棋。"<<std::endl;
	std::cout<<"————————游戏愉快————————"<<std::endl;
}
void Game::start(Data &data,AI &ai,Camera &camera,RecordManager &rm)
{
	switch (initstep)
	{
	case 0:{
			std::cout<<"————————————————————"<<std::endl;
			tx=7;
			ty=7;
			step=0;
			state=false;
			first=true;
			camera.init();
			data.init();
			rm.init();
			message="Choose game mode:(push 1 to one player;2 to two players)";
			break;
		}
	case 1:{
			mode=true;
			message="Choose who first:(push 1 you first;2 AI first)";
			break;
		}
	case 2:{
			if(inputnum==1) first=true;else first=false;
			message="Choose AI level:(1:low;2:medium;3:high)";
			break;
	}
	case 3:{
			mode=false;
			message="BLACK first.";
			state=true;
			break;
		}
	case 4:{
			ai.init(first,inputnum*2);
			if(!first)
				{
					rm.push(Record(data.getstate(),Coordinate(7,7)));
					data.setgobang(7,7);
					incStep();
			}
			mode=true;
			state=true;
			break;
		}
	}


}
