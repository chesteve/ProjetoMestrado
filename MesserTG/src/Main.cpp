//============================================================================
// Name        : CompactTraceDescriptor.cpp
// Author      : Anderson Paschoalon
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DatabaseInterface.h"
#include "DataProcessor.h"
#include "DummyFlow.h"
#include "NetworkTrace.h"
//#include "TestClass.h"
#include "Defines.h"
#include "Protocol.h"
#include "cfunctions.h"


//#define DEBUG 1
#define EXEC_BIN 1
#define REGRESSION_TESTS 1


//using namespace std;

int main()
{
#ifdef REGRESSION_TESTS
	RegressionTests rt;

	DataProcessor regTest_dp = DataProcessor();
	Protocol regTest_proto = Protocol();
	NetworkTrace regTest_nt;
	StochasticModelFit unityTest_smf = StochasticModelFit();

	regTest_dp.regression_tests();
	regTest_nt.regression_tests();
	regTest_proto.regression_tests();
	unityTest_smf.unity_tests();
	cfunctions_unitytests();

	rt.wait_int("Finished tests, press any key...");
#endif

	//TODO the main function is the controller: it should parse the
	// command-line options, instantiate any component, and say what it
	//should do. So it should parse the command

	string experimentName = "live_background-traffic-1";
	DataProcessor dp;
	DatabaseInterface dbif;
	long int nflows = 0;
	NetworkTrace* trace = NULL;

	cout << "creating a network trace" << endl;

	//Create Network Trace from database
	//TODO: the data object structure do not have to change.. I just want a
	// constructor that uses a experiment name and a database interface pointer
	// as input.
	dbif.getNumberOfFlows(experimentName, &nflows);

	trace = new NetworkTrace();

	dp.calculate(experimentName, &dbif, trace);

	trace->setInfoTracename("teste-chapolin");
	trace->setInfoCommentaries("este e um teste do compact trace descriptor");
	trace->setTrafficGenEngine("D-ITG");
	trace->setInfoCaptureInterface("eth0");
	trace->setInfoCaptureDate("07/04/2017");
	trace->writeToFile("kkk.xml");

#ifdef EXEC_BIN


	cout << "executing network trace" << endl;
	trace->exec(true);

	delete trace;

	//cout << "sleep before the next trace" << endl;
	//sleep(160);
#endif

#ifdef DEBUG_NetworkFlow
	cout << "trace->networkFlow[0]->getNetworkProtocol() = " << trace->networkFlow[0]->getNetworkProtocol() << endl;
	cout << "trace->networkFlow[0]->getNetworkDstAddr() = " << trace->networkFlow[0]->getNetworkDstAddr() << endl;
	cout << "trace->networkFlow[0]->getTransportProtocol()  = " << trace->networkFlow[0]->getTransportProtocol() << endl;
	cout << "trace->networkFlow[0]->getTransportDstPort() = " << trace->networkFlow[0]->getTransportDstPort() << endl;
	cout << "trace->networkFlow[2]->getNetworkProtocol() = " << trace->networkFlow[2]->getNetworkProtocol() << endl;
	cout << "trace->networkFlow[4]->getNetworkDstAddr() = " << trace->networkFlow[4]->getNetworkDstAddr() << endl;
	cout << "trace->networkFlow[6]->getTransportProtocol()  = " << trace->networkFlow[6]->getTransportProtocol() << endl;
	cout << "trace->networkFlow[30]->getTransportDstPort() = " << trace->networkFlow[30]->getTransportDstPort() << endl;
	cout << "trace->getNumberOfFlows() = " << trace->getNumberOfFlows() << endl;
#endif


	cout << "\n\n\n\n\n\n\n\n\n\n";

	NetworkTrace* tracetest = NULL;
	tracetest = new NetworkTrace("kkk.xml");
	//NetworkTrace traceTest = NetworkTrace("kkk.xml");
	tracetest->setInfoTracename("teste-chapolin");
	tracetest->setInfoCommentaries("este e um teste do compact trace descriptor");
	tracetest->setTrafficGenEngine("D-ITG");
	tracetest->setInfoCaptureInterface("eth0");
	tracetest->setInfoCaptureDate("07/04/2017");
	tracetest->writeToFile("copia-kjjjjj.xml");

	delete tracetest;

	cout << "llllasd"<< endl;

	return 0;
}
