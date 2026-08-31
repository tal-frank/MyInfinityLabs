#include <iostream> // STL
#include <string> // string variable
#include <map> // STL map
#include <list> // STL list

void PrintAllInputs(std::map<std::string, int>& map, std::list<std::string>& list)
{  
    std::list<std::string>::iterator list_iter;

    for(list_iter = list.begin(); list_iter != list.end(); ++list_iter)
    {
        if (1 < map[*list_iter])
        {
            std::cout << map[*list_iter] << " X ";
        }
        std::cout << *list_iter << std::endl;
    }
}

void Histo()
{
    std::map<std::string, int> map;
    std::list<std::string> list;
    std::string input = "";

    while ("." != input)
    {
        std::getline(std::cin, input);

        if (map.end() == map.find(input))
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