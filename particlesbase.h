#ifndef PARTICLESBASE_H
#define PARTICLESBASE_H


class ParticlesBase
{
public:
    ParticlesBase(int n, double d, double rho);
    ~ParticlesBase();

    virtual void calculateForce(double t)=0;
    virtual void postprocess(double t)=0;
    virtual void preprocess()=0;


    double **x_;
    double **v_;
//    double **x0_;
//    double **v0_;
    double **f_;
    double **ft_;
    double **fn_;
    double *dp_;
    double *r_;
    double *m_;
    double *rho_;
    int np_;
};

#endif // PARTICLESBASE_H
