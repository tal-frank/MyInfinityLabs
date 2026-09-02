#include <iostream>
#include <list>

#include "shapes.hpp"

void PrintShapeList(std::list<shape*> shape_list)
{
    std::list<shape*>::iterator iter;
    for (iter = shape_list.begin(); iter != shape_list.end(); ++iter)
    {
        (*iter)->Draw();
    }

}

int main()
{
    
    line l;
    rectangle r;
    square s;
    circle c;

    l.Draw();
    r.Draw();
    s.Draw();
    c.Draw();

    l.Move(2);
    r.Move(4);
    s.Move(6);
    c.Move(8);

    l.Draw();
    r.Draw();
    s.Draw();
    c.Draw();

    l.Move(8);
    r.Move(6);
    s.Move(4);
    c.Move(2);

    l.Draw();
    r.Draw();
    s.Draw();
    c.Draw();

    std::list<shape*> shape_list;

    shape_list.push_back(&l);
    shape_list.push_back(&r);
    shape_list.push_back(&s);
    shape_list.push_back(&c);

    PrintShapeList(shape_list);
    return 0;
}