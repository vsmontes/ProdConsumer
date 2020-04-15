#pragma once
#include <queue>
#include <thread>

#define BUFFER_COUNT (1000)
#define	MAX_BUFFER_SIZE (1000)

using namespace std;

template <typename T>
class CProducer
{

public:	

	unsigned long long	m_TotalRead;

	volatile bool		m_bProducerEnable;

	volatile bool		m_bConsumerEnable;

	volatile bool		m_bLoop;

	volatile int		m_CurrentWriteBuffer;

	queue<T>			m_Data[BUFFER_COUNT];

	CProducer(void);

	~CProducer(void);

protected:

	thread			ProdWorker;

	void			GetData();

	virtual T		GetStuff();
};

