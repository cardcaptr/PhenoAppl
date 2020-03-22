/**********************************************************************************************************
*
*   particlesDEM
*
*
*   Author  : Bruno Blais
*   File    : particlesdem.cpp
*
*   Description : Class to carry out force calculation for a DEM model
*
*
************************************************************************************************************/

#include "particlesdem.h"
#include "particlesbase.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>

double ParticlesDEM::height;

// Class constructor
// Nothing special, but note that the beggining and end of the hole is "hard coded" as a class member
ParticlesDEM::ParticlesDEM(int n, double d, double rho, double k, double gamma, double tLoading, double *g):
ParticlesBase(n,d,rho),k_(k), gamma_(gamma), tLoading_(tLoading)
{
    g_[0]=g[0];
    g_[1]=g[1];
    xminHole_=0.3;
    xmaxHole_=0.7;
}

// Initialize the position of the particles
// Velocities are already assumed to be zero from the base constructor of the class
// Right now the particles are arranged in a regular grid with a random factor to ensure
// The they do not pile perfectly
// Input:
//      -nx number of particles per x direction
//      -xmin minimal position of particles
//      -ymin minimal position of particles
//      -dx step between the particles
void ParticlesDEM::initializeParticles(int nx, double xmin,double ymin, double dx)
{
    srand (123456789);
    for (int i=0; i<np_ ; i++)
    {
        x_[i][0]=xmin + i%nx * dx + dx * 0.025*(rand()%10);
        x_[i][1]=ymin + i/nx * dx + dx * 0.025*(rand()%10);
    }

    double ymax = x_[np_-1][1] + 5 * dx;
    height = ymax;
}

    
// Main routine to calculate force
// input :
//      -t time
// output : No explicit output, but force is calculated is stored
// in the force vector f_
void ParticlesDEM::calculateForce(double t)
{
  
    // Reset force to gravity
    for (int i=0; i<np_ ; i++)
    {
        f_[i][0]=g_[0]*m_[i];
        f_[i][1]=g_[1]*m_[i];
    }

    calculateForceInterParticles();
    calculateForceOnLateralWalls();

    if (t<=tLoading_)
    {
        calculateForceBottomWallLoading();
    }
    else
    {
        calculateForceBottomWallUnloading();
    }

}

// Calculate the force between the particles
// Input : none
// Output : Inter particle force is added to the force vector f_
void ParticlesDEM::calculateForceInterParticles()
{
	// make a local copy for efficiency
    double**  f = f_;   //f_[i][*] is the force
	double** x = x_;    //x_[i][*] is the position
	double** v = v_;    //v_[i][*] is the velocity
	double*  r = r_;    //r_[i][*] is the radius
	const double k = k_;
	const double gamma = gamma_;
	//--------------------------
    double dist;    // eucledian norm of xi - xj
    double dn[2];   // normal overlap vector
    double vn[2];   // normal relative velocity
    double xn[2];   // particle i(x,y)
    double fn[2];   // normal force vector
    double nX, nY;  // normal vector
    double vijX, vijY;   // vi - vj vector
    double ijX, ijY;    // xi - xj vector

    for (int i=0; i<np_ ; i++)
    {
        for (int j=i+1 ; j < np_ ; j++)
        {
            // Calculate xi - xj
            ijX = x[i][0] - x[j][0];
            ijY = x[i][1] - x[j][1];

            // Find distance between particles
            dist = sqrt(ijX * ijX + ijY * ijY);
      
            if (dist <= (r_[i] + r_[j])) // overlap detected
            {
                // calculate overlap vector
                nX= ijX / dist;
                nY= ijY / dist;

                dn[0] = (dist - (r[i] + r[j])) * nX;
                dn[1] = (dist - (r[i] + r[j])) * nY;

                // calculate vij vector
                vijX = v[i][0] - v[j][0];
                vijY = v[i][1] - v[j][1];

                vn[0] = (vijX * nX + vijY * nY) * nX / dist;
                vn[1] = (vijX * nX + vijY * nY) * nY / dist;

                // Apply sum of forces to particle i
                fn[0] = -k * dn[0] - gamma * vn[0];
                fn[1] = -k * dn[1] - gamma * vn[1];

                f[i][0] += fn[0];
                f[i][1] += fn[1];
                f[j][0] += -fn[0];
                f[j][1] += -fn[1];

            }
        }
    }
}

// Calculate the force due to the lateral walls
// Input : none
// Output : Wall force is added to the force vector f_
void ParticlesDEM::calculateForceOnLateralWalls()
{
    // Top wall a y=height of bounding box
    
    double ymax = height;

     for(int i =0 ; i < np_ ; i++)
    {
       
        double dn = x_[i][1] + 0.5 * dp_[i];
        if (dn >= ymax)
        {
            dn = dn - ymax; // this insures vector is in +y direction
            double vn = v_[i][1];
            f_[i][1] += - k_ * dn - gamma_ * vn;
        }
    }

    // Left wall at x=0
    for(int i =0 ; i < np_ ; i++)
    {
        double dn = x_[i][0] - 0.5 * dp_[i];
        if (dn <= 0)
        {
            double vn = v_[i][0];
            f_[i][0] += -k_ * dn - gamma_ * vn;
        }
    }

    // Right wall at x=1
    for(int i =0 ; i < np_ ; i++)
    {
        double dn = x_[i][0] + 0.5 * dp_[i];
        if (dn >= 1)
        {
            dn = dn - 1; // this insures vector is in +x direction
            double vn = v_[i][0];
            f_[i][0] += - k_ * dn - gamma_ * vn;
        }
    }
}

