#include <iostream> 
#include <vector>
#include <deque>

int cmp (const std::deque <std::string> & text, const std::deque <std::string> & pattern)  // тупое сравнение text и pattern
{
	int sovp = 0;
	for (size_t j = 0; j < text.size(); ++j)
	{
		if (text[j] == pattern[sovp])
		   sovp++;
		else
		   return sovp;
	}
	return sovp;
}

std::vector<int> sp_func (const std::deque<std::string> & s)  // z-функция + sp-функция
{
	int n = s.size();
	
	std::vector<int> z (n);
	std::vector<int> sp (n);
	int l = 0, r = 0;
	
	for (int i = 1; i < n; ++i) 
	{
		if (i <= r)
		{
			z[i] = std::min (r-i+1, z[i-l]);
		}
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
		{
			++z[i];
		}
		if (i+z[i]-1 > r)
		{
			l = i,  r = i+z[i]-1;
		}
	}

	for (int i = n - 1; i >= 0; --i)
    {
        sp[i + z[i] - 1] = z[i];
    }
    
	return sp;
}

int main()
{
    std::cin.tie(0);
	std::cout.tie(0);
    std::ios::sync_with_stdio(false);
    
    std::deque <std::string> text;
    std::deque <std::string> pattern;
    
    char c;
    std::string word = "";
    while (c = getchar())     // получаем pattern
    {
        if (c != ' ' and c != '\n')
        {
            c = tolower(c);
            word += c;
        }
        else
        {
			if (word != "") pattern.push_back(word);
            word = "";
            if (c == '\n') break;
        }
    }
    
    word = "";
    std::deque <std::pair<int,int>> omg;
    int pos = 1, strok = 1;
    
    std::vector <int> sp_v = sp_func(pattern);
    
    while (c = getchar())   // получаем text в реальном времени (O_o)
    {
        if (c != ' ' and c != '\n' and c != EOF)
        {
            c = tolower(c);
            word += c;
        }
        else
        {
			if (word != "") 
			{
			    text.push_back(word);
			    omg.push_back({strok, pos});
			    pos++;
			    
			}
			if (c == '\n')
            {
                strok++;
                pos = 1;
                
            }
            word = "";
        }
        
        if (text.size() == pattern.size())     // КМП в реальном времени (O_o)
        {
            int sovp = cmp(text, pattern); 
            
            int t = std::max(sovp - sp_v[std::max(sovp - 1, 0)], 1);
            if (sovp == pattern.size()) std::cout << omg[0].first << ", " << omg[0].second << std::endl;
            
            for (int i = 0; i < t; ++i)
                text.pop_front();
            
            for (int i = 0; i < t; ++i)
                omg.pop_front();
            
        }
        if (c == EOF) break;
    }
    return 0;
}
