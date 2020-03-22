#include <cmath>
#include "particlesbase.h"


// Default constructor of the virtual class
// Mostly used to initialize the members and allocate their memory
ParticlesBase::ParticlesBase(int n, double d, double rho):
np_(n)
{
    const double pi=3.1416;

    // attribuate the size to the arrays
    x_ = new double*[n];
    v_ = new double*[n];
    f_ = new double*[n];
    ft_ = new double*[n];
    fn_ = new double*[n];
    dp_ = new double[n];
    r_ = new double[n];
    rho_ = new double[n];
    m_ = new double[n];

    for (int i=0 ; i<n ; i++)
    {
        x_[i] = new  double[3];
        v_[i] = new  double[3];
        f_[i] = new  double[3];
        ft_[i] = new  double[3];
        fn_[i] = new  double[3];

        dp_[i]=d;
        r_[i] = 0.5*d;
        rho_[i]=rho;
    }

    for (int i=0 ; i<n ; ++i)
    {
        for (int j =0 ; j<3 ; ++j)
        {
            x_[i][j] =0.;
            v_[i][j] =0.;
            f_[i][j] =0.;
            ft_[i][j] =0.;
            fn_[i][j] =0.;
            m_[i]=pi * std::pow(dp_[i],3) / 6. * rho_[i];
        }
    }

}

ParticlesBase::~ParticlesBase()
{

}
