#include <catch2/catch.hpp>

#include <umrob/polynomial.h>

#include <random>

TEST_CASE("Polynomial") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10., 10.0);

    for (size_t i = 0; i < 100; i++) {
        umrob::Polynomial poly;
        poly.constraints().xi = dis(gen);
        poly.constraints().xf = dis(gen);
        poly.constraints().yi = dis(gen);
        poly.constraints().yf = dis(gen);

        poly.computeCoefficients();

        auto dx = poly.constraints().xf - poly.constraints().xi;
        if (dx > 0) {
            REQUIRE(poly.evaluate(poly.constraints().xi - 1) ==
                    poly.constraints().yi);
            REQUIRE(poly.evaluate(poly.constraints().xf + 1) ==
                    poly.constraints().yf);
        } else {
            REQUIRE(poly.evaluate(poly.constraints().xi + 1) ==
                    poly.constraints().yi);
            REQUIRE(poly.evaluate(poly.constraints().xf - 1) ==
                    poly.constraints().yf);
        }

        auto last_value = poly.evaluate(poly.constraints().xi);
        for (size_t i = 1; i <= 10; i++) {
            auto x = poly.constraints().xi +
                     (poly.constraints().xf - poly.constraints().xi) * i / 10.;
            auto current_value = poly.evaluate(x);
            if (poly.constraints().yf > poly.constraints().yi) {
                REQUIRE(current_value > last_value);
            } else {
                REQUIRE(current_value < last_value);
            }
            last_value = current_value;
        }
    }
}