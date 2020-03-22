
#define _USE_MATH_DEFINES
#include <cmath>

#include "assert.h"
#include <iostream>

#include "tests.h"
#include "particlesspring.h"
#include "eulerintegrator.h"
#include "velocityverletintegrator.h"

template <typename T>
bool alq (T a, T b)
{
    return (std::abs(a-b)<1.e-12);
}

Tests::Tests()
{

}

void testSpringParticles()
{
    ParticlesSpring p(10,1,1,10);
    for (int i =0 ; i<p.np_; ++i)
    {
        p.x_[i][0]=0.;
        p.x_[i][1]=double(i);
    }

    p.calculateForce(0.);
    for (int i = 0 ; i < p.np_ ; ++i)
    {
        assert(alq<double>(p.f_[i][0],1.));
        assert(alq<double>(p.f_[i][1],-10.*double(i)));
    }

    std::cout << " ---> Spring particles force calculation is correct" << std::endl;

}

void testVerletIntegration()
{
    double tf=10.;
    double k=5;
    double gamma= 0.1;
    double mass = 4. * 3.1416 / 24;
    double omega=std::sqrt(k/mass);
    double omegap= std::sqrt(omega*omega - std::pow(gamma / (2*mass),2.));
    double as = std::exp(-gamma/(2.*mass)*tf) * std::cos(omegap * tf);
//    double as = std::exp(-gamma*tf) * std::cos(tf * std::sqrt(1.-xi*xi));


    ParticlesSpring p(1,1.,1,k,gamma);
    p.x_[0][0]=0.;
    p.x_[0][1]=1.;
    p.v_[0][0]=0.;
    p.v_[0][1]=-gamma/(2.*mass);

    VelocityVerletIntegrator e;

    e.integrate(0.001, 10000, 100000, &p);
    double x1[2];
    double v1[2];
    x1[0]=p.x_[0][0];
    x1[1]=p.x_[0][1];
    v1[0]=p.v_[0][0];
    v1[1]=p.v_[0][1];

    double error1=std::abs(as- x1[1]);
    assert(error1<0.02);
    std::cout << "1->Analytical position: " << as << " Numerical solution: " << x1[1] << " Error: "<< error1 << std::endl;


    p.x_[0][0]=0.;
    p.x_[0][1]=1.;
    p.v_[0][0]=0.;
    p.v_[0][1]=-gamma/(2.*mass);
    e.integrate(0.0005, 20000, 100000, &p);
    double x2[2];
    double v2[2];
    x2[0]=p.x_[0][0];
    x2[1]=p.x_[0][1];
    v2[0]=p.v_[0][0];
    v2[1]=p.v_[0][1];

    double error2=std::abs(as- x2[1]);
    assert(error2<0.01);
    std::cout << "2->Analytical solution: " << as << " Numerical solution: " << x2[1] << " Error: "<< error2 << std::endl;
    std::cout << " Error ratio : " << error1/ error2 << std::endl;


    std::cout << " ---> Verlet integrator is correct" << std::endl;
}

void testEulerIntegration()
{
    double tf=10.;
    double k=5;
    double gamma= 0.1;
    double mass = 4. * 3.1416 / 24;
    double omega=std::sqrt(k/mass);
    double omegap= std::sqrt(omega*omega - std::pow(gamma / (2*mass),2.));
    double as = std::exp(-gamma/(2.*mass)*tf) * std::cos(omegap * tf);


    ParticlesSpring p(1,1,1,k, gamma);
    p.x_[0][0]=0.;
    p.x_[0][1]=1.;
    p.v_[0][0]=0.;
    p.v_[0][1]=0.;

    EulerIntegrator e;

    e.integrate(0.01, 1000, &p);
    double x1[2];
    double v1[2];
    x1[0]=p.x_[0][0];
    x1[1]=p.x_[0][1];
    v1[0]=p.v_[0][0];
    v1[1]=p.v_[0][1];

    double error1=std::abs(as- x1[1]);
//    std::cout << "1->Analytical position: " << std::cos(omega*tf) << " Numerical solution: " << x1[1] << " Error: "<< error1 << std::endl;


    p.x_[0][0]=0.;
    p.x_[0][1]=1.;
    p.v_[0][0]=0.;
    p.v_[0][1]=0.;
    e.integrate(0.005, 2000, &p);
    double x2[2];
    double v2[2];
    x2[0]=p.x_[0][0];
    x2[1]=p.x_[0][1];
    v2[0]=p.v_[0][0];
    v2[1]=p.v_[0][1];

    double error2=std::abs(as- x2[1]);
//    std::cout << "2->Analytical solution: " << std::cos(omega*tf) << " Numerical solution: " << x2[1] << " Error: "<< error2 << std::endl;

//    std::cout << " Error ratio : " << error1/ error2 << std::endl;
    std::cout << " ---> Euler integrator is correct" << std::endl;

}

