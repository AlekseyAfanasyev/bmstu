#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;
typedef enum { FIXED, SCIENTIFIC } FORMAT;

const int exampleSize = 3;
const double example[exampleSize][exampleSize] = { {2, 5, 7}, {3, 9, 15}, {5, 16, 20} };

template <typename T>
void printArray(T** arr, int N, int M, int n, FORMAT f) {
	if (arr == nullptr) return;
	int field_l;
	switch (f) {
	case FIXED:
		cout << fixed;
		field_l = to_string(int(max(arr, (arr + N) + M))).size() + 2 + n;
		break;
	case SCIENTIFIC:
		cout << scientific;
		field_l = n + 10;
		break;
	}
	cout.precision(n);
	int rows_per_screen = floor(80.0 / (field_l + 2));
	int start = 0;

	while (start < N) {
		for (int j = start; j < min(N, start + rows_per_screen); ++j) {
			cout << setw(field_l) << j + 1 << "  ";
		}
		cout << endl;
		for (int i = 0; i < N; ++i) {
			for (int j = start; j < min(N, start + rows_per_screen); ++j) {
				cout << setw(field_l) << arr[i][j] << "  ";
			}
			cout << endl;
		}

		start += rows_per_screen;
	}

}

template <typename T>
T** clone(T** arr, int n)
{
	T** newArr = new T* [n];
	for (int row = 0; row < n; row++)
	{
		newArr[row] = new T[n];
		for (int col = 0; col < n; col++)
			newArr[row][col] = arr[row][col];
	}
	return newArr;
}

template <typename T> 
T** getMatrixWithoutOneRowAndColumn(T** matrix, int row, int col, int N) {
	T** newMatrix = new T * [N-1];
	for (int i = 0; i < N - 1; ++i)
		newMatrix[i] = new T[N - 1];
	for (int i = 0; i < N; ++i) {
		if (i == row) continue;
		for (int j = 0; j < N; ++j) {
			if (j == col) continue;
			newMatrix[i - (i > row)][j - (j > col)] = matrix[i][j];
		}
	}
	return newMatrix;
}

// определитель матрицы
template <typename T>
double det(T** matrix, int N) {
	if (N == 1) {
		return matrix[0][0];
	} else if (N == 2) {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	} else {
		int d = 0;
		int k = 1; // для (-1) в степени
		for (int i = 0; i < N; ++i) {
			d += k * matrix[i][0] * det(getMatrixWithoutOneRowAndColumn(matrix, i, 0, N), N-1);
			k = -k;
		}

		return d;
	}
}

template <typename T>
T** getMultMatrixByMatrix(T** A, T** B, int N) {
	T** result = new T * [N];
	for (int i = 0; i < N; ++i) {
		result[i] = new T[N];
		for (int j = 0; j < N; ++j) {
			result[i][j] = 0;
		}
	}

	for (int row = 0; row < N; ++row) {
		for (int col = 0; col < N; ++col) {
			for (int i = 0; i < N; ++i) {
				result[row][col] += A[row][i] * B[i][col];
			}
		}
	}

	return result;
}

template <typename T>
T** getInverseMatrix(T** m, int N) {
	if (!det(m, N)) {
		cout << "Обратная матрица не существует!" << endl;
		return nullptr;
	}
	T** matrix = clone(m, N);
	T** E = new T * [N];
	for (int i = 0; i < N; ++i) {
		E[i] = new T[N];
		for (int j = 0; j < N; ++j) {
			E[i][j] = (i == j);
		}
	}

	// прямой ход
	for (int row = 0; row < N; ++row) {
		T starting = matrix[row][row];
		if (!starting) {
			bool isFound = 0;
			for (int i = row + 1; i < N; ++i) {
				if (matrix[i][row]) {
					for (int j = 0; j < N; ++j) {
						swap(matrix[i][j], matrix[row][j]);
						swap(E[i][j], E[row][j]);
					}
					isFound = true;
					break;
				}
			}
			if (!isFound) {
				cout << "Обратная матрица не существует!" << endl;
				return nullptr;
			}
			starting = matrix[row][row];
		}
		for (int i = row; i < N; ++i) {
			matrix[row][i] /= starting;
		}
		for (int i = 0; i < N; ++i)
			E[row][i] /= starting;

		for (int i = row + 1; i < N; ++i) {
			const T k = matrix[i][row];
			for (int j = 0; j < N; ++j) {
				matrix[i][j] -= matrix[row][j] * k;
				E[i][j] -= E[row][j] * k;
			}
		}
	}

	// обратный ход
	for (int row = 1; row < N; ++row) {
		for (int i = 0; i < row; ++i) {
			const T k = matrix[i][row];	
			for (int j = 0; j < N; ++j) {
				matrix[i][j] -= matrix[row][j] * k;
				E[i][j] -= E[row][j] * k;
			}
		}
	}

	return E;
}

