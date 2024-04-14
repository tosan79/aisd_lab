#include <iostream>
#include <algorithm>
#include <limits>

typedef struct Coin {
    int p; // denominal
    int w; // weight
} Coin;

int main() {
    int F; // total weight of coins
    int C; // number of coins 
    std::cin >> F;
    std::cin >> C;

    Coin coins[C];
    for (int i = 0; i < C; i++)
        std::cin >> coins[i].p >> coins[i].w;

    // sort coins by weight (maybe can be skipped if input is already sorted)
    std::sort(coins, coins + C, [](Coin c1, Coin c2){ return c1.w < c2.w; });
 
    int K[F + 1], L[F + 1]; // K[i] is max value of coins weighing i grams (L[i] is min value)

    // backtracking
    int Kpath[F + 1], Lpath[F + 1];

    // base
    K[0] = L[0] = 0;

    for (int i = 1; i <= F; i++) {
        // case when there is no representation
        if (coins[0].w > i) {
            K[i] = L[i] = std::numeric_limits<int>::min();
            continue;
        }

        int max = K[i - coins[0].w] + coins[0].p;
        int Kstep = 0;
        
        int min = L[i - coins[0].w] + coins[0].p;
        int Lstep = 0;
        
        for (int j = 1; coins[j].w <= i && j < C; j++) {
            if (K[i - coins[j].w] + coins[j].p > max) {
                max = K[i - coins[j].w] + coins[j].p;
                Kstep = j;
            }
            if (L[i - coins[j].w] + coins[j].p < min) {
                min = L[i - coins[j].w] + coins[j].p;
                Lstep = j;
            }
        }

        K[i] = max;
        L[i] = min;

        Kpath[i] = Kstep;
        Lpath[i] = Lstep;
    }

    int Kresult[C], Lresult[C];
    for (int i = 0; i < C; i++)
        Kresult[i] = Lresult[i] = 0;

    int r = F ;
    while (r > 0) {
        Kresult[Kpath[r]]++;
        r -= coins[Kpath[r]].w;
    }

    r = F;
    while (r > 0) {
        Lresult[Lpath[r]]++;
        r -= coins[Lpath[r]].w;
    }
    
    // output

    if (K[F] < 0) {
        std::cout << "NIE\n";
        return 0;
    }
    std::cout << "TAK\n";
    std::cout << L[F] << "\n";
    
    // for (int i = 1; i <= F; i++)
    //     std::cout << Lpath[i] << " ";
    // std::cout << "\n";

    for (int i = 0; i < C; i++)
        std::cout << Lresult[i] << " ";
    std::cout << "\n";
    
    std::cout << K[F] << "\n";
    
    // for (int i = 1; i <= F; i++)
    //     std::cout << Kpath[i] << " ";
    // std::cout << "\n";

    for (int i = 0; i < C; i++)
        std::cout << Kresult[i] << " ";
    std::cout << "\n";

    return 0;
}