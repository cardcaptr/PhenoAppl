#include "velocityverletintegrator.h"
#include <iostream>
#include <fstream>
#include "particlesbase.h"
#include "solutionExporterLagrangian.h"

#define _USE_MATH_DEFINES
#include <cmath>

VelocityVerletIntegrator::VelocityVerletIntegrator()
{

}


// Integrate nIter iterations using a constant time step dt using a verlet integrator
// Input:
//      -dt
//      -nIter
//      -outputFrequency
//      -Particle class
void VelocityVerletIntegrator::integrate(double dt, int nIter, int outputFrequency, ParticlesBase* particles)
{
    double t=0;

    particles->preprocess();
    particles->calculateForce(t);

    for (int it=0 ; it < nIter ; ++it)
    {
        for (int i = 0 ; i < particles->np_; ++i)
        {
            const double mass = particles->m_[i];
            particles->v_[i][0]+=  0.5*dt/mass * (particles->f_[i][0]);
            particles->v_[i][1]+=  0.5*dt/mass * (particles->f_[i][1]);
        }


        for (int i = 0 ; i < particles->np_; ++i)
        {
            particles->x_[i][0] += particles->v_[i][0] * dt;
            particles->x_[i][1] += particles->v_[i][1] * dt;
        }

        particles->calculateForce(t);

        for (int i = 0 ; i < particles->np_; ++i)
        {
            const double mass = particles->m_[i];
            particles->v_[i][0]+= 0.5*dt/mass * (particles->f_[i][0]);
            particles->v_[i][1]+= 0.5*dt/mass * (particles->f_[i][1]);
        }
        t+=dt;

        if (it%outputFrequency==0 && nIter > outputFrequency)
        {
            writeLagrangianParticles("particles",it, particles);
            particles->postprocess(t);
        }
    }
    if (nIter > outputFrequency) writeLagrangianParticles("particles",nIter, particles);
}
