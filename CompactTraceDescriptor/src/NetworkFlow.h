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

//local includes
#include "ITGapi.h"
#include "Defines.h"
#include "StochasticModelFit.h"

//namespaces
using std::string;
using std::cout;
using std::cin;
using std::endl;

typedef struct protocol_support
{
	bool ethernet;
	bool arp;
	bool use_ip_add_list;
	bool ipv4;
	bool ipv6;
	bool igmp;
	bool gre;
	bool icmp;
	bool dccp;
	bool tcp;
	bool udp;
	bool smnp;
	bool html;
} protocolSupport;

class NetworkFlow
{
public:
	NetworkFlow();
	virtual ~NetworkFlow();
	static NetworkFlow *make_flow(string choise);

	virtual void flowGenerate() = 0;
	virtual std::thread flowThread() = 0;

	virtual int randTranportPort() = 0;
	virtual protocol getApplicationProtocol() const = 0;
	virtual void setApplicationProtocol(protocol applicationProtocol) = 0;
	virtual unsigned int getFlowDsByte() const = 0;
	virtual void setFlowDsByte(unsigned int flowDsByte) = 0;
	virtual double getFlowDuration() const = 0;
	virtual void setFlowDuration(double flowDuration) = 0;
	virtual double getFlowStartDelay() const = 0;
	virtual void setFlowStartDelay(double flowStartDelay) = 0;

	virtual protocol getLinkProtocol() const = 0;
	virtual void setLinkProtocol(protocol linkProtocol) = 0;
	virtual long int getLinkSrcAddrCount() const = 0;
	virtual void setLinkSrcAddrCount(long int linkSrcAddrCount) = 0;
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
	virtual unsigned long long int getNumberOfKbytes() const = 0;
	virtual void setNumberOfKbytes(unsigned long long int numberOfKbytes) = 0;
	virtual unsigned long long int getNumberOfPackets() const = 0;
	virtual void setNumberOfPackets(unsigned long long int numberOfPackets) = 0;
	virtual const protocolSupport& getProtocols() const = 0;
	virtual void setProtocols(const protocolSupport& protocols) = 0;

//TODO
//	virtual StochasticModelFit getPacketSizeModel_next() const = 0;
//	virtual void setPacketSizeModel_next(
//			StochasticModelFit* modelVet) const = 0;
	virtual StochasticModelFit getInterDepertureTimeModel_next()= 0;
	virtual void setInterDepertureTimeModels(
			StochasticModelFit* modelVet) = 0;

