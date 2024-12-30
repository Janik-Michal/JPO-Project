#include "filter.hpp"

class FIR : filter
{
private:
    vector<double> m_h {};
    vector<double> m_x {};
public:
    FIR(vector<double> x) : m_x(x) {}

    vector<double> OutSignal()
    {
        conv(m_h,m_x);
    }

    void setH(vector<double> h)
    {
        m_h = h;
    }


};