#ifndef INTERPOLATE_H
#define INTERPOLATE_H
#include <vector>
#include <functional>
#include <utility>
#include <cmath>
#include <ostream>

class Polynomial {
    private:
        std::vector<double> _data;
    public:
        Polynomial(const std::vector<double> &data);
        std::function<double(double)> eval() const;
        std::ostream& write(std::ostream &os) const;
        Polynomial operator +(const Polynomial &other) const;
        Polynomial operator *(const Polynomial &other) const;
        Polynomial operator *(double scalar) const;
        friend Polynomial operator *(double scalar, const Polynomial &poly);

        // Assignment operators.
        Polynomial operator +=(const Polynomial &other);
        Polynomial operator *=(const Polynomial &other);
};

std::ostream &operator<<(std::ostream& os, const Polynomial &p);
Polynomial create_neg_monomial(double root);

// Utility functions for messing with vectors.

template<typename T>
std::vector<std::pair<size_t, T>> enumerate(const std::vector<T> &vec) {
    std::vector<std::pair<size_t, T>> result_vec;
    size_t index = 0;
    for(auto &v : vec) {
        result_vec.emplace_back(index, v);
        index++;
    }
    return result_vec;
}

template<typename T>
std::vector<T> reverse(const std::vector<T> &vec) {
    return std::vector<T>(vec.rbegin(), vec.rend());
}

template<typename T>
std::pair<T, std::vector<T>> pluck(const std::vector<T> &vec, size_t index) {
    std::vector<T> result_vec;
    for(auto p : enumerate(vec)) {
        if(p.first != index) {
            result_vec.push_back(p.second);
        }
    }
    return std::pair<T, std::vector<T>>(vec.at(index), result_vec);
}

typedef struct {
    int x;
    int y;
} Point;

Polynomial lagrange_term(const Point &source, const std::vector<Point> &rest);
Polynomial lagrange_interpolate(const std::vector<Point> p_vec);
#endif
