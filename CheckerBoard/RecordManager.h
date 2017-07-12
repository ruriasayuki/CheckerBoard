#ifndef __gobang__RM__
#define __gobang__RM__
#include "mytype.h"
#include <stack>
class RecordManager{
	private:
		std::stack<Record> recordStack;
	public:
		void printfile();
		const Record pop(){
			if(recordStack.size()==0) throw "can't withdraw anymore!";
			Record a = recordStack.top();
			recordStack.pop();
			return a;
		}
		void push(const Record &r){ recordStack.push(r);};
		void init(){recordStack.empty();};
};

#endif