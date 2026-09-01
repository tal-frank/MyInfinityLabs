#include "shapes.hpp"

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

    return 0;
}