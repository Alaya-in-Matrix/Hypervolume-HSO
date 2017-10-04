#include "util.h"
#include "Obj.h"
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;
int main(int argNum, char** args)
{
    if(argNum < 2)
    {
        cerr << "Usage: hypervolume filepath" << endl;
    }
    string file_path = args[1];
    MatrixXd m = read_matrix(file_path).transpose();
    ParetoFronts pf(m);
    cout << "num obj: " << m.rows() << endl;
    cout << "num pnt: " << m.cols() << endl;
    cout << "nadir: "   << pf.nadir().transpose() << endl;
    cout << "hv: "      << pf.hypervolume() << endl;
    return EXIT_SUCCESS;
}
