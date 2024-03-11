#include <iostream>
#include <vector>
#include <stack>

// void dfs(int v) {
//     visited[v] = true;
//     t_in[v] = timer++;
//     //std::cout << v << " ";

//     for (auto u : A[v]) {
//         if (!visited[u]) {
//             dfs(u);
//         }
//     }
//     t_out[v] = timer++;
// }

int main() {
    int n; /* number of women */
    int q; /* number of queries */
    
    std::cin >> n >> q;

    std::vector<std::vector<int>> A; /* adjacency list representation */
    std::vector<bool> visited;
    std::vector<unsigned int> t_in;
    std::vector<unsigned int> t_out;


    A.resize(n + 1);
    t_in.resize(n + 1);
    t_out.resize(n + 1);
    visited.resize(n + 1, false);

    int m;
    for (int i = 1; i < n; i++) {
        std::cin >> m;
        A[m].push_back(i + 1);
    }

    unsigned int timer = 0;

    std::stack<int> stack;
    stack.push(1);

    while (!stack.empty()) {
        int v = stack.top();
        stack.pop();

        if (visited[v]) {
            t_out[v] = timer++;
        } else {
            visited[v] = true;
            t_in[v] = timer++;
            stack.push(v);
            for (auto u : A[v]) {   
                if (!visited[u]) {
                    stack.push(u);
                }
            }
        }
    }
    
    /* print the adjacency list */
    // for (unsigned long i = 1; i < A.size(); i++) {
    //     std::cout << i << ": ";
    //     for (auto u : A[i]) {
    //         std::cout << u << " ";
    //     }
    //     std::cout << "\n";
    // }

    /* print timestamps of in and out */
    // for (int i = 1; i <= n; i++) {
    //     std::cout << i << " t_in: " << t_in[i] << ", t_out: " << t_out[i] << "\n";
    // }

    // process the queries
    int a, d; // ancestor & descendant
    for (int i = 0; i < q; i++) {
        std::cin >> a >> d;
        if (t_in[a] < t_in[d] && t_out[a] > t_out[d]) {
            std::cout << "TAK\n";
        } else {
            std::cout << "NIE\n";
        }
    }

    return 0;
}