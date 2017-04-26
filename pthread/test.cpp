#include <iostream>
#include <memory>
#include <queue>
using namespace std;

class d {
public:
	template <class T>
		void operator () (T *p) {
			cout <<p->cnt<<endl; 
		}
};

struct a{
	int cnt;
	unique_ptr <a, d> *next;
};

int main () {
	queue<unique_ptr<a,d>>Q;
	Q.push(unique_ptr<a,d>(new a));
	Q.pop();
}
