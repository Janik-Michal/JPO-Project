#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>
#ifndef FILTER_HPP
#define FILTER_HPP

using std::vector;

namespace mj
{
    template <typename T>

    class filter
    {
    private:
    public:

        vector<T> conv(vector<T> f, vector<T> g)
        {
        int N = f.size();
        int M = g.size();
        
        vector<T> S(N+M-1,0.0);
        
        for(int i = 0;i < N;i++)
        {
            for(int j = 0;j < M;j++)
            {
                S[i+j] += f[i]*g[j];
            }
        }
        return S;
        }

        T sum_abs2(const std::vector<T>& y, int start, int end) 
        {
            return std::accumulate(y.begin() + start, y.begin() + end, 0.0, [](T acc, T val) 
            {
                return acc + val * val;
            });
        }

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