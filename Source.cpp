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

//��������� �����-�����
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

//�������� �� ������-����� �������(-��)
bool isSimple(string X)
{
	if (X == "4") return false; //���������� �.�. ������ �� 4 = 2, 2 < 2 � ���� � true

	//����� ������ ����� �� ��� ����� �� ���������� �� 2 �� ����� ����� �����
	//���� ���� �� ���� ���������� => ����� �� �������
	for (string i = "2"; isLessThan(i, Sqrt(X)); i = AddOne(i))
	{
		if (Mod(X, i)) return false;
	}

	return true;
}

string Sqrt(string X) //����� ������� �������������� (�������� ���� � ���������)
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

string AddOne(string X) //�������� � ������ �������, ������� ���������������� � ����������� ������ Add
{
	int iA = X.length();

	bool t = 1; // �������, 0 ��� 1

	for (int i = 0; i < iA && t; i++) //���� ���� ������� ���������� �� ���� ������ ������ ������
	{
		int s = X[iA - i - 1] + '1' - 2 * '0'; //������� �����
		X[iA - i - 1] = s % 10 + '0'; //��������� ����� ����� ���������� � ������� ������ ������
		t = s / 10; //����������, ���� �� �������
	}
	//��������� ���������� �������, ���� �� ����
	if (t) X.insert(X.begin(), '1');
	return X;
}

string Add(string A, string B) //����� ���� �����
{
	//�������� � ����������� ��������: ������� + �������
	if (A.length() < B.length()) // � A ����� ��������� ������ ������� �����
		swap(A, B);
	
	int lenA = A.length();

	//������ � ���������� �����: ��������� ������� ������
	while (B.length() < lenA)
		B.insert(B.begin(), '0');

	bool t = 0; // �������
	for (int i = 0; i < lenA; i++) //�� ���� ������-�������� ������
	{
		int s = A[lenA - i - 1] + B[lenA - i - 1] + t - 2 * '0'; //������� ����� ���� ����
		A[lenA - i - 1] = s % 10 + '0'; //��������� ����� ����� ���������� � ������� ����� ������ ������
		t = s / 10; //����������, ���� �� �������
		// - '0' ��� �������� �������� ���� ��� ����������� �������� �� ������� � �����
		// + '0' ��� ���������� �������� ���� ��� ����������� �������� �� ����� � ������
	}
	//��������� ���������� �������, ���� �� ����
	if (t) A.insert(A.begin(), '1');
	return A;
}

string Subt(string A, string B) //��������� ����� �� ������
{
	if (isLessThan(A, B)) // � A ����� ��������� ������� ����� �� ����
		swap(A, B);

	//�������� � ����������� ��������: ������� - �������
	int lenA = A.length();
	int lenB = B.length();

	for (int i = 0; i < lenB; i++) //�� ���� ������ ������
	{
		int s = A[lenA - i - 1] - B[lenB - i - 1]; //�������� �����, �������� ���� ���������� ���� � ������
		if (s < 0) //���� ��������� ������ ����, ���� ��������
		{
			int i1 = 2;
			//�� ���� �������� ������:
			while (A[lenA - i - i1] == '0')
			{
				//������ � ��������� ������ � ��������� � ��������� ����� �����
				A[lenA - i - i1] = '9'; i1++;
			}
			//�������� �������
			s += 10;
			A[lenA - i - i1]--;
		}
		A[lenA - i - 1] = s % 10 + '0'; //��������� ����� �������� ���������� � ������� ����� ������ ������
	}
	
	int zeros = 0;
	while (A[zeros] == '0') zeros++;
	if (zeros == A.length()) return "0"; //���� �������� ������ ������ �� �����
	A.erase(0, zeros);
	return A;
}

string Multiply(string A, string B) //������������ ���� �����
{
	if (A.length() < B.length()) // � A ����� ��������� ������ ������� �����
		swap(A, B);

	int lenA = A.length();
	int lenB = B.length();

	int t = 0; // �������

	string current_result = ""; //��������� ������������ ������ 1 �� ������� ����� ������ 2
	string result_sum = "0"; //����� ���� ����� ����������� � ���� �����
	int a, b; //������������� �����

	for (int i = 0; i < lenB; i++) //��� ���� ���� ������ 2
	{
		b = B[lenB - i - 1] - '0';
		for (int j = 0; j < lenA; j++) //����������� �� �� ����� ������� ������ 1
		{
			a = A[lenA - j - 1] - '0';
			int multi = a * b + t; 
			char digit = multi % 10 + '0'; //�� ������������ �������� ��������� �����
			current_result.insert(current_result.begin(), digit); //���������� ��������� � ����� ������ ����������
			t = multi / 10; //���������� ������� �������
		}
		//��������� ���������� �������, ���� �� ����
		if (t) current_result.insert(current_result.begin(), t + '0');
		t = 0;

		//���������� ������ ���� (�������� ����� ����� ��� ������������)
		for (int k = 0; k < i; k++)
			current_result.insert(current_result.end(), '0');
		
		//��������� ��� ������-���������� ������������
		result_sum = Add(result_sum, current_result);
		current_result = "";
	}
	return result_sum;
}

