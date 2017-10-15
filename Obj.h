#pragma once
#include <Eigen/Dense>
#include <string>
#include <vector>
#include <utility>

bool operator<=(const Eigen::VectorXd&, const Eigen::VectorXd&);
bool operator<(const Eigen::VectorXd&, const Eigen::VectorXd&);

class ParetoFronts
{
    Eigen::MatrixXd _extract_pareto(const Eigen::MatrixXd& objs) const;
    const Eigen::MatrixXd _pf;
    const Eigen::VectorXd _nadir;
    Eigen::MatrixXd sort_points(const Eigen::MatrixXd& pnts) const;
    double hypervolume(const Eigen::MatrixXd& pnts, const Eigen::VectorXd& ref) const;
    std::pair<Eigen::MatrixXd, Eigen::MatrixXd> partition(const Eigen::MatrixXd& pnts) const;
public:
    ParetoFronts(const Eigen::MatrixXd& objs);
    double hypervolume() const;
    Eigen::VectorXd nadir() const { return _nadir; }
};
