/*
 * DummyFlow.h
 *
 *  Created on: 14 de jun de 2016
 *      Author: apaschoalon
 */

#ifndef DUMMYFLOW_H_
#define DUMMYFLOW_H_

#include "NetworkFlow.h"

class DummyFlow: public NetworkFlow
{
public:
	/**
	 *
	 */
	DummyFlow();

	/**
	 *
	 */
	virtual ~DummyFlow();

	/**
	 *
	 * @return
	 */
	int server();

	/**
	 *
	 * @param flowId
	 * @param onTime
	 * @param npackets
	 * @param nbytes
	 * @param netInterface
	 */
	void flowGenerate(const counter& flowId, const time_sec& onTime,
			const uint& npackets, const uint& nbytes,
			const string& netInterface);

	void flowStart();

	std::thread flowThread()
	{
		return std::thread([=]
		{	flowStart();});
	}

private:

	/**
	 *
	 * @param sleep_time
	 */
	void fsleep(time_sec sleep_time);

};

#endif /* DUMMYFLOW_H_ */
