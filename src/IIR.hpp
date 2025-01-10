/**
 * @file IIR.hpp
 * @brief Implementation of IIR (Infinite Impulse Response) filter.
 *
 * This file defines the `IIR` class, which implements an infinite impulse 
 * response filter. It includes methods for signal filtering, stability 
 * analysis, and coefficient management.
 */

#include "filter.hpp"
#ifndef IIR_HPP
#define IIR_HPP

namespace mj
{
    /**
     * \brief IIR (Infinite Impulse Response) filter class.
     * 
     * The filter applies feedback and feedforward coefficients
     * to compute the output signal. It also includes methods for stability analysis.
     * 
     * \tparam T Data type for filter coefficients and signals.
     */
    template <typename T>
    class IIR : public filter<T>
    {
    private:
        std::vector<T> m_b; //!< Feedforward coefficients (numerator).
        std::vector<T> m_a; //!< Feedback coefficients (denominator).
        size_t m_L {};         //!< Length of the output signal. Default: 0 - This means that the output signal length
                            //   is automatically adjusted to the input signal length.

    public:
        /**
         * \brief Constructs an IIR filter with optional coefficients.
         * 
         * Initializes the IIR filter with default or provided feedforward and feedback coefficients.
         * Ensures that the first feedback coefficient is normalized to 1.
         * 
         * \param b Feedforward coefficients (default: {0.1, 0.1}).
         * \param a Feedback coefficients (default: {1.0, 0.1}).
         * \throws std::domain_error if the first feedback coefficient is zero.
         */
        IIR(std::vector<T> b = {0.1, 0.1}, std::vector<T> a = {1.0, 0.1}) : m_b(b), m_a(a) 
        {
            if (m_a[0] != 1)
            {
                if (m_a[0] == 0)
                {
                    throw std::domain_error("a[0] can't be zero!");
                }
                T div = m_a[0];
                for (size_t i = 0; i < m_a.size(); ++i) 
                {
                    m_a[i] = m_a[i] / div;
                }
                for (size_t i = 0; i < m_b.size(); ++i) 
                {
                    m_b[i] = m_b[i] / div;
                }
            }
        }

        /**
         * \brief Computes the output signal of the IIR filter.
         * 
         * Processes the input signal by applying feedforward and feedback coefficients.
         * Handles resizing of the input signal based on the specified length or power of 2.
         * 
         * \param x Input signal vector.
         * \return Output signal vector after applying the IIR filter.
         */
        std::vector<T> OutSignal(std::vector<T> x)
        {
            if (m_L == 0)
            {
                x.resize(this->next_power_of_2(x.size())); // Resize to the next power of 2.
            } 
            else if (m_L < x.size())
            {
                std::cout << "The size 'L' can't be smaller than the input vector (resizing x to the next power of 2): " << std::endl;
                x.resize(this->next_power_of_2(x.size()));
            } 
            else 
            {
                x.resize(m_L, 0.0);
            }

            int N = x.size();
            int M = m_b.size() - 1;
            int K = m_a.size() - 1;
            std::vector<T> y(N, 0.0);

            for (int n = 0; n < N; n++)
            {
                for (int k = 0; k <= M; k++)
                {
                    if (n - k >= 0) 
                    {
                        y[n] += m_b[k] * x[n - k];
                    }
                }
                for (int k = 1; k <= K; k++) 
                {
                    if (n - k >= 0) 
                    {
                        y[n] -= m_a[k] * y[n - k];
                    }
                }
            }
            return y;
        }

        /**
         * \brief Determines the stability of the IIR filter.
         * 
         * Checks the energy of the output signal to evaluate stability.
         * Compares the energy in the second half of the signal to the first half.
         * 
         * \return "This filter is stable" if stable, otherwise "This filter is unstable!".
         */
        std::string stability() 
        {
            int L = m_L;
            m_L = 31;
            std::vector<T> x(30, 0);
            x[0] = 1; // Impulse input.
            std::vector<T> y = OutSignal(x);

            T energy1 = this->sum_abs2(y, 0, y.size() / 2);
            T energy2 = this->sum_abs2(y, y.size() / 2, y.size());
            m_L = L;

            return (energy2 / energy1 >= 1.0) ? "This filter is unstable! - Please change coefficients" : "This filter is stable";
        }

        /**
         * \brief Sets the feedforward coefficients.
         * 
         * Updates the numerator coefficients for the IIR filter.
         * 
         * \param b New feedforward coefficient vector.
         * \throws std::invalid_argument if the vector is empty.
         */
        void SetB(const std::vector<T>& b)
        {
            if (b.empty()) 
            {
                throw std::invalid_argument("Vector b can't be empty!");
            }
            m_b = b;
        }

        /**
         * \brief Sets the feedback coefficients.
         * 
         * Updates the denominator coefficients for the IIR filter.
         * Ensures the first coefficient is normalized to 1.
         * 
         * \param a New feedback coefficient vector.
         * \throws std::invalid_argument if the vector is empty.
         * \throws std::domain_error if the first coefficient is zero.
         */
        void SetA(std::vector<T> a)
        {
            if (a.empty()) 
            {
                throw std::invalid_argument("Vector a can't be empty!");
            }
            if (a[0] != 1)
            {
                if (a[0] == 0)
                {
                    throw std::domain_error("Don't divide by zero!");
                }
                T div = a[0];
                for (size_t i = 0; i < a.size(); ++i) 
                {
                    a[i] = a[i] / div;
                }
                for (size_t i = 0; i < m_b.size(); ++i) 
                {
                    m_b[i] = m_b[i] / div;
                }
            }
            m_a = a;
        }

        /**
         * \brief Sets the output signal length.
         * 
         * Updates the length of the output signal vector.
         * 
         * \param L New length of the output signal.
         * \throws std::invalid_argument if L is less than zero.
         */
        void SetL(const int& L)
        {
            if (L < 0) 
            {
                throw std::invalid_argument("L can't be less than zero!");
            }
            m_L = L;
        }

        /**
         * \brief Retrieves the feedforward coefficients.
         * 
         * \return Current feedforward coefficient vector.
         */
        std::vector<T> getB() const
        {
            return m_b;
        }

        /**
         * \brief Retrieves the feedback coefficients.
         * 
         * \return Current feedback coefficient vector.
         */
        std::vector<T> getA() const
        {
            return m_a;
        }

        /**
         * \brief Retrieves the output signal length.
         * 
         * \return Current length of the output signal.
         */
        int getL() const
        {
            return m_L;
        }
    };
}

#endif
