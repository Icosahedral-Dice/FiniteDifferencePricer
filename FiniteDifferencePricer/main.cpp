//
//  main.cpp
//  FiniteDifferencePricer
//
//  Created by 王明森 on 12/11/22.
//

#include <iostream>
#include <iomanip>

#include "EuropeanOption.hpp"
#include "finite_difference_pricer.hpp"
#include "finite_difference_pricer_discrete_dividend.hpp"

void PrintVector(const std::vector<double>& vec) {
    for (auto elem : vec) {
        std::cout << elem << "\t";
    }
    std::cout << std::endl;
}

void Euro_explicit();
void American_explicit();
//void American_boundary();

void Euro_implicit(double alpha = .45) {
    EuropeanOption option(0., 37., 40, .75, .28, .04, .02);
    FiniteDifferencePricer::alpha_temp_ = alpha;
    FiniteDifferencePricer pricer(37., 40, .75, .28, .04, .02);
    
    std::cout << std::setprecision(8);
    std::cout << "Backward Euler, alpha = " << alpha << std::endl;
    std::cout << option.Put() << std::endl;
    
    for (std::size_t i = 4; i < 5; i <<= 2) {
        PrintVector(pricer.Price(i, Implicit, European));
    }
}

void Euro_imex(double alpha = .45) {
    EuropeanOption option(0., 37., 40, .75, .28, .04, .02);
    FiniteDifferencePricer::alpha_temp_ = alpha;
    FiniteDifferencePricer pricer(37., 40, .75, .28, .04, .02);
    
    std::cout << std::setprecision(8);
    std::cout << "Crank-Nicolson, alpha = " << alpha << std::endl;
//    std::cout << option.Put() << std::endl;
    
    for (std::size_t i = 4; i < 5; i <<= 2) {
        PrintVector(pricer.Price(i, ImEx, European));
    }
}

void American_imex(double alpha = .45) {
    EuropeanOption option(0., 37., 40, .75, .28, .04, .02);
    FiniteDifferencePricer::alpha_temp_ = alpha;
    FiniteDifferencePricer pricer(37., 40, .75, .28, .04, .02);
    
    std::cout << std::setprecision(10);
    std::cout << "Crank-Nicolson, alpha = " << alpha << std::endl;
//    std::cout << option.Put() << std::endl;
    
    for (std::size_t i = 4; i < 5; i <<= 2) {
        PrintVector(pricer.Price(i, ImEx, American));
    }
}


void American_imex2(double alpha = .45) {
    EuropeanOption option(0., 42., 40., 1., .32, .04, .02);
    FiniteDifferencePricer::alpha_temp_ = alpha;
    FiniteDifferencePricer pricer(42., 40., 1., .32, .04, .02);
    
    std::cout << std::setprecision(10);
    std::cout << "Crank-Nicolson, alpha = " << alpha << std::endl;
//    std::cout << option.Put() << std::endl;
    
    for (std::size_t i = 4; i < 5; i <<= 2) {
        PrintVector(pricer.Price(i, ImEx, American));
    }
}

void AmericanDiscDiv(double alpha = .4) {
    FiniteDifferencePricerDiscreteDividend::alpha_temp_ = 4;
    
    EuropeanOption option(0., 52., 50., 1., .2, .03, 0.);
    FiniteDifferencePricerDiscreteDividend pricer(option, 5. / 12., .01);
    
    PrintVector(pricer.PriceCall(4, ImEx, American));
}


int main(int argc, const char * argv[]) {
    
//    Euro_explicit();
//    American_explicit();
//    American_boundary();
//    Euro_implicit(.45);
//    Euro_imex(.45);
//    Euro_implicit(5);
//    Euro_imex(5);
    
//    American_imex(.45);
//    American_imex(5.);
    std::cout << std::fixed << std::setprecision(6);
    
    
    AmericanDiscDiv(.4);
    
    
    return 0;
}

// HW7
void Euro_explicit() {
    EuropeanOption option(0., 37., 40, .75, .28, .03, .015);
    FiniteDifferencePricer pricer(37., 40, .75, .28, .03, .015);
    
    std::cout << std::setprecision(8);
    std::cout << option.Put() << std::endl;
    for (std::size_t i = 4; i < 257; i <<= 2) {
        PrintVector(pricer.Price(i, Explicit, European));
    }
}

void American_explicit() {
    EuropeanOption option(0., 42., 40, .75, .32, .02, .04);
    FiniteDifferencePricer pricer(option);
    
    std::cout << std::setprecision(8);
    
    for (std::size_t i = 16; i < 17; i <<= 2) {
        PrintVector(pricer.Price(i, Explicit, American));
    }
}
//
//void American_boundary() {
//    FiniteDifferencePricer pricer(42., 40, .75, .32, .04, .02);
//
//    std::cout << std::setprecision(4);
//
//    std::vector<double> t;
//    std::vector<double> Sopt;
//    std::tie(t, Sopt) = pricer.AmericanPut_EarlyExDomain(16);
//    PrintVector(t);
//    PrintVector(Sopt);
//}
