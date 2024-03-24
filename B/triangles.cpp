#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef std::pair<int, int> Point;

double distance(Point& p, Point& q) {
    return std::sqrt(std::pow(p.first - q.first, 2) + std::pow(p.second - q.second, 2));
}

double perimeter(Point& p, Point& q, Point& r) {
    return distance(p, q) + distance(q, r) + distance(r, p);
}

double find_min_triangle(std::vector<Point> &X, std::vector<Point> &Y, int n, Point *res) {
    // initial minimal perimeter from the first three points
    double min_perim = perimeter(X[0], X[1], X[2]);
    for (int i = 0; i < 3; i++)
        res[i] = X[i];

    // small cases without recursion
    if (n < 7) {
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = j + 1; k < n; k++)
                    if (perimeter(X[i], X[j], X[k]) < min_perim) {
                        min_perim = perimeter(X[i], X[j], X[k]);
                        res[0] = X[i];
                        res[1] = X[j];
                        res[2] = X[k];
                    }
        return perimeter(res[0], res[1], res[2]);
    } else {
        // vertical line that divides points into two set
        int l = X[n / 2].first;
        
        // divide points into two sets
        std::vector<Point> XL, XR, YL, YR;
        std::copy(X.begin(), X.begin() + n / 2, std::back_inserter(XL));
        std::copy(X.begin() + n / 2, X.end(), std::back_inserter(XR));
        for (int i = 0; i < n; i++) {
            if ((int)YL.size() <= n/2 && Y[i].first <= l)
                YL.push_back(Y[i]);
            else
                YR.push_back(Y[i]);
        }

        // recursive call
        Point res_l[3], res_r[3];
        double d_l = find_min_triangle(XL, YL, n / 2, res_l);
        double d_r = find_min_triangle(XR, YR, n - n / 2, res_r);

        double d = std::min(d_l, d_r);

        std::vector<Point> Y1;
        for (auto &p : Y)
            if (std::abs(p.first - l) < d / 2)
                Y1.push_back(p);

        int n1 = Y1.size();
        for (int i = 0; i < n1; i++)
            for (int j = i + 1; j < n1 && j < i + 7; j++)
                for (int k = j + 1; k < n1 && k < j + 7; k++)
                    if (perimeter(Y1[i], Y1[j], Y1[k]) < min_perim) {
                        min_perim = perimeter(Y1[i], Y1[j], Y1[k]);
                        res[0] = Y1[i];
                        res[1] = Y1[j];
                        res[2] = Y1[k];
                    }

        if (min_perim < d)
            return min_perim;
        else {
            if (d_l < d_r) {
                for (int i = 0; i < 3; i++)
                    res[i] = res_l[i];
                return d_l;
            } else {
                for (int i = 0; i < 3; i++)
                    res[i] = res_r[i];
                return d_r;
            }
        }
    }
}

int main() {
    // read input
    int n;
    std::cin >> n;
    std::vector<Point> P(n);
    for (int i = 0; i < n; i++)
        std::cin >> P[i].first >> P[i].second;
    
    // result
    Point res[3];

    // points sorted by x coordinate
    std::vector<Point> X(P);
    std::sort(X.begin(), X.end(), [](Point& p, Point& q) {
        return p.first < q.first;
    });

    // points sorted by y coordinate
    std::vector<Point> Y(P);
    std::sort(Y.begin(), Y.end(), [](Point& p, Point& q) {
        return p.second < q.second;
    });

    find_min_triangle(X, Y, n, res);
    
    // print the solution
    for (int i = 0; i < 3; i++)
        std::cout << res[i].first << " " << res[i].second << "\n";
}