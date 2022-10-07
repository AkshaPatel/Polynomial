#include "HunPolynomial.h"
#include <vector>
#include <string>
#include <math.h>

HunPolynomial::HunPolynomial() {

}

HunPolynomial::HunPolynomial(std::vector<int> coefficients) {
    polynomial_coefficients = coefficients;
}

std::vector<int> HunPolynomial::Get_Polynomial() const {
    return polynomial_coefficients;
}

void HunPolynomial::Set(std::vector<int> coefficients) {
    polynomial_coefficients = coefficients;
}

std::vector<int> HunPolynomial::operator+(HunPolynomial& polynomial) {
    std::vector<int> sum, vec1, vec2;
    vec1 = Get_Polynomial();
    vec2 = polynomial.Get_Polynomial();
    int added_value;

    if (vec2.size() == 0)
        return vec1;
    if (vec1.size() == 0)
        return vec2;

    if (vec1.size() > vec2.size()) {
        int size_diff = vec1.size() - vec2.size();
        for (int i=0; i < size_diff; i++) {
            vec2.insert(vec2.begin(), 0);
        }
    }

    if (vec2.size() > vec1.size()) {
        int size_diff = vec2.size() - vec1.size();
        for (int i=0; i < size_diff; i++) {
            vec1.insert(vec1.begin(), 0);
        }
    }

    for (int i = 0; i < vec1.size(); i++) {
        added_value = vec1[vec1.size() - (1+i)] + vec2[vec2.size() - (1+i)];
        sum.insert(sum.begin(), added_value);
    }
    return sum;
}

std::vector<int> HunPolynomial::operator-(HunPolynomial& polynomial) {
    std::vector<int> difference, vec1, vec2;
    vec1 = Get_Polynomial();
    vec2 = polynomial.Get_Polynomial();
    int subtracted_value;

    if (vec2.size() == 0)
        return vec1;
    if (vec1.size() == 0) {
        for (int i=0; i < vec2.size(); i++) {
            vec2[i] = vec2[i] * -1;
        }
        return vec2;
    }

    if (vec1.size() > vec2.size()) {
        int size_diff = vec1.size() - vec2.size();
        for (int i=0; i < size_diff; i++) {
            vec2.insert(vec2.begin(), 0);
        }
    }

    if (vec2.size() > vec1.size()) {
        int size_diff = vec2.size() - vec1.size();
        for (int i=0; i < size_diff; i++) {
            vec1.insert(vec1.begin(), 0);
        }
    }

    for (int i = 0; i < vec1.size(); i++) {
        subtracted_value = vec1[vec1.size() - (1+i)] - vec2[vec2.size() - (1+i)];
        difference.insert(difference.begin(), subtracted_value);
    }
    return difference;
}

std::vector<int> HunPolynomial::operator*(HunPolynomial& polynomial) {
    std::vector<int> vec1, vec2;
    vec1 = Get_Polynomial();
    vec2 = polynomial.Get_Polynomial();

    if (vec2.size() == 0) {
        std::vector<int> Empty;
        return Empty;
    }
    if (vec1.size() == 0) {
        std::vector<int> Empty;
        return Empty;
    }

    std::vector<int> final_product(((vec1.size()-1) * (vec2.size()-1)) + 1, 0);

    if (vec1.size() > vec2.size()) {
        int size_diff = vec1.size() - vec2.size();
        for (int i=0; i < size_diff; i++) {
            vec2.insert(vec2.begin(), 0);
        }
    }

    if (vec2.size() > vec1.size()) {
        int size_diff = vec2.size() - vec1.size();
        for (int i=0; i < size_diff; i++) {
            vec1.insert(vec1.begin(), 0);
        }
    }

    int product;
    
    for (int i = vec1.size() - 1; i >= 0; i--) {
        for (int j = vec2.size() - 1; j >= 0; j--) {
            product = vec1[vec1.size() - (1+i)] * vec2[vec2.size() - (1+j)];
            final_product[final_product.size() - (1 + i+j)] += product;
        }
    }


    return final_product; 
}

std::ostream& operator<<(std::ostream& os, const HunPolynomial& polynomial) {
    int exponent = polynomial.Get_Polynomial().size() - 1;
    std::string output;

    for (int i = 0; i < polynomial.Get_Polynomial().size(); i++) {
        if (polynomial.Get_Polynomial()[i] == 0) {
            exponent--;
        }
        else if (exponent > 1) {
            if (polynomial.Get_Polynomial()[i] < 0) {
                if (polynomial.Get_Polynomial()[i] == -1) {
                    output +=  "- x^" + std::to_string(exponent) + " ";
                    exponent--;
                }
                else {
                    output +=  "- " + std::to_string((polynomial.Get_Polynomial()[i] / -1)) + "*x^" + std::to_string(exponent) + " ";
                    exponent--;
                }
            }
            else {
                if (output.length() == 0) {
                    if (polynomial.Get_Polynomial()[i] == 1) {
                        output += "x^" + std::to_string(exponent) + " ";
                        exponent--;
                    }
                    else {
                        output += std::to_string(polynomial.Get_Polynomial()[i]) + "*x^" + std::to_string(exponent) + " ";
                        exponent--;
                    }
                }
                else if (polynomial.Get_Polynomial()[i] == 1) {
                    output += "+ x^" + std::to_string(exponent) + " ";
                    exponent--;
                }
                else {
                    output += "+ " + std::to_string(polynomial.Get_Polynomial()[i]) + "*x^" + std::to_string(exponent) + " ";
                    exponent--;
                }

            }
        }
        else if (exponent == 1) {
            if (polynomial.Get_Polynomial()[i] < 0) {
                if (polynomial.Get_Polynomial()[i] == -1) {
                    output += "- x ";
                    exponent--;
                }
                else {
                    output += "- " + std::to_string(polynomial.Get_Polynomial()[i] / -1) + "*x ";
                    exponent--;
                } 
            }
            else {
                if (output.length() == 0) {
                    if (polynomial.Get_Polynomial()[i] == 1) {
                        output += "x ";
                        exponent--;
                    }
                    else {
                        output += std::to_string(polynomial.Get_Polynomial()[i]) + "*x ";
                        exponent--;
                    }
                }
                else if (polynomial.Get_Polynomial()[i] == 1) {
                    output += "+ x ";
                    exponent--;
                }
                else {
                    output += "+ " + std::to_string(polynomial.Get_Polynomial()[i]) + "*x ";
                    exponent--;
                }
            }
        }
        else {
            if (polynomial.Get_Polynomial()[i] < 0) {
                output += "- " + std::to_string(polynomial.Get_Polynomial()[i] / -1) + " ";
            }
            else {
                if (output.length() == 0) {
                    output += std::to_string(polynomial.Get_Polynomial()[i]) + " ";
                }
                else {
                    output += "+ " + std::to_string(polynomial.Get_Polynomial()[i]) + " ";
                }
            }
        }
    }
    os << output;
    return os;
}

float HunPolynomial::operator()(float variable) {
    float exponent = (float)Get_Polynomial().size() -1;
    float result = 0;

    for (int i = 0; i < Get_Polynomial().size(); i++) {
        result += Get_Polynomial()[i] * pow(variable, exponent);
        exponent--;
    }
    return result;
}

HunPolynomial::~HunPolynomial() {

}