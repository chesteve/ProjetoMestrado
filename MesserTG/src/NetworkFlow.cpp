/*
 * NetworkFlow.cpp
 *
 *  Created on: 15 de set de 2016
 *      Author: apaschoalon
 */

#include "NetworkFlow.h"
#include "DummyFlow.h"
#include "DitgFlow.h"
#include "PrintCharFlow.h"
#include "IperfFlow.h"
#include "OstinatoFlow.h"
#include "NemesisFlow.h"
#include "LibtinsFlow.h"

NetworkFlow* NetworkFlow::make_flow(const string& choise)
{
	if ((choise == "ditg") || (choise == "DITG") || (choise == "D-ITG"))
	{
		return new DitgFlow;
	}
	else if ((choise == "iperf") || (choise == "Iperf") || (choise == "IPERF"))
	{
		return new IperfFlow;
	}
	else if ((choise == "ostinato") || (choise == "Ostinato")
			|| (choise == "OSTINATO"))
	{
		return new OstinatoFlow;
	}
	else if ((choise == "Nemesis") || (choise == "nemesis")
			|| (choise == "NEMESIS"))
	{
		return new NemesisFlow;
	}
	else if ((choise == "Libtins") || (choise == "libtins")
			|| (choise == "LIBTINS"))
	{
		return new LibtinsFlow;
	}
	else
	{
		return new DummyFlow;
	}
}

NetworkFlow::NetworkFlow()
{

	///flow-level parameters initialization
	flowId = 0;
	flow_ds_byte = 0;
	flow_duration = 0;
	flow_start_delay = 0;
	number_of_kbytes = 0;
	number_of_packets = 0;

	///protocols parameters  initialization

	link_protocol = PROTOCOL__ETHERNET; //default
	mac_src = "";
	mac_dst = "";
	network_dst_addr = "";
	network_src_addr = "";
	network_protocol = PROTOCOL__IPV4; //default
	network_ttl = 64; //default
	network_hostList_conter = 0;
	transport_protocol = PROTOCOL__UDP; //default
	transport_dst_port = 0;
	transport_sctp_association_id = 0;
	transport_sctp_max_streams = 0;
	transport_src_port = 0;
	application_protocol = PROTOCOL__NULL;

	/// Interarrival
	ptr_interArrivalModelList = NULL;
	interDepertureTimeModel_counter = 0;
	ptr_session_onTimes = NULL;
	ptr_session_offTimes = NULL;
	sessionOnTimes_counter = 0;
	sessionOffTimes_counter = 0;

	/// Packet size parameters
	ptr_psMode1 = NULL;
	ptr_psMode2 = NULL;
	nkbytes_mode1 = 0;
	nkbytes_mode2 = 0;
	npacket_mode1 = 0;
	npackets_mode2 = 0;
	packetSizeModel1_counter = 0;
	packetSizeModel2_counter = 0;

}

NetworkFlow::~NetworkFlow()
{
	MESSER_LOG_INIT(DEBUG);
	//MESSER_DEBUG("@ <%s, %s>");

	ptr_interArrivalModelList->clear();
	ptr_session_onTimes->clear();
	ptr_session_offTimes->clear();

	ptr_psMode1->clear();
	ptr_psMode2->clear();

	//DEBUG
	//MESSER_DEBUG("ptr_interArrivalModelList->size(): %d <%s, %s>",
	//		ptr_interArrivalModelList->size());
	//MESSER_DEBUG("ptr_psMode1->size():%d  <%s, %s>", ptr_psMode1->size());
	//MESSER_DEBUG("ptr_psMode2->size(): %d <%s, %s>", ptr_psMode2->size());

	/// interarrival data structs
	delete ptr_interArrivalModelList;

	delete ptr_session_onTimes;
	delete ptr_session_offTimes;

	/// packet-size data structures
	delete ptr_psMode1;
	delete ptr_psMode2;
}

void NetworkFlow::print()
{
	//TODO
	cout << "flow created" << endl;
}

int NetworkFlow::randTranportPort()
{
	return (rand() % (MAX_TRANSPORT_PORT_NUMBER + 1));
}

//TODO implementar a lista de hosts -> catch these values from a list
string NetworkFlow::getHostIP()
{
	string dstIP;
	pthread_mutex_t lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	if (network_hostList_conter == 0)
	{
		dstIP = "172.16.0.1";
		network_hostList_conter++;
	}
	else
	{
		dstIP = "172.16.0.2";
		network_hostList_conter = 0;
	}
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);

	return (dstIP);
}

