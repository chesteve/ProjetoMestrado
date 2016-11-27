/*
 * NetworkFlow.cpp
 *
 *  Created on: 15 de set de 2016
 *      Author: apaschoalon
 */

#include "NetworkFlow.h"
#include "DummyFlow.h"
#include "DitgFlow.h"


NetworkFlow::NetworkFlow()
{
	// TODO Auto-generated constructor stub

}

NetworkFlow::~NetworkFlow()
{
	//nothing to do
}

NetworkFlow* NetworkFlow::make_flow(string choise)
{
#ifdef DEBUG_NetworkFlow
	cout << "NetworkFlow type: " << choise << endl;
#endif

	if (choise == "ditg")
		return new DitgFlow;
	else
		return new DummyFlow;

}
