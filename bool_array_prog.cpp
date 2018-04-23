#include <iostream>
#include "bool_array.cpp"

int main()
{
	bool_array t;


	t.dump("stdout");

	for (int i = 8; i < 16; ++i)
	{
		cout << t[i];
	}
	cout << endl;

	t[0] = 1;
	return 0;
}