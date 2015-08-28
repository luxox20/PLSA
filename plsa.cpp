#include "plsa.h"
/*
 #
 #
 #
 #
 #
 #
 #
 #
 #
 #
*/

Plsa::Plsa(){}

void Plsa::plsa_Train(Eigen::MatrixXd& data,int topics,int Max_Iterations, double tolerance){
    //Variables
    data.transposeInPlace();
    srand((unsigned int) time(0));
    M=data.rows();   // number of visual words
    Ni=data.cols();  // number of images
    K=topics;        // number of Topics
    map<int,double> table_likehood; // likelihood Values
    double offset=1e-7; // small offset to avoid numerical  problems in Pw_z

    //incializacion//
    P_z=Eigen::VectorXd::Ones(K)/K; // P(z);
    Pd_z=Eigen::MatrixXd::Random(Ni,K); // P(d|z)
    Pw_z=Eigen::MatrixXd::Random(M,K); //P(w|z)
    Pd_z=Pd_z.cwiseAbs();
    Pw_z=Pw_z.cwiseAbs();

    // normalize
    Normalize(Pd_z);
    Normalize(Pw_z);

    cout <<"P(d|z) "<< Pd_z.colwise().sum()<<endl;
    cout <<"P(w|z) " <<Pw_z.colwise().sum()<<endl;

    //EM algorithm
    for (int i=0;i<Max_Iterations;i++)
    {
        double dli=0;

        E_step();
        M_step(data);

        table_likehood[i]=loglikehood(data);
        Pw_z=(Pw_z.array()+offset).matrix();

        if (i>0)
        {
            dli=table_likehood[i]-table_likehood[i-1];
            if (dli< tolerance)
            {
              cout<<" finalizo en: "<<i<<endl;
              break;
            }
        }
    }
}


void Plsa::plsa_test(MatrixXd& data, int topics, int Max_Iterations, double tolerance, MatrixXd &Fixed_Pw_z)
{

}
//E-step Estimate P(z|w,d)
void Plsa::E_step()
{

   MatrixXd sum_Pz_wd=MatrixXd::Zero(M,Ni);
   for (int i=0;i<K;i++)
   {
     Pz_wd[i]=(Pw_z.col(i)*Pd_z.col(i).transpose())*P_z(i);
     sum_Pz_wd+=Pz_wd[i];
   }

   MatrixXd a=MatrixXd::Ones(M,Ni);

   for (int j=0;j<K;j++)
   {
     Pz_wd[j]=Pz_wd[j].cwiseProduct(a.cwiseQuotient(sum_Pz_wd));
   }
}
/*******M step, maximazize log-likelihood*/
void Plsa::M_step(MatrixXd &data)
{
    MatrixXd X;
    for (int i=0;i<K;i++)
    {
      Pw_z.col(i)=(Pz_wd[i].cwiseProduct(data)).rowwise().sum();//suma de filas[vector(1XN)]
      Pd_z.col(i)=(Pz_wd[i].cwiseProduct(data)).colwise().sum();//suma de columnas[vector(1XN)]
    }

    //normalize
    RowVectorXd Temp;
    RowVectorXd C;
    VectorXd E;
    VectorXd T;
    Temp=RowVectorXd::Ones(K);
    T=VectorXd::Ones(K); // vector of K with ones
    P_z=Pd_z.colwise().sum();
    cout<<P_z;

    C=Pd_z.colwise().sum(); //suma de columnas[vector(1XN)]
    Temp=Temp.cwiseQuotient(C);
    Pd_z=Pd_z*(Temp.asDiagonal());

    C=Pw_z.colwise().sum(); //
    Temp=Temp.cwiseQuotient(C);
    Pw_z=Pw_z*(Temp.asDiagonal());

    E=P_z.rowwise().sum();
    P_z=P_z.cwiseProduct(T.cwiseQuotient(E));

}

void Plsa::get_size()
{

}

void Plsa::Normalize(MatrixXd &Mat)
{
  RowVectorXd Temp;
  Temp=RowVectorXd::Ones(K);
  Temp=Temp.cwiseQuotient(Mat.colwise().sum());
  Mat=Mat*Temp.asDiagonal();
}

double Plsa::loglikehood(MatrixXd &data)
{
  MatrixXd Pw_d=MatrixXd::Zero(M,Ni);
  double likehood=0;

  for (int i=0;i<K;i++)
  {
    Pw_d+=((Pw_z.col(i)*Pd_z.col(i).transpose())*P_z(i));
  }

  likehood=logeps(Pw_d).cwiseProduct(data).sum();
  cout<<likehood<<endl;

  return likehood;

}

MatrixXd Plsa::logeps(MatrixXd mat){
	for(int i=0;i<mat.rows();i++)
		for(int j=0;j<mat.cols();j++)
			mat(i,j)=log(mat(i,j)+std::numeric_limits<double>::epsilon());
	return mat;
}

MatrixXd Plsa::GetPw_z()
{
  MatrixXd P=Pw_z;
  return Pw_z;
}

MatrixXd Plsa::GetPd_z()
{
  MatrixXd P=Pd_z;
  return P;
}

VectorXd Plsa::GetP_z()
{
  VectorXd P=P_z;
  return P;
}
