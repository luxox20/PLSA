#ifndef PLSA_H
#define PLSA_H

#include <Eigen/Dense>
#include <iostream>
#include <cstdlib>
#include <map>
#include <limits>
#include <cmath>

using namespace std;
using namespace Eigen;

class Plsa
{
  public:
          Plsa();
          void plsa_init(MatrixXd& data,int topics,int Max_Iterations, double tolerance);
          //void train();
          void test();
  private:
          int M;
          int Ni;
          int K;
          MatrixXd Pw_z; // P(w|z);
          MatrixXd Pd_z; // P(d|z);
          VectorXd P_z; // P(z);
          map<int,MatrixXd> Pz_wd; // P(z|w,d)
          // Private functions
          void get_size();
          void E_step();
          void M_step(MatrixXd &data);
          void Normalize();
          double loglikehood(MatrixXd &data);
          MatrixXd logeps(MatrixXd mat);

};
#endif