string Devide(string A, string B, bool mod) //������������� ������� ���� �����
{
	if (isLessThan(A, B)) return "0"; //div �������� �� ������� ����� 0
	//mod ��� ������ ������ �� ����������� � ����� 0, �� ��� �� ����������

	string subA = ""; //������� ��������� �� �, �����, ������� ����� ������ �� � � ��������� ����
	string div = ""; //div ���������, ����� ����� ������� �� �����������
	char j_char; //����� �� 1 �� 9 � ���� �������, ������� ��������� div
	string j_str; //����� �� 1 �� 9 � ���� ������, ������ j_char ��� ���������� ��������� ��������
	int zeros; //������� ����� ������� ���� � ������ ����� � ��������, ����� ����� ������� �� ���������� � ������� ������
	bool start = true; //��� ������� � �������, ������� �� ��������� ����, � ����� ����� ���������

	//� ������� ����� (�������� ��� ����������) ���������� �� ���� ������
	for (int i = 0; i < A.length(); i++)
	{
		//��������� ����� ������, ���� ��������� ���� � �������� �������
		if (subA == "0" && A[i] == '0')
		{
			div.insert(div.end(), '0');
			continue;
		}

		//�������� ����� (�������� ����� �����, ������� ��������� �� ��������)
		subA.insert(subA.end(), A[i]);

		//� subA ����� ������� if ����� ���������� ����, ������� ��
		zeros = 0;
		while (subA[zeros] == '0') zeros++;
		if (zeros > 0) subA.erase(0, zeros);

		//���� �������� � �, ������� ������ ��� ����� ��������
		if (isLessThan(subA, B))
		{
			if (start) continue; //��������� �� ���� � ������� � ����� ������ ������
			//�������� �� ���� � �������, �������� ���������� �������� ���� � �����
			if (A.length() > 0) div.insert(div.end(), '0');
			continue;
		}

		//"�����" ��� �������� �� ��������, ��������� ������������ B*2, B*3, B*4, ..., B*10
		for (int j = 2; j <= 10; j++)
		{
			j_char = j + '0';
			j_str = string(1, j_char); //����������

			//���� B*j ��������� ��������, ������ �� ����� ��������� ����� ��� ������
			if (isLessThan(subA, Multiply(B, j_str)))
			{
				//������ ���������� �������� j ��� ��������� ����� ������ div �.�. j - 1
				j_char = j - 1 + '0';
				j_str = string(1, j_char);

				//��������� ����� � ����� ������ ������
				div.insert(div.end(), j_char);

				//� A ���� ����� �������� ����
				zeros = 0;
				while (A[zeros] == '0') zeros++;
				if (zeros > 0) A.erase(0, zeros);

				//������� �������������� �������� �� ������ ��������� ����� �, ����� ������������ �����, ����������
				A.erase(0, subA.length());

				//������� ������� ����� ������������� ������� (���������� ����, ��� ��� ������� � ������� ���� ����� "�������" ����������)
				subA = Subt(subA, Multiply(B, j_str));

				if (subA == "0") //���� � ������� ��������� 0, ��� �� ���� ���������� � ������ ��������� �����
				{
					i = -1; //�������� ����� � i=0 (����� break ��������� i++ � i ������ ������ 0)
				}
				else
				{
					//���������� �������� � ������ ��������� ����������� ����� � ��������� ���������, ����� �� �������� ���
					A = subA + A;
					//��������� ���� ����� � ����� �����-������� � �������� ������, ������� ��� ����� ����� ����������� ���� �����
					//����� ����� ���������� i++ � i ������ ������ subA.length(), ��� ��� ��� ����� ����� ���� ���� subA � ������ ������ A
					i = subA.length() - 1;
				}	
				start = false; //������ ����� ��������� �� ���� � �������
				break;
			}
		}
	}
	if (mod) return subA; //���� �������� mod=true, ������ div ���������� mod, ������� �������� � ��������� ����������� subA
	return div;
}

bool Mod(string A, string B) //������� �� ����� A ������ �� �
{
	string mod = Devide(A, B, true);
	if (mod == "0") return true;
	return false;
}

void printMultipliers(string X) //������ ����������
{
	if (!isSimple(X)) //���� ����� � �� �������
	{
		for (string i = "2"; isLessThan(i, X); i = AddOne(i)) //���������� ��� ����� �� 2 �� 
		{
			if (isSimple(i)) //���� ��� ����� �������, ��� ����� ���� ����������
			{
				while (Mod(X, i)) //����� �� ���� ��������� ��� �� ��� ���, ���� ������� ������
				{
					X = Devide(X, i, false); //����� �������� �� ����
					cout << i << " x "; //������ �����������

					if (isSimple(X)) //���� � ����� �������
					{
						cout << X << endl; //��������� ��������� - ���� �����, ������� ������� ������
						return;
					}
				}
			}
		}
	}
	cout << X << endl; //��������� ��������� - ���� �����, ������� ������� ������
}


bool Check(string str) //�������� �� ������
{
	for (int i = 0; i < str.length(); i++) //��� ���� ����-�������� ������
		if (str[i] < '0' || str[i] > '9') //���� ������� ������ ����� ��� �������� 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
		{
			cout << "����� �� ������ ���� ������������� � ��������� �������, �������� �� ����.\n��������� ����: ";
			return false;
		}
	return str.length(); //���� ������ ������, ����� false, ����� true
}

int main() 
{
	SetConsoleOutputCP(1251);
	
	string input;
	cout << "������� �����: ";

	do
	{
		cin >> input;
	} while (!Check(input));
	
	cout << "��������..." << endl;

	printMultipliers(input);

	cout << "������!";
	system("pause>nul");
	return 0;
}