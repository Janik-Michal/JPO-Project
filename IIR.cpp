#include "filter.hpp"

class IIR : filter
{
private:
    std::vector<double> m_b;
    std::vector<double> m_a;
    int m_L {};
public:
    IIR(const std::vector<double>& b = {1.0},const std::vector<double>& a = {1.0}) : m_b(b), m_a(a) 
    {
        if(m_a[0] != 1)
        {       
            if (m_a[0] ==  0)   
            {
                throw std::domain_error("Don't divide by zero!");
            }
            for (size_t i = 0; i < m_a.size(); ++i) 
            {
                m_a[i] = m_a[i] / m_a[0];
            }
            for (size_t i = 0; i < m_b.size(); ++i) 
            {
                m_b[i] = m_b[i] / m_a[0];
            }
        }
    }
  

    std::vector<double> lti_filter(std::vector<double> x)
    {
        if(m_L == 0)
        {
            x.resize(next_power_of_2(x.size())); //rozmiar x jako równe potęgi 2 
        }else if(m_L < x.size())
        {
            std::cout << "the size of output vector cannot be smaller than input vector" << std::endl;
        }else{
            x.resize(m_L,0.0);
        }
        int N = x.size();
        int M = m_b.size() - 1;
        int K = m_a.size() - 1;
        std::vector<double> y(N, 0.0);

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
        vector<double> x {1,(20,0.0)};
        vector<double> y = lti_filter(x);

        double energy1 = sum_abs2(y, 0, y.size()/2 - 1);
        double energy2 = sum_abs2(y, y.size()/2 - 1, y.size());

        if(energy2/energy1>=1)
        {
            return "the filter is unstable";
        } else
        {
            return "the filter is stable";
        }
    }

    void SetB(const vector<double> &b)
    {
        if (b.empty()) 
        {
            throw std::invalid_argument("Vector a cannot be empty!");
        }
        m_b = b;
    }

    void SetA(const vector<double> &a)
    {
        if (a.empty()) 
        {
            throw std::invalid_argument("Vector b cannot be empty!");
        }
        m_a = a;
    }

    void SetL(const int &L)
    {
        if (L<0) 
        {
            throw std::invalid_argument("L cannot be less than zero!");
        }
        m_L = L;
    }

    
};

int main()
{
    IIR iir({0.009856381838533497, 0.02956914551560049, 0.02956914551560049, 0.009856381838533497},{1.0, -2.2253012610556193, 1.955403057140463, -0.6512507413765761});
    vector<double> c = iir.lti_filter({0.96, -0.08, 0.39, -0.39, -0.13, 0.41, 0.14, 0.9, -0.14, 1.0, -0.62});
    for(int i = 0;i<c.size();i++)
    {
        std::cout<<c[i]<<" ";
    }
}