// Calculate the force due to the bottom wall during loading
// Input : none
// Output : Wall force is added to the force vector f_
void ParticlesDEM::calculateForceBottomWallLoading()
{

    // Bottom wall a y=0
    for(int i =0 ; i < np_ ; i++)
    {
        double dn = x_[i][1] - 0.5 * dp_[i];
        if (dn<=0)
        {
            double vn = v_[i][1];
            f_[i][1] += -k_ * dn - gamma_ * vn;
        }
    }

}

// Calculate the force due to the bottom wall during unloading
// Input : none
// Output : Wall force is added to the force vector f_
void ParticlesDEM::calculateForceBottomWallUnloading()
{
    // make a local copy for efficiency
    double** f = f_;   //f_[i][*] is the force
    double** x = x_;    //x_[i][*] is the position
    double** v = v_;    //v_[i][*] is the velocity
    double* r = r_;    //r_[i][*] is the radius
    const double k = k_;
    const double gamma = gamma_;
    //--------------------------
    double dist;    // eucledian norm of xi - xj
    double dn[2];   // normal overlap vector
    double vn[2];   // normal relative velocity
    double xn[2];   // particle i(x,y)
    double fn[2];   // normal force vector
    double nX, nY;  // normal vector
    double vijX, vijY;   // vi - vj vector
    double ijX, ijY;    // xi - xj vector
    double xwall[2];  // treat the boundary like a fixed particle 

    // Bottom wall a y=0
    for (int i = 0; i < np_; i++)
    {
        if (x[i][1] > 0.0 && (x[i][0] <= xminHole_ || x[i][0] >= xmaxHole_))
        {
            dn[1] = x_[i][1] - 0.5 * dp_[i];
            if (dn[1] <= 0)
            {
                vn[1] = v_[i][1];
                f_[i][1] += -k_ * dn[1] - gamma_ * vn[1];
            }
        }

        else if (x[i][0] > xminHole_)
        {
            xwall[0] = xminHole_;
            xwall[1] = 0.0;
            // Calculate xi - xj
            ijX = x[i][0] - xwall[0];
            ijY = x[i][1] - xwall[1];

            //Calculating distance between particle and edge of right opening
            dist = sqrt(ijX * ijX + ijY * ijY);
            
     
            if (dist <= r[i]) // overlap detected
             {
                // calculate overlap vector
                nX = ijX / dist;
                nY = ijY / dist;

                dn[0] = (dist - r[i]) * nX;
                dn[1] = (dist - r[i]) * nY;

                // calculate vij vector
                vijX = v[i][0] - 0;
                vijY = v[i][1] - 0;

                vn[0] = (vijX * nX + vijY * nY) * nX / dist;
                vn[1] = (vijX * nX + vijY * nY) * nY / dist;

                // Apply sum of forces to particle i
                fn[0] = -k * dn[0] - gamma * vn[0];
                fn[1] = -k * dn[1] - gamma * vn[1];

                f[i][0] += fn[0];
                f[i][1] += fn[1];
            }
        }

        else if (x[i][0] < xmaxHole_)
        {
            xwall[0] = xminHole_;
            xwall[1] = 0.0;
            // Calculate xi - xj
            ijX = x[i][0] - xwall[0];
            ijY = x[i][1] - xwall[1];

            //Calculate distance between particle and left opening
            dist = sqrt(ijX * ijX + ijY * ijY);

            if (dist <= r[i])// overlap detected
            {
                // calculate overlap vector
                nX = ijX / dist;
                nY = ijY / dist;

                dn[0] = (dist - r[i]) * nX;
                dn[1] = (dist - r[i]) * nY;

                // calculate vij vector
                vijX = v[i][0] - 0;
                vijY = v[i][1] - 0;

                vn[0] = (vijX * nX + vijY * nY) * nX / dist;
                vn[1] = (vijX * nX + vijY * nY) * nY / dist;

                // Apply sum of forces to particle i
                fn[0] = -k * dn[0] - gamma * vn[0];
                fn[1] = -k * dn[1] - gamma * vn[1];

                f[i][0] += fn[0];
                f[i][1] += fn[1];
            }
        }

    }
}
// Preprocessing function called by the integrator
// Input : none
// Output : none
void ParticlesDEM::preprocess()
{
    // Open a file and write the header
    // This file will be used to write the number of particles as a function of time
    std::string name = "output/particleCount.dat";
    particleCountFile_.open(name.c_str());
    particleCountFile_ << "t\tN" << std::endl;

}


// Postprocessing function called by the integrator
// Input : none
// Output : none
void ParticlesDEM::postprocess(double t)
{
    //Count how many particles are above the treshold
    double yTres=0.;
    int nParticles =0;
    for (int i = 0 ; i<np_ ; ++i)
    {
        if (x_[i][1]>yTres) nParticles++;
    }

        particleCountFile_ << t <<" " << nParticles << std::endl;
}
