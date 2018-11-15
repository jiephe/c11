#include <atomic>
#include "test_thread.h"
#include "BlockingQueue.h"

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

BlockingQueue<int> bq;
int put_count = 20;
int take_count = 20; 

void bq_func1()
{
	for (int i = 0; i < put_count; ++i)
	{
		bq.put(i);
		printf("put value is : %d\n", i);
	}
}

void bq_func12()
{
	for (int i = 0; i < take_count; ++i)
	{
		int a = bq.take();
		printf("take value is : %d\n", a);
	}
}

int main()
{
	//test BlockingQueue
	std::thread bq_1(bq_func1);
	std::thread bq_2(bq_func12);

	bq_1.join();

	//for _BLOCK_ wait forever
	bq_2.join();

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