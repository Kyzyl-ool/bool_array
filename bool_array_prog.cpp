#include <iostream>
#include "bool_array.cpp"

int main()
{
	bool_array t(4);

	for (int i = 0; i < t.length(); i += 5)
	{
		t.set_true(i);
	}
	t.set_false(8);


	t.dump("stdout");

	for (int i = 0; i < 8; ++i)
	{
		cout << t[i];
	}
	cout << endl;
	return 0;
}