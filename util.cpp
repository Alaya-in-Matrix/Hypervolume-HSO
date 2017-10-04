#include <Eigen/Dense>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;
using namespace Eigen;
Eigen::RowVectorXd split_line(const string& line)
{
    // split one line by ' '
    RowVectorXd v;
    vector<double> vec;

    stringstream s(line);
    string tok;
    while (s >> tok)
    {
        vec.push_back(stod(tok));
    }
    v = Map<VectorXd>(vec.data(), vec.size());
    return v;
}
MatrixXd read_matrix(const string& path)
{
    ifstream mfile(path);
    assert(mfile.is_open() && !mfile.fail());

    string line;
    vector<RowVectorXd> tmp_container;
    while (!mfile.eof() && getline(mfile, line))
    {
        VectorXd v = split_line(line);
        tmp_container.push_back(v);
    }
    mfile.close();
    if (!tmp_container.empty())
    {
        const size_t dim = tmp_container[0].size();
        MatrixXd m(tmp_container.size(), dim);
        for (size_t i = 0; i < tmp_container.size(); ++i)
        {
            if ((size_t)tmp_container[i].size() != dim)
            {
                cerr << "Invalid vector read from file, dim not match" << endl;
                exit(EXIT_FAILURE);
            }
            m.row(i) = tmp_container[i];
        }
        return m;
    }
    else
    {
        cerr << "Empty matrix in file " << path << endl;
        exit(EXIT_FAILURE);
    }
}
