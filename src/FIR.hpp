/**
 * @file FIR.hpp
 * @brief Implementation of FIR (Finite Impulse Response) filter.
 *
 * This file defines the `FIR` class, which implements a finite impulse 
 * response filter. It supports signal convolution and provides methods 
 * to manage filter coefficients.
 */

#include "filter.hpp"
#ifndef FIR_HPP
#define FIR_HPP

namespace mj
{
    /**
     * \brief FIR (Finite Impulse Response) filter class.
     * 
     * \tparam T Data type for filter coefficients and signals.
     */
    template <typename T>
    class FIR : public filter<T>
    {
    private:
        vector<T> m_x {};        //!< Input signal vector.
        vector<T> m_h {1, 2, 1}; //!< Impulse response coefficients (default values).
    public:
        /**
         * \brief Constructs an FIR filter with an input signal.
         * 
         * Initializes the FIR filter with a given input signal vector.
         * 
         * \param x Input signal vector.
         * \throws std::invalid_argument if the input vector is empty.
         */
        FIR(const vector<T>& x) : m_x(x)
        {
            if (x.empty()) 
            {
                throw std::invalid_argument("Vector x cannot be empty!");
            } 
        }

        /**
         * \brief Constructs an FIR filter with input and impulse response vectors.
         * 
         * Initializes the FIR filter with both input signal and impulse response vectors.
         * 
         * \param x Input signal vector.
         * \param h Impulse response vector.
         * \throws std::invalid_argument if either vector is empty.
         */
        FIR(const vector<T>& x, const vector<T>& h) : m_x(x), m_h(h) 
        {
            if (x.empty() || h.empty()) 
            {
                throw std::invalid_argument("Vector cannot be empty!");
            }
        }

        /**
         * \brief Computes the output signal of the FIR filter.
         * 
         * Performs convolution between the impulse response and the input signal
         * to compute the filtered output signal.
         * 
         * \return Output signal vector after applying the FIR filter.
         */
        vector<T> OutSignal()
        {
            return this->conv(m_h, m_x);
        }

        /**
         * \brief Sets the impulse response coefficients.
         * 
         * Updates the impulse response coefficients of the FIR filter.
         * 
         * \param h New impulse response vector.
         * \throws std::invalid_argument if the vector is empty.
         */
        void setH(const vector<T>& h)
        {
            if (h.empty()) 
            {
                throw std::invalid_argument("Vector x cannot be empty!");
            } 
            m_h = h;
        }

        /**
         * \brief Sets the input signal vector.
         * 
         * Updates the input signal for the FIR filter.
         * 
         * \param x New input signal vector.
         * \throws std::invalid_argument if the vector is empty.
         */
        void setX(const vector<T>& x)
        {
            if (x.empty()) 
            {
                throw std::invalid_argument("Vector x cannot be empty!");
            } 
            m_x = x;
        }

        /**
         * \brief Gets the impulse response coefficients.
         * 
         * Retrieves the current impulse response coefficients of the FIR filter.
         * 
         * \return Current impulse response vector.
         */
        vector<T> getH() const
        {
            return m_h;
        }

        /**
         * \brief Gets the input signal vector.
         * 
         * Retrieves the current input signal of the FIR filter.
         * 
         * \return Current input signal vector.
         */
        vector<T> getX() const
        {
            return m_x;
        }
    };
}

#endif
