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

    // backtracking data structure
    int K_bt[F + 1][C], L_bt[F + 1][C];
    for (int i = 0; i <= F; i++)
        for (int j = 0; j < C; j++)
            K_bt[i][j] = L_bt[i][j] = 0;

    // base
    K[0] = L[0] = 0;

    for (int i = 1; i <= F; i++) {
        // case when there is no representation
        if (coins[0].w > i) {
            K[i] = L[i] = std::numeric_limits<int>::min();
            continue;
        } 
        
        int max = K[i - coins[0].w] + coins[0].p;
        for (int x = 0; x < C; x++)
            K_bt[i][x] = K_bt[i - coins[0].w][x];
        K_bt[i][0]++;
        
        int min = L[i - coins[0].w] + coins[0].p;
        for (int x = 0; x < C; x++)
            L_bt[i][x] = L_bt[i - coins[0].w][x];
        L_bt[i][0]++;

        //std::cout << "i " << i << " max/min " << max << " " << min << " | ";
        for (int j = 1; coins[j].w <= i && j < C; j++) {
            //std::cout << "j " << j << " m " << K[i - coins[j].w] + coins[j].p << ", (coins[j].w = " << coins[j].w << " ";
            if (K[i - coins[j].w] + coins[j].p > max) {
                max = K[i - coins[j].w] + coins[j].p;
                for (int x = 0; x < C; x++)
                    K_bt[i][x] = K_bt[i - coins[0].w][x];
                K_bt[i][j]++;
            }
            if (L[i - coins[j].w] + coins[j].p < min) {
                min = L[i - coins[j].w] + coins[j].p;
                for (int x = 0; x < C; x++)
                    L_bt[i][x] = L_bt[i - coins[j].w][x];                
                L_bt[i][j]++;
            }
        }

        K[i] = max;
        L[i] = min;
        //std::cout << "\n";
    }

    // backtracking - actual distribution of coins for K[F] & L[F]


    // for (int i = 0; i <= F; i++)
    //     std::cout << "K[" << i << "] = " << K[i] << ", L[" << i << "] = " << L[i] << "\n";

    // output:
    // 1. if we can achieve F at all. if yes:
    // 2. minimal value & 3. it's distribution
    // 4. maximal value & 5. it's distribution

    if (K[F] < 0) {
        std::cout << "NIE\n";
        return 0;
    } else {
        std::cout << "TAK\n";
        std::cout << L[F] << "\n";
        for (int i = 0; i < C; i++)
            std::cout << L_bt[F][i] << " ";
        std::cout << "\n";
        std::cout << K[F] << "\n";
        for (int i = 0; i < C; i++)
            std::cout << K_bt[F][i] << " ";
        std::cout << "\n";
    }
}