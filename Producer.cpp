#include <iostream>
#include <chrono>
#include <thread>
#include "Producer.h"

template class CProducer<int>; 

static unsigned int counter = 1;


template <typename T>
CProducer<T>::CProducer(void)
{
	m_TotalRead = 0;
	m_bLoop = true;
	m_bProducerEnable = true;
	m_bConsumerEnable = true;
	m_CurrentWriteBuffer = 0;
	ProdWorker = thread(&CProducer<T>::GetData,this);
}


template <typename T>
CProducer<T>::~CProducer(void)
{
}


template <typename T>
void CProducer<T>::GetData(void)
{
	while(m_bLoop)
	{
		if (m_bProducerEnable)
		{	
			m_Data[m_CurrentWriteBuffer].push( GetStuff() );

			m_TotalRead++;

			if ( counter == 1000 )
			{
				m_bProducerEnable = false;
				cout << "Total Read: " << m_TotalRead << endl;
			}

			if (m_Data[m_CurrentWriteBuffer].size() > MAX_BUFFER_SIZE)
			{
				if (m_CurrentWriteBuffer == (BUFFER_COUNT-1))
					m_CurrentWriteBuffer = 0;
				else
					m_CurrentWriteBuffer++;
			}
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

}


template <typename T>
T CProducer<T>::GetStuff(void)
{
	return T(counter++);
}