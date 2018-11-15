#pragma once

#include <atomic>
#include <memory>
#include <thread>
#include <windows.h>

class CThreadTest
{
public:
	CThreadTest();
	~CThreadTest();

	void StartThread();
	void StopThread();

public:
	static DWORD WINAPI old_cb(LPVOID arg);

	void new_cb();

private:
	std::atomic<int>				m_int_;
	std::shared_ptr<std::thread>	m_new_thread_;
	HANDLE							m_old_thread_;
};