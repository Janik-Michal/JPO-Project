#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>

using std::vector;

class filter
{
private:
    vector<double> m_v {};
public:

    vector<double> conv(vector<double> f, vector<double> g)
    {
    int N = f.size();
    int M = g.size();
    
    vector<double> S(N+M-1,0.0);
    
    for(int i = 0;i < N;i++)
    {
        for(int j = 0;j < M;j++)
        {
            S[i+j] += f[i]*g[j];
        }
    }
    return S;
    }

    double sum_abs2(const std::vector<double>& y, int start, int end) 
    {
        return std::accumulate(y.begin() + start, y.begin() + end, 0.0, [](double acc, double val) 
        {
            return acc + val * val;
        });
    }

    int next_power_of_2(int n) 
    {
        if (n <= 0) 
        {
            return 1;
        } else
        {
            return std::pow(2, std::ceil(std::log2(n)));
        }
    }

    std::vector<double> operator/(const double scalar) {
    if (scalar == 0) {
        throw std::domain_error("Dzielenie przez zero!");
    }
    std::vector<double> result(m_v.size());
    for (size_t i = 0; i < m_v.size(); ++i) {
        result[i] = m_v[i] / scalar;
    }
    return result;
}

};
