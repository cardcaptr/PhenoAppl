/**********************************************************************************************************
*
*   particlesSpring
*
*
*   Author  : Bruno Blais
*   File    : particlesspring.h
*
*   Description : Dummy class used for the unit testing of the integrator
*
*
************************************************************************************************************/

#ifndef PARTICLESSPRING_H
#define PARTICLESSPRING_H

#include "particlesbase.h"

class ParticlesSpring : public ParticlesBase
{
public:
    ParticlesSpring(int n, double d, double rho, double k, double gamma=0);
    void calculateForce(double t);
    virtual void preprocess(){};
    virtual void postprocess(double t){};

private:
    double k_;
    double gamma_;
};

#endif // PARTICLESSPRING_H
