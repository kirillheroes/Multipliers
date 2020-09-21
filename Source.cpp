#include <string>
#include <iostream> 
#include <windows.h>
using namespace std;

bool isLessThan(string, string);
bool isLessOrEqualThan(string, string);
string AddOne(string);
bool isSimple(string);
string Devide(string, string, bool);
bool Mod(string, string);
void printMultipliers(string);
bool Check(string);
string Sqrt(string);
string Add(string, string);
string Multiply(string, string);
string Subt(string, string);

//сравнение строк-чисел
bool isLessThan(string x, string y)
{
	if (x.length() < y.length()) return true;
	if (x.length() > y.length()) return false;
	return x < y;
}

bool isLessOrEqualThan(string x, string y)
{
	if (x.length() < y.length()) return true;
	if (x.length() > y.length()) return false;
	return x <= y;
}

//является ли строка-число простой(-ым)
bool isSimple(string X)
{
	if (X == "4") return false; //исключение т.к. корень из 4 = 2, 2 < 2 и уйдёт в true

	//делим данное число на все числа из промежутка от 2 до корня этого числа
	//если хоть на одно поделилось => число не простое
	for (string i = "2"; isLessThan(i, Sqrt(X)); i = AddOne(i))
	{
		if (Mod(X, i)) return false;
	}

	return true;
}

string Sqrt(string X) //через плошадь прямоугольника (алгоритм взят в Интернете)
{
	string height = "1";
	string width = X;
	
	while (isLessThan("1", Subt(width, height)))
	{
		height = Devide(Add(width, height), "2", false);
		width = Devide(X, height, false);
	}
	return height;
}

string AddOne(string X) //прибавка к строке единицы, немного оптимизированная и укороченная версия Add
{
	int iA = X.length();

	bool t = 1; // десятки, 0 или 1

	for (int i = 0; i < iA && t; i++) //пока есть десятки проходимся по всем цифрам справа налево
	{
		int s = X[iA - i - 1] + '1' - 2 * '0'; //считаем сумму
		X[iA - i - 1] = s % 10 + '0'; //последнюю цифру суммы записываем в текущий символ строки
		t = s / 10; //определяем, есть ли десятки
	}
	//добавляем оставшийся десяток, если он есть
	if (t) X.insert(X.begin(), '1');
	return X;
}

string Add(string A, string B) //сумма двух строк
{
	//приводим к нормальному столбику: большее + меньшее
	if (A.length() < B.length()) // в A будет храниться строка большей длины
		swap(A, B);
	
	int lenA = A.length();

	//привод к одинаковой длине: заполняем меньшее нулями
	while (B.length() < lenA)
		B.insert(B.begin(), '0');

	bool t = 0; // десятки
	for (int i = 0; i < lenA; i++) //по всем цифрам-символам строки
	{
		int s = A[lenA - i - 1] + B[lenA - i - 1] + t - 2 * '0'; //считаем сумму двух цифр
		A[lenA - i - 1] = s % 10 + '0'; //последнюю цифру суммы записываем в текущую цифру первой строки
		t = s / 10; //определяем, есть ли десятки
		// - '0' это удаление терминал нуля для корректного перехода от символа в число
		// + '0' это добавление терминал нуля для корректного перехода из числа в символ
	}
	//добавляем оставшийся десяток, если он есть
	if (t) A.insert(A.begin(), '1');
	return A;
}

string Subt(string A, string B) //вычитание строк по модулю
{
	if (isLessThan(A, B)) // в A будет храниться большее число из двух
		swap(A, B);

	//приводим к нормальному столбику: большее - меньшее
	int lenA = A.length();
	int lenB = B.length();

	for (int i = 0; i < lenB; i++) //по всем цифрам строки
	{
		int s = A[lenA - i - 1] - B[lenB - i - 1]; //вычитаем цифры, терминал нули вычитаются друг с другом
		if (s < 0) //если результат меньше нуля, надо занимать
		{
			int i1 = 2;
			//из нуля занимать нельзя:
			while (A[lenA - i - i1] == '0')
			{
				//ставим в результат девять и переходим к следующей слева цифре
				A[lenA - i - i1] = '9'; i1++;
			}
			//занимаем десяток
			s += 10;
			A[lenA - i - i1]--;
		}
		A[lenA - i - 1] = s % 10 + '0'; //последнюю цифру разности записываем в текущую цифру первой строки
	}
	
	int zeros = 0;
	while (A[zeros] == '0') zeros++;
	if (zeros == A.length()) return "0"; //если получили строку только из нулей
	A.erase(0, zeros);
	return A;
}

string Multiply(string A, string B) //перемножение двух строк
{
	if (A.length() < B.length()) // в A будет храниться строка большей длины
		swap(A, B);

	int lenA = A.length();
	int lenB = B.length();

	int t = 0; // десятки

	string current_result = ""; //результат перемножения строки 1 на текущую цифру строки 2
	string result_sum = "0"; //сумма всех таких результатов и есть ответ
	int a, b; //перемножаемые цифры

	for (int i = 0; i < lenB; i++) //для всех цифр строки 2
	{
		b = B[lenB - i - 1] - '0';
		for (int j = 0; j < lenA; j++) //перемножаем их со всеми цифрами строки 1
		{
			a = A[lenA - j - 1] - '0';
			int multi = a * b + t; 
			char digit = multi % 10 + '0'; //от произведения отсекаем последнюю цифру
			current_result.insert(current_result.begin(), digit); //записываем результат в конец строки результата
			t = multi / 10; //определяем наличие десяток
		}
		//добавляем оставшийся десяток, если он есть
		if (t) current_result.insert(current_result.begin(), t + '0');
		t = 0;

		//дописываем справа нули (смещение строк влево при произведении)
		for (int k = 0; k < i; k++)
			current_result.insert(current_result.end(), '0');
		
		//суммируем все строки-результаты произведений
		result_sum = Add(result_sum, current_result);
		current_result = "";
	}
	return result_sum;
}

