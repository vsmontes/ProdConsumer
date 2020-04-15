#include <iostream>
#include <chrono>
#include <thread>

#include "Consumer.h"
#include "Producer.h"

template class CConsumer<int>; 

template <typename T>
CConsumer<T>::CConsumer(CProducer<T> * prod)
{
	m_TotalProcessed = 0;
	m_CurrentReadBuffer = 0;
	m_Producer = prod;
	ProcessWorker = thread(&CConsumer<T>::ProcessData,this);
}


template <typename T>
CConsumer<T>::~CConsumer(void)
{
}


template <typename T>
void CConsumer<T>::ProcessData(void)
{
	while (m_Producer->m_bLoop)
	{
		if  (m_Producer->m_bConsumerEnable) 
		{
			if ( (m_CurrentReadBuffer != m_Producer->m_CurrentWriteBuffer) || (m_Producer->m_bProducerEnable == false) ) 
			{
				if ( ! m_Producer->m_Data[m_CurrentReadBuffer].empty() )
				{
					m_ProcessedData[m_CurrentReadBuffer].push( DoStuff(m_Producer->m_Data[m_CurrentReadBuffer].front()) );
					m_Producer->m_Data[m_CurrentReadBuffer].pop();
					m_TotalProcessed++;
				}
				else
				{
					if (m_CurrentReadBuffer == (BUFFER_COUNT-1))
						m_CurrentReadBuffer = 0;
					else
					{
						m_CurrentReadBuffer++;
					}
				}
			}

			if ( (m_Producer->m_bProducerEnable == false) && (m_Producer->m_TotalRead == m_TotalProcessed) )
			{
				cout << "Total Processed: " << m_TotalProcessed << endl;
				m_Producer->m_bConsumerEnable = false;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

template <typename T>
T CConsumer<T>::DoStuff(T in)
{
	return T(in * 10);
}