#ifndef __gobang__MYTYPE__
#define __gobang__MYTYPE__
#include<string>
class Coordinate{
	public:
		int x,y;
		Coordinate() {x=-1;y=-1;}
		Coordinate(int i,int j):x(i),y(j) {}
		Coordinate &operator=(const Coordinate &B) {
			this->x=B.x;
			this->y=B.y;
			return *this;
		}
};
class Record{
	private:
		int state;
		Coordinate co;
	public:
		Record();
		Record(const int state,const Coordinate &t){
			this->state = state;
			co = t;
		}
		Coordinate getCo(){return co;}
};
#endif