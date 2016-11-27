/*
 * ConstantsDeinition.h
 *
 *  Created on: 4 de jul de 2016
 *      Author: apaschoalon
 */

#ifndef DEFINES_H_
#define DEFINES_H_

// Debug defines
//#define DEBUG 1 // basic debug
//#define DEBUG_DataProcessor_calculate_loop 1
//#define DEBUG_DataProcessor_calculate 1
//#define DEBUG_NetworkFlow 1
//#define DEBUG_flowThread 1
//#define DEBUG_DatabaseInterface 1
//#define DEBUG_NetworkTrace_exec 1


//Math
#define MEGA_POWER 1000000

//Protocol code
typedef unsigned short int protocol_code;
#define IPV4_CODE 2048
#define ARP_CODE 2054
#define ARP_CODE_REV 2056
#define IPV6_CODE 34525
#define ICMP_CODE 1
#define TCP_CODE 6
#define UDP_CODE 17
#define DCCP_CODE 33
#define GRE_CODE 47
#define ICMPV6_CODE 58
#define SCTP_CODE 132

//Protocols
typedef unsigned short int protocol;
#define PROTOCOL__NULL 0
#define PROTOCOL__ETHERNET 1
#define PROTOCOL__IPV4 2
#define PROTOCOL__IPV6 3
#define PROTOCOL__ARP 4
#define PROTOCOL__ICMP 5
#define PROTOCOL__ICMPV6 6
#define PROTOCOL__TCP 7
#define PROTOCOL__UDP 8
#define PROTOCOL__DCCP 9
#define PROTOCOL__GRE 10
#define PROTOCOL__SCTP 11
#define PROTOCOL__HTTP 12
#define PROTOCOL__HTML 13
#define PROTOCOL__SMTP 14

//Stochastic models
typedef unsigned short int stochastic_model;
#define WEIBULL "weibull"
#define NORMAL "normal"
#define EXPONENTIAL_MEAN "exponential-mean"
#define EXPONENTIAL_LINEAR_REGRESSION "exponential-linear-regression"
#define PARETO_LINEAR_REGRESSION "pareto-linear-regression"
#define PARETO_MAXIMUM_LIKEHOOD "pareto-maximum-likehood"
#define CAUCHY "cauchy"
#define CONSTANT  "constant"
#define NO_MODEL "no-model-selected"


/*
#define MODEL__NULL 0
#define MODEL__BIMODAL_CONSTANT_CONSTANT 1
#define MODEL__BIMODAL_CONSTANT_WEIBULL 3
//#define MODEL__BIMODAL_NORMAL_CONSTANT 4
//#define MODEL__BIMODAL_NORMAL_NORMAL 5
//#define MODEL__BIMODAL_NORMAL_WEIBULL 6
#define MODEL__BIMODAL_WEIBULL_CONSTANT 7
//#define MODEL__BIMODAL_WEIBULL_NORMAL 8
#define MODEL__BIMODAL_WEIBULL_WEIBULL 9
#define MODEL__CONSTANT 10
#define MODEL__NORMAL 11
#define MODEL__PARETO 12
#define MODEL__WEIBULL 13
#define MODEL__GAMMA 14
#define MODEL__EXPONENTIAL 15
#define MODEL__UNIFORM 16
#define MODEL__CAUCHY 17
#define MODEL__POISSON 18
*/

//Miscellaneous
//typedef string ip_addr;
typedef int port_number;
#define HLINE "----------"
#define TAB "::"
#define MAX_TRANSPORT_PORT_NUMBER 65535

//Debug
#define TEST_FUNCTIONS 1

#endif /* DEFINES_H_ */
