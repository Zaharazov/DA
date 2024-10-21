#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);
 
    std::vector<long long> mas;
    long long n;
    std::cin >> n;
    
    for (long long i = 0; i < n; ++i)
    {
        long long rebro;
        std::cin >> rebro;
        mas.push_back(rebro);
    }
 
    sort(mas.rbegin(), mas.rend());

    long double otv_s = 0.0, otv_i;

    for (long long i = 0; i < n - 2; ++i)
    {
        long long a = mas[i];
        long long b = mas[i + 1];
        long long c = mas[i + 2];
        
        if (a < b + c)
        {
            long double p = (a + b + c) / 2.0;
            long double s = sqrtl(p * (p - a) * (p - b) * (p - c));
            
            if (s > otv_s) 
            {
                otv_s = s;
                otv_i = i;
            }
        }
    }
    if (otv_s > 0)
    {
        std::cout.precision(3);
        std::cout << std::fixed << otv_s << std::endl;
        std::cout << mas[otv_i + 2] << " " << mas[otv_i + 1] << " " << mas[otv_i];
    }
    else
    {
        std::cout << 0;
    }

    return 0;
}
