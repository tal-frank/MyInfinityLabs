#include <stdio.h>

void HanoiTower(int n, char from, char to, char mid) 
{
    if (0 == n) 
    {
        return;
    }
    
    HanoiTower(n - 1, from, mid, to);
    printf("Disk %d moved from %c to %c\n", n, from, to);
    HanoiTower(n - 1, mid, to, from);
}

int main() 
{
    int n = 5;

    HanoiTower(n, 'A', 'C', 'B');
    return 0;
}