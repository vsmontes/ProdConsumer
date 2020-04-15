#pragma once
#include <stack>
#include <thread>

#include "Producer.h"

using namespace std;

template <typename T>
class CConsumer
{

public:

	CConsumer(CProducer<T> * prod);

	~CConsumer(void);

protected:

	unsigned long long		m_TotalProcessed;

	int						m_CurrentReadBuffer;

	CProducer<T> *			m_Producer;

	stack<T>				m_ProcessedData[BUFFER_COUNT];

	thread					ProcessWorker;

	void					ProcessData();

	virtual T				DoStuff(T in);
};

