/*
 * OstinatoFlow.h
 *
 *  Created on: 30 de abr de 2017
 *      Author: anderson
 */

#ifndef OSTINATOFLOW_H_
#define OSTINATOFLOW_H_

// Usar essa API https://github.com/little-dude/simple-ostinato

#include "NetworkFlow.h"
#include "DummyFlow.h"

class OstinatoFlow: public DummyFlow
{
public:

	OstinatoFlow()
	{

	}

	virtual ~OstinatoFlow()
	{

	}

	inline void flowGenerate(const counter& flowId, const time_sec& onTime,
			const unsigned int& npackets, const string& netInterface)
	{

	}
};

#endif /* OSTINATOFLOW_H_ */
