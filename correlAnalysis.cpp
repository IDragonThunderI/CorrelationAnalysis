#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <numeric>

int main() {
	setlocale(LC_ALL, "");

	double n;
	std::vector<double> xi;
	std::vector<double> yi;

	std::wcout << L"Введите количество элементов: ";
	std::cin >> n;

	double buf;
	std::wcout << L"Введите xi: ";
	for (int i = 0; i < n; i++) {
		std::cin >> buf;
		xi.push_back(buf);
	}

	std::wcout << L"Введите yi: ";
	for (int i = 0; i < n; i++) {
		std::cin >> buf;
		yi.push_back(buf);
	}

	std::wcout << L"\n#=======================================================#\n";
	double x_ = accumulate(xi.begin(), xi.end(), 0.0) / n;
	double y_ = accumulate(yi.begin(), yi.end(), 0.0) / n;

	std::wcout << std::setw(21) << std::left << L"\nxi: " << std::right;
	for (int i = 0; i < n; i++) {
		std::wcout << std::setw(8) << std::setprecision(4) << xi.at(i);
	}
	std::wcout << std::setw(21) << std::left << L"\nyi: " << std::right;
	for (int i = 0; i < n; i++) {
		std::wcout << std::setw(8) << std::setprecision(4) << yi.at(i);
	}
	std::wcout << std::setw(21) << std::left << L"\nxi - x—: " << std::right;
	for (int i = 0; i < n; i++) {
		std::wcout << std::setw(8) << std::setprecision(4) << xi.at(i) - x_;
	}
	std::wcout << std::setw(21) << std::left << L"\nyi - y—: " << std::right;
	for (int i = 0; i < n; i++) {
		std::wcout << std::setw(8) << std::setprecision(4) << yi.at(i) - y_;
	}
	std::vector<double> xy;
	std::wcout << std::setw(21) << std::left << L"\n(xi - x—)(yi - y—): " << std::right;
	for (int i = 0; i < n; i++) {
		xy.push_back((xi.at(i) - x_) * (yi.at(i) - y_));
		std::wcout << std::setw(8) << std::setprecision(4) << xy.at(i);
	}
	std::vector<double> x2;
	std::wcout << std::setw(21) << std::left << L"\n(xi - x—)^2: " << std::right;
	for (int i = 0; i < n; i++) {
		x2.push_back(pow(xi.at(i) - x_, 2));
		std::wcout << std::setw(8) << std::setprecision(4) << x2.at(i);
	}
	std::vector<double> y2;
	std::wcout << std::setw(21) << std::left << L"\n(yi - y—)^2: " << std::right;
	for (int i = 0; i < n; i++) {
		y2.push_back(pow(yi.at(i) - y_, 2));
		std::wcout << std::setw(8) << std::setprecision(4) << y2.at(i);
	}

	std::wcout << L"\n\nx—: " << x_;
	std::wcout << L"\ny—: " << y_;

	double r = accumulate(xy.begin(), xy.end(), 0.0) / sqrt(accumulate(x2.begin(), x2.end(), 0.0) * accumulate(y2.begin(), y2.end(), 0.0));
	double t = r * (sqrt(n - 2.0) / sqrt(1.0 - pow(r, 2)));
	std::wcout << L"\n\nr: " << std::setprecision(4) << r;
	std::wcout << L"\ntв: " << std::setprecision(4) << t;

	std::wcout << L"\n\nДалее проверяете неравенство |tв| < t_alpha(n - 2) по таблице распределения Стьюдента.\n"
	<< L"Если неравенство выполняется, то гипотеза H0 принимается => коэфф. корреляции незначим и зависимости не существует."
	<< L" Поэтому регрессионный анализ не нужен и на этом задача окончена.\n";

	bool incorrect = true;
	char answer;
	while (incorrect) {
		std::wcout << L"Неравенство выполнилось? (y/n): ";
		std::cin >> answer;
		if (answer == 'y') {
			std::wcout << L"Задача выполнена.\n";
			return 0;
		}
		if (answer == 'n') {
			incorrect = false;
		}
	}

	double sy = sqrt(accumulate(y2.begin(), y2.end(), 0.0) / n);
	double sx = sqrt(accumulate(x2.begin(), x2.end(), 0.0) / n);
	std::wcout << L"\nSy: " << std::setprecision(4) << sy;
	std::wcout << L"\nSx: " << std::setprecision(4) << sx;

	std::vector<double> yTilda;
	std::wcout << std::setw(21) << std::left << L"\n\nyi~: " << std::right;
	for (int i = 0; i < n; i++) {
		yTilda.push_back(r * sy / sx * (xi.at(i) - x_) + y_);
		std::wcout << std::setw(8) << std::setprecision(4) << yTilda.at(i);
	}
	std::vector<double>  sTilda;
	std::wcout << std::setw(21) << std::left << L"\n(yi~ - y—)^2: " << std::right;
	for (int i = 0; i < n; i++) {
		sTilda.push_back(pow(yTilda.at(i) - y_, 2));
		std::wcout << std::setw(8) << std::setprecision(4) << sTilda.at(i);
	}

	double d = accumulate(sTilda.begin(), sTilda.end(), 0.0) / accumulate(y2.begin(), y2.end(), 0.0);
	double f = d * (n - 2.0) / (1.0 - d);
	std::wcout << L"\n\nd: " << std::setprecision(4) << d;
	std::wcout << L"\nFв: " << std::setprecision(4) << f;

	int k1 = 1;
	int k2 = n - 2;
	std::wcout << L"\n\nk1: " << k1;
	std::wcout << L"\nk2: " << k2;

	std::wcout << L"\n\nДалее проверяете неравенство Fв > Fкр(k1, k2) по таблице квантилий распределения Фишера.\n"
	<< L"Если неравенство выполняется, то коэфф. детерминации d статистически значим, иначе уравнение регрессии в целом статистически незначимо.";
	std::wcout << "\n";

	return 0;
}
