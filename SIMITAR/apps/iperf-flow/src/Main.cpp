// Deps
#include <iostream>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <algorithm>
#include <tclap/CmdLine.h>
// Simitar
#include <NetworkTrace.h>
#include <DummyFlow.h>
#include <SimitarWorkspace.h>
// Local
//#include "IperfFlowt.h"

void cli_error_messege(std::string arg, std::string arg_name,
		std::string expected_values_msg);

bool cli_check_val(std::string val, std::vector<std::string> expectedVals);

int main(int argc, char** argv)
{
	try
	{
		///
		/// CLI parser
		///

		// program description
		char progDescription[] = "SIMITAR dummy-flow component.";
		// version information
		char version[CHAR_BUFFER];
		SimitarWorkspace workspace = SimitarWorkspace();
		std::string str_version = workspace.version_tag() + ":"
				+ workspace.version_name();
		strcpy(version, str_version.c_str());

		// comamnd line parsing
		TCLAP::CmdLine cmd(progDescription, ' ', version);
		TCLAP::ValueArg<std::string> mode_arg("m", "mode",
				"Operation mode, as a client or a server", true, "", "string");
		TCLAP::ValueArg<std::string> in_arg("x", "xml", "xml", true,
				"Compact Trace Descriptor XML. They are saved at data/xml/ directory.",
				"string");
		TCLAP::ValueArg<std::string> dst_list_arg("d", "dst-list-ip",
				"Text file in CSV format containing a list of desired destinations of IP and MAC adresses, used as servers, in the client mode. These destinations are addressed to the flows in a ring-oriented way.",
				false, "", "string");
		TCLAP::ValueArg<std::string> dst_server_arg("p", "dst-ip",
				"Instead of a text file, defines a single server destination IP address in the command line.",
				false, "", "string");
		TCLAP::ValueArg<std::string> eth_arg("e", "ether",
				"Ethernet interface to send the traffic, as provided by the command `ifconfig`.",
				false, "", "string");

		cmd.add(mode_arg);
		cmd.add(in_arg);
		cmd.add(dst_list_arg);
		cmd.add(dst_server_arg);
		cmd.add(eth_arg);

		cmd.parse(argc, argv);

		std::string mode = mode_arg.getValue();
		std::string input_xml = in_arg.getValue();
		std::string dst_list_file = dst_list_arg.getValue();
		std::string dst_ip_str = dst_server_arg.getValue();
		std::string eth_interface = eth_arg.getValue();
		bool flag_dst_list_file = (dst_list_file == "") ? false : true;
		bool flag_dst_ip_str = (dst_ip_str == "") ? false : true;

		if (!cli_check_val(mode,
		{ "client", "server" }))
		{
			cli_error_messege(mode, "mode", "`client` or `server`");
			return (-1);
		}

		///
		/// Actual execution
		///

		//TODO
		NetworkTrace netTrace = NetworkTrace(input_xml.c_str(), "iperf");
		if (mode == "client")
		{
			netTrace.exec();
		}
		else
		{
			netTrace.server();
		}

	} catch (TCLAP::ArgException &e)  // catch any exceptions
	{
		std::cerr << "dummy-flow Error: " << e.error() << " for arg "
				<< e.argId() << std::endl;
	}

	return (0);

}

/**
 * Print an error message if the input argument is an invalid balue
 * @param arg input CLI argument
 * @param arg_name argument name
 * @param expected_values message with expected values
 */
void cli_error_messege(std::string arg, std::string arg_name,
		std::string expected_values_msg)
{
	std::cerr << "trace-analyzer Error: invalid argument " << arg << " for "
			<< arg_name << ". Expected " << expected_values_msg
			<< ". Use --help for help." << std::endl;

}

/**
 * Check if the CLI input argument is a valid value
 * @param val input CLI argument.
 * @param expectedVals vector with valid CLI arguments.
 * @return
 */
bool cli_check_val(std::string val, std::vector<std::string> expectedVals)
{
	uint m = expectedVals.size();

	for (uint i = 0; i < m; i++)
		if (val == expectedVals[i])
			return (true);

	return (false);
}
