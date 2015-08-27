#include "plsa.h"
/*
% Notation:
% X ... (M x Ni) term-document matrix (observed data)
%       X(i,j) stores number of occurrences of word i in document j
%
% M  ... number of words
% Ni ... number of images
% K  ... number of topics
%
% Fixed_Pw_z ... fixed Pw_z density (for recognition only)
%                leave empty in learning
%                N.B. Must be of size m by K
%
% Li   ... likelihood for each iteration
% Pz   ... P(z)
% Pd_z ... P(d|z)
% Pw_z ... P(w|z) corresponds to beta parameter in LDA
%
% Pz_wd ... P(z|w,d) posterior on z
*/

Plsa::Plsa(){
}

void Plsa::plsa_init(Eigen::MatrixXd& data,int topics,int Max_Iterations, int tolerance)
{     data.transposeInPlace();
      //srand((unsigned int) time(0));
      M=data.rows();  // number of visual words
      Ni=data.cols();  // number of images
      cout << M<<"X"<<Ni<<" "<<endl;
      K=topics;
      //incializacion//
      P_z=Eigen::VectorXd::Ones(K)/K; // P(z);
      Pd_z=Eigen::MatrixXd::Random(Ni,K); // P(d|z) Matrix de tamaño NixK
      Pw_z=Eigen::MatrixXd::Random(M,K); //P(w|z)
      Pd_z=Pd_z.cwiseAbs(); // valor absoluto
      Pw_z=Pw_z.cwiseAbs(); // valor absoluto
      //cout<<Pw_z.rows()<<"x"<<Pw_z.cols()<<endl;
      //cout<<Pd_z.rows()<<"x"<<Pw_z.cols()<<endl;

      //cout<< Pd_z.colwise().sum() << endl;
      //cout<< P_z<<" "<<endl;



      // normalize
      RowVectorXd Temp;
      Temp=RowVectorXd::Ones(K); // vector with K ones
      //cout<< Temp<< endl;
      Temp=Temp.cwiseQuotient(Pd_z.colwise().sum()); //Temp/C
      Pd_z=Pd_z*Temp.asDiagonal();

      Temp=RowVectorXd::Ones(K);
      Temp=Temp.cwiseQuotient(Pw_z.colwise().sum());
      Pw_z=Pw_z*Temp.asDiagonal();

      cout <<"P(d|z) "<< Pd_z.colwise().sum()<<endl;
      cout <<"P(w|z) " <<Pw_z.colwise().sum()<<endl;

       //percfecto
      //cout<<Pw_z.rows()<<"x"<<Pw_z.cols()<<endl;
      //cout<<Pd_z.rows()<<"x"<<Pw_z.cols()<<endl;
      /*for (int i=0; i<M;i++)
      {
        for (int j=0;j<K;j++)
        {
          //cout<<Pw_z(i,j)<<" ";

        }
        //cout<<endl;
      }*/

      E_step();
      //cout<<data.cols()<<endl;
      //cout<<Pz_wd[1].cols();
      M_step(data);
      //temp=Pd_z.colwise().sum();






}


void Plsa::test()
{

}

void Plsa::E_step()
{

   MatrixXd sum_Pz_wd=MatrixXd::Zero(M,Ni);
   for (int i=0;i<K;i++)
   {
     //cout<<"col"<<Pw_z.col(i)<<endl;
     //cout<<"c"<<Pd_z.col(i).transpose()<<endl;
     //cout<<"P_z"<<P_z(i)<<endl;

     Pz_wd[i]=(Pw_z.col(i)*Pd_z.col(i).transpose())*P_z(i);
     sum_Pz_wd+=Pz_wd[i];

     //Pz_wd+=(Pw_z.col(i)*Pd_z.col(i).transpose())*Pz(i);
   }
   MatrixXd a=MatrixXd::Ones(M,Ni);

   for (int j=0;j<K;j++)
   {
     Pz_wd[j]=Pz_wd[j].cwiseProduct(a.cwiseQuotient(sum_Pz_wd));
   }
    cout<<Pz_wd[0].cols()<<endl;
    //cout<<datos.cols()<<endl;

    //cout<<Pz_wd[0].cwiseProduct(datos);
   //cout<<sum_Pz_wd.rows()<<"X"<<sum_Pz_wd.cols()<<endl;
   //cout << Pz_wd[0].sum()<<endl;
}

void Plsa::M_step(MatrixXd &data)
{
    MatrixXd X;
    for (int i=0;i<K;i++)
    {
      //Pz_wd[i].cols();
      //cout<<"-columnas Pw_z"<<Pw_z.col(i)<<endl;
      MatrixXd X=data.cwiseProduct(Pz_wd[i]);
      cout<<i+1<<"::"<<X.rows()<<"X"<<X.cols()<<endl;

      //cout<<X.cols()<<endl;
      //cout<<Pw_z.cols();
      //Pw_z.col(i)=X.rowwise().sum();
      //Pd_z.col(i)=X.
      //Pw_z.col(i)=X.rowwise().sum();
      Pw_z.col(i)=(Pz_wd[i].cwiseProduct(data)).rowwise().sum();//suma de filas[vector(1XN)]
      Pd_z.col(i)=(Pz_wd[i].cwiseProduct(data)).colwise().sum();//suma de columnas[vector(1XN)]


    }
    //normalize
    RowVectorXd Temp;
    RowVectorXd C;
    Temp=RowVectorXd::Ones(K); // vector of K with ones
    P_z=Pd_z.colwise().sum();
    cout<<P_z;

    C=Pd_z.colwise().sum(); //suma de columnas[vector(1XN)]
    Pd_z=Pd_z*(Temp.cwiseQuotient(C).asDiagonal());

    C=Pw_z.colwise().sum(); //
    Pw_z=Pw_z*(Temp.cwiseQuotient(C).asDiagonal());

    //C=Pw_z.colwise;
    //for (int j=0;j<K;j++)
    //{

    //}
}
void Plsa::get_size()
{

}

void Plsa::Normalize()
{

}
