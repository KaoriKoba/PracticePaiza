#include <iostream>
#include <cmath>

long long discriminant(long long a, long long b, long long c); // 判別式

int main()
{
    long long N, K;
    int maxT = 0;
    
    std::cin >> N >> K;
    
    for (int i = 0; i < N; ++i)
    {
        long long a, b, c;
        long long d;
        
        std::cin >> a >> b >> c;
        d = discriminant( a, b, c-K);
        
        if ( d >= 0 ) // 判別式が負の場合、木ははじめからKを越えている状態
        {
            double t;
            t = (-b + std::sqrt(d)) / (2*a);
            
            if ( maxT < t )
            {
                maxT = std::ceil( t );
            }
        }
        
    }
    
    std::cout << maxT << std::endl;
}

// 判別式
long long discriminant(long long a, long long b, long long c)
{
    long long d = (b*b)-(4*a*c);
    return d;
}