unsigned int NetworkFlow::getFlowDsByte() const
{
	return flow_ds_byte;
}

void NetworkFlow::setFlowDsByte(unsigned int flowDsByte)
{
	//allowed range [0, 255]
	//Under Linux you need root privileges to set the DS byte to a value
	//larger than 160
	if (flowDsByte < 255)
		flow_ds_byte = flowDsByte;
	else
		flow_ds_byte = 255;
}

protocol NetworkFlow::getApplicationProtocol() const
{
	return application_protocol;
}

void NetworkFlow::setApplicationProtocol(protocol applicationProtocol)
{
	application_protocol = applicationProtocol;
}

double NetworkFlow::getFlowDuration() const
{
	return flow_duration;
}

void NetworkFlow::setFlowDuration(double flowDuration)
{
	flow_duration = flowDuration;
}

double NetworkFlow::getFlowStartDelay() const
{
	return flow_start_delay;
}

void NetworkFlow::setFlowStartDelay(double flowStartDelay)
{
	flow_start_delay = flowStartDelay;
}

protocol NetworkFlow::getLinkProtocol() const
{
	return link_protocol;
}

void NetworkFlow::setLinkProtocol(protocol linkProtocol)
{
	link_protocol = linkProtocol;
}

const string& NetworkFlow::getNetworkDstAddr() const
{
	return network_dst_addr;
}

void NetworkFlow::setNetworkDstAddr(const string& networkDstAddr)
{
	network_dst_addr = networkDstAddr;
}

int NetworkFlow::getNetworkHostListConter() const
{
	return network_hostList_conter;
}

void NetworkFlow::setNetworkHostListConter(int networkHostListConter)
{
	network_hostList_conter = networkHostListConter;
}

protocol NetworkFlow::getNetworkProtocol() const
{
	return network_protocol;
}

void NetworkFlow::setNetworkProtocol(protocol networkProtocol)
{
	network_protocol = networkProtocol;
}

const string& NetworkFlow::getNetworkSrcAddr() const
{
	return network_src_addr;
}

void NetworkFlow::setNetworkSrcAddr(const string& networkSrcAddr)
{
	network_src_addr = networkSrcAddr;
}

unsigned int NetworkFlow::getNetworkTtl() const
{
	return network_ttl;
}

void NetworkFlow::setNetworkTtl(unsigned int networkTtl)
{
	network_ttl = networkTtl;
}

unsigned long int NetworkFlow::getNumberOfKbytes() const
{
	return number_of_kbytes;
}

void NetworkFlow::setNumberOfKbytes(unsigned long int numberOfKbytes)
{
	number_of_kbytes = numberOfKbytes;
}

unsigned long int NetworkFlow::getNumberOfPackets() const
{
	return number_of_packets;
}

void NetworkFlow::setNumberOfPackets(unsigned long int numberOfPackets)
{
	number_of_packets = numberOfPackets;
}

unsigned int NetworkFlow::getTransportDstPort() const
{
	return transport_dst_port;
}

void NetworkFlow::setTransportDstPort(unsigned int transportDstPort)
{
	transport_dst_port = transportDstPort;
}

unsigned int NetworkFlow::getTransportSctpAssociationId() const
{
	return transport_sctp_association_id;
}

void NetworkFlow::setTransportSctpAssociationId(
		unsigned int transportSctpAssociationId)
{
	transport_sctp_association_id = transportSctpAssociationId;
}

unsigned int NetworkFlow::getTransportSctpMaxStreams() const
{
	return transport_sctp_max_streams;
}

void NetworkFlow::setTransportSctpMaxStreams(
		unsigned int transportSctpMaxStreams)
{
	transport_sctp_max_streams = transportSctpMaxStreams;
}

unsigned int NetworkFlow::getTransportSrcPort() const
{
	return transport_src_port;
}

void NetworkFlow::setTransportSrcPort(unsigned int transportSrcPort)
{
	transport_src_port = transportSrcPort;
}

protocol NetworkFlow::getTransportProtocol() const
{
	return transport_protocol;
}

void NetworkFlow::setTransportProtocol(protocol transportProtocol)
{
	transport_protocol = transportProtocol;
}

