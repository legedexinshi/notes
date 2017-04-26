#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct A{
	char *x;
	A (A&& a) {
		x=a.x;
		a.x=0;
		cout <<233<<endl;
	}
	~A() {
		delete x;
	}
	A() {cout<<2<<endl;x=new char;*x='A';}
};

int x(int a) {
	int f=2;
	return a*f;
}
A x() {
	A c;
	cout <<*c.x<<' '<<c.x<<endl;
	return c;
}
int main () {
	A a,b;
	cout <<*a.x<<' '<<a.x<<endl;
	cout <<*b.x<<' '<<b.x<<endl;
	A c(	(	x()));
	cout <<*c.x<<' '<<c.x<<endl;
}
