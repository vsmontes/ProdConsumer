
#include <stdio.h>

#include "Producer.h"
#include "Consumer.h"

int main()
{

	CProducer<int> prod;
	CConsumer<int> con(&prod);

	getchar();

	return 0;
}