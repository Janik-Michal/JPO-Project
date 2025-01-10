#include "filter.hpp"
#ifndef FIR_HPP
#define FIR_HPP

namespace mj
{
    template <typename T>

    class FIR : public filter<T>
    {
    private:
        vector<T> m_h {1,2,1};
        vector<T> m_x {};
    public:
        FIR(const vector<T>& x) : m_x(x)
        {
        if (x.empty()) 
            {
                throw std::invalid_argument("Vector x cannot be empty!");
            } 
        }
        FIR(const vector<T>& x,const vector<T>& h) : m_x(x), m_h(h) 
        {
            if (x.empty()||h.empty()) 
            {
                throw std::invalid_argument("Vector cannot be empty!");
            }
        }

        vector<T> OutSignal()
        {
            return this -> conv(m_h,m_x);
        }

        void setH(const vector<T>& h)
        {
            if (h.empty()) 
            {
                throw std::invalid_argument("Vector x cannot be empty!");
            } 
            m_h = h;
        }

        void setX(const vector<T>& x)
        {
            if (x.empty()) 
            {
                throw std::invalid_argument("Vector x cannot be empty!");
            } 
            m_x = x;
        }

        vector<T> getH() const
        {
            return m_h;
        }

        vector<T> getX() const
        {
            return m_x;
        }
    };
}
#endif
