#include "test_thread.h"

CThreadTest::CThreadTest()
	:m_int_(100)
{}

CThreadTest::~CThreadTest()
{}

void CThreadTest::StartThread()
{
	m_new_thread_.reset(new std::thread([this] {this->new_cb(); }));

	int count = m_new_thread_.use_count();
	std::thread* pThread = m_new_thread_.get();

	DWORD  threadId;
	m_old_thread_ = CreateThread(NULL, 0, old_cb, this, 0, &threadId);
}

void CThreadTest::StopThread()
{
	m_new_thread_->join();

	WaitForSingleObject(m_old_thread_, INFINITE);
}

DWORD CThreadTest::old_cb(LPVOID arg)
{
	CThreadTest* pThreadTest = (CThreadTest*)arg;

	printf("m_int_ is : %d\n", pThreadTest->m_int_._My_val);

	return 0;
}

void CThreadTest::new_cb()
{
	printf("m_int_ is : %d\n", m_int_._My_val);
}