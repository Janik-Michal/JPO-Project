#include "filter.hpp"
#ifndef IIR_HPP
#define IIR_HPP

namespace mj
{
    template <typename T>

    class IIR : public filter<T>
    {
    private:
        std::vector<T> m_b;
        std::vector<T> m_a;
        int m_L {};
    public:
        IIR(std::vector<T> b = {0.1,0.1}, std::vector<T> a = {1.0,0.1}) : m_b(b), m_a(a) 
        {
            if(m_a[0] != 1)
            {       
                if (m_a[0] ==  0)   
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
    

        std::vector<T> OutSignal(std::vector<T> x)
        {
            if(m_L == 0)
            {
                x.resize(this->next_power_of_2(x.size())); //rozmiar x jako równe potęgi 2 
            }else if(m_L < x.size())
            {
                std::cout << "the size 'L' can't be smaller than input vector (using resize x to the next power of 2): " << std::endl;
                x.resize(this->next_power_of_2(x.size()));
            }else{
                x.resize(m_L,0.0);
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

        std::string stability() 
        {
            int L = m_L;
            m_L = 31;
            vector<T> x(30, 0);
            x[0] = 1;
            vector<T> y = OutSignal(x);

            T energy1 = this->sum_abs2(y, 0, y.size() / 2);
            T energy2 = this->sum_abs2(y, y.size() / 2, y.size());
            m_L = L;

            return (energy2/energy1 >= 1.0) ? "This filter is unstable! - Please change coefficients" : "This filter is stable";
        }



        void SetB(const vector<T> &b)
        {
            if (b.empty()) 
            {
                throw std::invalid_argument("Vector a can't be empty!");
            }
            m_b = b;
        }

        void SetA(vector<T> a)
        {
            if (a.empty()) 
            {
                throw std::invalid_argument("Vector b can't be empty!");
            }
            if(a[0] != 1)
            {       
                if (a[0] ==  0)   
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

        void SetL(const int &L)
        {
            if (L<0) 
            {
                throw std::invalid_argument("L can't be less than zero!");
            }
            m_L = L;
        }

        vector<T> getB() const
        {
            return m_b;
        }

        vector<T> getA() const
        {
            return m_a;
        }

        int getL() const
        {
            return m_L;
        }
    };
}
#endif