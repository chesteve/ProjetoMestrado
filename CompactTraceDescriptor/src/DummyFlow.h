/*
 * DummyFlow.h
 *
 *  Created on: 14 de jun de 2016
 *      Author: apaschoalon
 */

#ifndef DUMMYFLOW_H_
#define DUMMYFLOW_H_

#include "NetworkFlow.h"
//external libraries
/*
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

 //local includes
 #include "ITGapi.h"
 #include "Defines.h"

 //namespaces
 using std::string;
 using std::cout;
 using std::cin;
 using std::endl;

 TODO Implementation of L2 data structures
 typedef struct mac_dst_n {
 string mac_dst;
 unsigned float frequency; //0-1
 struct mac_dst_n* next;
 }mac_dst_node;

 typedef struct l2_addr_list{
 string mac_src;
 unsigned long int mac_dst_count;
 mac_dst_node nodes;
 struct l2_addr_list* next;
 } l2_addr;
 */

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

	// TODO Design Pattern Factory -> in this version I will not use any Design
	// Pattern, I'll just create two functions: flowGenerate and
	// flowGenerateDummy. Then, next time, I'll create a better organized and
	// extensible class
	/**
	 *
	 * @return
	 */
	void flowGenerate();
//	void flowGenerateDummy();

	std::thread flowThread()
	{

#ifdef DEBUG_flowThread
		cout << "Debug: std::thread flowThread() ok!" << endl;
#endif

		return std::thread([=]
		{	flowGenerate();});
	}

