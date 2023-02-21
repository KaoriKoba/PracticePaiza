#include <iostream>

int main (void)
{
    int N, C=0, bit =1;
    int flag = 0;
    
    std::cin >> N;
    
    for ( C = 0 ; N > 1 ; C++ )
    {
        flag += bit & N;
        N = N >> 1;
    }

    std::cout << (C + (flag >0 ? 1:0)) << '\n';
}
