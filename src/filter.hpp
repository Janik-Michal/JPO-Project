/**
 * @file filter.hpp
 * @brief Base class and utility functions for signal processing filters.
 *
 * This file defines the `filter` class, which provides fundamental 
 * operations like convolution, sum of squared absolute values, and 
 * finding the next power of 2. These utilities are used by both FIR 
 * and IIR filters.
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>
#ifndef FILTER_HPP
#define FILTER_HPP

using std::vector;

namespace mj
{
    /**
     * @brief Class filter witch base functions for signal filtration
     * 
     * \tparam T Type of data used in the filter operations.
     */
    template <typename T>
    class filter
    {
    public:
        /**
         * \brief Computes the convolution of two vectors.
         * 
         * The convolution operation calculates the linear convolution of two input vectors.
         * 
         * \param f First input vector.
         * \param g Second input vector.
         * \return Resulting vector after performing convolution.
         */
        vector<T> conv(vector<T> f, vector<T> g)
        {
            int N = f.size();
            int M = g.size();
            
            vector<T> S(N + M - 1, 0.0);
            
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    S[i + j] += f[i] * g[j];
                }
            }
            return S;
        }

        /**
         * \brief Computes the sum of squared absolute values in a specified range of a vector.
         * 
         * \param y Input vector.
         * \param start Start index of the range.
         * \param end End index of the range.
         * \return The sum of squared absolute values within the specified range.
         */
        T sum_abs2(const std::vector<T>& y, int start, int end) 
        {
            return std::accumulate(y.begin() + start, y.begin() + end, 0.0, [](T acc, T val) 
            {
                return acc + val * val;
            });
        }

        /**
         * \brief Finds the next power of 2 greater than or equal to the input value.
         * 
         * \param n Input integer.
         * \return The smallest power of 2 greater than or equal to \p n.
         */
        int next_power_of_2(int n) 
        {
            if (n <= 0) 
            {
                return 1;
            }
            else
            {
                return std::pow(2, std::ceil(std::log2(n)));
            }
        }
    };
}

/**
 * \brief Overloads the output stream operator for vectors.
 * 
 * Outputs the contents of a vector in a human-readable format, enclosed in square brackets and separated by commas.
 * 
 * \tparam T Type of elements in the vector.
 * \param os Output stream.
 * \param vec Vector to be printed.
 * \return The modified output stream with the vector content.
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) 
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) 
    {
        os << vec[i];
        if (i != vec.size() - 1) 
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

#endif