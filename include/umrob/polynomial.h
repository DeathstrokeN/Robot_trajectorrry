//! \file polynomial.h
//! \author Benjamin Navarro
//! \brief Declaration of the Polynomial class
//! \date 09-2020

#pragma once

namespace umrob {

//! \brief A general purpose fith-order polynomial
//!
class Polynomial {
public:
    //! \brief Polynomial constraints, i.e value, first and second derivative at
    //! the endpoints
    //!
    struct Constraints {
        double xi{0};   //!< Initial x value
        double xf{1};   //!< Final x value
        double yi{0};   //!< Initial y value
        double yf{1};   //!< Final y value
        double dyi{0};  //!< Initial y first derivative
        double dyf{0};  //!< Final y first derivative
        double d2yi{0}; //!< Initial y second derivative
        double d2yf{0}; //!< Final y second derivative
    };

    //! \brief Read/write access to the polynomial constraints
    //!
    //! \return Constraints& The constraints
    Constraints& constraints();

    //! \brief Read only access to the polynomial constraints
    //!
    //! \return Constraints& The constraints
    const Constraints& constraints() const;

    //! \brief Compute the polynomial coefficients based on its constraints
    //!
    //! \param parameters The polynomial parameters
    void computeCoefficients();

    //! \brief Evaluate the polynomial for the given input
    //!
    //! If x is outside the [xi,xf] range, the output will be either yi or yf
    //! depending on which limit is crossed
    //!
    //! \param x Input value
    //! \return double Output value
    double evaluate(double x);

    //! \brief Evaluate the polynomial first derivative for the given input
    //!
    //! If x is outside the [xi,xf] range, the output will be either dyi or dyf
    //! depending on which limit is crossed
    //!
    //! \param x Input value
    //! \return double First output derivative
    double evaluateFirstDerivative(double x);

    //! \brief Evaluate the polynomial second derivative for the given input
    //!
    //! If x is outside the [xi,xf] range, the output will be either d2yi or
    //! d2yf depending on which limit is crossed
    //!
    //! \param x Input value
    //! \return double Second output derivative
    double evaluateSecondDerivative(double x);

private:
    //! \brief Polynomial coefficients
    //!
    //! y = ax^5 + bx^4 + cx^3 + dx^2 + ex + f
    //!
    struct Coefficients {
        double a{0};
        double b{0};
        double c{0};
        double d{0};
        double e{0};
        double f{0};
    };

    Constraints constraints_;
    Coefficients coefficients_;
};

} // namespace umrob