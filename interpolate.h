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

// C++ is a functional language, right?

template<typename T1, typename T2>
std::vector<T2> map(std::function<T2(T1)> f, const std::vector<T1> &vec) {
    std::vector<T2> result_vec;
    for(auto &v : vec) {
        result_vec.push_back(f(v));
    }
    return result_vec;
}

template<typename T1, typename T2>
T2 foldl(std::function<T2(T2, T1)> f, const std::vector<T1> &vec, T2 acc) {
    for(auto &v : vec) {
        acc = f(acc, v);
    }
    return acc;
}

double sum_vec(std::vector<double> v);

template<typename T1, typename T2>
std::vector<std::pair<T1, T2>> zip_with_padding(const std::vector<T1> &v1,
                                                const std::vector<T2> &v2,
                                                T1 def1,
                                                T2 def2) {
    std::vector<std::pair<T1, T2>> result_vec;
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    while(it1 != v1.end() || it2 != v2.end()) {
        result_vec.emplace_back(
            (it1 != v1.end() ? *it1 : def1),
            (it2 != v2.end() ? *it2 : def2));
        if(it1 != v1.end()) {
            ++it1;
        }
        if(it2 != v2.end()) {
            ++it2;
        }
    }

    return result_vec;
}

// Lagrange interpolation stuff

class myPoint {
    public:
        int x;
        int y;
        myPoint(int x, int y);
};

Polynomial lagrange_term(const myPoint &source, const std::vector<myPoint> &rest);
Polynomial lagrange_interpolate(const std::vector<myPoint> p_vec);


#endif

