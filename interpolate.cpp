#include "interpolate.h"

Polynomial::Polynomial(const std::vector<double> &data) {
    _data = data;
    return;
}

std::function<double(double)> Polynomial::eval() const {
    return [*this](double x) {
        double sum = 0;
        for(auto p : enumerate(reverse(this->_data))) {
            sum += pow(x, p.first) * p.second;
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
    return reverse(map<std::pair<double, double>, double>(
        [](std::pair<double, double> p) { return p.first + p.second; },
        zip_with_padding<double, double>(
            reverse(_data), reverse(other._data), 0, 0)));
}


Polynomial Polynomial::operator *(const Polynomial &other) const {
    std::vector<double> result_vec;
    for(size_t i = 0; i < _data.size() + other._data.size() - 1; i++) {
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
    return map<double, double>(
        [scalar](double coef) { return coef * scalar; },
        _data);
}

Polynomial operator *(double scalar, const Polynomial &poly) {
    return poly * scalar;
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

Polynomial lagrange_term(const myPoint &source, const std::vector<myPoint> &rest) {
    double divisor = 1;
    Polynomial result_poly({1});
    for(auto p : rest) {
        divisor *= (source.x - p.x);
        result_poly *= create_neg_monomial(p.x);
    }

    return result_poly * (source.y / divisor);
}

Polynomial lagrange_interpolate(const std::vector<myPoint> p_vec) {
    Polynomial result_poly({0});
    for(size_t i = 0; i < p_vec.size(); i++) {
        auto plucked = pluck(p_vec, i);
        result_poly += lagrange_term(plucked.first, plucked.second);
    }
    return result_poly;
}

double sum_vec(std::vector<double> v) {
    return foldl<double, double>([](double x, double y) { return x + y; },
                                 v,
                                 0);
}

myPoint::myPoint(int x, int y) {
    this->x = x;
    this->y = y;
}

