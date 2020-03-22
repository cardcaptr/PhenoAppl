/******************************************************************************
*	Class Parser
*	Author : Bruno Blais
*
*	Role : This class takes care of parsing the particles and time elements
*
******************************************************************************/


#include "tinyxml2.h"
#include <iostream> 
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <regex>
#include <sstream>

#ifndef PARSER
#define PARSER

class  Parser
{
 public:
    Parser();                       // Public constructor
    ~Parser(); 	                    // Public destructor
    int parse();		    // Parse the xml document
    int getNp() {return np_;};
    double getDt() {return dt_;};
    double getYmax() { return ymax_; };
    double getEndtime() {return endtime_;};
    int getOutputFrequency() {return outputFrequency_;};
    double getLoadingTime() {return loadingTime_;};

 private:
        int np_;          // number particles
        double ymax_;   // height of box
        double dt_;       // timestep
        double endtime_;  // endtime of simulation
		double loadingTime_;  // endtime of simulation
        int outputFrequency_;
};
 
// Templated classes to detect if a number has what it takes to be an int or a double
// Serves as a sanity check for the xml parsing 
template<typename T>
bool isInt(T x)
{
    std::string s;
    std::regex e ("^-?\\d+");
    std::stringstream ss; 
    ss << x;
    ss >>s;
    if (std::regex_match (s,e)) return true;
    else return false;
}

template<typename T>
bool isDouble(T x)
{
    std::string s;
    std::regex e ("^-?\\d*\\.?\\d+");
    std::stringstream ss; 
    ss << x;
    ss >>s;
    if (std::regex_match (s,e)) return true;
    else return false;
}

#endif // PARSER DEFINITION