StochasticModelFit NetworkFlow::getInterDepertureTimeModel_next()
{

	StochasticModelFit themodel;
	unsigned int i = 0;

	if (ptr_interArrivalModelList == NULL)
	{
		themodel.set(NO_MODEL, 0, 0, datum::inf, datum::inf);
		ptr_interArrivalModelList->push_back(themodel);

		cerr << "Error @ " << __PRETTY_FUNCTION__ << endl
				<< "Trying to get a StochasticModelFit, but no model was set.\n"
				<< "NO_MODEL set as default" << endl;
	}
	else
	{

		for (list<StochasticModelFit>::iterator it =
				ptr_interArrivalModelList->begin();
				it != ptr_interArrivalModelList->end(); it++)
		{
			if (i >= interDepertureTimeModel_counter)
			{

				themodel = *it;
				break;
			}
			else
			{
				i++;
			}

		}

	}

	if ((ptr_interArrivalModelList->size() - 1)
			> interDepertureTimeModel_counter)
	{
		interDepertureTimeModel_counter++;
	}

	return (themodel);

}

void NetworkFlow::setInterDepertureTimeModels(
		list<StochasticModelFit>* modelList)
{

	ptr_interArrivalModelList = modelList;
	interDepertureTimeModel_counter = 0;
}

void NetworkFlow::setSessionTimesOnOff(vector<time_sec>* onTimesVec,
		vector<time_sec>* offTimesVec)
{
	ptr_session_onTimes = onTimesVec;
	ptr_session_offTimes = offTimesVec;
}

time_sec NetworkFlow::getSessionOnTime_next()
{
	//MESSER_LOG_INIT(NOTICE);
	time_sec theTime = 0;

	//MESSER_DEBUG("ptr_session_onTimes->size()=%d", ptr_session_onTimes->size());

	if (sessionOnTimes_counter >= ptr_session_onTimes->size())
	{
		//MESSER_DEBUG(
		//		"No more On times available on the stack. The last was the %dth value. It will be reseted  @ <%s, %s>",
		//		sessionOnTimes_counter);
		sessionOnTimes_counter = 0;
		theTime = ptr_session_onTimes->at(sessionOnTimes_counter);

	}
	else
	{
		theTime = ptr_session_onTimes->at(sessionOnTimes_counter);
		sessionOnTimes_counter++;
	}

	return (theTime);
}

time_sec NetworkFlow::getSessionOffTime_next()
{
	MESSER_LOG_INIT(NOTICE);
	time_sec theTime = 0;

	if (sessionOffTimes_counter >= ptr_session_offTimes->size())
	{
//		MESSER_DEBUG(
//				"No more Off times available on the stack. The last was the \
//%dth value. Now, it will return 0, and than will be reseted. This is because, \
//the On/Off times should aways start with a On. After that, it will be reseted  @ <%s, %s>",
//				sessionOffTimes_counter);

		//theTime = ptr_session_offTimes->at(sessionOffTimes_counter);
		theTime = 0;
		sessionOffTimes_counter = 0;

	}
	else
	{
		theTime = ptr_session_offTimes->at(sessionOffTimes_counter);
		sessionOffTimes_counter++;
	}

	return (theTime);
}

StochasticModelFit NetworkFlow::getPacketSizeModelMode1_next()
{
	StochasticModelFit themodel;
	if (ptr_psMode1 == NULL)
	{
		themodel.set(NO_MODEL, 0, 0, datum::inf, datum::inf);
		ptr_psMode1->push_back(themodel);
	}
	else
	{
		counter i = 0;
		for (list<StochasticModelFit>::iterator it = ptr_psMode1->begin();
				it != ptr_psMode1->end(); it++)
		{
			if (i == packetSizeModel1_counter)
			{
				themodel = *it;
				break;
			}
			i++;

		}
	}

	if (ptr_psMode1->size() > packetSizeModel1_counter)
	{
		packetSizeModel1_counter++;
	}

	return (themodel);
}

StochasticModelFit NetworkFlow::getPacketSizeModelMode2_next()
{
	StochasticModelFit themodel;
	if (ptr_psMode2 == NULL)
	{
		themodel.set(NO_MODEL, 0, 0, datum::inf, datum::inf);
		ptr_psMode2->push_back(themodel);
	}
	else
	{
		counter i = 0;
		for (list<StochasticModelFit>::iterator it = ptr_psMode2->begin();
				it != ptr_psMode2->end(); it++)
		{
			if (i == packetSizeModel2_counter)
			{
				themodel = *it;
				break;
			}
			i++;

		}
	}

	if (ptr_psMode2->size() > packetSizeModel2_counter)
	{
		packetSizeModel2_counter++;
	}

	return (themodel);

}

