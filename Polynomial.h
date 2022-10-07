# pragma once

#include <iostream>
#include <vector>

class HunPolynomial {
public:
    HunPolynomial();
    HunPolynomial(std::vector<int> coefficients);
    ~HunPolynomial();

    std::vector<int> Get_Polynomial() const;
    void Set(std::vector<int> coefficients);

    std::vector<int> operator+(HunPolynomial& polynomial);
    std::vector<int> operator-(HunPolynomial& polynomial);
    std::vector<int> operator*(HunPolynomial& polynomial);
    friend std::ostream& operator<<(std::ostream& os, const HunPolynomial& polynomial);
    float operator()(float variable);

private:
    std::vector<int> polynomial_coefficients;
};