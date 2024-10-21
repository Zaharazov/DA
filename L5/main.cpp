#include <iostream>
#include <map>
#include <string>

struct Node // вершина
{
    int first_symb;
    int * last_symb;
    std::map<char, Node*> deti;
    Node * suf_link = NULL;
    
    Node(int _first_symb, int* _last_symb) // конструктор
    {
        first_symb = _first_symb;
        last_symb = _last_symb;
    }
};
    
class Suf_tree // Дерево
{
public:
    Node* root;
    Node* current_node; // текущая вершина, с которой мы работаем на каждом шаге
    std::string text;
    int global_last_symb; // глобальный индекс, указывающий на конец текущей суффиксной строки

    Suf_tree(const std::string& s) // конструктор
    {
        text = s;               
        global_last_symb = -1;         
        root = new Node(-1, NULL); 
        current_node = root;     
    }
    
    void build()
    {
        for (int i = 0; i < text.size(); ++i)   insert(i);  
    }
    
    Node* last_suf_node = NULL; // последняя вершина, c которой мы создаем суффиксную ссылку.
    int current_edge = -1; // индекс символа, с которого начинается текущее ребро
    int current_length = 0; // длина текущего совпадающего суффикса 
    int ostalos_suff = 0; // количество суффиксов, которые нужно еще добавить

    void insert(int symb_pos) // вставка
    {
        last_suf_node = NULL;
        global_last_symb++;
        ostalos_suff++;

        while (ostalos_suff > 0) 
        {
            if (current_length == 0) current_edge = symb_pos;

            char current_char = text[current_edge];
            if (!current_node->deti[current_char]) // нет суффикса с началом - current_char
            {
                current_node->deti[current_char] = new Node(symb_pos, &global_last_symb); // создаем новый суффикс
                if (last_suf_node) last_suf_node->suf_link = current_node; // создание суффиксной ссылки
                last_suf_node = NULL; // закончили с ссылками на этом шаге
            } 
            else // есть суффикс с началом - current_char
            {
                Node* next_node = current_node->deti[current_char]; // переходим в эту вершину
                int edge_length = *next_node->last_symb - next_node->first_symb + 1; // длина текущего ребра

                if (current_length >= edge_length) // если прошли уже совпавшую часть
                {
                    current_edge += edge_length;
                    current_length -= edge_length;
                    current_node = next_node;
                    continue;
                }

                if (text[next_node->first_symb + current_length] == text[symb_pos]) // символ  текущего суффикса и символ текущей обработки
                {
                    ++current_length;
                    if (last_suf_node) last_suf_node->suf_link = current_node; // создаем суффиксную ссылку
                    break;
                }
                // если символы не совпали, разбиваем вершину
                Node* split_node = new Node(next_node->first_symb, new int(next_node->first_symb + current_length - 1)); // вместо last_symb ссылка на последний совпавший элемент
                current_node->deti[current_char] = split_node;
                next_node->first_symb += current_length; // убираем совпавшую часть в старой вершине
                
                split_node->deti[text[next_node->first_symb]] = next_node; // переделали ссылку на старую вершину
                split_node->deti[text[symb_pos]] = new Node(symb_pos, &global_last_symb); // вершина с новым суффиксом
                
                if (last_suf_node) last_suf_node->suf_link = split_node; // установка суффиксной ссылким
                last_suf_node = split_node;
            }

            --ostalos_suff; // вставили суффикс
            
            if (current_node == root) 
            {
                if (current_length > 0)
                {
                    --current_length;
                    ++current_edge;
                }
            } 
            else  // переход по суффиксной ссылке
            {
                current_node = current_node->suf_link;
            }
        }
    }
    
    std::string get_otvet() // поиск
    {
        std::string otvet = "";
        Node * current = root; // начинаем с корня
        int len = text.size() / 2; // длина искомой строки
        
        while (otvet.size() < len)  // собираем строку пока не получим нужную длину
        {
            auto iter = current->deti.begin(); // ищем наименьший лексикографический суффикс
            if (iter->first == '$') iter++;
            current = iter->second; 
            
            for (int i = current->first_symb; i <= *current->last_symb; ++i) // проходим по элементам строки в вершине
            {
                if (otvet.size() == len) break;
                otvet += text[i];
            }
        }
        return otvet;
    }
};

int main() 
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    std::string text; // = "slushaytevelikogozaharanavsehploshadkah";
    std::cin >> text;
    Suf_tree tree(text + text + "$");
    
    tree.build();
    
    std::cout << tree.get_otvet() << std::endl;
    
    tree.root = NULL;
    
    return 0;
}
