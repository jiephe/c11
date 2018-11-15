#include <atomic>
#include "test_thread.h"

int count = 10000;
std::atomic_int iAtomicVar = count;
int iVar = count;

void fun1()
{
	for (int i = 0; i < count/2; i++)
	{
		iAtomicVar--;
		iVar--;
	}
}

void fun2()
{
	for (int i = 0; i < count/2; i++)
	{
		iAtomicVar--;
		iVar--;
	}
}

int main()
{
	//test thread & Lambda
	CThreadTest ct;
	ct.StartThread();
	ct.StopThread();

	//---------------------------------------------------
	//test atomic

	std::thread t1(fun1);
	std::thread t2(fun2);

	t1.join();
	t2.join();

	printf("iAtomicVar: %d\n", iAtomicVar._My_val);
	printf("iVar: %d\n", iVar);

	while (true)
	{
		auto c = getchar();
		if (c == 'q')
			break;
	}

	return 0;
}