	/*
	 virtual double getIdtCauchyScale() const = 0;
	 virtual void setIdtCauchyScale(double idtCauchyScale) = 0;
	 virtual double getIdtCauchyShape() const = 0;
	 virtual void setIdtCauchyShape(double idtCauchyShape) = 0;
	 virtual double getIdtConstant() const = 0;
	 virtual void setIdtConstant(double idtConstant) = 0;
	 virtual double getIdtExponential() const = 0;
	 virtual void setIdtExponential(double idtExponentialE) = 0;
	 virtual double getIdtGammaScale() const = 0;
	 virtual void setIdtGammaScale(double idtGammaScale) = 0;
	 virtual double getIdtGammaShape() const = 0;
	 virtual void setIdtGammaShape(double idtGammaShape) = 0;
	 virtual stochastic_model getIdtModel1() const = 0;
	 virtual void setIdtModel1(stochastic_model idtModel1) = 0;
	 virtual stochastic_model getIdtModel2() const = 0;
	 virtual void setIdtModel2(stochastic_model idtModel2) = 0;
	 virtual stochastic_model getIdtModel3() const = 0;
	 virtual void setIdtModel3(stochastic_model idtModel3) = 0;
	 virtual stochastic_model getIdtModel4() const = 0;
	 virtual void setIdtModel4(stochastic_model idtModel4) = 0;
	 virtual stochastic_model getIdtModel5() const = 0;
	 virtual void setIdtModel5(stochastic_model idtModel5) = 0;
	 virtual stochastic_model getIdtModel6() const = 0;
	 virtual void setIdtModel6(stochastic_model idtModel6) = 0;
	 virtual stochastic_model getIdtModel7() const = 0;
	 virtual void setIdtModel7(stochastic_model idtModel7) = 0;
	 virtual stochastic_model getIdtModel8() const = 0;
	 virtual void setIdtModel8(stochastic_model idtModel8) = 0;
	 virtual stochastic_model getIdtModel9() const = 0;
	 virtual void setIdtModel9(stochastic_model idtModel9) = 0;
	 virtual double getIdtNormalStdDev() const = 0;
	 virtual void setIdtNormalStdDev(double idtNormalStddev) = 0;
	 virtual double getIdtNormalMean() const = 0;
	 virtual void setIdtNormalMean(double idtNormalMean) = 0;
	 virtual double getIdtParetoScale() const = 0;
	 virtual void setIdtParetoScale(double idtParetoScale) = 0;
	 virtual double getIdtParetoShape() const = 0;
	 virtual void setIdtParetoShape(double idtParetoShape) = 0;
	 virtual double getIdtPoissonMean() const = 0;
	 virtual void setIdtPoissonMean(double idtPoissonMean) = 0;
	 virtual double getIdtUniformMaxpktsize() const = 0;
	 virtual void setIdtUniformMaxpktsize(double idtUniformMaxpktsize) = 0;
	 virtual double getIdtUniformMinpktsize() const = 0;
	 virtual void setIdtUniformMinpktsize(double idtUniformMinpktsize) = 0;
	 virtual double getIdtWeibullScale() const = 0;
	 virtual void setIdtWeibullScale(double idtWeibullScale) = 0;
	 virtual double getIdtWeibullShape() const = 0;
	 virtual void setIdtWeibullShape(double idtWeibullShape) = 0;

	 virtual double getPsBimodalMode1Constant() const = 0;
	 virtual void setPsBimodalMode1Constant(double psBimodalMode1Constant) = 0;
	 virtual double getPsBimodalMode1NormalDevstd() const = 0;
	 virtual void setPsBimodalMode1NormalDevstd(double psBimodalMode1NormalDevstd) = 0;
	 virtual double getPsBimodalMode1NormalMean() const = 0;
	 virtual void setPsBimodalMode1NormalMean(double psBimodalMode1NormalMean) = 0;
	 virtual double getPsBimodalMode1WeibullScale() const = 0;
	 virtual void setPsBimodalMode1WeibullScale(double psBimodalMode1WeibullScale) = 0;
	 virtual double getPsBimodalMode1WeibullShape() const = 0;
	 virtual void setPsBimodalMode1WeibullShape(double psBimodalMode1WeibullShape) = 0;
	 virtual double getPsBimodalMode2Constant() const = 0;
	 virtual void setPsBimodalMode2Constant(double psBimodalMode2Constant) = 0;
	 virtual double getPsBimodalMode2NormalDevstd() const = 0;
	 virtual void setPsBimodalMode2NormalDevstd(double psBimodalMode2NormalDevstd) = 0;
	 virtual double getPsBimodalMode2NormalMean() const = 0;
	 virtual void setPsBimodalMode2NormalMean(double psBimodalMode2NormalMean) = 0;
	 virtual double getPsBimodalMode2WeibullScale() const = 0;
	 virtual void setPsBimodalMode2WeibullScale(double psBimodalMode2WeibullScale) = 0;
	 virtual double getPsBimodalMode2WeibullShape() const = 0;
	 virtual void setPsBimodalMode2WeibullShape(double psBimodalMode2WeibullShape) = 0;
	 virtual stochastic_model getPsBimodalTypeMode1() const = 0;
	 virtual void setPsBimodalTypeMode1(stochastic_model psBimodalTypeMode1) = 0;
	 virtual stochastic_model getPsBimodalTypeMode2() const = 0;
	 virtual void setPsBimodalTypeMode2(stochastic_model psBimodalTypeMode2) = 0;
	 virtual int getPsConstant() const = 0;
	 virtual void setPsConstant(int psConstant) = 0;
	 virtual double getPsExponential() const = 0;
	 virtual void setPsExponential(double psExponential) = 0;
	 virtual stochastic_model getPsModel1() const = 0;
	 virtual void setPsModel1(stochastic_model psModel1) = 0;
	 virtual stochastic_model getPsModel2() const = 0;
	 virtual void setPsModel2(stochastic_model psModel2) = 0;
	 virtual stochastic_model getPsModel3() const = 0;
	 virtual void setPsModel3(stochastic_model psModel3) = 0;
	 virtual stochastic_model getPsModel4() const = 0;
	 virtual void setPsModel4(stochastic_model psModel4) = 0;
	 virtual stochastic_model getPsModel5() const = 0;
	 virtual void setPsModel5(stochastic_model psModel5) = 0;
	 virtual stochastic_model getPsModel6() const = 0;
	 virtual void setPsModel6(stochastic_model psModel6) = 0;
	 virtual stochastic_model getPsModel7() const = 0;
	 virtual void setPsModel7(stochastic_model psModel7) = 0;
	 virtual stochastic_model getPsModel8() const = 0;
	 virtual void setPsModel8(stochastic_model psModel8) = 0;
	 virtual double getPsNormalMean() const = 0;
	 virtual void setPsNormalMean(double psNormalMean) = 0;
	 virtual double getPsNormalStdDev() const = 0;
	 virtual void setPsNormalStdDev(double psNormalStdDev) = 0;
	 virtual double getPsParetoScale() const = 0;
	 virtual void setPsParetoScale(double psParetoScale) = 0;
	 virtual double getPsParetoShape() const = 0;
	 virtual void setPsParetoShape(double psParetoShape) = 0;
	 virtual double getPsPoissonMean() const = 0;
	 virtual void setPsPoissonMean(double psPoissonMean) = 0;
	 virtual double getPsUniformMaxpktsize() const = 0;
	 virtual void setPsUniformMaxpktsize(double psUniformMaxpktsize) = 0;
	 virtual double getPsUniformMinpktsize() const = 0;
	 virtual void setPsUniformMinpktsize(double psUniformMinpktsize) = 0;
	 virtual double getPsWeibullScale() const = 0;
	 virtual void setPsWeibullScale(double psWeibullScale) = 0;
	 virtual double getPsWeibullShape() const = 0;
	 virtual void setPsWeibullShape(double psWeibullShape) = 0;
	 */

	virtual unsigned int getTransportDstPort() const = 0;
	virtual void setTransportDstPort(unsigned int transportDstPort) = 0;
	virtual unsigned int getTransportSctpAssociationId() const = 0;
	virtual void setTransportSctpAssociationId(
			unsigned int transportSctpAssociationId) = 0;
	virtual unsigned int getTransportSctpMaxStreams() const = 0;
	virtual void setTransportSctpMaxStreams(
			unsigned int transportSctpMaxStreams) = 0;
	virtual unsigned int getTransportSrcPort() const = 0;
	virtual void setTransportSrcPort(unsigned int transportSrcPort) = 0;
	virtual protocol getTransportProtocol() const = 0;
	virtual void setTransportProtocol(protocol transportProtocol) = 0;

};

#endif /* NETWORKFLOW_H_ */
