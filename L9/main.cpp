#include <iostream>
#include <vector>
#include <set>
#include <queue>

void bfs (int start, std::vector<std::vector<int>> & graph, std::vector<bool> & visited) 
{
    std::queue<int> q;
    std::set<int> otvet;

    q.push(start);

    while (!q.empty()) 
    {
        int current = q.front();
        q.pop();
        otvet.insert(current + 1); 

        for (int i : graph[current]) 
        {
            if (!visited[i]) 
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    for (int x : otvet) std::cout << x << " ";
    std::cout << std::endl;
}

int main() 
{
    int n, m;
    std::cin >> n >> m;
    
    std::vector <bool> visited(n, false);
    std::vector <std::vector<int>> graph(n);
    
    for (int i = 0; i < m; ++i) 
    {
        int p1, p2;
        std::cin >> p1 >> p2;
        graph[p1 - 1].push_back(p2 - 1); 
        graph[p2 - 1].push_back(p1 - 1); 
    }

    for (int i = 0; i < n; ++i) 
    {
        if (!visited[i]) bfs(i, graph, visited);
    }

    return 0;
}
