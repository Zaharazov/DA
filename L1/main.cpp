#include <iostream>
#include <vector>

struct object
{
   char key[33];
   int ind;
};

int hex_to_int (char & a)
{
    if ((a - '0') <= 9 and (a - '0') >= 0) return a - '0';
    if ((a - '0') > 9 or (a - '0') < 0) return a - '0' - 39;
    return 0;
}

//0123456789ABCDEF
void count_sort (const size_t & ind, std::vector<object> & mas, const size_t & it)
{
    int entry[16] = {0};
    std::vector<object> mas2(it);
    
    for (size_t i = 0; i < it; ++i)
    {
        entry[hex_to_int(mas[i].key[ind])] += 1;
    }
    
    for (size_t i = 1; i < 16; ++i)
    {
        entry[i] += entry[i - 1];
    }
    
    for (int i = it - 1; i >= 0; --i)
    {
        int new_position = --entry[hex_to_int(mas[i].key[ind])];
        mas2[new_position] = mas[i];
    }
    
	for (int i = 0; i < it; ++i)
    {
    	mas[i] = mas2[i];
    }
}

int main()
{
	std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::vector<object> mas(1e6);
    std::vector<std::string> s_mas;
    size_t it = 0;
    std::string value;
    
    while (std::cin >> mas[it].key)
    {
        std::cin >> value;
        s_mas.push_back(value);
        mas[it++].ind = s_mas.size() - 1;
    }
    
    for (int i = 31; i >= 0; --i)
    {
        count_sort(i, mas, it);
    }
    
    for (int i = 0; i < it; ++i)
    {
        std::cout << mas[i].key << '\t' << s_mas[mas[i].ind] << '\n';
    }
    
    return 0;
}
