#include <umrob/polynomial.h>

namespace umrob {

Polynomial::Constraints& Polynomial::constraints() {
    return constraints_;
}

const Polynomial::Constraints& Polynomial::constraints() const {
    return constraints_;
}

// clang-format off
/* Simplified coefficient for xi = 0 and dx = xf-xi
 * a = -(12*yi - 12*yf + 6*dx*dyf + 6*dx*dyi - d2yf*dx^2 + d2yi*dx^2)/(2*dx^5)
 * b = (30*yi - 30*yf + 14*dx*dyf + 16*dx*dyi - 2*d2yf*dx^2 + 3*d2yi*dx^2)/(2*dx^4) 
 * c = -(20*yi - 20*yf + 8*dx*dyf + 12*dx*dyi - d2yf*dx^2 + 3*d2yi*dx^2)/(2*dx^3) 
 * d = d2yi/2 
 * e = dyi 
 * f = yi
 */
void Polynomial::computeCoefficients() {
    // TODO implement
}
// clang-format on

//! y = ax^5 + bx^4 + cx^3 + dx^2 + ex + f
double Polynomial::evaluate([[maybe_unused]] double x) {
    // TODO implement
    return 0;
}

//! dy = 5ax^4 + 4bx^3 + 3cx^2 + 2dx + e
double Polynomial::evaluateFirstDerivative([[maybe_unused]] double x) {
    // TODO implement
    return 0;
}

//! d2y = 20ax^3 + 12bx^2 + 6cx + 2d
double Polynomial::evaluateSecondDerivative([[maybe_unused]] double x) {
    return 0;
}

} // namespace umrob