/*
 * StochasticModelFit.h
 *
 *  Created on: 6 de nov de 2016
 *      Author: apaschoalon
 */

#ifndef STOCHASTICMODELFIT_H_
#define STOCHASTICMODELFIT_H_

#include <string>
using std::string;

/**
 * This struct must only be generated by the method DataProcessor::fitModels()
 */
typedef struct stochastic_model_fitting
{
	//AIC criterion value for the model
	double aic;

	//BIC criterion value for the model
	double bic;

	//String with a human-readable name of the current model
	string modelName;

	//first parameter (in alphabetical order) of the model
	double param1;

	//second parameter (in alphabetical order) of the model
	double param2;

	//Number of models setted by the method DataProcessor::fitModels()
	unsigned int size;

} StochasticModelFit;

int compareBic(const void* a, const void* b);
int compareAic(const void* a, const void* b);



#endif /* STOCHASTICMODELFIT_H_ */
