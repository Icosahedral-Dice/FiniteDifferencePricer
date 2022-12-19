//
//  finite_difference_pricer_discrete_dividend.hpp
//  FiniteDifferencePricer
//
//  Created by 王明森 on 12/18/22.
//

#ifndef finite_difference_pricer_discrete_dividend_hpp
#define finite_difference_pricer_discrete_dividend_hpp

#include "finite_difference_pricer.hpp"

// ERSATZ. Only handles one discrete dividend event.

class FiniteDifferencePricerDiscreteDividend : public FiniteDifferencePricer {
    // Option data
    double S0_;
    double K_;
    double T_;
    double sigma_;
    double r_;
    double q_;
    double t_div_;

    // Heat equation transformation coefficients
    double a_;
    double b_;

    // Finite difference parameters
    double tau_final_;
    double tau_div_;
    double x_l1_;
    double x_r1_;
    double x_compute1_;

    double x_l2_;
    double x_r2_;
    double x_compute2_;

    std::size_t N_, N_l_;

    // Boundary conditions
//    std::function<double (double)> boundary2_tau_0_;  // no need
    std::function<double (double)> boundary2_x_l_;
    std::function<double (double)> boundary2_x_r_;

    std::function<double (double)> boundary1_tau_0_;
    std::function<double (double)> boundary1_x_l_;
    std::function<double (double)> boundary1_x_r_;

    // 1. Computational domain
    // will change the value of x_r_, cannot be const
    std::tuple<std::size_t, double, double, double> DomainParams_1_(std::size_t M);
    // also return M2
    std::tuple<std::size_t, double, double, double, double> DomainParams_2_(std::size_t M);

    std::vector<double>  BuildMesh(std::size_t N, double dx, double x_l_) const;

    // 3. Finite difference scheme, get u_mesh & u_mesh_prev
    std::vector<std::vector<double>> FiniteDifference_expl(double alpha, const std::vector<double>& x_mesh, std::size_t M, double dtau, std::vector<double>* umesh_before_div = nullptr) const;

//    std::vector<std::vector<double>> FiniteDifference_impl(double alpha, const std::vector<double>& x_mesh, std::size_t M, double dtau) const;

    std::vector<std::vector<double>> FiniteDifference_imex(double alpha, const std::vector<double>& x_mesh, std::size_t M, double dtau, std::vector<double>* umesh_before_div = nullptr) const;

    // Advance time (modify u-mesh in place, row by row from tau = 0 boundary)
    // Forward Euler
    void advance_explicit(double tau, double alpha, const std::vector<double>& x_mesh, std::vector<double>& u_mesh, int state_) const;
    // Backward Euler
//    void advance_implicit(double tau, double alpha, const std::vector<double>& x_mesh, std::vector<double>& u_mesh, const boost::numeric::ublas::triangular_matrix<double, boost::numeric::ublas::lower>& L, const boost::numeric::ublas::triangular_matrix<double, boost::numeric::ublas::upper>& U) const;
    // Crank-Nicolson
    void advance_imex(double tau, double alpha, const std::vector<double>& x_mesh, std::vector<double>& u_mesh, const boost::numeric::ublas::triangular_matrix<double, boost::numeric::ublas::lower>& L, const boost::numeric::ublas::triangular_matrix<double, boost::numeric::ublas::upper>& U, const boost::numeric::ublas::symmetric_matrix<double>& b_multiplier, int state_) const;

    // 4. Pointwise convergence
    std::vector<double> Approximate(const std::vector<double>& x_mesh, const std::vector<double>& u_mesh, double dx) const;

    // 5. RMS error
    double RMS(const std::vector<double>& x_mesh, const std::vector<double>& u_mesh) const;

    // 6. Greeks
    std::vector<double> Greeks(const std::vector<double>& x_mesh, const std::vector<double>& u_mesh, std::vector<double>& u_mesh_prev, double dtau, double V_approx) const;
};


#endif /* finite_difference_pricer_discrete_dividend_hpp */