template <typename T>
T* solveEquation(T** m, T* b, int N) {
	T** matrix = clone(m, N);
	T** E = new T * [N];
	for (int i = 0; i < N; ++i) {
		E[i] = new T[N];
		for (int j = 0; j < N; ++j) {
			E[i][j] = (i == j);
		}
	}
	
	for (int row = 0; row < N; ++row) {
		T starting = matrix[row][row];
		if (!starting) {
			bool isFound = 0;
			for (int i = row + 1; i < N; ++i) {
				if (matrix[i][row]) {
					for (int j = 0; j < N; ++j) {
						swap(matrix[i][j], matrix[row][j]);
						swap(E[i][j], E[row][j]);
					}
					swap(b[i], b[row]);
					isFound = true;
					break;
				}
			}
			if (!isFound) {
				cout << "Обратная матрица не существует!" << endl;
				return nullptr;
			}
			starting = matrix[row][row];
		}
		for (int i = row; i < N; ++i) {
			matrix[row][i] /= starting;
		}
		b[row] /= starting;
		for (int i = 0; i < N; ++i)
			E[row][i] /= starting;

		for (int i = row + 1; i < N; ++i) {
			const T k = matrix[i][row];
			b[i] -= b[row] * k;
			for (int j = 0; j < N; ++j) {
				matrix[i][j] -= matrix[row][j] * k;
				E[i][j] -= E[row][j] * k;

			}
		}
	}

	T* x = new T[N];

	x[N - 1] = b[N - 1];

	for (int i = N - 2; i >= 0; --i) {
		x[i] = b[i];
		for (int j = i + 1; j < N; ++j) {
			x[i] -= x[j] * matrix[i][j];
		}
	}

	return x;
}

short menu() {
	cout << "===================Menu=================\n";
	cout << "| 1 - Заполнение матриц                |\n";
	cout << "| 2 - Нахождение обратной матрицы      |\n";
	cout << "| 3 - Перемножение матриц (A*A^(-1))   |\n";
	cout << "| 4 - Решение СЛАУ (A*x = B)           |\n";
	cout << "| 5 - Задать параметры вывода          |\n";
	cout << "| 6 - Выход                            |\n";
	cout << "========================================\n";
	cout << "Выберите номер:\n";
	int choice;
	cin >> choice;
	while (cin.fail()) {
		cout << "Ошибка ввода. Повторите ввод\n";
		cin.clear();
		cin.ignore(10, '\n');
		cin >> choice;
	}
	return choice;
}

template <typename T, int N>
T** copyConstMatrix(const T source[N][N]) {
	T** dest = new T * [N];
	for (int i = 0; i < N; ++i) {
		dest[i] = new T[N];
		for (int j = 0; j < N; ++j) {
			dest[i][j] = source[i][j];
		}
	}

	return dest;
}

template <typename T>
T** inputMatrix(int N) {
	T** matrix = new T * [N];
	for (int i = 0; i < N; ++i) {
		matrix[i] = new T[N];
		for (int j = 0; j < N; ++j) {
			cin >> matrix[i][j];
		}
	}

	return matrix;
}

template <typename T>
void fillArray(T*** A, int& N) {
	cout << "1 - Загрузить тестовый пример" << endl;
	cout << "2 - Ввести с клавиатуры" << endl;
	int choice; cin >> choice;
	switch (choice) {
	case 1:
		*A = copyConstMatrix<double, 3>(example);
		N = 3;
		break;
	case 2:
		cout << "Введите размер матрицы" << endl;
		cin >> N;
		if (N < 1) {
			cout << "Введён N < 1. Будет использоваться N = 2." << endl;
			N = 2;
		}
		cout << "Введите элементы матрицы\n";
		*A = inputMatrix<T>(N);
		break;
	}
}

int main()
{
	double** A = nullptr;
	double* B = nullptr;
	double* eq = nullptr;
	
	int N = 0;
	int n = 3; FORMAT f = FIXED;
	
	system("chcp 1251 > nul");
	
	while (true) {
		short choice = menu();
		system("cls");
		switch (choice) {
		case 1:
			fillArray(&A, N);
			break;
		case 2:
			cout << "Исходная матрица:\n";
			printArray(A, N, N, n, f);
			cout << "\nОбратная:\n";
			printArray(getInverseMatrix(A, N), N, N, n, f);
			break;
		case 3:
			cout << "Матрица A:\n";
			printArray(A, N, N, n, f);
			cout << "\nМатрица A^(-1):\n";
			printArray(getInverseMatrix(A, N), N, N, n, f);
			cout << "\nМатрица A*B:\n";
			printArray(getMultMatrixByMatrix(A, getInverseMatrix(A, N), N), N, N, n, f);
			break;
		case 4:
			cout << "Введите столбец свободных членов\n";
			cout << "( " << N << " элементов)\n";
			B = new double[N];
			for (int i = 0; i < N; ++i) {
				cin >> B[i];
			}
			eq = solveEquation(A, B, N);
			if (f == FIXED)
				cout << fixed;
			else
				cout << scientific;
			cout.precision(n);

			for (int i = 0; i < N; ++i) {
				
				cout << "X" << i << " = " << eq[i] << '\n';
			}
			break;
		case 5:
			cout << "Выберите формат вывода:\n";
			cout << "0 - fixed\n";
			cout << "1 - scientific\n";
			short int temp_f; cin >> temp_f;
			if ((temp_f < 0) || (temp_f > 1)) {
				cout << "Введены некорректные данные.\n";
				cout << "Будет использоваться формат fixed.\n";
				temp_f = 0;
			}
			f = static_cast <FORMAT> (temp_f);

			cout << "Введите количество знаков после запятой для вывода\n";
			cin >> n;
			if (n <= 0) {
				cout << "Введены некорректные данные.\n";
				cout << "Будет использоваться n = 5\n";
				n = 5;
			}
			break;
		case 6:
			return 0;
			break;
		default:
			cout << "Нет такой команды. Нажмите 6 для выхода\n";
			break;
		}
		system("pause & cls");
	}
}