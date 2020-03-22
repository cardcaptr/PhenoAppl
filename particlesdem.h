/**********************************************************************************************************
*
*   particlesDEM
*
*
*   Author  : Bruno Blais
*   File    : particlesdem.h
*
*   Description : Class to carry out force calculation for a DEM model
*
*
************************************************************************************************************/

#ifndef PARTICLESDEM_H
#define PARTICLESDEM_H

#include "particlesbase.h"
#include <fstream>


class ParticlesDEM : public ParticlesBase
{
public:
    ParticlesDEM(int n, double d, double rho, double k, double gamma, double tLoading, double* g);
    static double height;
    virtual void calculateForce(double t);
    void calculateForceInterParticles();
    void calculateForceBottomWallLoading();
    void calculateForceBottomWallUnloading();
    void calculateForceOnLateralWalls();
    virtual void preprocess();
    virtual void postprocess(double t);
    void initializeParticles(int nx, double xmin,double ymin, double dx);

private:
    double k_;
    double gamma_;
    double tLoading_;
    double g_[2];
    double xminHole_;
    double xmaxHole_;
    std::ofstream particleCountFile_;
};

#endif // PARTICLES_H
