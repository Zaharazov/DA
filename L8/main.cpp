#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios::sync_with_stdio(false);
    
    long long n, m;
    std::vector<long long> weight, cost;

    std::cin >> n >> m;
    std::vector<std::vector<std::vector<long long>>> dp(n + 1, std::vector<std::vector<long long>>(n + 1, std::vector<long long>(m + 1, 0)));
    for (int i = 0; i < n; ++i)
    {
        long long w, c;
        std::cin >> w >> c;
        weight.push_back(w);
        cost.push_back(c);
    }
    
    // ищем макс сумму
    
    for (int k = 1; k < n + 1; ++k)
    {
        for (int i = 1; i < n + 1; ++i)
        {
            for (int j = 0; j < m + 1; ++j)
            {
                dp[k][i][j] = dp[k][i - 1][j];
                
                if (weight[i - 1] <= j)
                {
                    if (k == 1)
                    {
                        dp[k][i][j] = std::max(dp[k][i][j], cost[i - 1]);
                        // если один предмет, то берем его
                    }
                    else if (dp[k - 1][i - 1][j - weight[i - 1]] != 0)
                    {
                        dp[k][i][j] = std::max(dp[k][i][j], (dp[k - 1][i - 1][j - weight[i - 1]] / (k - 1) + cost[i - 1]) * k);
                        // умножаем на k, только если в рюкзаке k предметов
                    }
                    
                    
                }
            }
        }
    }
    
    // ищем максимальную ценность
    
    long long otvet = 0, otvet_k = 0;
    
    for (int k = 1; k < n + 1; ++k)
    {
        // std::cout << "{" << dp[k][n][m] << "} ";
        if (dp[k][n][m] > otvet) 
        {
            otvet_k = k;
            otvet = dp[k][n][m];  
        }
    }
    
    std::cout << otvet << std::endl;
    
    // ищем, какие вещи положили в рюкзак
    
    std::vector<long long> otvet_objects;
    long long k = otvet_k, i = n, j = m;
    
    while (i != 0)
    {
        if (dp[k][i][j] == dp[k][i - 1][j])
        {
            i -= 1;
        }
        else
        {
            otvet_objects.push_back(i);
            k -= 1;
            i -= 1;
            j -= weight[i];
        }
    }
    
    sort(otvet_objects.begin(), otvet_objects.end());
    for (int i = 0; i < otvet_objects.size(); ++i)
        std::cout << otvet_objects[i] << " "; 
        
    return 0;
}
