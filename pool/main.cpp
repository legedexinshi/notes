#include <iostream>
#include "ThreadPool_c11.cpp"

using namespace std;

void *func (void *x) {
	int *X = (int *)x;
	printf("task %d is being excuted by thread 0x%lx\n"
			, *X, (unsigned long)pthread_self());
	sleep(5);
	printf("task %d is finished by thread 0x%lx\n"
			, *X, (unsigned long)pthread_self());
	return (void *)0;
}

int main() {
	ThreadPool Tp;
	Tp.init(5);
	while (1) {
		int *x = new int;
		cin >> *x;
		if (*x == 0) break;
		Tp.addtask (func, x);
	}
	Tp.destroy();
	cout << "over" << endl;
	sleep(10);
}
