/*
 * DataProcessor.h
 *
 *  Created on: 14 de jun de 2016
 *      Author: apaschoalon
 */

#ifndef DATAPROCESSOR_H_
#define DATAPROCESSOR_H_

//external libs
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <malloc.h>
#include <err.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <array>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include <armadillo>

//local libs
#include "Defines.h"
#include "DatabaseInterface.h"
#include "NetworkTrace.h"
#include "StochasticModelFit.h"
#include "RegressionTests.h"

//namespaces
using std::string;
using std::cerr;
using std::isnan;
using std::sort;
using namespace arma;

#define DEBUG_StochasticModelFit 1

//TODO: this class must be static... or not
class DataProcessor
{
public:

	/**
	 * Default constructor
	 */
	DataProcessor();

	/**
	 * Destructor. Clean any allocated memory
	 */
	virtual ~DataProcessor();

	/**
	 * @brief  Returns a string information about the class
	 * Returns a string information about the class
	 *
	 * @param void
	 * @return string
	 */
	string toString(void);

	/**
	 * @brief This method parameterize a network trace.
	 * Through the database interface class, this method retrieves all desired
	 * data from the database, in order to calculate and set parameters in a
	 * NetworkTrace class instance. This method knows all the labels and types
	 * of each database column, and how to deal with them correctly. So this
	 * method should be up to date with the database. After calculating all
	 * parameters, this class should save the data on the Network trace
	 * object and on its flows through netTrace.set() and netTace.flow[n].set()
	 * methods.
	 *
	 * @param experimentName experiment name string
	 * @param databaseInterface class interface to the database
	 * @param netTrace network trace class, which will be parameterized
	 * @return returns 0 in success
	 */
	int calculate(const string& experimentName,
			DatabaseInterface* databaseInterface, NetworkTrace* netTrace);

	/**
	 * @brief Set the information criterion.
	 * May be setted as "aic" or "bic". If any other string is used as input,
	 * it prints an error message, and set "aic" as default.
	 *
	 * @param criterion
	 */
	void setInformationCriterion(const string& criterion);

	/**
	 * @brief Returns the information criterion.
	 * Returns the information criterion string setted in the DataProcessor
	 * class. The default value is "aic".
	 *
	 * @return
	 */
	const string& getInformationCriterion();

	/**
	 * Run regression tests for the methods of this class
	 */
	void regression_tests();

private:

	/**
	 * Minimum amount of packets to be processed by the dataProcessor algorithm
	 */
	int minimumAmountOfPackets = 10;

	/**
	 * A time smaller than the min_time resolution. Once the current resolution
	 * is 1e-6, min_time is half of this value. This value is used as default
	 * as substitute for times equal to zero.
	 */
	//double min_time = 5e-7;
	double min_time = 5e-8;

	/**
	 * A very small time value. This is used to avoid evaluating the operation
	 * log(0), which is undefined.
	 */
	double diferential = 4e-14;

	/**
	 * Information Criterion used in the DataProcessor. May be AIC
	 * (string "aic") or BIC (string "bic"). The default value is "aic".
	 */
	string informationCriterionParam = "aic";

	/**
	 * Default Weibull alpha, in case a invalid value is estimated, since alpha > 0.
	 * It was estimated found experimentally on a traffic trace of a local LAN.
	 */
	double default_weibullAlpha = 0.120355;

	/**
	 * Default Weibull beta, in case a invalid value is estimated, since beta > 0.
	 * It was estimated found experimentally on a traffic trace of a local LAN.
	 */
	double default_weibullBeta = 0.001629;

	/**
	 * Default Exponential lambda, in case a invalid value is estimated, since lambda > 0.
	 * It was estimated found experimentally on a traffic trace of a local LAN.
	 */
	double default_exponentialLambda = 0.009752;

	/**
	 * Default Pareto alpha, in case a invalid value is estimated since alpha > 0.
	 * It was estimated found experimentally on a traffic trace of a local LAN.
	 */
	double default_paretoAlpha = 0.061065;

	/**
	 * Default Pareto xm, in case a invalid value is estimated since xm > 0.
	 * It was estimated found experimentally on a traffic trace of a local LAN.
	 */
	double default_paretoXm = min_time;

	/**
	 * Default Cauchy gamma, in case a invalid value is estimated since gamma > 0.
	 * It was estimated found experimentally on a traffic trace of a local LAN.
	 */
	double default_cauchyGamma = 1.935832;

	/**
	 * Default Cauchy gamma, in case a invalid value is estimated since gamma > 0.
	 * It was estimated found experimentally on a traffic trace of a local LAN.
	 */
	double default_cauchyX0 = -7.245692;

	/**
	 * A close zero value, but greater (to calc tangent of a vector)
	 */
	double almost_zero = 000001;

	/**
	 * A close one value, but smaller (to calc tangent of a vector)
	 */
	double almost_one = 0.999999;

	/**
	 * calculate the most frequent element from a list
	 * @param thelist
	 * @return
	 */
	long int mode(list<long int>& thelist);

	/**
	 * 	ACTUAL FUNCTIONS
	 */

	/**
	 * @brief
	 * Take as input a vector <T> vet[], its first and last position to be
	 * sorted. After the execution vet[] will be sorted.
	 *
	 * @param vet C vector
	 * @param left fist position of the C vector to be sorted, usually 0.
	 * @param right last position of the C vector to be sorted, usually size-1;
	 */
	template<typename T> void quickSort(T* vet, int left, int right);

	/**
	 * @brief
	 * Evaluate the mode (the most frequent value) of a list list<T>
	 *
	 * @param theList
	 * @return
	 */
	template<typename T> T mode(list<T>* theList);

	/**
	 * @brief Converts a list<T> to a C vector.
	 * Converts a list<T> to a C vector.
	 * @param theList
	 * @return
	 */
	template<typename T> T* list_to_cvector(list<T>* theList) const;

	/**
	 * @brief Delete a C vector
	 * @param c_vet pointer to the C vector
	 */
	template<typename T> void delete_cvector(T* c_vet) const;

	/**
	 * @brief Compare two C vectors T.
	 * Compare two C vectors of types T. If they are equal, returns "true". If
	 * they are not, returns "false".
	 *
	 * @param vet1
	 * @param vet2
	 * @param size
	 * @return
	 */
	template<typename T> bool isEqual(const T* vet1, const T* vet2,
			const int size);
	/**
	 * \brief convert a C vector T to a list<T>
	 *
	 * @param theList pointer to an empty list
	 * @param vet pointer to a C vector
	 * @param size size of the C vector
	 */
	template<typename T> void vectorC_to_list(list<T>* theList, T* vet,
			int size);

	bool isRealPositive(double val);

	bool isRealPositive(double val1, double val2);

	/**
	 * Return an empirical vector of the Cumulative distribution function.
	 * This method take as input a list<double> of empirical data, and create a
	 * vector (of the same size) of an empirical evaluation of the cumulative
	 * distribution function. Return must be freed using delete.
	 *
	 * @param list<double>
	 * @return vec* empirical cumulative vector
	 */
	vec* empiricalCdf(list<double>& empiricalData);

	//feature matrix: return a matrix X(m, 2) = [1 data]. Must be freed using delete.
	/**
	 * @brief Creates a feature matrix for linear regression
	 * Creates a feature matrix X(m, 2) = [1 data], for the linear regression.
	 * Must be freed using delete.
	 *
	 * @param empiricalData list<double> of the empirical data.
	 * @return returns a pointer to the feature matrix
	 */
	mat* featureMatrix(list<double>& empiricalData);

	/**
	 * @brief Creates a feature matrix for linear regression
	 * Creates a feature matrix X(m, 2) = [1 data], for the linear regression.
	 * Must be freed using delete.
	 *
	 * @param empiricalData vector vec of the empirical data.
	 * @return returns a pointer to the feature matrix
	 */
	mat* featureMatrix(const vec& empiricalData);

