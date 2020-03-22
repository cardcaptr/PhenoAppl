/**********************************************************************************************************
*
*   particlesSpring
*
*
*   Author  : Bruno Blais
*   File    : particlesspring.cpp
*
*   Description : Dummy class used for the unit testing of the integrator
*
*
************************************************************************************************************/

#include "particlesspring.h"
#include <iostream>
#include <cmath>

ParticlesSpring::ParticlesSpring(int n, double d, double rho, double k, double gamma):
    ParticlesBase(n,d,rho),
    k_(k), gamma_(gamma)
{

}

void ParticlesSpring::calculateForce(double t)
{
    for (int i =0 ; i < np_ ; ++i)
    {
        f_[i][0]=1.;
        f_[i][1]= -k_ * (x_[i][1]) - gamma_* v_[i][1];
//        std::cout << " f " << f_[i][1] << std::endl;
    }
}
