/*
 * cmdline_parser.cpp
 *
 *  Created on: 22 Feb 2012
 *      Author: simon
 */

#include "cmdline_parser.h"

//-------------------------------------------------------------------------//
// Constructor, initialise the variables_map object with default
// constructor, options_descriptor with the name "Options"
//-------------------------------------------------------------------------//
cmdline_parser::cmdline_parser(void) : vm(), od("Options")
{
	// Shorter alias for the boost::program_options namespace
	namespace po = boost::program_options;

	// Add two cmdline options
	// --help or -?
	// --file or -f, with a default value of "string.txt"
	od.add_options()
		("help,?", "produce help message")
		("file,f", po::value<std::string>()->default_value("string.txt"),
			"string file name");
};

//-------------------------------------------------------------------------//
// Process the cmdline
//-------------------------------------------------------------------------//
bool cmdline_parser::process_cmdline(int argc, char * argv[])
{
	// Shorter alias for the boost::program_options namespace
	namespace po = boost::program_options;

	// Clear the variable map
	vm.clear();

	// Parse the cmdline arguments defined by argc and argv,
	// looking for the options defined in the od variable,
	// and store them in the vm variable.
	po::store(po::parse_command_line(argc, argv, od), vm);
	po::notify(vm);

	// Assume processing always succeeds
	return true;
}

//-----------------------------------------------------------------------//
// Return the database filename
//-------------------------------------------------------------------------//
std::string cmdline_parser::get_filename(void) const
{
	// Return whatever value is stored in file as a string
	return vm["file"].as<std::string>();
}

//-----------------------------------------------------------------------//
// Should we print cmdline help?
//-------------------------------------------------------------------------//
bool cmdline_parser::should_print_help(void) const
{
	// Are there instances of the help option stored in the variable map
	return vm.count("help") > 0;
}

//-------------------------------------------------------------------------//
// Print out the options_descriptor to the supplied output stream
//-------------------------------------------------------------------------//
void cmdline_parser::print_help(std::ostream & out) const
{
	out << od;
}