	/**
	 * @brief Compute cost of the gradient descendent function
	 * It returns the value of the cost function for the list of parameteres
	 *
	 * @param X feature matrix
	 * @param y expected values
	 * @param theta linear regression coeficients [theta1; theta2]
	 * @return cost value
	 */
	double computeCost(const mat& X, const vec& y, const vec& theta);

	/**
	 * @brief Gradient descendent algorithm
	 * Evaluates the gradient descendent
	 *
	 * @param X feature matrix
	 * @param y
	 * @param learning_rate
	 * @param num_iters
	 * @param theta
	 * @param J_history
	 */
	void gradientDescendent(const mat& X, const vec& y,
			const double learning_rate, const int num_iters, vec& theta,
			vec& J_history);

	/**
	 * @brief information criterion
	 *
	 * @param data
	 * @param functionName
	 * @param paramVet
	 * @param criterion
	 * @return
	 */
	double informationCriterion(const vec& data, const string& functionName,
			const vec& paramVet, const string& criterion);

	/**
	 * @brief natural logarithm of likehood function
	 *
	 * @param data
	 * @param functionName
	 * @param paramVet
	 * @return
	 */
	double logLikehood(const vec& data, const string& functionName,
			const vec& paramVet);
	/**
	 * @brief fit weibull alpha and betha using linear regression
	 *
	 * @param interArrival
	 * @param interArrivalCdf
	 * @param paramVec
	 * @param informationCriterion
	 */
	void weibullFitting(const vec& interArrival, const vec& interArrivalCdf,
			vec& paramVec, vec& informationCriterion);

	/**
	 * @brief evaluate mean and standard deviation
	 *
	 * @param interArrival
	 * @param paramVec
	 * @param informationCriterion
	 */
	void normalFitting(const vec& interArrival, vec& paramVec,
			vec& informationCriterion);

	/**
	 * @brief evaluate lambda using linear regression
	 *
	 * @param interArrival
	 * @param interArrivalCdf
	 * @param paramVec
	 * @param informationCriterion
	 */
	void exponentialLrFitting(const vec& interArrival,
			const vec& interArrivalCdf, vec& paramVec,
			vec& informationCriterion);

	/**
	 * @brief evaluate lambda using mean estimation
	 *
	 * @param interArrival
	 * @param paramVec
	 * @param informationCriterion
	 */
	void exponentialMeFitting(const vec& interArrival, vec& paramVec,
			vec& informationCriterion);

	/**
	 * @brief evaluate pareto's alpha and xm using Linear regression
	 *
	 * @param interArrival
	 * @param interArrivalCdf
	 * @param paramVec
	 * @param informationCriterion
	 */
	void paretoLrFitting(const vec& interArrival, const vec& interArrivalCdf,
			vec& paramVec, vec& informationCriterion);

	/**
	 * @brief evaluate pareto's alpha and xm using maximum likehood method
	 *
	 * @param interArrival
	 * @param interArrivalCdf
	 * @param paramVec
	 * @param informationCriterion
	 */
	void paretoMlhFitting(const vec& interArrival, const vec& interArrivalCdf,
			vec& paramVec, vec& informationCriterion);

	/**
	 * @brief evaluate cauchy's gamma and x0 using linear regression
	 *
	 * @param interArrival
	 * @param interArrivalCdf
	 * @param paramVec
	 * @param informationCriterion
	 */
	void cauchyFitting(const vec& interArrival, const vec& interArrivalCdf,
			vec& paramVec, vec& informationCriterion);

	/**
	 * @brief
	 *
	 * @param interArrival
	 * @param paramVec
	 * @param informationCriterion
	 */
	void constantFitting(const vec& interArrival, vec& paramVec,
			vec& informationCriterion);

	/**
	 * @brief returns probability of a given
	 * @param x
	 * @param alpha
	 * @param betha
	 * @return
	 */
	double pdf_weibull(double x, double alpha, double betha);

	/**
	 *
	 * @param x
	 * @param alpha
	 * @param betha
	 * @return
	 */
	double cdf_weibull(double x, double alpha, double betha);

	/**
	 *
	 * @param x
	 * @param lambda
	 * @return
	 */
	double pdf_exponential(double x, double lambda);

	/**
	 *
	 * @param x
	 * @param lambda
	 * @return
	 */
	double cdf_exponential(double x, double lambda);

	/**
	 *
	 * @param x
	 * @param alpha
	 * @param xm
	 * @return
	 */
	double pdf_pareto(double x, double alpha, double xm);

	/**
	 *
	 * @param x
	 * @param alpha
	 * @param xm
	 * @return
	 */
	double cdf_pareto(double x, double alpha, double xm);

	/**
	 *
	 * @param x
	 * @param gamma
	 * @param x0
	 * @return
	 */
	double pdf_cauchy(double x, double gamma, double x0);

	/**
	 *
	 * @param x
	 * @param gamma
	 * @param x0
	 * @return
	 */
	double cdf_cauchy(double x, double gamma, double x0);

	/**
	 *
	 * @param x
	 * @param mu
	 * @param sigma
	 * @return
	 */
	double pdf_normal(double x, double mu, double sigma);

	/**
	 *
	 * @param x
	 * @param mu
	 * @param sigma
	 * @return
	 */
	double cdf_normal(double x, double mu, double sigma);

	/**
	 *
	 * @param x_min
	 * @param x_max
	 * @return
	 */
	double pdf_uniform(double x_min, double x_max);

	/**
	 *
	 * @param x
	 * @param x_min
	 * @param x_max
	 * @return
	 */
	double cdf_uniform(double x, double x_min, double x_max);

	/**
	 * @brief
	 * Take as input a list o inter-arrival times, and a pointer to a C vector
	 * of the struct StochasticModelFit. The available models are ordered here,
	 * from the best to the worst, according to the specified criterion BIC or
	 * AIC. If it is not specified, it uses as default AIC.
	 * If the empirical data has only a single entry, it will set just a single
	 * constant model with all parameters equal to zero, and AIC and BIC equals
	 * to infinite
	 *
	 * @param empiricalData
	 * @param criterion
	 * @return
	 */
	//StochasticModelFit* fitModelsInterArrival(list<double>& empiricalData,
	//		const string& criterion);
	list<StochasticModelFit>* fitModelsInterArrival(list<double>& empiricalData,
			const string& criterion);
	list<StochasticModelFit>* fitModelsPsSize(list<double>& empiricalData);

	/**
	 * Guess the application protocol, based on the transport protocol and
	 * port numbers
	 *
	 * @param transportProtocol
	 * @param srcPort
	 * @param dstPort
	 * @return
	 */
	protocol aplicationProtocol(protocol transportProtocol, port_number srcPort,
			port_number dstPort);

	/**
	 * @brief
	 *
	 * @param arrivalVet
	 * @param cut_time
	 * @param min_on_time
	 * @param onTimes
	 * @param offTimes
	 */
	void calcOnOff(list<time_sec>& deltaVet, const time_sec cut_time,
			const time_sec min_on_time, vector<time_sec>* onTimes,
			vector<time_sec>* offTimes);

