#include <iostream> // STL
#include <string> // string variable
#include <map> // STL map
#include <list> // STL list

void PrintAllInputs(std::map<std::string, int>& map, std::list<std::string>& list)
{
    std::map<std::string, int>::iterator map_iter;
    
    std::list<std::string>::iterator list_iter;
    std::list<std::string>::iterator list_end;
    list_iter = list.begin();
    list_end = list.end();
    
    while (list_end != list_iter)
    {
        map_iter = map.find(*list_iter);
        if (1 < map_iter->second)
        {
            std::cout << map_iter->second << " X ";
        }
        std::cout << *list_iter << std::endl;
        ++list_iter;
    }
}

void Histo()
{
    std::map<std::string, int> map;
    std::list<std::string> list;
    std::string input;

    while ("." != input)
    {
        std::getline(std::cin, input);

        std::map<std::string, int>::iterator map_iter;
        map_iter = map.find(input);

        if (map.end() == map_iter)
        {
            list.push_back(input);
        }

        ++map[input];
    }
    PrintAllInputs(map, list);
}

int main()
{
    Histo();
    return 0;
}