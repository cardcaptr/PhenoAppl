/*******************************************************************
*	movingParticles
*	Author : Bruno Blais
*
*	Student Name : 
*
*	Role : Discrete Element Method
*
********************************************************************/

// C++ Standard includes
#include <iostream> 
#include <cmath>

// Library includes
#include "tinyxml2.h"

// Local includes
#include "parser.h"
#include "particlesdem.h"
#include "velocityverletintegrator.h"
#include "solutionExporterLagrangian.h"
#include "tests.h"
#include "particlesbase.h"

// Creates a bounding box of the domain by writing a BoundingBox VTK
// Input:
//      -xmin
//      -xmax
//      -ymin
//      -ymax
void writeBoundingBox(double xmin, double xmax, double ymin, double ymax)
{
    double g[2] = {0., 0.};
    ParticlesDEM boundaries(4,1.,1.,1.,1.,1.,g);
    boundaries.x_[0][0]=xmin;
    boundaries.x_[1][0]=xmin;
    boundaries.x_[2][0]=xmax;
    boundaries.x_[3][0]=xmax;
    boundaries.x_[0][1]=ymin;
    boundaries.x_[1][1]=ymax;
    boundaries.x_[2][1]=ymin;
    boundaries.x_[3][1]=ymax;
    writeLagrangianParticles("BoundingBox",0,&boundaries);
}

int main()
{
//   testSpringParticles();
//   testEulerIntegration();
//   testVerletIntegration();

    Parser parser;
    parser.parse();


    // Get the number of particles in theta and r
    int np = parser.getNp();
    double dt = parser.getDt();
	double tLoading = parser.getLoadingTime();
    double endTime=parser.getEndtime();
    int outputFrequency = parser.getOutputFrequency();
    int nIter = int(endTime/dt);
    std::cout << "-------------------" << std::endl;
    std::cout << " Simulating with : " << std::endl;
    std::cout << "np : " << np << std::endl;
    std::cout << "dt : " << dt << std::endl;
	std::cout << "loadingTime: " << tLoading << std::endl;
    std::cout << "endTime : " << endTime << std::endl;
    std::cout << "nIter : " << nIter <<  std::endl;
    std::cout << "-------------------" << std::endl;

    // Physical properties are hard coded for this problem, but again they could be introduced in the Parser.
    double dp=0.04;
    double rho=1000;
    double g[2]={0,-9.81};
    double k=1e5;
    double gamma=10;
    double ymax;

    // Create the particles with DEM contact model
    ParticlesDEM p(np,dp,rho,k,gamma,tLoading,g);

    // Initialize the particles position
    // Arguments are nx, xmin, ymin, dx
    p.initializeParticles(15,0.06,0.1,0.06);
    ymax = ParticlesDEM::height;
    
    // Write a particle at the corner of a bounding box. This allows you to outline the domain
     writeBoundingBox(0.,1.,0.,ymax);

    // Create a Velocity Verlet Integrator
    VelocityVerletIntegrator integrator;

    // Use it to do nIter iterations
    integrator.integrate(dt,nIter,outputFrequency,&p);

    return 0;
}

