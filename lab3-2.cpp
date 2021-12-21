#include <iostream>
using namespace std;

// Шаблонный класс Вектор
// Первый параметр - тип данных, второй - размерность вектора (не шаблон)
template<class T, size_t _dimension>
class Vector {

private:
	// Создание статического массива заданной размерности и типа
	T _data[_dimension];

public:
	// Конструктор, использущий initializer_list
	// Нужен для инициализации вектора как массива с помощью скобок {} 
	Vector(const std::initializer_list<T>& list)
	{
		size_t i = 0;
		for (const auto& element : list) {
			_data[i++] = element;
		}
	}
	// Перегрузка оператора присваивания с тем же initializer_list
	// для того присваивать значения через {}
	Vector& operator= (const std::initializer_list<T>& list) {
		size_t i = 0;
		for (const auto& element : list) {
			_data[i++] = element;
		}

		return *this;
	}

	// Возвращает длину вектора
	// Формула длины вектора = Корень из суммы квадратов координат вектора
	double length() const {
		// Подсчет суммы квадратов
		T sum = 0;
		for (const T& coor : _data) {
			sum += coor*coor; 
			//pow() не сработал. Ошибка: "нет перегруженной функции, принимающей 1 аргументов"
		}
		// Возвращаем корень суммы
		return sqrt(sum);
	}

	// Возвращает размерность
	size_t dimension() const { return _dimension; }

	// Возвращает длину между векторами
	// Формула: корень из суммы квадратов разностей координат векторов
	double distanceBetween(Vector& other) const {
		// Вывод ошибки если вектора разной размерности и выход
		if (_dimension != other.dimension()) {
			std::cout << "ERROR: vectors are in different dimensions\n";
			exit(1);
		}
		// Считаем сумму квадратов разностей
		T sum = 0;
		for (int i = 0; i < _dimension; i++) {
			sum += (other[i] - _data[i]) * (other[i] - _data[i]);
		}

		// возращаем корень суммы
		return sqrt(sum);
	}

	// Метод доступа к элементу массива (возращает копию данных, т.е. их нельзя изменить)
	T at(int index) const { return _data[index]; }
	// перегрузка оператора доступа к элементу массива (возвращает по ссылке, данные можно изменить)
	T& operator[](int index) { return _data[index]; }

	// Gерегрузка оператора вывода - печатает данные в виде "[a, b, c]"
	friend std::ostream& operator<< (std::ostream& out, const Vector& vec) {
		out << "[";
		for (size_t i = 0; i < vec.dimension() - 1; i++) {
			out << vec.at(i) << ", ";
		}
		out << vec.at(vec.dimension() - 1) << "]";

		return out;
	}
};

int main() {

	double x, y, z; // Создание переменных для ввода координат векторов
	/* TODO: Сделать ввод координат красивее.Может быть через метод.А то выглядит ужасно. */ 
	cout << "Enter coordinates of the first vector\n"; //Запрос на ввод координат первого вектора
	cout << "Enter X: ";
	cin >> x;
	cout << "Enter Y: ";
	cin >> y;
	cout << "Enter Z: ";
	cin >> z;
	Vector<double, 3> vec1{ x, y, z }; //Создание координат через конструктор
	cout << "Vector 1: " << vec1 << "\n"; //Вывод вектора
	cout << "<=======================>\n\n";

	cout << "Enter coordinates of the second vector\n"; //Запрос на ввод координат первого вектора
	cout << "Enter X: ";
	cin >> x;
	cout << "Enter Y: ";
	cin >> y;
	cout << "Enter Z: ";
	cin >> z;
	Vector<double, 3> vec2 = { x, y, z }; //Создание координат через operator=
	cout << "Vector 2: " << vec2 << "\n"; //Вывод вектора
	cout << "<=======================>\n\n";

	// Вывод векторов и их длин
	cout << "Vector 1 " << vec1 << " has a length " << vec1.length() << endl;
	cout << "Vector 2 " << vec2 << " has a length " << vec2.length() << endl;

	// Вывод расстояния между векторами
	cout << "Distance between Vector 1 and Vector 2: " << vec1.distanceBetween(vec2);

	return 0;
}