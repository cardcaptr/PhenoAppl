#ifndef EULERINTEGRATOR_H
#define EULERINTEGRATOR_H

#include "particlesbase.h"


class EulerIntegrator
{
public:
    EulerIntegrator();
    void integrate(double dt, int nIter, ParticlesBase* particles);

private:
    double dt_;
    double finalTime_;


};

#endif // EULERINTEGRATOR_H
