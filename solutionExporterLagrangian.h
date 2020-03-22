/**********************************************************************************************************
*
*   LBM BURST CODE
*   
*   
*   Author  : Bruno Blais
*   File    : readwrite.h
*   Date    : November 9th 2012    
*   Began   : November 8th 2012
*
*   Description : This is the header for the reading and writing functions function
*
************************************************************************************************************/
#include <string>
#include "particlesdem.h"

#ifndef SOLUTIONEXPORTERLAGRANGIAN_H
#define SOLUTIONEXPORTERLAGRANGIAN_H // Prevents multiple definition of the same class
  void writeLagrangianScalar(std::string, int,int, double**, double*);
  void writeLagrangianVector(std::string, int,int, double**, double**);
  void writeLagrangianParticles(std::string, int, ParticlesBase *pbase);
#endif
