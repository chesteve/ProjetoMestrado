/*
 * PrintCharFlow.h
 *
 *  Created on: 9 de mai de 2017
 *      Author: anderson
 */

#ifndef PRINTCHARFLOW_H_
#define PRINTCHARFLOW_H_

#include "DummyFlow.h"

class PrintCharFlow: public DummyFlow
{
public:
	PrintCharFlow()
	{

	}
	virtual ~PrintCharFlow()
	{

	}
	void flowGenerate(counter flowId, time_sec onTime, unsigned int npackets,
			string netInterface)
	{

	}
};

#endif /* PRINTCHARFLOW_H_ */