	vec interArrivalSample =
	{ 0, 0, 0.000203, 1e-05, 0.318392, 1.00003, 0.517214, 3.2e-05, 7.6e-05,
			0.159572, 0.028456, 0.000267, 1.6e-05, 0.000362, 0.001436, 0.012243,
			0.052051, 0.010572, 0.300375, 1.6e-05, 0.00012, 0.171993, 0.000161,
			0.180517, 0.336145, 9e-06, 0.007852, 0.044852, 0.020313, 0.030458,
			0.218979, 0.250961, 0.158453, 0.042762, 0.129894, 0.01578, 0.016078,
			3.1e-05, 2.2e-05, 0.000309, 1.8e-05, 7.1e-05, 3e-06, 0.00018, 6e-06,
			0.041497, 0.094336, 0.030568, 0.69278, 0.083745,
			0.09501999999999999, 0.246721, 0.000322, 1.5e-05, 6.4e-05, 0.00031,
			6.600000000000001e-05, 0.000203, 5.4e-05, 4e-06, 4.6e-05,
			0.0005509999999999999, 0.046676, 0.000133, 0.00025, 0.000106, 4e-06,
			6e-05, 0.000579, 0.020548, 0.020144, 0.00017, 4.3e-05, 3.8e-05,
			0.000403, 8.8e-05, 9.2e-05, 2.1e-05, 8.899999999999999e-05, 7.9e-05,
			0.037013, 0.003625, 0.000174, 0.001402, 0.01547, 0.000137, 0.000257,
			0.000181, 0.000249, 0.000175, 0.000262, 0.000188, 0.000245,
			0.000198, 0.000194, 0.039691, 0.377134, 0.025489,
			0.08887399999999999, 0.071201, 0.118396, 0.011301, 0.18306,
			0.471818, 1.2e-05, 0.057105, 0.158384, 0.033412, 0.279247, 0.615341,
			0.07193099999999999, 0.041286, 6e-06, 6.4e-05, 0.000615, 0.000159,
			1.5e-05, 0.179127, 0.003532, 0.087938, 0.128529, 0.003537, 0.555139,
			0.312737, 0.614656, 0.20354, 0.18178, 0.728741, 0.227757, 0.657457,
			1.122729, 0.000405, 1.1e-05, 0.876119, 1.999258, 0.936457, 0.000285,
			1.2e-05, 4.5e-05, 5.3e-05, 0.000321, 0.000137, 0.00026, 0.00031,
			0.000224, 2.5e-05, 0.000171, 3.7e-05, 0.000211, 9.3e-05, 0.000175,
			2.8e-05, 0.000447, 0.000124, 3e-06, 0.000121, 0.000124, 1.3e-05,
			0.000111, 0.000129, 3e-06, 3.6e-05, 3e-06, 1.8e-05, 3.9e-05,
			8.6e-05, 0.00021, 0.000239, 0.000161, 3.2e-05, 0.000224, 0.001489,
			0.00078, 0.000127, 7e-06, 0.000197, 0.000703, 2.5e-05, 0.000145,
			0.00263, 0.001061, 0.001058, 8e-06, 1.5e-05, 4.6e-05, 0.001069,
			0.013118, 6.4e-05, 0.016585, 0.008005, 0.004525, 0.01047, 1.1e-05,
			4e-06, 1e-06, 1e-06, 1e-06, 0.000346, 0.003028, 0.3629, 0.605291,
			0.024532, 0.13292, 6e-06, 2e-06, 2e-06, 2e-06, 2e-06, 3.5e-05,
			0.000585, 0.000348, 0.000227, 0.000171, 7e-06, 0.08057, 0.758265,
			0.999926, 0.026228, 0.430843, 0.460833, 0.076263, 0.682728,
			0.000663, 0.286479, 0.000348, 1.2e-05, 5e-05, 0.000407, 4.8e-05,
			0.000171, 5e-05, 0.000202, 3.5e-05, 0.000215, 2.7e-05, 0.000227,
			3.3e-05, 0.000461, 0.000124, 8e-06, 0.000109, 0.000124, 7e-06,
			0.000115, 0.000123, 1e-06, 0.000122, 0.000125, 3e-06, 0.000122,
			0.000121, 1.8e-05, 0.000105, 3.5e-05, 4e-06, 4.6e-05, 0.000216,
			8.6e-05, 0.000174, 0.000106, 0.00019, 7.8e-05, 0.000171, 7.1e-05,
			0.000256, 0.000219, 0.000174, 8.899999999999999e-05, 0.000168,
			0.000114, 8e-06, 4.5e-05, 0.000549, 0.041588, 9.399999999999999e-05,
			0.000272, 5.8e-05, 4e-06, 4.2e-05, 0.000563, 0.012524, 0.011557,
			0.000133, 0.033325, 8.1e-05, 3.4e-05, 0.000523, 0.041159, 5.2e-05,
			2.3e-05, 5.7e-05, 0.016827, 9.500000000000001e-05, 0.000229,
			7.1e-05, 0.000184, 7.2e-05, 0.000183, 5.3e-05, 0.000166, 3.2e-05,
			0.000225, 0.037247, 1.000281, 1.5e-05, 1.8e-05, 3.9e-05, 7e-06,
			6e-06, 5.9e-05, 8e-06, 4e-06, 4.7e-05, 0.000492, 4.2e-05, 7e-06,
			4e-06, 3e-06, 6e-06, 2.5e-05, 6e-05, 1.8e-05, 6e-06, 1.8e-05, 6e-06,
			5.7e-05, 1.5e-05, 0.000178, 3.4e-05, 6e-06, 4e-06, 4e-06, 7e-06,
			0.000154, 1.6e-05, 4e-06, 3e-06, 4e-06, 5.7e-05, 0.000236, 4.2e-05,
			7e-06, 3e-06, 4e-06, 0.000261, 4.1e-05, 6e-06, 8.3e-05, 4.9e-05,
			8e-06, 5e-06, 4e-06, 4e-06, 5e-06, 1.1e-05, 0.000377, 4.3e-05,
			8e-06, 4e-06, 4e-06, 6e-06, 4e-06, 9e-06, 0.000183, 2.7e-05, 6e-06,
			3e-06, 4e-06, 0.000203, 2.5e-05, 6e-06, 3e-06, 4e-06, 6e-06, 0.0002,
			2.8e-05, 6e-06, 4e-06, 4e-06, 7e-06, 0.000205, 2.7e-05, 6e-06,
			4e-06, 3e-06, 0.000183, 2.9e-05, 6e-06, 4e-06, 3e-06, 7e-06,
			0.000217, 2.6e-05, 6e-06, 4e-06, 3e-06, 6e-06, 0.000209, 3.5e-05,
			6e-06, 3e-06, 3e-06, 0.000247, 4.3e-05, 5e-06, 3e-06, 3e-06, 7e-06,
			8.000000000000001e-05, 1.4e-05, 4e-06, 4e-06, 3e-06, 7.6e-05,
			0.000233, 4.2e-05, 6e-06, 3e-06, 3e-06, 0.000108, 1.4e-05, 5e-06,
			4e-06, 5.5e-05, 0.000259, 3.3e-05, 3.4e-05, 0.000106, 0.000304,
			0.000247, 3.3e-05, 0.000169, 0.000276, 3.3e-05, 3.2e-05, 0.000112,
			0.000275, 0.000284, 0.000244, 6.4e-05, 0.00013, 0.000222, 0.000244,
			0.000377, 0.000136, 0.000324, 6.1e-05, 0.000101, 0.000304, 0.000205,
			0.000298, 0.000202, 0.000265, 4.3e-05, 0.000182, 0.000198, 3.6e-05,
			0.036618, 0.167993, 0.000405, 5.6e-05, 0.132945, 0.5075499999999999,
			1.839101, 0.160079, 0.856059, 0.00019, 0.814619, 0.001748, 0.326707,
			0.016594, 0.104517, 0.000487, 1.2e-05, 3.5e-05, 0.030896, 1.3e-05,
			2.5e-05, 2e-06, 5.6e-05, 2e-06, 0.00016, 8e-06, 1e-06, 4.4e-05,
			6e-06, 0.000232, 2e-06, 9.6e-05, 5e-06, 1e-06, 0.000219, 3e-06,
			1e-06, 0.000281, 4e-06, 1e-06, 0.000247, 2e-06, 1e-06, 0.000182,
			4e-06, 1e-06, 0.000234, 3e-06, 2e-06, 0.000331, 7e-06, 2e-06,
			0.000228, 7e-06, 0.000124, 0.000342, 0.000243, 0.000109, 8e-06,
			0.00015, 6.1e-05, 8e-06, 0.006888, 7.4e-05, 0.033877, 0.03964,
			0.031221, 0.027626, 0.029209, 0.027819, 0.008146, 0.003837,
			0.054232, 0.141787, 0.189477, 0.000731, 0.037917, 0.239763,
			0.016276, 0.101792, 0.121279, 0.569522, 0.162138, 0.167452,
			0.100904, 0.050978, 0.193571, 0.023699, 0.00188, 0.7299330000000001,
			0.14706, 0.069059, 0.000354, 2.1e-05, 0.000376, 0.051512, 4e-05,
			0.00026, 1.9e-05, 5.1e-05, 4e-06, 6e-05, 0.000322, 4.5e-05, 1.3e-05,
			9e-06, 7.8e-05, 3.9e-05, 0.000258, 5.4e-05, 6.9e-05, 8e-06, 6.2e-05,
			0.000148, 4.2e-05, 0.000136, 5.7e-05, 4.7e-05, 0.000226, 0.00012,
			0.000106, 5.4e-05, 0.000169, 9.7e-05, 0.000135, 5.3e-05, 0.000161,
			5.6e-05, 2.9e-05, 1.1e-05, 2.8e-05, 2.9e-05, 0.000329, 4.8e-05,
			2.4e-05, 1e-05, 3.4e-05, 2.8e-05, 0.000345, 0.000111, 0.000216,
			8e-06, 0.010716, 0.000189, 0.002223, 0.000222, 0.000261, 6.1e-05,
			0.000497, 0.000121, 6e-06, 3.1e-05, 7.4e-05, 0.000316, 0.000201,
			0.000241, 0.037019, 0.011593, 0.025272, 1.2e-05, 0.005462, 0.000153,
			0.000308, 1.8e-05, 0.000457, 0.000157, 1.2e-05, 0.000111,
			6.499999999999999e-05, 8.500000000000001e-05, 0.000121, 0.036178,
			0.062789, 0.209764, 2.2e-05, 0.000104, 0.000598, 0.000113, 0.000858,
			0.001237, 1.1e-05, 6.4e-05, 0.022295, 0.002239, 0.02595, 0.048743,
			2.3e-05, 0.048933, 0.000101, 3.8e-05, 0.134329, 0.013961, 1e-05,
			0.003331, 7e-06, 0.006234, 0.000175, 8e-06, 0.0002, 0.000699,
			2.4e-05, 0.001724, 6e-06, 0.000252, 1.3e-05, 0.00269, 0.000125,
			7e-06, 0.000158, 0.007282, 0.015473, 0.064868, 6e-06, 0.216,
			2.2e-05, 2.9e-05, 6.9e-05, 0.000317, 1.4e-05, 0.002346, 0.00051,
			0.005226, 2e-05, 0.019417, 0.001007, 0.000196, 0.005594, 0.005761,
			0.008026, 0.09038, 0.000229, 0.000128, 0.209391, 0.231852, 0.032119,
			5e-06, 5e-06, 2e-06, 2e-06, 1e-06, 2e-06, 3.3e-05, 0.000664, 1e-05,
			2e-06, 0, 1e-06, 1e-06, 8.899999999999999e-05, 1.8e-05, 2.7e-05,
			5e-06, 1e-06, 1e-06, 0.000308, 4e-06, 2e-06, 2e-06, 0.000159, 5e-06,
			1e-06, 1e-06, 0.000537, 8e-06, 2e-06, 2e-06, 1e-06, 1e-06, 1e-06,
			0.00044, 1e-05, 2e-06, 3e-06, 3e-06, 3e-06, 2e-06, 0.0001, 0.000368,
			1e-05, 1e-06, 3e-06, 3e-06, 4e-06, 2e-06, 0.000452, 5e-06, 3e-06,
			2e-06, 2e-06, 2e-06, 0.000215, 6e-06, 2e-06, 2e-06, 0.000259, 7e-06,
			3e-06, 1e-06, 0.000209, 5e-06, 2e-06, 1e-06, 0.000236, 4e-06, 1e-06,
			2e-06, 0.000238, 3e-06, 1e-06, 2e-06, 0.000252, 1.6e-05, 1e-06,
			1e-06, 0.000255, 1.2e-05, 1e-06, 2e-06, 0.000202, 1.5e-05, 1e-06,
			1e-06, 0.000251, 1.2e-05, 1e-06, 1e-06, 0.000198, 4e-06, 1e-06,
			2e-06, 0.000254, 4e-06, 1e-06, 1e-06, 0.00013, 0.000103, 2e-06,
			1e-06, 1e-06, 0.00023, 5e-06, 2e-06, 1e-06, 0.000244, 4e-06, 1e-06,
			0, 0.000233, 6e-06, 1e-06, 1e-06, 0.000241, 4e-06, 1e-06, 1e-06,
			0.000238, 6e-06, 3e-06, 1e-06, 0.000234, 6e-06, 2e-06, 1e-06,
			0.000234, 8e-06, 1e-06, 1e-06, 0.000236, 7e-06, 1e-06, 1e-06,
			0.000236, 4e-06, 1e-06, 1e-06, 0.000237, 5e-06, 1e-06, 2e-06,
			0.000236, 2e-06, 3e-06, 4e-06, 0.000237, 6e-06, 3e-06, 3e-06,
			0.000232, 4e-06, 2e-06, 1e-06, 0.000238, 4e-06, 1e-06, 2e-06,
			0.000239, 6e-06, 1e-06, 1e-06, 0.00024, 2e-06, 1e-06, 1e-06,
			0.000241, 3e-06, 2e-06, 1e-06, 0.000238, 4e-06, 2e-06, 1e-06,
			0.000237, 3e-06, 1e-06, 2e-06, 0.00024, 5e-06, 1e-06, 1e-06,
			0.000237, 4e-06, 1e-06, 1e-06, 0.00024, 3e-06, 2e-06, 1e-06,
			0.000305, 4e-06, 2e-06, 0.000194, 1.2e-05, 1e-06, 0.000223, 1.2e-05,
			1e-06, 0.000235, 1.5e-05, 1e-06, 0.000224, 1.2e-05, 2e-06, 0.000231,
			1.1e-05, 2e-06, 0.000225, 6e-06, 2e-06, 1e-06, 0.000245, 1.4e-05,
			1e-06, 0.000218, 2e-06, 1e-06, 0.000243, 3e-06, 2e-06, 0.00024,
			4e-06, 1e-06, 0.00024, 4e-06, 2e-06, 0.000238, 2e-06, 1e-06, 1e-06,
			0.000241, 2e-06, 1e-06, 0.000242, 4e-06, 1e-06, 0.000241, 2e-06,
			1e-06, 0.000242, 4e-06, 1e-06, 0.00024, 4e-06, 1e-06, 0.000243,
			1.6e-05, 2e-06, 0.000225, 1.2e-05, 2e-06, 0.000231, 1.5e-05,
			0.00023, 1.1e-05, 2e-06, 0.000231, 1.1e-05, 0.000237, 1.4e-05,
			0.000219, 4e-06, 2e-06, 0.000241, 5e-06, 0.000245, 3e-06, 0.000247,
			6e-06, 3e-06, 0.000229, 5e-06, 0.000238, 6e-06, 3e-06, 0.000244,
			1.3e-05, 0.000243, 2e-06, 0.000222, 0.000245, 3e-06, 2e-06,
			0.000239, 3e-06, 3e-06, 0.000238, 1e-06, 1e-06, 0.000244, 3e-06,
			2e-06, 0.000239, 2e-06, 0.000244, 1e-06, 0.000244, 0.000245,
			0.000255, 0.000243, 0.000251, 1.6e-05, 0.000231, 1.3e-05, 0.000228,
			1.2e-05, 0.000238, 5e-06, 0.000235, 1.3e-05, 0.000192, 7.8e-05,
			1.4e-05, 9.8e-05, 9.7e-05, 0.000236, 0.000256, 0.000247, 2e-05,
			8.4e-05, 1.2e-05, 0.000104, 6.9e-05, 1.3e-05, 0.000179, 0.000245,
			0.000256, 1e-06, 9.2e-05, 0.000124, 1.7e-05, 0.000242, 0.000143,
			1.7e-05, 0.064764, 0.268533, 0.000247, 0.000117, 4.6e-05, 0.0001,
			0.00026, 1.3e-05, 7.8e-05, 0.000413, 7.499999999999999e-05,
			0.000187, 7.6e-05, 0.00019, 0.015809, 0.000237, 4e-05, 2.3e-05,
			0.000115, 0.000268, 9e-06, 3.1e-05, 0.000317, 0.000248, 0.00025,
			0.000111, 0.00018, 3.2e-05, 0.000196, 5.3e-05, 0.000188, 4.7e-05,
			0.000197, 6.1e-05, 0.000184, 6.8e-05, 0.000187, 0.03969, 0.401298,
			0.191103, 0.038273, 0.155567, 2.8e-05, 0.000256,
			6.600000000000001e-05, 1.2e-05, 0.000205, 1.5e-05, 0.413707,
			0.02753, 0.142191, 0.120225, 0.761589, 0.148513,
			0.07999199999999999, 0.443199, 1.476141, 0.380089, 0.005695,
			0.000311, 1.2e-05, 0.008484999999999999, 0.849543, 0.00359,
			0.751508, 1.292865, 0.179771, 0.5266, 0.366045, 2e-05, 1.03151,
			1.2e-05, 0.6017670000000001, 0.705453, 1.29376, 0.388697, 0.000119,
			0.000292, 1.4e-05, 7e-06, 0.000235, 1e-05, 0.171773,
			0.07598100000000001, 0.310302, 0.0004, 1.7e-05, 8.1e-05, 0.000385,
			0.000118, 0.000302, 0.000114, 0.000281, 2.9e-05, 0.000209, 2.7e-05,
			0.000239, 2.5e-05, 0.000212, 6e-05, 0.000224, 9.1e-05, 0.000233,
			1.9e-05, 0.000198, 1.9e-05, 0.000289, 0.000267, 0.000198, 6e-05,
			0.000195, 7.6e-05, 3e-06, 2e-06, 1e-06, 2e-06, 2e-06, 6.9e-05,
			0.000555, 0.000244, 0.000241, 0.039375, 0.000124, 0.000288,
			9.899999999999999e-05, 3e-06, 6.2e-05, 0.000571, 0.048884, 0.000149,
			1.4e-05, 6e-06, 6e-06, 3.3e-05, 1.6e-05, 7e-06, 2.5e-05, 0.000324,
			0.000219, 9e-06, 0.000153, 0.000128, 0.00011, 0.000155, 9e-06,
			0.00017, 7.3e-05, 0.037596, 0.027548, 0.000148, 0.00018, 0.016617,
			7.499999999999999e-05, 0.000234, 3.3e-05, 0.000171, 2.8e-05,
			0.000231, 3.5e-05, 0.00019, 2.8e-05, 0.000209, 0.039791, 0.832296,
			1.999254, 0.048807, 0.016688, 0.103137, 0.855847, 0.655344,
			0.000661, 0.013452, 0.168439, 0.136821, 0.025272, 9e-06,
			0.007948999999999999, 0.037041, 0.047981, 0.008460000000000001,
			0.04047, 0.009528, 0.020497, 0.072979, 0.009079, 0.11388, 0.023627,
			0.016839, 0.235363, 0.200238, 0.259802, 0.133895, 0.19443, 0.003572,
			0.124423, 0.003563, 0.37003, 0.040397, 0.3915, 0.000331, 1.7e-05,
			0.186427, 0.003647, 0.000144, 0.004702, 0.542918, 0.227775,
			0.641863, 0.034463, 0.016594, 0.419727, 0.000376, 3.6e-05, 0.000115,
			0.000327, 0.0005330000000000001, 0.00028, 0.000207, 0.000324,
			0.000296, 1e-05, 7e-06, 4.2e-05, 0.000562, 0.010122, 3.8e-05,
			0.018846, 0.000187, 0.000264, 0.000181, 0.000292, 0.000118,
			0.000469, 0.01084, 0.000237, 3.8e-05, 0.019239, 2.8e-05, 0.000227,
			0.0001, 0.000213, 0.000112, 0.000241, 0.000121, 0.000312, 0.000149,
			0.000209, 0.000133, 0.000296, 0.000132, 0.000214, 0.00166, 0.02373,
			0.001922, 4e-06, 4.3e-05, 3e-06, 5.1e-05, 3e-06, 5.6e-05, 2e-06,
			5.4e-05, 1e-06, 0.000392, 8e-06, 1e-06, 4.8e-05, 3e-06, 3.7e-05,
			2e-06, 0.000158, 1e-05, 2e-06, 1e-06, 4.7e-05, 0.000205, 3e-06,
			1e-06, 1e-06, 0.000516, 0.000201, 0.000213, 0.000308, 0.000241,
			0.00026, 0.000234, 0.169798, 8.500000000000001e-05, 0.0003,
			0.000144, 3e-06, 2e-06, 6.8e-05, 0.000589, 0.03856, 0.035385,
			0.000115, 0.000179, 5.8e-05, 0.000143, 0.000343, 0.000129, 0.000214,
			7.2e-05, 0.000288, 8.1e-05, 0.000203, 5.1e-05, 0.000369,
			9.500000000000001e-05, 0.000176, 0.001365, 0.013006, 0.001368,
			3e-06, 1e-06, 1e-06, 1e-06, 2e-06, 5.2e-05, 2e-06, 6.3e-05, 1.3e-05,
			1e-06, 1e-06, 6.7e-05, 2e-06, 1e-06, 4.3e-05, 4e-06, 6.1e-05, 1e-06,
			1e-06, 7.1e-05, 2e-06, 7e-06, 0.0002, 0.000255, 0.000229, 0.000516,
			0.000282, 0.000244, 0.000256, 0.000238, 0.000242, 0.000245,
			0.029151, 8.3e-05, 0.000294, 0.000143, 5e-06, 2e-06, 6.4e-05,
			0.000604, 0.012818, 0.00022, 0.019331, 0.000117, 0.000224, 0.000222,
			0.000234, 7.6e-05, 0.000216, 6.7e-05, 0.00028, 7.1e-05, 0.000219,
			4.5e-05, 0.000249, 6.7e-05, 0.000193, 0.001358, 0.013339, 0.001356,
			4e-06, 1e-06, 1e-06, 1e-06, 2e-06, 1e-06, 3.5e-05, 1e-06, 3.2e-05,
			6e-06, 6.8e-05, 1e-06, 1e-06, 4e-05, 7e-06, 1.5e-05, 2.7e-05, 5e-06,
			3.2e-05, 6e-06, 2.5e-05, 3e-05, 0.000278, 0.000251, 0.000215,
			0.000489, 0.000514, 0.000257, 0.000257, 0.000243, 0.000218,
			0.010181, 0.001256, 3e-05, 0.017594, 6.499999999999999e-05,
			0.000246, 0.000173, 4e-06, 1e-06, 6.499999999999999e-05, 0.000554,
			0.032475, 0.000117, 0.000258, 0.00054, 0.000265, 0.000146, 0.000199,
			6.9e-05, 0.000292, 0.000126, 0.000205, 0.000109, 0.000287, 0.000119,
			0.00021, 0.001505, 0.01251, 0.001603, 3e-06, 2e-06, 1e-06, 1e-06,
			2e-06, 1e-06, 4.5e-05, 3e-06, 6.7e-05, 1.2e-05, 1e-06, 1e-06,
			6.7e-05, 1.9e-05, 1e-06, 1e-06, 1e-05, 1.9e-05, 5.9e-05, 2e-06,
			9.3e-05, 2e-06, 0.000219, 0.000245, 0.000208, 0.000262, 0.000498,
			0.000251, 0.000244, 0.000246, 0.000244, 0.000247, 0.02889, 8.1e-05,
			0.000216, 0.000107, 3e-06, 2e-06, 6.9e-05, 0.0005820000000000001,
			0.01628, 0.00018, 5.4e-05, 0.000269, 0.015699, 2.2e-05, 0.000102,
			0.000347, 0.00041, 0.000227, 7.7e-05, 0.0002, 6.2e-05, 0.000236,
			4.8e-05, 0.00018, 7.499999999999999e-05, 0.000302, 9.2e-05,
			0.000167, 0.001491, 0.012937, 0.001596, 3e-06, 2e-06, 2e-06, 1e-06,
			2e-06, 2e-06, 2e-06, 1e-06, 3.4e-05, 3e-06, 7.499999999999999e-05,
			1.8e-05, 1e-06, 1e-06, 1e-06, 6e-05, 2e-06, 9e-06, 5.3e-05, 5e-06,
			2e-05, 1e-05, 0.000295, 0.000242, 0.000245, 0.000522, 0.000488,
			0.000247, 0.000243, 0.000246, 0.000246, 0.028895, 8.2e-05, 0.000303,
			0.000144, 5e-06, 2e-06, 6.8e-05, 0.000595, 0.009254, 0.027474,
			0.012253, 0.000107, 0.000184, 5.8e-05, 0.000119, 0.000216, 4e-05,
			0.000201, 2.2e-05, 0.000263, 4.1e-05, 0.000208,
			6.999999999999999e-05, 0.000266, 3.7e-05, 0.000167, 0.001494,
			0.013389, 0.001558, 4e-06, 2e-06, 1e-06, 2e-06, 1e-06, 1e-06,
			3.8e-05, 3e-06, 6.1e-05, 1e-06, 1e-06, 4.2e-05, 4e-06, 5.6e-05,
			4e-06, 1e-06, 3e-05, 8e-06, 5.4e-05, 1e-06, 1e-06, 2.6e-05,
			0.000256, 0.000241, 0.000244, 0.000553, 0.000246, 0.00022, 0.00024,
			0.000244, 0.000247, 0.000213, 0.028935, 8.899999999999999e-05,
			0.000214, 8.2e-05, 4e-06, 2e-06, 5.9e-05, 0.000562, 0.032548,
			0.000119, 0.000226, 0.0003, 0.000213, 4e-05, 0.000167, 3.3e-05,
			0.000333, 0.000132, 0.000208, 9.1e-05, 0.000296, 0.000118, 0.000181,
			0.00152, 0.013032, 0.001587, 4e-06, 2e-06, 1e-06, 2e-06, 2e-06,
			2e-06, 3.8e-05, 2e-06, 8.1e-05, 1e-06, 0, 1.6e-05, 1e-06, 5e-05,
			4e-06, 5.6e-05, 1e-06, 1e-06, 3.1e-05, 9e-06, 2.8e-05, 9e-06,
			0.00026, 0.000242, 0.000249, 0.000486, 0.000245, 0.000245, 0.000348,
			0.000419, 0.000279, 0.028802, 8.3e-05, 0.000286, 0.000115, 4e-06,
			2e-06, 5.9e-05, 0.000559, 0.000241, 0.002101, 3.5e-05, 0.030066,
			0.000106, 0.000205, 0.001807, 0.000205, 7.2e-05, 0.000191, 3e-05,
			0.000302, 0.000137, 0.000201, 8.899999999999999e-05, 0.000306,
			0.000116, 0.000325, 0.001743, 0.011198, 0.001645, 3e-06, 2e-06,
			2e-06, 1e-06, 2e-06, 1e-06, 1e-05, 3.5e-05, 2e-06, 6.7e-05, 2e-06,
			0, 4.5e-05, 8e-06, 2.2e-05, 3.3e-05, 8e-06, 7.1e-05, 1.4e-05, 1e-06,
			1e-06, 2.7e-05, 0.000255, 0.00024, 0.000243, 0.0005240000000000001,
			0.000242, 0.000246, 0.000282, 0.000452, 0.000251, 0.045419,
			8.500000000000001e-05, 0.000254, 6.1e-05, 2e-06, 3e-06, 6.9e-05,
			0.000559, 0.032483, 7.2e-05, 0.000221, 0.000143, 0.000211, 7.4e-05,
			0.0002, 4.9e-05, 0.000301, 0.000129, 0.000212, 9.2e-05, 0.000262,
			6e-05, 0.000198, 0.001624, 0.013169, 0.001673, 3e-06, 1e-06, 1e-06,
			2e-06, 2e-06, 1e-06, 4e-05, 3e-06, 6.4e-05, 1e-06, 1e-06, 4.8e-05,
			6e-06, 1.2e-05, 6.3e-05, 2e-06, 5.2e-05, 2e-06, 1e-06, 0, 3.5e-05,
			1e-06, 0.000295, 0.000239, 0.000243, 0.000492, 0.000243, 0.000278,
			0.00031, 0.000424, 0.000219, 0.028386, 0.000228, 5.4e-05, 0.000213,
			3.5e-05, 0.000238, 0.007959000000000001, 2.2e-05, 7.1e-05, 0.000481,
			0.000111, 4e-06, 1e-06, 6.8e-05, 0.000623, 0.038715, 0.010124,
			0.000116, 0.000228, 6.2e-05, 0.002913, 0.000265, 2.1e-05, 0.000179,
			1.5e-05, 1.3e-05, 0.000229, 3.9e-05, 0.000196, 3.5e-05, 0.000269,
			7.3e-05, 0.000191, 5.3e-05, 0.000247, 2.2e-05, 0.000177, 0.001569,
			0.010022, 0.001705, 3e-06, 2e-06, 1e-06, 1e-06, 3e-06, 1e-06, 1e-06,
			1e-06, 3.6e-05, 2e-06, 6.499999999999999e-05, 1e-06, 1e-06, 6e-05,
			1e-06, 1e-06, 5.6e-05, 1e-06, 4.2e-05, 4e-06, 1.7e-05, 2e-06,
			0.000327, 0.000232, 0.00025, 0.000239, 0.000501, 0.000215, 0.000245,
			0.000244, 0.000246, 0.000325, 0.02873, 8.7e-05, 0.000337, 0.000112,
			3e-06, 2e-06, 5.5e-05, 0.00056, 0.032383, 0.000119, 0.000246,
			0.001701, 0.000251, 0.004701, 0.000195, 0.006657, 0.027981, 7.3e-05,
			0.00024, 0.019186, 0.000333, 7.7e-05, 0.000241, 0.037189, 0.272651,
			0.227517, 6e-06, 2e-06, 2e-06, 1e-06, 2e-06, 3.7e-05, 2e-06,
			3.4e-05, 2e-06, 0.0006089999999999999, 1.8e-05, 3e-06,
			6.499999999999999e-05, 3e-06, 5.6e-05, 9e-06, 3e-06, 1e-06,
			6.499999999999999e-05, 5e-06, 1e-06, 0.000207, 9e-06, 2e-06, 1e-06,
			1e-06, 0.000442, 9e-06, 1e-06, 2e-06, 1e-06, 1e-06, 3.5e-05,
			0.000105, 1.2e-05, 7.499999999999999e-05, 3e-06, 1e-06, 1e-06,
			1e-06, 1e-06, 1e-06, 0.00047, 3e-06, 2e-06, 1e-06, 1e-06, 1e-06,
			1e-06, 0.000255, 4e-06, 1e-06, 2e-06, 1e-06, 1e-06, 2e-06, 0.000462,
			4e-06, 2e-06, 1e-06, 1e-06, 1e-06, 1e-06, 0.000234, 4e-06, 1e-06,
			1e-06, 1e-06, 0.00024, 6e-06, 1e-06, 2e-06, 1e-06, 0.000236, 5e-06,
			1e-06, 1e-06, 1e-06, 0.000256, 4e-06, 1e-06, 1e-06, 1e-06, 0.00022,
			2e-06, 1e-06, 0.000242, 4e-06, 2e-06, 0.000241, 5e-06, 2e-06,
			0.000233, 3e-06, 2e-06, 0.000239, 5e-06, 2e-06, 0.000238, 4e-06,
			1e-06, 0.00024, 5e-06, 1e-06, 0.000239, 3e-06, 1e-06, 0.000245,
			0.000279, 0.000142, 0.000114, 8.7e-05, 5e-06, 0.000157, 0.000225,
			0.000241, 6.2e-05, 0.000185, 6.2e-05, 4e-06, 0.000144, 0.000247,
			0.000255, 6.600000000000001e-05, 0.00017, 7.499999999999999e-05,
			1.5e-05, 0.000168, 0.000258, 6.8e-05, 0.000165, 7.7e-05, 5e-06,
			0.000145, 0.000242, 6.8e-05, 0.00018, 9.8e-05, 5e-06, 0.000169,
			0.000265, 0.000232, 5.3e-05, 2.5e-05, 5e-06, 0.009259, 0.039637,
			0.00865, 2.8e-05, 5e-06, 5e-06, 0.009263, 2.7e-05, 0.087632, 6e-05,
			0.000318, 1.4e-05, 1.6e-05, 2e-06, 5e-06, 4.2e-05, 0.00032,
			0.037569, 0.703033, 0.214916, 0.64994, 0.04462, 0.302059, 0.999951,
			0.137821, 0.039703, 0.027832, 0.000366, 1.7e-05, 0.000111, 0.000346,
			0.000131, 0.00019, 4.5e-05, 4e-06, 2e-06, 3.8e-05, 0.000618,
			0.036949, 0.0052, 0.000138, 0.0002, 0.000107, 9.399999999999999e-05,
			4e-06, 5.9e-05, 0.000579, 0.032121, 0.000118, 1.5e-05, 3.3e-05,
			3e-06, 0.000374, 0.000259, 6e-06, 0.00016, 5.3e-05,
			6.600000000000001e-05, 0.036463, 0.00435, 0.000131, 0.0002,
			0.016695, 0.000124, 0.000254, 7.7e-05, 0.000202, 6.9e-05, 0.000174,
			4.5e-05, 0.000229, 6.7e-05, 0.000176, 0.038503, 0.271061, 0.036943,
			0.003036, 0.307457, 0.23321, 0.029976, 0.000198, 0.62617, 3e-05,
			0.000353, 1.9e-05, 1e-05, 2e-06, 0.109966, 0.651886, 0.213682,
			4.9e-05, 2.7e-05, 0.000236, 1e-05, 4.6e-05, 2e-06, 0.00011, 2e-06,
			0.000152, 1e-06, 0.133729, 0.609789, 0.031985, 2.2e-05, 9.6e-05,
			0.016657, 9.1e-05, 0.000312, 0.000155, 0.000175, 3.6e-05, 0.000326,
			0.000222, 5e-06, 4.3e-05, 4e-06, 3.9e-05, 1.9e-05, 2.4e-05, 2.7e-05,
			2e-06, 5.9e-05, 0.000446, 2e-05, 3e-06, 5.8e-05, 2e-06, 6e-05,
			3e-06, 5.8e-05, 1e-05, 3e-06, 2e-06, 6.2e-05, 0.000145, 4e-06,
			1e-06, 1e-06, 3.7e-05, 0.000475, 4e-06, 2e-06, 1e-06, 2e-06,
			3.5e-05, 9e-06, 3.5e-05, 1e-06, 0.00041, 8e-06, 2e-06, 1e-06, 1e-06,
			2e-06, 1e-06, 3.9e-05, 2e-06, 0.000412, 4e-06, 2e-06, 1e-06, 1e-06,
			2e-06, 1e-06, 1e-06, 3.9e-05, 0.000437, 4e-06, 2e-06, 1e-06, 2e-06,
			1e-06, 1e-06, 2e-06, 1e-06, 0.000476, 4e-06, 2e-06, 1e-06, 2e-06,
			1e-06, 1e-06, 1e-06, 1e-06, 0.000455, 5e-06, 1e-06, 1e-06, 1e-06,
			1e-06, 1e-06, 0.000236, 1e-06, 2e-06, 1e-06, 1e-06, 0.000242, 5e-06,
			2e-06, 1e-06, 0.000302, 7e-06, 1e-06, 2e-06, 0.000174, 4e-06, 2e-06,
			1e-06, 0.000263, 3e-06, 2e-06, 1e-06, 0.000206, 5e-06, 1e-06, 2e-06,
			0.000263, 9e-06, 2e-06, 1e-06, 0.000241, 1.1e-05, 2e-06, 1e-06,
			0.000262, 1.9e-05, 3e-06, 1e-06, 0.000223, 1.9e-05, 0.000224,
			0.000248, 0.000244, 0.000217, 0.00024, 0.000244, 0.000246, 0.000221,
			0.000274, 0.000241, 0.000212, 0.000277, 0.000213, 0.000281,
			0.000242, 0.000245, 0.000244, 0.000246, 0.000244, 0.00025, 0.00024,
			0.000247, 0.000244, 0.000242, 0.001342, 0.000379, 0.034867,
			0.000105, 0.000224, 9.3e-05, 0.000182, 2.7e-05, 0.00026, 3.4e-05,
			0.000379, 0.039497, 0.5442, 0.357434, 1.099135, 0.041655, 0.85846,
			0.09723900000000001, 0.311746, 0.29389, 0.394283, 0.308007,
			0.445888, 0.148214, 0.097913, 0.307962, 0.692039, 0.307906,
			0.593507, 0.056654, 0.041922, 0.033815, 0.274117,
			0.8501919999999999, 4.8e-05, 4e-05, 5.2e-05, 0.000176, 3.5e-05,
			7.8e-05, 4.1e-05, 3.9e-05, 1.4e-05, 3.8e-05, 2e-05, 1e-05, 5e-06,
			3e-05, 1.3e-05, 0.14915, 0.026055, 0.003791, 0.562937, 1.999277,
			1.065992, 0.000143, 0.523873, 0.311931, 0.028066, 0.069262,
			0.239786, 1.759471, 0.246945, 0.756221, 0.697726, 0.000743,
			0.297642, 0.003465, 0.913362, 1.3e-05, 0.0866, 0.081234, 0.025897,
			0.050497, 0.259128, 0.014569, 0.564476, 0.004333, 0.312601,
			0.003488, 0.683764, 0.995133, 0.004903, 0.270456,
			0.6224730000000001, 0.000158, 0.161523, 0.000449, 2e-05, 0.000129,
			0.000428, 0.000134, 0.000275, 0.000131, 0.000373, 8.8e-05, 0.000344,
			7.6e-05, 0.000289, 9.899999999999999e-05, 0.000266, 0.00011,
			0.000218, 0.000129, 0.000203, 3.2e-05, 0.000265,
			8.899999999999999e-05, 0.000232, 7.9e-05, 0.000238, 0.000368,
			0.000233, 0.000121, 0.000228, 0.000164, 5e-06, 3e-06, 2e-06, 1e-06,
			8.8e-05, 0.000565, 0.000216, 0.034407, 0.000127, 0.000216, 5.8e-05,
			3e-06, 5.7e-05, 0.000566, 0.032524, 0.000164, 1.9e-05, 8e-06,
			2.2e-05, 1.4e-05, 1.4e-05, 4.4e-05, 0.000401, 5.6e-05, 9.6e-05,
			7e-06, 0.000133, 8e-06, 0.000248, 1.3e-05, 1e-06, 0.000302, 7.6e-05,
			0.036992, 0.028077, 0.000239, 0.000188, 0.016701, 0.000103,
			0.000332, 0.000134, 0.000307, 0.00013, 0.000323, 0.000139, 0.000212,
			0.000116, 0.000175, 0.037659, 0.132015, 0.312029, 0.297586,
			1.336091, 0.663151, 1.295715, 0.703577, 0.296261, 0.101385, 0.22987,
			0.000233, 0.434696, 0.000419, 3.6e-05, 0.000159, 0.000332, 0.000899,
			0.000119, 0.00019, 0.0352, 0.144224, 0.05227, 0.149337, 0.185305,
			0.000393, 0.184107, 5.8e-05, 0.000343, 0.183449, 0.000685, 0.000284,
			1.5e-05, 0.000102, 0.000448, 0.00037, 1.8e-05, 0.000112, 0.000401,
			0.00012, 0.00029, 0.000119, 0.000243, 6.4e-05, 0.000177, 5.4e-05,
			0.000188, 5.4e-05, 0.000279, 9.2e-05, 0.000504, 0.000166, 1.5e-05,
			5.4e-05, 0.000175, 1.5e-05, 7.7e-05, 0.000155, 1.5e-05, 0.000101,
			0.000401, 0.000268, 0.000207, 0.0001, 0.000145,
			0.0009700000000000001, 7.2e-05, 0.036994, 0.14733, 0.010867,
			0.037774, 0.056528, 0.10916, 0.000384, 1e-05, 2.9e-05, 0.000265,
			0.037653, 0.175573, 1.9e-05, 0.676889, 0.702174, 0.297846, 1.701447,
			0.066121, 5e-06, 5e-06, 2e-06, 2e-06, 3e-06, 1e-06, 2e-06, 3e-06,
			2e-06, 0.000725, 1.9e-05, 2e-06, 1e-06, 1e-06, 1e-06, 1e-06,
			6.999999999999999e-05, 2e-05, 2e-06, 3e-06, 1e-06, 1e-06, 1e-06,
			0.000218, 7e-06, 1e-06, 1e-06, 1e-06, 7.2e-05, 0.000155, 6e-06,
			1e-06, 1e-06, 1e-06, 0.000256, 3e-06, 2e-06, 1e-06, 0.000559,
			1.6e-05, 0.000227, 0.000299, 2.6e-05, 0.00012, 0.000264, 1.5e-05,
			0.000238, 1.5e-05, 1.4e-05, 0.000224, 0.000234, 1.5e-05, 0.000223,
			0.006457, 2.2e-05, 0.016599, 0.07625899999999999, 0.238719,
			0.000408, 0.037377, 0.08400299999999999, 0.003761, 0.124235,
			0.003565, 1.337726, 1.999245, 1.075482, 2.9e-05, 0.000378, 2e-05,
			9e-06, 2e-06, 1.8e-05, 6e-06, 0.923339, 1.999252, 1.10893, 0.003052,
			0.887231, 1.999357, 1.735131, 0.000561, 0.263547, 1.066412,
			0.000189, 6.7e-05, 0.932557, 0.069161, 0.000414, 1.7e-05, 0.000328,
			0.076215, 0.148162, 1.6e-05, 0.000117, 0.119362, 0.000372, 1.7e-05,
			0.7902090000000001, 0.794934, 0.918648, 0.0002, 1.080404, 0.413585,
			3.6e-05, 0.000285, 5.5e-05, 4e-06, 2.5e-05, 5e-06, 0.091326,
			0.003882, 0.572217, 7e-06, 4e-06, 2e-06, 2e-06, 8e-06, 4.3e-05,
			2e-06, 2e-06, 3.3e-05, 0.000581, 2.4e-05, 3e-06, 2e-06, 2e-06,
			2e-06, 2e-06, 0.000154, 6e-06, 2e-06, 2e-06, 2e-06, 0.000242,
			1.4e-05, 3e-06, 6.600000000000001e-05, 9e-06, 0.00015, 6.8e-05,
			2e-05, 0.000135, 6.7e-05, 1.3e-05, 0.000447, 6.3e-05, 6e-06,
			0.000211, 5e-06, 0.000197, 0.000266, 1.8e-05, 1.8e-05, 0.000206,
			5.2e-05, 1e-05, 0.070046, 1.1e-05, 0.844631, 1.999285, 0.37526,
			0.269128, 0.000144, 0.428814, 0.000377, 2e-05, 0.000132, 0.000335,
			0.000146, 0.00032, 0.00014, 0.000315, 9.000000000000001e-05,
			0.000326, 7.8e-05, 0.000348, 0.000138, 0.000309, 0.000191, 0.000269,
			9.2e-05, 0.000228, 8.1e-05, 0.000333, 0.000478, 0.000208, 0.000122,
			0.000251, 0.000158, 6e-06, 3e-06, 2e-06, 2e-06, 3.7e-05, 0.000592,
			0.000243, 0.026904, 0.000156, 0.000307, 0.000234, 1.1e-05, 5.5e-05,
			0.000566, 0.032068, 0.000263, 5.9e-05, 4.3e-05, 4.5e-05, 4.2e-05,
			4.2e-05, 4e-05, 0.000202, 0.000138, 3.5e-05, 2.2e-05, 3e-05,
			0.000149, 0.000149, 3e-05, 5.4e-05, 0.000164, 2.8e-05, 0.000127,
			0.03696, 0.019837, 0.00032, 0.000252, 0.016369, 0.000222, 0.000284,
			0.000233, 0.000254, 0.00022, 0.000266, 0.000239, 0.000251, 0.000192,
			0.000192, 0.037031, 1.7e-05, 0.116766, 0.192277, 0.435377, 0.091586,
			3.1e-05, 0.000373, 1.9e-05, 1e-05, 2e-06, 0.000261, 1.4e-05,
			0.280014, 0.023348, 3.2e-05, 2.9e-05, 0.000314, 2.2e-05, 1.2e-05,
			2e-06, 0.000253, 1.7e-05, 0.975979, 0.62699, 0.37293,
			0.9999749999999999, 0.626341, 0.492913, 0.014529, 0.570348,
			0.076026, 0.235104, 0.003504, 0.606799, 0.126116, 0.99708, 0.306968,
			0.005815, 0.563343, 0.123881, 0.303074, 0.697012, 0.303014,
			0.075444, 0.000103, 0.496756, 0.124502, 0.303213,
			0.06970899999999999, 0.6271060000000001, 0.303057, 0.571645,
			0.428396, 1.129816, 0.441094, 1.216598, 0.184097, 0.598553,
			1.762639, 0.000133, 0.236455, 0.700106, 0.025727, 0.876292,
			0.003488, 0.124494, 0.00356, 0.265654, 0.031362, 0.997795,
			0.9701149999999999, 0.029865, 0.913193, 0.000163,
			0.08662400000000001, 0.969381, 0.030588, 1.000004, 0.968747,
			1.999191, 0.181717, 0.003031, 0.476371, 0.000189, 0.498117,
			0.001757, 0.094473, 0.070796, 0.257284, 0.415613, 0.324319,
			0.103689, 3e-05, 0.000304, 1.9e-05, 1.3e-05, 1e-06,
			0.09349499999999999, 2.2e-05, 0.042766, 0.496198, 0.263337,
			0.138729, 0.028411, 0.088029, 0.031219, 0.388701, 0.324931,
			0.266295, 0.268827, 0.235355, 0.105707, 1.7e-05, 0.123881, 0.381654,
			0.076361, 0.09857399999999999, 0.11765, 0.07213, 0.144328, 0.047985,
			0.061286, 0.019094, 0.083081, 0.000315, 1.3e-05, 0.171753, 0.072075,
			0.152366, 0.031976, 0.46934, 0.197771, 0.036378 };

	void save_data_on_file(const string& fileName, const mat& vet1,
			const mat& vet2);
	void save_data_on_file(const string& fileName, list<double>& theList);
	void printTestResult(string testName, bool result);
	bool compareDouble(double val1, double val2);
	bool compareDouble(double val1, double val2, double acErr);
	bool compareMat(mat& mat1, mat& mat2);
	bool test_QuickSort();
	bool test_Mode();
	bool test_list_tocvector();
	bool test_empiricalCdf();
	bool test_computeCost();
	bool test_informationCriterion();
	bool test_gradientDescendent();
	bool test_pdf_weibull();
	bool test_cdf_weibull();
	bool test_pdf_exponential();
	bool test_cdf_exponential();
	bool test_pdf_pareto();
	bool test_cdf_pareto();
	bool test_pdf_cauchy();
	bool test_cdf_cauchy();
	bool test_fitModelsInterArrival();
	bool test_modelSelection();
	bool test_calcOnOff();
};

#endif /* DATAPROCESSOR_H_ */
