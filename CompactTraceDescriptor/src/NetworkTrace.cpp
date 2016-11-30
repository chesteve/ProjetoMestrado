/*
 * NetworkTrace.cpp
 *
 *  Created on: 14 de jun de 2016
 *      Author: apaschoalon
 */

#include "NetworkTrace.h"

//NetworkTrace::NetworkTrace(long int nFlows)
//{
//	netFlow = new NetworkFlow[nFlows + 1];
//	numberOfFlows = nFlows + 1;
//}
NetworkTrace::NetworkTrace(string trafficGen)
{
	trafficGenEngine = trafficGen;
}

NetworkTrace::NetworkTrace()
{
}

NetworkTrace::NetworkTrace(FILE* CompactTraceDescriptor, string trafficGen)
{
	trafficGenEngine = trafficGen;
	//TODO Read data from a file

}

NetworkTrace::~NetworkTrace()
{
	for (unsigned int i = 0; i < networkFlow.size(); i++)
		delete[] networkFlow[i];
}

const string& NetworkTrace::getInfoCaptureDate() const
{
	return info_captureDate;
}

void NetworkTrace::setInfoCaptureDate(const string& infoCaptureDate)
{
	info_captureDate = infoCaptureDate;
}

const string& NetworkTrace::getInfoCaptureInterface() const
{
	return info_captureInterface;
}

void NetworkTrace::setInfoCaptureInterface(const string& infoCaptureInterface)
{
	info_captureInterface = infoCaptureInterface;
}

const string& NetworkTrace::getInfoCommentaries() const
{
	return info_commentaries;
}

void NetworkTrace::setInfoCommentaries(const string& infoCommentaries)
{
	info_commentaries = infoCommentaries;
}

const string& NetworkTrace::getInfoTracename() const
{
	return info_tracename;
}

void NetworkTrace::setInfoTracename(const string& infoTracename)
{
	info_tracename = infoTracename;
}

int NetworkTrace::writeToFile(void) const
{
	int returnFlag = 0;

	writeToFile(info_tracename);

	return returnFlag;
}

int NetworkTrace::writeToFile(const string& fileName) const
{
	int returnFlag = 0;

	//TODO

	return returnFlag;
}

long int NetworkTrace::getNumberOfFlows() const
{

	return (networkFlow.size());
	//return numberOfFlows;
}

const string NetworkTrace::toString() const
{
	string tostring = "";

	tostring = info_tracename + info_captureInterface + info_captureDate
			+ info_commentaries;

	return (tostring);
}

int NetworkTrace::pushback_Netflow(NetworkFlow* vetNetFlow)
{
	networkFlow.push_back(vetNetFlow);
	return (0);
}

int NetworkTrace::exec(bool verbose)
{
	int size = this->getNumberOfFlows();
	int i = 0;
	std::thread* th_flw = new std::thread[size];

#ifdef DEBUG_NetworkTrace_exec
	cout << "this->getNumberOfFlows() = " << this->getNumberOfFlows() << endl;
#endif

	for (i = 0; i < size; i++)
	{
		//TODO passar o tipo de flow(dummy, ostinado, ditg), e um contador indicando o numero da flow
		th_flw[i] = networkFlow[i]->flowThread();
		//dummy
		//th_flw[i] = netFlow[i].flowThread2();
	}
	for (i = 0; i < size; i++)
	{
		th_flw[i].join();
	}

	delete[] th_flw;

	return 0;

}
