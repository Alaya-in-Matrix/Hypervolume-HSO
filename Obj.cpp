#include "Obj.h"
#include <limits>
#include <iostream>
#include <cassert>
using namespace std;
using namespace Eigen;

bool operator<=(const VectorXd& v1, const VectorXd& v2) 
{
    assert(v1.size() == v2.size());
    return (v1.array() <= v2.array()).all(); 
}
bool operator<(const VectorXd& v1, const VectorXd& v2)
{
    assert(v1.size() == v2.size());
    return (v1.array() <= v2.array()).all() and v1 != v2;
}

ParetoFronts::ParetoFronts(const MatrixXd& pnts) 
    : _pf(_extract_pareto(pnts)), 
      _nadir(pnts.rowwise().maxCoeff())
{}
MatrixXd ParetoFronts::_extract_pareto(const MatrixXd& objs) const
{
    vector<VectorXd> cache;
    for (Index i = 0; i < objs.cols(); ++i)
    {
        bool dominated = false;
        for (Index j = 0; j < objs.cols(); ++j)
        {
            if (objs.col(j) < objs.col(i))
            {
                dominated = true;
                break;
            }
        }
        if (!dominated) cache.push_back(objs.col(i));
    }
    MatrixXd pf(objs.rows(), cache.size());
    for (size_t i = 0; i < cache.size(); ++i)
    {
        pf.col(i) = cache[i];
    }
    return pf;
}
MatrixXd ParetoFronts::sort_points(const MatrixXd& pnts) const
{
    MatrixXd sorted = pnts;
    vector<size_t> idxs(pnts.cols());
    for(size_t i = 0; i < idxs.size(); ++i)
        idxs[i] = i;
    std::sort(idxs.begin(), idxs.end(), [&](const size_t i1, const size_t i2)->bool{
            return pnts(0, i1) < pnts(0, i2);
    });

    for(Index i = 0; i < pnts.cols(); ++i)
        sorted.col(i) = pnts.col(idxs[i]);
    return sorted;
}
double ParetoFronts::hypervolume(const MatrixXd& pnts, const VectorXd& ref) const
{
    const size_t num_obj = pnts.rows();
    const size_t num_pnt = pnts.cols();
    assert(ref.size() == (Index)num_obj);
    if(num_obj == 1)
    {
        if(num_pnt != 1)
            assert(pnts.cwiseEqual(pnts(0)).all());
        return ref(0) - pnts(0, 0);
    }
    else
    {
        MatrixXd sorted     = sort_points(pnts);
        VectorXd prev_point = ref;
        double hv           = 0;
        for(long i = num_pnt - 1; i >= 0; --i)
        {
            const VectorXd curr_point = sorted.col(i);
            const double width = prev_point(0) - curr_point(0);
            const MatrixXd tmp_pnts = _extract_pareto(sorted.leftCols(i + 1).bottomRows(num_obj - 1));

            const double sub_hv = hypervolume(tmp_pnts, ref.tail(num_obj - 1));

            hv += width * sub_hv;
            prev_point = curr_point;
        }
        return hv;
    }
}

double ParetoFronts::hypervolume() const
{
    return hypervolume(_pf, _nadir);
}

pair<MatrixXd, MatrixXd> ParetoFronts::partition(const MatrixXd& pnts) const
{
    const size_t num_obj = pnts.rows();
    const size_t num_pnt = pnts.cols();
    if(num_obj == 1)
    {
        // if there is more than one points, they must be identical
        if(num_pnt != 1)
        {
            for(size_t i = 1; i < num_pnt; ++i)
            {
                if(pnts(i) != pnts(0))
                {
                    cerr << "error pnts:\n" << pnts << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    else
    {
    }
}