void NetworkFlow::setPacketSizeModel(list<StochasticModelFit>* modelVet1,
		list<StochasticModelFit>* modelVet2, long int nkbytesMode1,
		long int nkbytesMode2, long int nPacketsMode1, long int nPacketsMode2)
{
	ptr_psMode1 = modelVet1;
	ptr_psMode2 = modelVet2;
	packetSizeModel1_counter = 0;
	packetSizeModel2_counter = 0;
	nkbytes_mode1 = nkbytesMode1;
	nkbytes_mode2 = nkbytesMode2;
	npacket_mode1 = nPacketsMode1;
	npackets_mode2 = nPacketsMode2;

}

long int NetworkFlow::getNkbytesMode1() const
{
	return nkbytes_mode1;
}

long int NetworkFlow::getNkbytesMode2() const
{
	return nkbytes_mode2;
}

long int NetworkFlow::getNpacketsMode1() const
{
	return npacket_mode1;
}

unsigned int NetworkFlow::getNumberOfInterdepertureTimeModels()
{
	if (ptr_interArrivalModelList != NULL)
	{
		return (ptr_interArrivalModelList->size());
	}
	else
	{
		return (0);
	}
}

//TODO test -> not tested
unsigned int NetworkFlow::getNumberOfPsMode1Models() const
{
	if (ptr_psMode1 != NULL)
	{
		return (ptr_psMode1->size());
	}
	else
	{
		return (0);
	}
}

//TODO test -> not tested
unsigned int NetworkFlow::getNumberOfPsMode2Models() const
{
	if (ptr_psMode2 != NULL)
	{
		return (ptr_psMode2->size());
	}
	else
	{
		return (0);
	}
}

long int NetworkFlow::getNpacketsMode2() const
{
	return npackets_mode2;
}
void NetworkFlow::setMacAddr(const string& macSrc, const string& macDst)
{
	mac_src = macSrc;
	mac_dst = macDst;
}

const string& NetworkFlow::getMacSrcAddr()
{
	return (mac_src);
}

const string& NetworkFlow::getMacDstAddr()
{
	return (mac_dst);
}

void NetworkFlow::resetCounters()
{
	interDepertureTimeModel_counter = 0;
	sessionOnTimes_counter = 0;
	sessionOffTimes_counter = 0;
	packetSizeModel1_counter = 0;
	packetSizeModel2_counter = 0;
}

inline int NetworkFlow::getLocalIfIp(char* interface, char* ipaddr)
{
	struct ifaddrs *ifaddr, *ifa;
	int family, s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1)
	{
		perror("getifaddrs");
		return (-1);
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
	{

		if (ifa->ifa_addr == NULL)
			continue;

		s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host,
		NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		if ((strcmp(ifa->ifa_name, "lo") != 0)
				&& (ifa->ifa_addr->sa_family == AF_INET))
		{
			if (s != 0)
			{
				printf("getnameinfo() failed: %s\n", gai_strerror(s));
				return (-2);
			}
			strcpy(interface, ifa->ifa_name);
			strcpy(ipaddr, host);
			break;
		}
	}

	freeifaddrs(ifaddr);
	return (0);
}

inline int NetworkFlow::getLocalIp(const char* interface, char* ipaddr)
{
	struct ifaddrs *ifaddr, *ifa;
	int family, s;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1)
	{
		perror("getifaddrs");
		return (-1);
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
	{

		if (ifa->ifa_addr == NULL)
			continue;

		s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host,
		NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		if ((strcmp(ifa->ifa_name, interface) == 0)
				&& (ifa->ifa_addr->sa_family == AF_INET))
		{
			if (s != 0)
			{
				printf("getnameinfo() failed: %s\n", gai_strerror(s));
				return (-2);
			}

			strcpy(ipaddr, host);
			break;
		}
	}

	freeifaddrs(ifaddr);
	return (0);
}

//DEBUG
void NetworkFlow::printModels()
{

	for (list<StochasticModelFit>::iterator it =
			ptr_interArrivalModelList->begin();
			it != ptr_interArrivalModelList->end(); it++)
	{
		it->print();
	}

}

vector<time_sec> *NetworkFlow::getSessionOnVector()
{
	return (ptr_session_onTimes);
}

vector<time_sec> *NetworkFlow::getSessionOffVector()
{
	return (ptr_session_offTimes);
}

//DEBUG ERASE IT
//void NetworkFlow::logOnOff()
//{
//	MESSER_LOG_INIT(DEBUG);
//
//	char ontimes[CHAR_LARGE_BUFFER];
//	char offtimes[CHAR_LARGE_BUFFER];
//	vector2str(*ptr_session_onTimes, ontimes);
//	vector2str(*ptr_session_offTimes, offtimes);
//	MESSER_DEBUG("trace>> ontimes=[%s], offtimes=[%s]", ontimes, offtimes);
//}
