#include "tinyxml2.h"
#include "parser.h"

// Constructor
Parser::Parser()
{

}

// Destructor
Parser::~Parser()
{
}

int Parser::parse()
{
  // Initialize document
  tinyxml2::XMLDocument doc;
  
  std::cout << " Parsing " << std::endl;
  // Load the file
  doc.LoadFile( "resources/parameter.xml" );	
  
  tinyxml2::XMLElement* root = doc.FirstChildElement("MAIN" );
  if (root == NULL)  
  {
    std::cout << "Root element of XML file MAIN is not present \n";
    std::cout << "XML Reader will crash \n";
    return tinyxml2::XML_ERROR_FILE_READ_ERROR;
  }
  // Pointer to particles sub-category of the XML file
  tinyxml2::XMLElement* particles = root->FirstChildElement("particles");
  if (particles == NULL)
  {
    std::cout << "A particles information category is necessary \n" << std::endl;
    return tinyxml2::XML_ERROR_FILE_READ_ERROR;
  }

  // Get the number of particles
  np_ = atoi(particles->FirstChildElement("np")->GetText());
  std::cout << "Number of particles parsed : " << np_ << std::endl;

  // Pointer to time sub-category of the XML file
  tinyxml2::XMLElement* timeInfo = root->FirstChildElement("time");
  if (timeInfo == NULL)
  {
    std::cout << "A time information category is necessary \n" << std::endl;
    return tinyxml2::XML_ERROR_FILE_READ_ERROR;
  }

  dt_ = atof(timeInfo->FirstChildElement("dt")->GetText());
  std::cout << "Time step : " << dt_ << std::endl;

  endtime_ = atof(timeInfo->FirstChildElement("endTime")->GetText());
  std::cout << "End time : " << endtime_ << std::endl;
  
  loadingTime_ = atof(timeInfo->FirstChildElement("loadingTime")->GetText());
  std::cout << "Loading time : " << endtime_ << std::endl;

  outputFrequency_ = atoi(timeInfo->FirstChildElement("outputFrequency")->GetText());
  std::cout << "Output Frequency : " << outputFrequency_ << std::endl;

  return doc.ErrorID();
}

