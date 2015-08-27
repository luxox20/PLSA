
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <Eigen/Dense>
#include "plsa.h"


using namespace std;
//using namespace Eigen;
//functions
bool OpenFiles(ifstream& data_train,ifstream& data_test);
void ReadFiles(Eigen::MatrixXd &data,ifstream &datos_file);


int main(int argc, char *argv[])
{
    string path_file1;
    string path_file2;
    ifstream histogram_train("histogram_train.txt");
    ifstream histogram_test("histogram_test.txt");
    Eigen::MatrixXd data_train;
    Eigen::MatrixXd data_test;
    Plsa p;
    int topics=2,Max_Iterations=100,tolerance=1;

    /*if (argc==2)
    {
      int topics;
    }*/

    /*for (int i=0;i<5;i++)
    {
      //for (int j=0;j<5;j++)
      //{
        //cout<<P_z(i)<<" ";
      //}
      cout<< endl;
    }*/

    if (!OpenFiles(histogram_train,histogram_test))
    {
      return -1;
    }
    else
    {
      //int X=10,Y=100;
      //(X,Y);
      // read histogram from a textfile
      ReadFiles(data_train,histogram_train);
      cout<<data_train.rows()<<endl;
      //ReadFiles(data_test,histogram_test);
      p.plsa_init(data_train,topics,Max_Iterations,tolerance);
      //cout<< data_train(1,1)<<endl ;
      //Eigen::MatrixXd pxy;
    }





  //MatrixXd pxgz(X,Z);
  //MatrixXd pygz(Y,Z);
  //VectorXd pz(Y);
  //PLSA p;




return 0;
}

/*void leerArchivo (){


}*/

bool OpenFiles(ifstream &data_train,ifstream &data_test)
{
    if(!data_train.is_open())
    {
        cout<< "error to open file histogram_train.txt"<<endl;
        return false;
    }
    if(!data_test.is_open())
    {
        cout<< "error to open file histogram_test"<<endl;
        return false;
    }
    return true;
}

void ReadFiles(Eigen::MatrixXd &data,ifstream &datos_file)
{
    /***************/
    string line;
    uint i,j;
    //vector<int> entries;
    /*************/
    getline(datos_file,line);
    int rows=stoi(line);
    getline(datos_file,line);
    int cols=stoi(line);
    //cout<< rows<<"X" <<cols<<endl;
    data.resize(rows,cols);
    //cout<<data.rows()<<endl;
    for(i=0; getline(datos_file, line) ; i++)
    {
        line.size();
        //cout<< line<<endl;
        istringstream s(line);
        string field;
        //entries stoi
        for(j=0; getline(s, field,' ') ; j++){
            data(i,j)=stoi(field);
        }
    }
}
