#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <numeric>
using namespace std;

int main()
{
	double n;
	vector<double> xi;
	vector<double> yi;

	wcout << L"Введите количество элементов: ";
	cin >> n;

	double buf;
	wcout << L"Введите xi: ";
	for (int i = 0; i < n; i++)
	{
		cin >> buf;
		xi.push_back(buf);
	}

	wcout << L"Введите yi: ";
	for (int i = 0; i < n; i++)
	{
		cin >> buf;
		yi.push_back(buf);
	}

	wcout << L"\n#=======================================================#\n";
	double x_ = accumulate(xi.begin(), xi.end(), 0.0) / n;
	double y_ = accumulate(yi.begin(), yi.end(), 0.0) / n;

	wcout << setw(21) << left << L"\nxi: " << right;
	for (int i = 0; i < n; i++)
	{
		wcout << setw(8) << setprecision(4) << xi.at(i);
	}
	wcout << setw(21) << left << L"\nyi: " << right;
	for (int i = 0; i < n; i++)
	{
		wcout << setw(8) << setprecision(4) << yi.at(i);
	}
	wcout << setw(21) << left << L"\nxi - x—: " << right;
	for (int i = 0; i < n; i++)
	{
		wcout << setw(8) << setprecision(4) << xi.at(i) - x_;
	}
	wcout << setw(21) << left << L"\nyi - y—: " << right;
	for (int i = 0; i < n; i++)
	{
		wcout << setw(8) << setprecision(4) << yi.at(i) - y_;
	}
	vector<double> xy;
	wcout << setw(21) << left << L"\n(xi - x—)(yi - y—): " << right;
	for (int i = 0; i < n; i++)
	{
		xy.push_back((xi.at(i) - x_) * (yi.at(i) - y_));
		wcout << setw(8) << setprecision(4) << xy.at(i);
	}
	vector<double> x2;
	wcout << setw(21) << left << L"\n(xi - x—)^2: " << right;
	for (int i = 0; i < n; i++)
	{
		x2.push_back(pow(xi.at(i) - x_, 2));
		wcout << setw(8) << setprecision(4) << x2.at(i);
	}
	vector<double> y2;
	wcout << setw(21) << left << L"\n(yi - y—)^2: " << right;
	for (int i = 0; i < n; i++)
	{
		y2.push_back(pow(yi.at(i) - y_, 2));
		wcout << setw(8) << setprecision(4) << y2.at(i);
	}

	wcout << L"\n\nx—: " << x_;
	wcout << L"\ny—: " << y_;

	double r = accumulate(xy.begin(), xy.end(), 0.0) / sqrt(accumulate(x2.begin(), x2.end(), 0.0) * accumulate(y2.begin(), y2.end(), 0.0));
	double t = r * (sqrt(n - 2.0) / sqrt(1.0 - pow(r, 2)));
	wcout << L"\n\nr: " << setprecision(4) << r;
	wcout << L"\ntв: " << setprecision(4) << t;

	wcout << L"\n\nДалее проверяете неравенство |tв| < t_alpha(n - 2) по таблице распределения Стьюдента.\n"
	<< L"Если неравенство выполняется, то гипотеза Ho принимается => коэфф. корелляции незначим и зависимости не существует."
	<< L" Поэтому регрессионный анализ не нужен и на этом задача окончена.\n";

	bool incorrect = true;
	char answer;
	while (incorrect)
	{
		wcout << L"Неравенство выполнилось? (y/n): ";
		cin >> answer;
		if (answer == 'y')
		{
			wcout << L"Задача выполнена.\n";
			return 0;
		}
		if (answer == 'n')
			incorrect = false;
	}

	double sy = sqrt(accumulate(y2.begin(), y2.end(), 0.0) / n);
	double sx = sqrt(accumulate(x2.begin(), x2.end(), 0.0) / n);
	wcout << L"\nSy: " << setprecision(4) << sy;
	wcout << L"\nSx: " << setprecision(4) << sx;

	vector<double> yTilda;
	wcout << setw(21) << left << L"\n\nyi~: " << right;
	for (int i = 0; i < n; i++)
	{
		yTilda.push_back(r * sy / sx * (xi.at(i) - x_) + y_);
		wcout << setw(8) << setprecision(4) << yTilda.at(i);
	}
	vector<double>  sTilda;
	wcout << setw(21) << left << L"\n(yi~ - y—)^2: " << right;
	for (int i = 0; i < n; i++)
	{
		sTilda.push_back(pow(yTilda.at(i) - y_, 2));
		wcout << setw(8) << setprecision(4) << sTilda.at(i);
	}

	double d = accumulate(sTilda.begin(), sTilda.end(), 0.0) / accumulate(y2.begin(), y2.end(), 0.0);
	double f = d * (n - 2.0) / (1.0 - d);
	wcout << L"\n\nd: " << setprecision(4) << d;
	wcout << L"\nFв: " << setprecision(4) << f;

	int k1 = 1;
	int k2 = n - 2;
	wcout << L"\n\nk1: " << k1;
	wcout << L"\nk2: " << k2;

	wcout << L"\n\nДалее проверяете неравенство Fв > Fкр(k1, k2) по таблице квантилий распределения Фишера.\n"
	<< L"Если неравенство выполняется, то коэфф. детерминации d статистически значим, иначе уравнение регрессии в целом статистически незначимо.";
	wcout << "\n";

	return 0;
}
