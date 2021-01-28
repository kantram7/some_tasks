#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef long double ld;

struct point {
	ld x;
	ld y;
};

// ищет самую левую и самую правую точки (то есть с min и max значениями y)
pair<ld, ld> min_max_x(const vector<point>& v) {

	ld min = v[0].x, max = v[0].x;
	for (size_t i = 1; i < v.size(); i++) {
		if (v[i].x > max) max = v[i].x;
		else if (v[i].x < min) min = v[i].x;
	}

	return { min, max };
}

// площадь многоугольника по точкам
ld area(const vector<point>& v) {
	ld sum = 0, n = v.size();
	for (size_t i = 0; i < n - 1; i++) {
		sum = sum + (v[i].x + v[i + 1].x) * (v[i].y - v[i + 1].y);
	}
	sum = sum + (v[n - 1].x + v[0].x) * (v[n - 1].y - v[0].y);
	return abs(sum) / 2;
}

// ищет у точки на отрезке между точками lh и rh, если известен х
ld find_y(const point& lh, const point& rh, ld mid_x) {
	return (mid_x * (rh.y - lh.y) - rh.y * lh.x + lh.y * rh.x) / (rh.x - lh.x);
}

// главная функция
// принимает список точек (в порядке обхода по часовой или против) и необходимую точность t
ld cut(const vector<point>& v, ld t) {

	auto [ min_x, max_x ] = min_max_x(v);
	ld main_area = area(v);
	int v_size = v.size();

	// рассматриваем прямую ровно между крайней левой и крайней правой точками много-ка
	while (true) {
		// точки слева (и на) предполагаемой прямой
		vector<point> lh;

		ld mid_x = min_x + (max_x - min_x) / 2;

		for (size_t i = 0; i < v_size; i++) {

			// точки справа от предполагаемой прямой
			if (v[i].x > mid_x) {
				size_t prev = ((i == 0) ? v_size : i) - 1;
				// если перешагнули предполагаемую прямую - нужно найти у точки пересечения прямой со сторонойф фигуры,
				// то есть отрезка прошлая_точка - текущая_точка (для первой в списке точки прошлая - последняя в списке)
				if (v[prev].x < mid_x) {
					lh.push_back({ mid_x, find_y(v[prev], v[i], mid_x) });
				}
			}
			// точки слева от предполагаемой прямой
			else if (v[i].x < mid_x) {
				size_t prev = ((i == 0) ? v_size : i) - 1;
				// если перешагнули предполагаемую прямую - нужно найти у точки пересечения прямой со сторонойф фигуры
				if (v[prev].x > mid_x) {
					lh.push_back({ mid_x, find_y(v[prev], v[i], mid_x) });
				}
				lh.push_back(v[i]);
			}
			// если точка фигуры на предполагаемой прямой
			else { 
				lh.push_back(v[i]);
			}
		}

		ld left_area = area(lh); // площадь фигуры слева от предполагаемой прямой
		ld right_area = main_area - left_area; // площадь фигуры справа от предполагаемой прямой

		// под точностью не меньше 10^(-6) я понимаю максимальную разницу площадей фигур, полученных разделением исходной фигуры прямой
		
		// если левая площадь больше, значит искомая прямая находится левее рассмотренной на этом шаге
		if (left_area > right_area) {
			// если разница плолощадей меньше необходимой точности, то искомый х найден
			if ((left_area - right_area) < t) {
				return mid_x;
			}
			max_x = mid_x;
		}
		// и наоборот
		else {
			if ((right_area - left_area) < t) {
				return mid_x;
			}
			min_x = mid_x;
		}
	}
}

int main() {

	int n;
	cin >> n;

	vector<point> v(n);

	for (int i = 0; i < n; i++) {
		cin >> v[i].x >> v[i].y;
	}

	std::cout << std::fixed << std::setprecision(8);
	cout << cut(v, pow(10, -7)) << endl;


	return 0;
}