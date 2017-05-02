/*
 * NetworkFlow.h
 *
 *  Created on: 15 de set de 2016
 *      Author: apaschoalon
 */

#ifndef NETWORKFLOW_H_
#define NETWORKFLOW_H_

//external libraries
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <string>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <pthread.h>
#include <string>
#include <list>
#include <ITGapi.h>
#include <vector>

//local includes

#include "Defines.h"
#include "Protocol.h"
#include "StochasticModelFit.h"
#include "RegressionTests.h"

//namespaces
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::list;
using std::vector;

class NetworkFlow
{
public:
	//Create flow
	NetworkFlow();
	virtual ~NetworkFlow();
	static NetworkFlow *make_flow(string choise);
	virtual void print() = 0;

	virtual std::thread flowThread() = 0;
	virtual void flowGenerate() = 0;

	//
	//Flow-level data
	//
	virtual time_sec getFlowDuration() const = 0;
	virtual void setFlowDuration(time_sec flowDuration) = 0;
	virtual time_sec getFlowStartDelay() const = 0;
	virtual void setFlowStartDelay(time_sec flowStartDelay) = 0;
	virtual unsigned long int getNumberOfKbytes() const = 0;
	virtual void setNumberOfKbytes(unsigned long int numberOfKbytes) = 0;
	virtual unsigned long int getNumberOfPackets() const = 0;
	virtual void setNumberOfPackets(unsigned long int numberOfPackets) = 0;

	//
	//Packet-level data
	//
	virtual int randTranportPort() = 0;
	virtual unsigned int getFlowDsByte() const = 0;
	virtual void setFlowDsByte(unsigned int flowDsByte) = 0;
	virtual protocol getApplicationProtocol() const = 0;
	virtual void setApplicationProtocol(protocol applicationProtocol) = 0;
	virtual protocol getLinkProtocol() const = 0;
	virtual void setLinkProtocol(protocol linkProtocol) = 0;
	//virtual long int getLinkSrcAddrCount() const = 0;
	//virtual void setLinkSrcAddrCount(long int linkSrcAddrCount) = 0;
	virtual const string& getNetworkDstAddr() const = 0;
	virtual void setNetworkDstAddr(const string& networkDstAddr) = 0;
	virtual int getNetworkHostListConter() const = 0;
	virtual void setNetworkHostListConter(int networkHostListConter) = 0;
	virtual protocol getNetworkProtocol() const = 0;
	virtual void setNetworkProtocol(protocol networkProtocol) = 0;
	virtual const string& getNetworkSrcAddr() const = 0;
	virtual void setNetworkSrcAddr(const string& networkSrcAddr) = 0;
	virtual unsigned int getNetworkTtl() const = 0;
	virtual void setNetworkTtl(unsigned int networkTtl) = 0;
	virtual unsigned int getTransportDstPort() const = 0;
	virtual void setTransportDstPort(unsigned int transportDstPort) = 0;
	virtual unsigned int getTransportSctpAssociationId() const = 0;
	virtual void setTransportSctpAssociationId(
			unsigned int transportSctpAssociationId) = 0;
	virtual unsigned int getTransportSctpMaxStreams() const = 0;
	virtual void setTransportSctpMaxStreams(
			unsigned int transportSctpMaxStreams) = 0;
	virtual port_number getTransportSrcPort() const = 0;
	virtual void setTransportSrcPort(port_number transportSrcPort) = 0;
	virtual protocol getTransportProtocol() const = 0;
	virtual void setTransportProtocol(protocol transportProtocol) = 0;

	//
	//Packet-size
	//
	virtual StochasticModelFit getPacketSizeModelMode1_next() = 0;
	virtual StochasticModelFit getPacketSizeModelMode2_next() = 0;
//	virtual void setPacketSizeModel(StochasticModelFit* modelVet1,
//			StochasticModelFit* modelVet2, long int nkbytesMode1,
//			long int nkbytesMode2, long int nPacketsMode1,
//			long int nPacketsMode2) = 0;
	virtual void setPacketSizeModel(list<StochasticModelFit>* modelVet1,
			list<StochasticModelFit>* modelVet2, long int nkbytesMode1,
			long int nkbytesMode2, long int nPacketsMode1,
			long int nPacketsMode2) = 0;
	virtual long int getNkbytesMode1() const = 0;

	virtual long int getNkbytesMode2() const = 0;

	virtual long int getNpacketsMode1() const = 0;

	virtual long int getNpacketsMode2() const = 0;

	virtual unsigned int  getNumberOfPsMode2Models() const = 0;
	virtual unsigned int  getNumberOfPsMode1Models() const = 0;


	//DEBUG
	virtual void printModels() = 0;


	//
	//Inter-arrival-size
	//
	virtual void setInterDepertureTimeModels(list<StochasticModelFit>* modelList) = 0;
//	virtual void setInterDepertureTimeModels(StochasticModelFit* modelVet) = 0;
	virtual StochasticModelFit getInterDepertureTimeModel_next()= 0;
	virtual unsigned int getNumberOfInterdepertureTimeModels()= 0;

	virtual void setInterFileTimeModel(list<StochasticModelFit>* modelList) = 0;
//	virtual void setInterFileTimeModel(StochasticModelFit* modelVet) = 0;
	virtual StochasticModelFit getInterFileTimeModel_next() = 0;
	virtual time_sec getInterFileTime() = 0;
	virtual unsigned int getNumberOfInterfileTimeModels()= 0;

	//virtual void setInterSessionTimeModel(list<StochasticModelFit>* modelList) = 0;
	virtual void setInterSessionTimesOnOff(vector<time_sec>* onOffList) = 0;
//	virtual void setInterSessionTimeModel(StochasticModelFit* modelVet) = 0;
//	virtual StochasticModelFit getInterSessionTimeModel_next() = 0;
	virtual time_sec getInterSessionOnOffTime_next() = 0;
//	virtual time_sec getInterSessionTime() = 0;
	virtual unsigned int getNumberOfSessionOnOffTimes()= 0;

};

#endif /* NETWORKFLOW_H_ */