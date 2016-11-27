/*
 * DitgFlow.h
 *
 *  Created on: 16 de set de 2016
 *      Author: apaschoalon
 */

#ifndef DITGFLOW_H_
#define DITGFLOW_H_

#include "NetworkFlow.h"
#include "DummyFlow.h"


class DitgFlow: public DummyFlow
{
public:
	DitgFlow();
	virtual ~DitgFlow();
	void flowGenerate();
};

#endif /* DITGFLOW_H_ */
