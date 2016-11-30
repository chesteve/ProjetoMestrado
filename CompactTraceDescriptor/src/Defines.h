/*
 * ConstantsDeinition.h
 *
 *  Created on: 4 de jul de 2016
 *      Author: apaschoalon
 */

#ifndef DEFINES_H_
#define DEFINES_H_

/*******************************************************************************
 * Defines
 ******************************************************************************/
//Math
#define MEGA_POWER 1000000

//Stochastic Models
#define WEIBULL "weibull"
#define NORMAL "normal"
#define EXPONENTIAL_MEAN "exponential-mean"
#define EXPONENTIAL_LINEAR_REGRESSION "exponential-linear-regression"
#define PARETO_LINEAR_REGRESSION "pareto-linear-regression"
#define PARETO_MAXIMUM_LIKEHOOD "pareto-maximum-likehood"
#define CAUCHY "cauchy"
#define CONSTANT  "constant"
#define CONSTANT_SINGLE_DATA "constant-single-data"
#define NO_MODEL "no-model-selected"

// Debug defines
//#define DEBUG 1 // basic debug
//#define DEBUG_DataProcessor_calculate_loop 1
//#define DEBUG_DataProcessor_calculate 1
//#define DEBUG_NetworkFlow 1
//#define DEBUG_flowThread 1
//#define DEBUG_DatabaseInterface 1
//#define DEBUG_NetworkTrace_exec 1
#define DEBUG_DataProcessor_interArrival 1

//Misc
#define TEST_FUNCTIONS 1 //execute regression testes
#define HLINE "----------"
#define TAB "::"

/*******************************************************************************
 * Types
 ******************************************************************************/

/**
 *
 */
enum protocol_enum{
	PROTOCOL__NULL,
	PROTOCOL__ETHERNET,
	PROTOCOL__IPV4,
	PROTOCOL__IPV6,
	PROTOCOL__ARP,
	PROTOCOL__ICMP,
	PROTOCOL__ICMPV6,
	PROTOCOL__TCP,
	PROTOCOL__UDP,
	PROTOCOL__DCCP,
	PROTOCOL__GRE,
	PROTOCOL__SCTP,
	PROTOCOL__HTTP,
	PROTOCOL__HTML,
	PROTOCOL__SMTP
};

/**
 *
 */
typedef protocol_enum protocol;

/**
 *
 */
typedef enum information_criterion_enum{
	AIC,
	BIC
}information_criterion;

/**
 *
 */
typedef unsigned short int protocol_code;

/**
 *
 */
typedef unsigned short int stochastic_model;

/**
 *
 */
typedef unsigned int port_number;

/**
 *
 */
typedef unsigned short int ttl_val;

/**
 *
 */
typedef double time_sec;

/**
 *
 */
typedef unsigned short int packet_size;

/**
 *
 */
typedef long int kbytes;

/**
 *
 */
typedef unsigned int counter;


/*******************************************************************************
 * Constants
 ******************************************************************************/

/**
 *
 */
const time_sec FILE_CUT_TIME = 0.1;

/**
 *
 */
const time_sec SESSION_CUT_TIME = 30;

/**
 *
 */
const int PACKET_SIZE_MODE_CUT_VALUE = 500;

/**
 *
 */
const protocol_code IPV4_CODE = 2048;

/**
 *
 */
const protocol_code ARP_CODE = 2054;

/**
 *
 */
const protocol_code ARP_CODE_REV = 2056;

/**
 *
 */
const protocol_code IPV6_CODE = 34525;

/**
 *
 */
const protocol_code ICMP_CODE = 1;

/**
 *
 */
const protocol_code TCP_CODE = 6;

/**
 *
 */
const protocol_code UDP_CODE = 17;

/**
 *
 */
const protocol_code DCCP_CODE = 33;

/**
 *
 */
const protocol_code GRE_CODE = 47;

/**
 *
 */
const protocol_code ICMPV6_CODE = 58;

/**
 *
 */
const protocol_code SCTP_CODE = 132;

/**
 *
 */
const port_number MAX_TRANSPORT_PORT_NUMBER = 65535;

#endif /* DEFINES_H_ */
