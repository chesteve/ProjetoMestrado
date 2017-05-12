/*
 * NetworkFlow.h
 *
 *  Created on: 15 de set de 2016
 *      Author: apaschoalon
 */

#ifndef NETWORKFLOW_H_
#define NETWORKFLOW_H_

//#define _GNU_SOURCE
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
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

//local includes

#include "Defines.h"
#include "Protocol.h"
#include "StochasticModelFit.h"
#include "RegressionTests.h"
#include "MesserLog.h"
#include "cfunctions.h"

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
	static NetworkFlow *make_flow(const string& choise);

	inline virtual std::thread flowThread() = 0;
	inline virtual void flowGenerate(const counter& flowId,
			const time_sec& onTime, const unsigned int& npackets,
			const string& netInterface) = 0;

	inline int getLocalIfIp(char* interface, char* ipaddr);

	inline int getLocalIp(const char* interface, char* ipaddr);

	virtual void print() = 0;

	void resetCounters();

	///
	///Return the next IP address form the destination-hosts file
	///@return
	///
	string getHostIP();

	///
	///returns a random transport port number
	///@return
	///
	int randTranportPort();
	protocol getApplicationProtocol() const;
	void setApplicationProtocol(protocol applicationProtocol);
	unsigned int getFlowDsByte() const;
	void setFlowDsByte(unsigned int flowDsByte);
	double getFlowDuration() const;
	void setFlowDuration(time_sec flowDuration);
	double getFlowStartDelay() const;
	void setFlowStartDelay(time_sec flowStartDelay);

	protocol getLinkProtocol() const;
	void setLinkProtocol(protocol linkProtocol);
	void setMacAddr(const string& macSrc, const string& macDst);
	const string& getMacSrcAddr();
	const string& getMacDstAddr();

	const string& getNetworkDstAddr() const;
	void setNetworkDstAddr(const string& networkDstAddr);
	int getNetworkHostListConter() const;
	void setNetworkHostListConter(int networkHostListConter);
	protocol getNetworkProtocol() const;
	void setNetworkProtocol(protocol networkProtocol);
	const string& getNetworkSrcAddr() const;
	void setNetworkSrcAddr(const string& networkSrcAddr);
	unsigned int getNetworkTtl() const;
	void setNetworkTtl(unsigned int networkTtl);
	unsigned long int getNumberOfKbytes() const;
	void setNumberOfKbytes(unsigned long int numberOfKbytes);
	unsigned long int getNumberOfPackets() const;
	void setNumberOfPackets(unsigned long int numberOfPackets);

	unsigned int getTransportDstPort() const;
	void setTransportDstPort(unsigned int transportDstPort);
	unsigned int getTransportSctpAssociationId() const;
	void setTransportSctpAssociationId(unsigned int transportSctpAssociationId);
	unsigned int getTransportSctpMaxStreams() const;
	void setTransportSctpMaxStreams(unsigned int transportSctpMaxStreams);
	unsigned int getTransportSrcPort() const;
	void setTransportSrcPort(unsigned int transportSrcPort);
	protocol getTransportProtocol() const;
	void setTransportProtocol(protocol transportProtocol);

	void setInterDepertureTimeModels(list<StochasticModelFit>* modelList);
	StochasticModelFit getInterDepertureTimeModel_next();
	unsigned int getNumberOfInterdepertureTimeModels();

	//void setInterFileTimeModel(list<StochasticModelFit>* modelList);
	//StochasticModelFit getInterFileTimeModel_next();
	//time_sec getInterFileTime();
	//unsigned int getNumberOfInterfileTimeModels();

	void setSessionTimesOnOff(vector<time_sec>* onTimesVec,
			vector<time_sec>* offTimesVec);
	time_sec getSessionOnTime_next();
	time_sec getSessionOffTime_next();
//	void getSessionOfOffVectors(vector<time_sec>* onTimes,
//			vector<time_sec>* offTimes);
	vector<time_sec>* getSessionOnVector();
	vector<time_sec>* getSessionOffVector();

	StochasticModelFit getPacketSizeModelMode1_next();
	StochasticModelFit getPacketSizeModelMode2_next();

	void setPacketSizeModel(list<StochasticModelFit>* modelList1,
			list<StochasticModelFit>* modelList2, long int nkbytesMode1,
			long int nkbytesMode2, long int nPacketsMode1,
			long int nPacketsMode2);
	long int getNkbytesMode1() const;
	long int getNkbytesMode2() const;
	long int getNpacketsMode1() const;
	long int getNpacketsMode2() const;

	unsigned int getNumberOfPsMode2Models() const;
	unsigned int getNumberOfPsMode1Models() const;

	//DEBUG
	void printModels();

	unsigned int getFlowId() const
	{
		return flowId;
	}

	void setFlowId(unsigned int flowId)
	{
		this->flowId = flowId;
	}

	//void logOnOff();

private:

	////////////////////////////////////////////////////////////////////////////
	/// Flow-level options
	////////////////////////////////////////////////////////////////////////////

	time_sec flow_duration;
	time_sec flow_start_delay;
	unsigned int flow_ds_byte;
	unsigned long int number_of_packets;
	unsigned long int number_of_kbytes;
	unsigned int flowId;

	////////////////////////////////////////////////////////////////////////////
	/// Protocol stack options
	////////////////////////////////////////////////////////////////////////////

	/// L2: Link Layer
	protocol link_protocol;
	string mac_src;
	string mac_dst;

	/// L3: Network Layer
	unsigned int network_ttl;
	protocol network_protocol;
	string network_dst_addr;
	string network_src_addr;
	int network_hostList_conter;

	///L4: Transport Layer
	unsigned int transport_dst_port;
	unsigned int transport_src_port;
	protocol transport_protocol;
	unsigned int transport_sctp_association_id;
	unsigned int transport_sctp_max_streams;

	/// L5: Application Layer
	protocol application_protocol;

	////////////////////////////////////////////////////////////////////////////
	/// Interperture time
	////////////////////////////////////////////////////////////////////////////

	/// Interarrival
	list<StochasticModelFit>* ptr_interArrivalModelList; //file interdeperture time
	counter interDepertureTimeModel_counter = 0; //counter of for model get method
	/// Session on/off
	vector<time_sec>* ptr_session_onTimes;
	vector<time_sec>* ptr_session_offTimes;
	counter sessionOnTimes_counter = 0;
	counter sessionOffTimes_counter = 0;

	////////////////////////////////////////////////////////////////////////////
	///Packet Size Model
	////////////////////////////////////////////////////////////////////////////

	list<StochasticModelFit>* ptr_psMode1;
	list<StochasticModelFit>* ptr_psMode2;
	long int nkbytes_mode1;
	long int nkbytes_mode2;
	long int npacket_mode1;
	long int npackets_mode2;
	counter packetSizeModel1_counter;
	counter packetSizeModel2_counter;

};

#endif /* NETWORKFLOW_H_ */
