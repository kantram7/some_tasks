#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> point;

bool one_line(const point& a, const point& b, const point& c) {
    // три точки на одной прямой
    return (b.first - a.first) * (c.second - a.second) == (c.first - a.first) * (b.second - a.second);
}

bool int_between(int a, int b, int c) {
    // значение с между a и b 
    return (((a <= c) && (c <= b)) || ((b <= c) && (c <= a)));
}

bool point_between(const point& a, const point& b, const point& c) {
    // лежит ли третья точка c между а и b
    if (!one_line(a, b, c)) return false; // если они не лежат на одной прямой

    // точка между двух других, если её х и у между соответствующими двух других точек
    if (a.first != b.first) return int_between(a.first, b.first, c.first);
    else return int_between(a.second, b.second, c.second);

    // можно с помощью произведений векторов, но больше вычислений
 }

int vars(const vector<point>& v) {
    int result = 0;
    
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            result++;
            for (size_t q = 0; q < v.size(); q++) {
                if (v[q] != v[i] && v[q] != v[j]) {
                    if (point_between(v[i], v[j], v[q])) {
                        result--;
                        break;
                    }
                }
            }
        }
    }
    return result;
}

int main()
{
    int n, x, y;
    cin >> n;

    vector<point> points(n);

    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        points[i] = { x, y };
    }

    cout << vars(points) * 2;

    return 0;
}
