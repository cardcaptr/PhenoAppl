#include <cmath>
#include <iostream>
#include <fstream>
#include "eulerintegrator.h"
#include "particlesbase.h"
#include <string>



EulerIntegrator::EulerIntegrator()
{

}

void EulerIntegrator::integrate(double dt, int nIter, ParticlesBase* particles)
{
    double t=0;
    std::ofstream outputSolution;
    std::string name = "numSolution-"+std::to_string(nIter)+".dat";
    outputSolution.open(name.c_str());
    outputSolution << "t x v" << std::endl;
    outputSolution << t << " "<< particles->x_[0][1] << " " << particles->v_[0][1]  << std::endl;


    for (int it=0 ; it < nIter ; ++it)
    {

        particles->calculateForce(t);
        for (int i = 0 ; i < particles->np_; ++i)
        {
            double mass = 3.1416 *  4./24. * pow(particles->dp_[i],3.) * particles->rho_[i];
            for (int dim = 0 ; dim <2 ; dim++)
            {
                particles->x_[i][dim] += particles->v_[i][dim] * dt;
                particles->v_[i][dim] += particles->f_[i][dim] / mass * dt;
//                if (dim==1) std::cout << "x : " << particles->x_[i][dim] << " v : " << particles->v_[i][dim] << std::endl;
            }
        }

        t+=dt;
        outputSolution << t << " "<< particles->x_[0][1] << " " << particles->v_[0][1]  << std::endl;
    }
}
