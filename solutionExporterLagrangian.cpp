/**********************************************************************************************************
*
*   solutionExporterEulerian
*
*
*   Author  : Bruno Blais
*   File    : solutionExporterEulerian.cpp
*
*   Description : Used to house functions for exportation of solution DATA to paraview LEGACY format
*
*
************************************************************************************************************/

//*******************
//  GENERAL INCLUDES
//*******************

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>


//*******************
// HEADER INCLUDES
//*******************
#include "solutionExporterLagrangian.h"
#include "particlesdem.h"



//*******************
// STD USAGE
//*******************

using namespace std;
void writeLagrangianScalar(string label, int iter, int nParticles, double** pos, double* scalar)
{
    ostringstream oss;

    // Write iteration number to flux
    oss << iter;

    // Establish the file name
    string filename = "output/"+label+"_"+oss.str()+".vtk";

    // Declare the output flux and open the file
    ofstream file(filename.c_str(), ios::out | ios::trunc);
    cout << "Saving file: " << filename << endl;

    if(file)  // File has been opened correctly
    {
        file << "# vtk DataFile Version 2.0" << endl;
        file << "Output" << endl;
        file << "ASCII" << endl;
        file << "DATASET POLYDATA" << endl;
        file << "POINTS" << " " << nParticles << " " << "float" << endl;
        for (int i=0 ; i< nParticles ; ++i)
        {
            file << pos[i][0] << " " << pos[i][1] << " " << pos[i][2] <<endl ;

        }

        file << "POINT_DATA" << " " << nParticles <<  endl;
        file << "SCALARS" << " " << "ScalarValue" << " " << "double" <<  endl;
        file << "LOOKUP_TABLE default" << endl;
        for (int i=0 ; i< nParticles ; ++i)
        {
            file <<  scalar[i] <<endl ;
        }
        file.close();  // close the file
    }
}

void writeLagrangianVector(string label, int iter, int nParticles, double** pos, double** vect)
{
    ostringstream oss;

    // Write iteration number to flux
    oss << iter;

    // Establish the file name
    string filename = "output/"+label+"_"+oss.str()+".vtk";

    // Declare the output flux and open the file
    ofstream file(filename.c_str(), ios::out | ios::trunc);
    cout << "Saving file: " << filename << endl;

    if(file)  // File has been opened correctly
    {
        file << "# vtk DataFile Version 2.0" << endl;
        file << "Output" << endl;
        file << "ASCII" << endl;
        file << "DATASET POLYDATA" << endl;
        file << "POINTS" << " " << nParticles << " " << "float" << endl;
        for (int i=0 ; i< nParticles ; ++i)
        {
            file << pos[i][0] << " " << pos[i][1] << " " << pos[i][2] <<endl ;

        }

        file << "POINT_DATA" << " " << nParticles <<  endl;
        file << "VECTORS" << " " << "Velocity" << " " << "double" <<   endl;
        file << "LOOKUP_TABLE default" << endl;
        for (int i=0 ; i< nParticles ; ++i)
        {
             file << vect[i][0] << " " << vect[i][1] << " " << vect[i][2] <<endl ;
        }
        file.close();  // close the file
    }
}

void writeLagrangianParticles(string label, int iter, ParticlesBase *p)
{
    ostringstream oss;

    // Write iteration number to flux
    oss << iter;

    // Establish the file name
    string filename = "output/"+label+"_"+oss.str()+".vtk";

    // Declare the output flux and open the file
    ofstream file(filename.c_str(), ios::out | ios::trunc);
    cout << "Saving file: " << filename << endl;

    if(file)  // File has been opened correctly
    {
        file << "# vtk DataFile Version 2.0" << endl;
        file << "Output" << endl;
        file << "ASCII" << endl;
        file << "DATASET POLYDATA" << endl;
        file << "POINTS" << " " << p->np_ << " " << "float" << endl;
        for (int i=0 ; i< p->np_ ; ++i)
        {
            file << p->x_[i][0] << " " << p->x_[i][1] << " " << 0. <<endl ;

        }

        file << "POINT_DATA" << " " << p->np_ <<  endl;
        file << "SCALARS" << " " << "Diameter" << " " << "double" <<  endl;
        file << "LOOKUP_TABLE default" << endl;
        for (int i=0 ; i< p->np_ ; ++i)
        {
            file <<  p->dp_[i] <<endl ;
        }

        file << "VECTORS" << " " << "Velocity" << " " << "double" <<   endl;
        for (int i=0 ; i< p->np_ ; ++i)
        {
             file << p->v_[i][0] << " " << p->v_[i][1] << " " << 0 <<endl ;
        }

        file << "VECTORS" << " " << "Force" << " " << "double" <<   endl;
        for (int i=0 ; i< p->np_ ; ++i)
        {
             file << p->f_[i][0] << " " << p->f_[i][1] << " " << 0 <<endl ;
        }

        file << "VECTORS" << " " << "Normal-Force" << " " << "double" <<   endl;
        for (int i=0 ; i< p->np_ ; ++i)
        {
             file << p->ft_[i][0] << " " << p->ft_[i][1] << " " << 0 <<endl ;
        }


        file << "VECTORS" << " " << "Tangential-Force" << " " << "double" <<   endl;
        for (int i=0 ; i< p->np_ ; ++i)
        {
             file << p->fn_[i][0] << " " << p->fn_[i][1] << " " << 0 <<endl ;
        }


        file.close();  // close the file
    }
}
