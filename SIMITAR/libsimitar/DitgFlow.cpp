/*
 * DitgFlow.cpp
 *
 *  Created on: 15 de set de 2017
 *      Author: anderson
 */

#include "DitgFlow.h"

/**
 * Must sett time scale factor
 */
DitgFlow::DitgFlow()
{
	setTimeScale(milliseconds);
}

DitgFlow::~DitgFlow()
{
	// nothing to do
}

int DitgFlow::server(const std::string& netInterface)
{
	// popen args
	FILE *in;
	char buff[512];
	//iperf args

	char command[2048] = "ITGRecv ";
	printf(
			"NOTE: Use Compact Trace Descriptors parameterized in milliseconds (sufix .ms) in the client side.\n");

	if (!(in = popen(command, "r")))
	{
		std::cerr << "DitgFlow error: cannot execute command `" << command
				<< "`" << std::endl;
		return -1;
	}

	while (fgets(buff, sizeof(buff), in) != NULL)
	{
		simitar_iostream_mutex.lock();
		std::cout << buff;
		simitar_iostream_mutex.unlock();
	}

	pclose(in);
	return (0);
}

void DitgFlow::flowGenerate(const counter& flowId, const time_sec& onTime,
		const uint& npackets, const uint& nbytes, const string& netInterface)
{
	simitar_iostream_mutex.lock();
	printf("command:%s\n",
			ditg_command(onTime, npackets, nbytes, netInterface).c_str());
	simitar_iostream_mutex.unlock();

	// popen args
	FILE *in;
	char buff[512];
	//iperf args
	char command[2048];
	strcpy(command,
			ditg_command(onTime, npackets, nbytes, netInterface).c_str());

	if (!(in = popen(command, "r")))
	{
		std::cerr << "DitgFlow error: cannot execute command `" << command
				<< "`" << std::endl;
		return;
	}

	while (fgets(buff, sizeof(buff), in) != NULL)
	{
		simitar_iostream_mutex.lock();
		std::cout << buff;
		simitar_iostream_mutex.unlock();
	}

	pclose(in);

}