//	//TODO polimorfismo
//	std::thread flowThread2()
//	{
//		return std::thread([=]
//		{	flowGenerateDummy();});
//	}

	/**
	 * Return the next IP address form the destination-hosts file
	 * @return
	 */
	string getHostIP();

	/**
	 * returns a random transport port number
	 * @return
	 */
	int randTranportPort();
	protocol getApplicationProtocol() const;
	void setApplicationProtocol(protocol applicationProtocol);
	unsigned int getFlowDsByte() const;
	void setFlowDsByte(unsigned int flowDsByte);
	double getFlowDuration() const;
	void setFlowDuration(double flowDuration);
	double getFlowStartDelay() const;
	void setFlowStartDelay(double flowStartDelay);

	protocol getLinkProtocol() const;
	void setLinkProtocol(protocol linkProtocol);
	long int getLinkSrcAddrCount() const;
	void setLinkSrcAddrCount(long int linkSrcAddrCount);
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
	unsigned long long int getNumberOfKbytes() const;
	void setNumberOfKbytes(unsigned long long int numberOfKbytes);
	unsigned long long int getNumberOfPackets() const;
	void setNumberOfPackets(unsigned long long int numberOfPackets);
	const protocolSupport& getProtocols() const;
	void setProtocols(const protocolSupport& protocols);

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

	//StochasticModelFit getPacketSizeModel_next() const;
	//void setPacketSizeModel_next(StochasticModelFit* modelVet) const;
	StochasticModelFit getInterDepertureTimeModel_next();
	void setInterDepertureTimeModels(StochasticModelFit* modelVet);
	/*
	 double getIdtCauchyScale() const;
	 void setIdtCauchyScale(double idtCauchyScale);
	 double getIdtCauchyShape() const;
	 void setIdtCauchyShape(double idtCauchyShape);
	 double getIdtConstant() const;
	 void setIdtConstant(double idtConstant);
	 double getIdtExponential() const;
	 void setIdtExponential(double idtExponentialE);
	 double getIdtGammaScale() const;
	 void setIdtGammaScale(double idtGammaScale);
	 double getIdtGammaShape() const;
	 void setIdtGammaShape(double idtGammaShape);
	 stochastic_model getIdtModel1() const;
	 void setIdtModel1(stochastic_model idtModel1);
	 stochastic_model getIdtModel2() const;
	 void setIdtModel2(stochastic_model idtModel2);
	 stochastic_model getIdtModel3() const;
	 void setIdtModel3(stochastic_model idtModel3);
	 stochastic_model getIdtModel4() const;
	 void setIdtModel4(stochastic_model idtModel4);
	 stochastic_model getIdtModel5() const;
	 void setIdtModel5(stochastic_model idtModel5);
	 stochastic_model getIdtModel6() const;
	 void setIdtModel6(stochastic_model idtModel6);
	 stochastic_model getIdtModel7() const;
	 void setIdtModel7(stochastic_model idtModel7);
	 stochastic_model getIdtModel8() const;
	 void setIdtModel8(stochastic_model idtModel8);
	 stochastic_model getIdtModel9() const;
	 void setIdtModel9(stochastic_model idtModel9);
	 double getIdtNormalStdDev() const;
	 void setIdtNormalStdDev(double idtNormalStddev);
	 double getIdtNormalMean() const;
	 void setIdtNormalMean(double idtNormalMean);
	 double getIdtParetoScale() const;
	 void setIdtParetoScale(double idtParetoScale);
	 double getIdtParetoShape() const;
	 void setIdtParetoShape(double idtParetoShape);
	 double getIdtPoissonMean() const;
	 void setIdtPoissonMean(double idtPoissonMean);
	 double getIdtUniformMaxpktsize() const;
	 void setIdtUniformMaxpktsize(double idtUniformMaxpktsize);
	 double getIdtUniformMinpktsize() const;
	 void setIdtUniformMinpktsize(double idtUniformMinpktsize);
	 double getIdtWeibullScale() const;
	 void setIdtWeibullScale(double idtWeibullScale);
	 double getIdtWeibullShape() const;
	 void setIdtWeibullShape(double idtWeibullShape);

	 double getPsBimodalMode1Constant() const;
	 void setPsBimodalMode1Constant(double psBimodalMode1Constant);
	 double getPsBimodalMode1NormalDevstd() const;
	 void setPsBimodalMode1NormalDevstd(double psBimodalMode1NormalDevstd);
	 double getPsBimodalMode1NormalMean() const;
	 void setPsBimodalMode1NormalMean(double psBimodalMode1NormalMean);
	 double getPsBimodalMode1WeibullScale() const;
	 void setPsBimodalMode1WeibullScale(double psBimodalMode1WeibullScale);
	 double getPsBimodalMode1WeibullShape() const;
	 void setPsBimodalMode1WeibullShape(double psBimodalMode1WeibullShape);
	 double getPsBimodalMode2Constant() const;
	 void setPsBimodalMode2Constant(double psBimodalMode2Constant);
	 double getPsBimodalMode2NormalDevstd() const;
	 void setPsBimodalMode2NormalDevstd(double psBimodalMode2NormalDevstd);
	 double getPsBimodalMode2NormalMean() const;
	 void setPsBimodalMode2NormalMean(double psBimodalMode2NormalMean);
	 double getPsBimodalMode2WeibullScale() const;
	 void setPsBimodalMode2WeibullScale(double psBimodalMode2WeibullScale);
	 double getPsBimodalMode2WeibullShape() const;
	 void setPsBimodalMode2WeibullShape(double psBimodalMode2WeibullShape);
	 stochastic_model getPsBimodalTypeMode1() const;
	 void setPsBimodalTypeMode1(stochastic_model psBimodalTypeMode1);
	 stochastic_model getPsBimodalTypeMode2() const;
	 void setPsBimodalTypeMode2(stochastic_model psBimodalTypeMode2);
	 int getPsConstant() const;
	 void setPsConstant(int psConstant);
	 double getPsExponential() const;
	 void setPsExponential(double psExponential);
	 stochastic_model getPsModel1() const;
	 void setPsModel1(stochastic_model psModel1);
	 stochastic_model getPsModel2() const;
	 void setPsModel2(stochastic_model psModel2);
	 stochastic_model getPsModel3() const;
	 void setPsModel3(stochastic_model psModel3);
	 stochastic_model getPsModel4() const;
	 void setPsModel4(stochastic_model psModel4);
	 stochastic_model getPsModel5() const;
	 void setPsModel5(stochastic_model psModel5);
	 stochastic_model getPsModel6() const;
	 void setPsModel6(stochastic_model psModel6);
	 stochastic_model getPsModel7() const;
	 void setPsModel7(stochastic_model psModel7);
	 stochastic_model getPsModel8() const;
	 void setPsModel8(stochastic_model psModel8);
	 double getPsNormalMean() const;
	 void setPsNormalMean(double psNormalMean);
	 double getPsNormalStdDev() const;
	 void setPsNormalStdDev(double psNormalStdDev);
	 double getPsParetoScale() const;
	 void setPsParetoScale(double psParetoScale);
	 double getPsParetoShape() const;
	 void setPsParetoShape(double psParetoShape);
	 double getPsPoissonMean() const;
	 void setPsPoissonMean(double psPoissonMean);
	 double getPsUniformMaxpktsize() const;
	 void setPsUniformMaxpktsize(double psUniformMaxpktsize);
	 double getPsUniformMinpktsize() const;
	 void setPsUniformMinpktsize(double psUniformMinpktsize);
	 double getPsWeibullScale() const;
	 void setPsWeibullScale(double psWeibullScale);
	 double getPsWeibullShape() const;
	 void setPsWeibullShape(double psWeibullShape);
	 */

