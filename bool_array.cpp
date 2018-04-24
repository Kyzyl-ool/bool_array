#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <fstream>

using std::calloc;

class helping_class
{
public:
	char* data;
	char number;
	void operator=(bool value);
};

class bool_array
{
private:
	char* data; unsigned int count;
	unsigned int count_of_blocks;
public:
	bool_array();
	bool_array(int n);
	~bool_array();

	unsigned int length();

	void expand();
	void strip();

	helping_class operator[](unsigned int n);
	char operator=(bool value);
	void set_true(int n);
	void set_false(int n);
	void append(bool value);
	
	void dump(std::string output_name);
};

bool_array::bool_array():
count_of_blocks(1)
{
	data = (char* )calloc(1, sizeof(char));
}

bool_array::bool_array(int n):
count_of_blocks(n)
{
	data = (char* )calloc(n, sizeof(char));
}

bool_array::~bool_array()
{
	free(data);
}

void bool_array::expand()
{
	count_of_blocks++;
	char* tmp = (char* )malloc(count_of_blocks*sizeof(char));
	for (int i = 0; i < count_of_blocks - 1; ++i)
	{
		tmp[i] = data[i];
	}
	tmp[count_of_blocks] = 0;

	free(data);
	data = tmp;
}

void bool_array::strip()
{
	count_of_blocks--;
	char* tmp = (char* )malloc(count_of_blocks*sizeof(char));
	for (int i = 0; i < count_of_blocks; ++i)
	{
		tmp[i] = data[i];
	}
	free(data);
	data = tmp;
}

// bool bool_array::operator[](unsigned int n)
// {
// 	if (n >= count_of_blocks*8)
// 	{
// 		assert(!"ВЫХОД ЗА ПРЕДЕЛЫ БУЛЕВСКОГО МАССИВА");
// 	}

// 	return (data[n/8] & (1 << (n%8)));
// }

using std::cout;
using std::endl;
using std::ofstream;
void bool_array::dump(std::string output_name)
{
	if (output_name != "stdout")
	{
		ofstream fout(output_name);
	}
	else
	{
		cout << "bool_array dump.\n";
		cout << "{" << endl << "	count_of_blocks: " << count_of_blocks << endl << "	data: ";
		for (int i = 0; i < count_of_blocks; ++i)
		{
			cout << (data[i] & 0b00000001);
			cout << (data[i] & 0b00000010)/2;
			cout << (data[i] & 0b00000100)/4;
			cout << (data[i] & 0b00001000)/8;
			cout << (data[i] & 0b00010000)/16;
			cout << (data[i] & 0b00100000)/32;
			cout << (data[i] & 0b01000000)/64;
			cout << (data[i] & 0b10000000)/128;
			cout << ' ';
		}
		cout << endl << "}" << endl;
	}
}

void bool_array::set_false(int n)
{
	if (n >= (count_of_blocks+1)*8)
		assert(!"ВЫХОД ЗА ДАЛЬНИЕ ПРЕДЕЛЫ БУЛЕВСКОГО МАССИВА");
	else if (n >= count_of_blocks*8)
		expand();

	data[n / 8] = (data[n / 8] & (255 - (1 << n%8)));
}

void bool_array::set_true(int n)
{
	if (n >= (count_of_blocks+1)*8)
		assert(!"ВЫХОД ЗА ДАЛЬНИЕ ПРЕДЕЛЫ БУЛЕВСКОГО МАССИВА");
	else if (n >= count_of_blocks*8)
		expand();

	data[n / 8] = (data[n/8] | (1 << (n % 8)));
}

unsigned int bool_array::length()
{
	return count_of_blocks*8;
}

helping_class bool_array::operator[](unsigned int n)
{
	if (n >= (count_of_blocks+1)*8)
		assert(!"ВЫХОД ЗА ДАЛЬНИЕ ПРЕДЕЛЫ БУЛЕВСКОГО МАССИВА");
	else if (n >= count_of_blocks*8)
		expand();
	
	helping_class tmp;
	tmp.data = &data[n / 8];
	tmp.number = n % 8;

	return tmp;
}

void helping_class::operator=(bool value)
{
	if (value)
		*data = (*data | (1 << number));
	else
		*data = (*data & (255 - (1 << number)));
}

std::ostream& operator<<(std::ostream& out, helping_class t)
{
	if (*t.data & (1 << t.number))
	{
		out << 1;
	}
	else
	{
		out << 0;
	}

	return out;
}