std::string DitgFlow::ditg_command(const time_sec& onTime, const uint& npackets,
		const uint& nbytes, const string& netInterface)
{
	std::string strCommand = "ITGSend ";

	/**
	 * Flow-level settings
	 */
	int fileTimeout = int(this->getFlowDuration() * 1000);
	//duration
	if (fileTimeout == 0)
		fileTimeout = 1;
	strCommand += " -t " + std::to_string(fileTimeout);
	//DS byte
	strCommand += " -b " + std::to_string(this->getFlowDsByte());
	//Guarantee the mean packet rate
	strCommand += " -j 1";

	/**
	 * Network-layer settings
	 */
	//tty byte
	strCommand += " -f " + std::to_string(this->getNetworkTtl());
	//destination and sources IPv4/IPv6 address
	strCommand += " -a " + this->getNetworkDstAddr();
	//strCommand += " -sa " + this->getNetworkSrcAddr();

	/**
	 * Transport-layer settings
	 */
	if (this->getTransportProtocol() == PROTOCOL__TCP)
	{
		strCommand += " -T TCP -D ";
		strCommand += " -rp " + std::to_string(this->getTransportDstPort());
		//strCommand += " -sp " + std::to_string(this->getTransportSrcPort());
	}
	else if (this->getTransportProtocol() == PROTOCOL__UDP)
	{
		strCommand += " -T UDP ";
		strCommand += " -rp " + std::to_string(this->getTransportDstPort());
		//strCommand += " -sp " + std::to_string(this->getTransportSrcPort());
	}
	else if (this->getTransportProtocol() == PROTOCOL__ICMP)
	{
		//TODO set ICMP type
		strCommand += " -T ICMP ";
	}
	else if (this->getTransportProtocol() == PROTOCOL__SCTP)
	{
		//TODO Set D-ITG compile file to support SCTP
		// To enable this option D-ITG has to be compiled with"sctp" option enabled (i.e.  make sctp=on).
		//strCommand += " -T SCTP "
		//		+ std::to_string(this->getTransportSctpAssociationId()) + " "
		//		+ std::to_string(this->getTransportSctpMaxStreams()) + " ";
		strCommand += " -T SCTP ";
	}
	else if (this->getTransportProtocol() == PROTOCOL__DCCP)
	{
		//TODO Set D-ITG compile file to support DCCP
		//To enable this option D-ITG has to be compiled with "dccp" option enabled (i.e.  make dccp=on).
		strCommand += " -T DCCP ";
	}
	else
	{
		strCommand += " -T UDP -rp " + std::to_string(this->randTranportPort());
	}

	/**
	 * Application protocol
	 */

	if (this->getApplicationProtocol() == PROTOCOL__Telnet)
	{
		strCommand += " Telnet ";
	}
	else if (this->getApplicationProtocol() == PROTOCOL__DNS)
	{
		strCommand += " DNS ";
	}
	else
	{
		/// From D-ITG documentation
		///  Note:
		/// - Emulation is obtained by properly replicating packet sizes and IDTs. The payload of the
		///  application is not reproduced (i.e. bytes above transport layer have no real meaning).
		///- Application layer options have to be specified as the last option.
		///- If you specify an application layer protocol you cannot specify any inter-departure time,
		///  or packet size option.

		/**
		 * Inter-departure time options
		 */
		for (int i = 0;; i++)
		{
			StochasticModelFit idtModel = this->getInterDepertureTimeModel(i);

			if (idtModel.modelName() == WEIBULL)
			{
				//idtModel.param1 = alpha (shape)
				//idtModel.param2 = betha (scale)
				strCommand += " -W " + std::to_string(idtModel.param1()) + " "
						+ std::to_string(idtModel.param2());
				break;
			}
			else if (idtModel.modelName() == NORMAL)
			{
				//idtModel.param1 = mu (shape)
				//idtModel.param2 = sigma dev
				strCommand += " -N " + std::to_string(idtModel.param1()) + " "
						+ std::to_string(idtModel.param2());
				break;
			}
			// TODO exponetial uses mean
			//else if (idtModel.modelName() == EXPONENTIAL_MEAN)
			//{
			//	//idtModel.param1 = mean
			//	strCommand += " -E " + std::to_string(idtModel.param1());
			//	break;
			//}
			// TODO exponetial uses mean
			//else if (idtModel.modelName() == EXPONENTIAL_LINEAR_REGRESSION)
			//{
			//	//idtModel.param1 = mean
			//	strCommand += " -E " + std::to_string(idtModel.param1());
			//	break;
			//}
			/// Pareto Maximum likehood has horrible results
			//else if ( idtModel.modelName() == PARETO_MAXIMUM_LIKEHOOD)
			//{
			//	//idtModel.param1 = alpha (shape)
			//	//idtModel.param2 = xm (scale)
			//	strCommand += " -V " + std::to_string(idtModel.param1()) + " "
			//			+ std::to_string(idtModel.param2());
			//	break;
			//}
			else if (idtModel.modelName() == PARETO_LINEAR_REGRESSION)
			{
				//idtModel.param1 = alpha (shape)
				//idtModel.param2 = xm (scale)
				strCommand += " -V " + std::to_string(idtModel.param1()) + " "
						+ std::to_string(idtModel.param2());
				break;
			}
			else if (idtModel.modelName() == CAUCHY)
			{
				//idtModel.param1 = gamma (scale)
				//idtModel.param2 = xm (shape - location)
				strCommand += " -Y " + std::to_string(idtModel.param2()) + " "
						+ std::to_string(idtModel.param1());
				break;
			}
			else if (idtModel.modelName() == CONSTANT)
			{
				strCommand += " -C " + std::to_string(idtModel.param1());
				break;
			}
		}

		/**
		 * Packet-size options
		 */
		StochasticModelFit ps1Model = this->getPacketSizeModelMode1(0);
		StochasticModelFit ps2Model = this->getPacketSizeModelMode2(0);
		int psM1 = int(ps1Model.param1());
		int psM2 = int(ps2Model.param1());
		int psSize = (psM2 > psM1) ? psM2 : psM1;
		strCommand += " -c " + std::to_string(psSize);

	}

	return (strCommand);
}