protected:
	protocolSupport protocols;

private:
	/**
	 * Flow-level options
	 */
	double flow_duration;
	double flow_start_delay;
	unsigned int flow_ds_byte;
	unsigned long long int number_of_packets;
	unsigned long long int number_of_kbytes;

	/**
	 * Protocol stack options
	 */
	//TODO Implementation of L2 structures
	//TODO L2: Link Layer
	protocol link_protocol;
	long int link_src_addr_count;
	//l2_addr linkedlist;

	//L3: Network Layer
	unsigned int network_ttl;
	protocol network_protocol;
	string network_dst_addr;
	string network_src_addr;
	int network_hostList_conter;

	//L4: Transport Layer
	unsigned int transport_dst_port;
	unsigned int transport_src_port;
	protocol transport_protocol;
	unsigned int transport_sctp_association_id;
	unsigned int transport_sctp_max_streams;

	//L5: Application Layer
	protocol application_protocol;
	// TODO Application Layer implementation

	/**
	 * Interperture time
	 */
	StochasticModelFit* interArrivalvet;
	int interDepertureTimeModel_counter;

	/**
	 * Packet Size Model
	 */
	StochasticModelFit* psMode1;
	StochasticModelFit* psMode2;
	int packetSizeModel_counter;

	/*
	stochastic_model ps_model1;
	stochastic_model ps_model2;
	stochastic_model ps_model3;
	stochastic_model ps_model4;
	stochastic_model ps_model5;
	stochastic_model ps_model6;
	stochastic_model ps_model7;
	stochastic_model ps_model8;
	//bimodal
	stochastic_model ps_bimodal_type_mode1;
	double ps_bimodal_mode1_constant;
	double ps_bimodal_mode1_normal_mean;
	double ps_bimodal_mode1_normal_devstd;
	double ps_bimodal_mode1_weibull_shape;
	double ps_bimodal_mode1_weibull_scale;
	stochastic_model ps_bimodal_type_mode2;
	double ps_bimodal_mode2_constant;
	double ps_bimodal_mode2_normal_mean;
	double ps_bimodal_mode2_normal_devstd;
	double ps_bimodal_mode2_weibull_shape;
	double ps_bimodal_mode2_weibull_scale;
	//weibull
	double ps_weibull_shape;
	double ps_weibull_scale;
	//pareto
	double ps_pareto_shape;
	double ps_pareto_scale;
	//constant
	int ps_constant;
	//Normal
	double ps_normal_mean;
	double ps_normal_stdDev;
	//uniform
	double ps_uniform_maxpktsize;
	double ps_uniform_minpktsize;
	//exponential
	double ps_exponential;
	//poisson
	double ps_poisson_mean;

	stochastic_model idt_model1;
	stochastic_model idt_model2;
	stochastic_model idt_model3;
	stochastic_model idt_model4;
	stochastic_model idt_model5;
	stochastic_model idt_model6;
	stochastic_model idt_model7;
	stochastic_model idt_model8;
	stochastic_model idt_model9;
	//constant: packet rate per second
	double idt_constant;
	//weibull
	double idt_weibull_shape;
	double idt_weibull_scale;
	//pareto
	double idt_pareto_shape;
	double idt_pareto_scale;
	//gamma
	double idt_gamma_shape;
	double idt_gamma_scale;
	//cauchy
	double idt_cauchy_shape;
	double idt_cauchy_scale;
	//poisson
	double idt_poisson_mean;
	//normal
	double idt_normal_mean;
	double idt_normal_stdDev;
	//uniform
	double idt_uniform_maxpktsize;
	double idt_uniform_minpktsize;
	//exponential
	double idt_exponential;
	*/

};

#endif /* DUMMYFLOW_H_ */
