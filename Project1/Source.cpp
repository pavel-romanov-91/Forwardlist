#include<iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	const int n = 5;
	int arr[n] = { 3,5,8,13,21 };
	const int* const p_arr = arr;
	for (int i = 0; i < n; i++)
	{
		*(p_arr + i) *= 10;
		*p_arr *= 10;
		//cout << *p_arr << tab;
		//cout << *(p_arr + i) << tab;
		//p_arr++;
	}
	cout << endl;
}