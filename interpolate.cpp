#include "interpolate.h"

Polynomial::Polynomial(const std::vector<double> &data) {
    _data = data;
    return;
}

std::function<double(double)> Polynomial::eval() const {
    return [this](double x) {
        double sum = 0;
        for(auto p : enumerate(reverse(this->_data))) {
            sum += p.second * std::pow(x, p.first);
        }
        return sum;
    };
}

std::ostream& Polynomial::write(std::ostream &os) const {
    for(auto p : reverse(enumerate(reverse(_data)))) {
        os << p.second;
        if(p.first > 0) {
            os << "x";
            if(p.first > 1) {
                os << "^" << p.first;
            }
            
            os << " + ";
        }
    }

    return os;
}

Polynomial Polynomial::operator +(const Polynomial &other) const {
    std::vector<double> result_vec;
    auto it1 = _data.rbegin();
    auto it2 = other._data.rbegin();

    while(it1 != _data.rend() || it2 != other._data.rend()) {
        result_vec.push_back(
            (it1 != _data.rend() ? *it1 : 0) +
            (it2 != other._data.rend() ? *it2 : 0));
        if(it1 != _data.rend())
            ++it1;
        if(it2 != other._data.rend())
            ++it2;
    }
    return reverse(result_vec);
}


Polynomial Polynomial::operator *(const Polynomial &other) const {
    std::vector<double> result_vec;
    for(int i = 0; i < _data.size() + other._data.size() - 1; i++) {
        result_vec.push_back(0);
    }

    for(auto p1 : enumerate(_data)) {
        for(auto p2 : enumerate(other._data)) {
            result_vec[p1.first + p2.first] += p1.second * p2.second;
        }
    }
    return result_vec;
}

Polynomial Polynomial::operator *(double scalar) const {
    std::vector<double> result_vec;
    for(auto coef : _data) {
        result_vec.push_back(coef * scalar);
    }
    return result_vec;
}

Polynomial operator *(double scalar, const Polynomial &poly) {
    std::vector<double> result_vec;
    for(auto coef : poly._data) {
        result_vec.push_back(coef * scalar);
    }
    return result_vec;
}

Polynomial Polynomial::operator +=(const Polynomial &other) {
    *this = *this + other;
    return *this;
}

Polynomial Polynomial::operator *=(const Polynomial &other) {
    *this = *this * other;
    return *this;
}

Polynomial create_neg_monomial(double root) {
    std::vector<double> result_vec;
    result_vec.push_back(1);
    result_vec.push_back(-root);
    return result_vec;
}


std::ostream &operator<<(std::ostream &os, const Polynomial &p) {
    return p.write(os);
}

Polynomial lagrange_term(const Point &source, const std::vector<Point> &rest) {
    double divisor = 1;
    Polynomial result_poly({1});
    for(auto p : rest) {
        divisor *= (source.x - p.x);
        result_poly *= create_neg_monomial(p.x);
    }

    return result_poly * (source.y / divisor);
}

Polynomial lagrange_interpolate(const std::vector<Point> p_vec) {
    Polynomial result_poly({0});
    for(size_t i = 0; i < p_vec.size(); i++) {
        auto plucked = pluck(p_vec, i);
        result_poly += lagrange_term(plucked.first, plucked.second);
    }
    return result_poly;
}