string Devide(string A, string B, bool mod) //целочисленное деление двух строк
{
	if (isLessThan(A, B)) return "0"; //div меньшего на большее равен 0
	//mod для такого случая не вычисляется и равен 0, он нам не пригодится

	string subA = ""; //текущая подстрока из А, число, которое будем делить на В в очередном шаге
	string div = ""; //div результат, числа после запятой не вычисляются
	char j_char; //число от 1 до 9 в виде символа, будущий результат div
	string j_str; //число от 1 до 9 в виде строки, аналог j_char для выполнения строковых операций
	int zeros; //нередко будем стирать нули в начале чисел и подчисел, здесь будем хранить их количество в текущий момент
	bool start = true; //для деления в частном, сначала не добавляем нули, а потом будем добавлять

	//в текущем числе (исходном или обрезанном) проходимся по всем цифрам
	for (int i = 0; i < A.length(); i++)
	{
		//заполняем ответ нулями, если встречаем нули и подчисло нулевое
		if (subA == "0" && A[i] == '0')
		{
			div.insert(div.end(), '0');
			continue;
		}

		//подчисло растёт (выделяем такое число, которое поделится на делитель)
		subA.insert(subA.end(), A[i]);

		//в subA после первого if могут накопиться нули, удаляем их
		zeros = 0;
		while (subA[zeros] == '0') zeros++;
		if (zeros > 0) subA.erase(0, zeros);

		//ищем подчисло в А, которое больше или равно делителю
		if (isLessThan(subA, B))
		{
			if (start) continue; //проверять на ноль в частном в самом начале нельзя
			//проверка на ноль в частном, возможно необходимо дописать нуль в ответ
			if (A.length() > 0) div.insert(div.end(), '0');
			continue;
		}

		//"делим" это подчисло на делитель, перебирая произведения B*2, B*3, B*4, ..., B*10
		for (int j = 2; j <= 10; j++)
		{
			j_char = j + '0';
			j_str = string(1, j_char); //наЯндексил

			//если B*j превзошло подчисло, значит мы нашли очередную цифру для ответа
			if (isLessThan(subA, Multiply(B, j_str)))
			{
				//значит предыдущее значение j это очередная цифра ответа div т.е. j - 1
				j_char = j - 1 + '0';
				j_str = string(1, j_char);

				//добавляем цифру в конец строки ответа
				div.insert(div.end(), j_char);

				//в A тоже могли остаться нули
				zeros = 0;
				while (A[zeros] == '0') zeros++;
				if (zeros > 0) A.erase(0, zeros);

				//удаляем использованное подчисло из начала исходного числа А, чтобы сформировать новое, обрезанное
				A.erase(0, subA.length());

				//считаем разницу между получившимися числами (аналогично тому, как при делении в столбик вниз растёт "лесенка" вычислений)
				subA = Subt(subA, Multiply(B, j_str));

				if (subA == "0") //если в разнице получился 0, его не надо записывать в начало исходного числа
				{
					i = -1; //стартуем вновь с i=0 (после break произойдёт i++ и i станет равным 0)
				}
				else
				{
					//необходимо дописать в начало исходного обрезанного числа А результат вычитания, чтобы не потерять его
					A = subA + A;
					//следующий счёт начнём с такой цифры-символа в исходной строке, которая идёт сразу после вставленной нами части
					//после этого выполнится i++ и i станет равным subA.length(), это как раз сразу после всех цифр subA в начале строки A
					i = subA.length() - 1;
				}	
				start = false; //теперь можем проверять на ноль в частном
				break;
			}
		}
	}
	if (mod) return subA; //если передали mod=true, вместо div возвращаем mod, который хранится в последнем посчитанном subA
	return div;
}

bool Mod(string A, string B) //делится ли число A нацело на В
{
	string mod = Devide(A, B, true);
	if (mod == "0") return true;
	return false;
}

void printMultipliers(string X) //печать множителей
{
	if (!isSimple(X)) //если число Х не простое
	{
		for (string i = "2"; isLessThan(i, X); i = AddOne(i)) //перебираем все числа от 2 до 
		{
			if (isSimple(i)) //если это число простое, оно может быть множителем
			{
				while (Mod(X, i)) //делим на него множество раз до тех пор, пока делится нацело
				{
					X = Devide(X, i, false); //делим исходное на него
					cout << i << " x "; //печать результатов

					if (isSimple(X)) //если Х стало простым
					{
						cout << X << endl; //последний множитель - само число, ставшее простым числом
						return;
					}
				}
			}
		}
	}
	cout << X << endl; //последний множитель - само число, ставшее простым числом
}


bool Check(string str) //проверка на дурака
{
	for (int i = 0; i < str.length(); i++) //для всех цифр-символов строки
		if (str[i] < '0' || str[i] > '9') //если текущий символ лежит вне пределов 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
		{
			cout << "Число не должно быть отрицательным и содержать символы, отличные от цифр.\nПовторите ввод: ";
			return false;
		}
	return str.length(); //если строка пустая, вернёт false, иначе true
}

int main() 
{
	SetConsoleOutputCP(1251);
	
	string input;
	cout << "Введите число: ";

	do
	{
		cin >> input;
	} while (!Check(input));
	
	cout << "Вычисляю..." << endl;

	printMultipliers(input);

	cout << "Готово!";
	system("pause>nul");
	return 0;
}