#ifndef VELOCITYVERLETINTEGRATOR_H
#define VELOCITYVERLETINTEGRATOR_H

#include "particlesbase.h"


class VelocityVerletIntegrator
{
public:
    VelocityVerletIntegrator();
//    void integrate (double dt, int nIter, ParticlesBase* particles);
    void integrate (double dt, int nIter, int outputFrequency, ParticlesBase* particles);
};

#endif // VELOCITYVERLETINTEGRATOR_H
