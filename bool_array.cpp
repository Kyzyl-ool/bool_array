#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <fstream>

using std::calloc;

class bool_array
{
private:
	char* data;
	unsigned int count_of_blocks;

	void expand();
	void strip();
public:
	bool_array();
	~bool_array();

	bool operator[](unsigned int n);
	char operator=(bool value);

	void dump(std::string output_name);
};

bool_array::bool_array()
{
	data = (char* )calloc(1, sizeof(char));
	count_of_blocks = 1;
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

bool bool_array::operator[](unsigned int n)
{
	if (n >= count_of_blocks*8)
	{
		assert(!"ВЫХОД ЗА ПРЕДЕЛЫ БУЛЕВСКОГО МАССИВА");
	}

	return (data[n/8] & (1 << (7 - n%8)));
}

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
		cout << "bool_array dump. Status: " << "NONE.\n";
		cout << "{" << endl << "	count_of_blocks: " << count_of_blocks << endl << "	data: ";
		for (int i = 0; i < count_of_blocks; ++i)
		{
			cout << (data[i] & 0b10000000)/128;
			cout << (data[i] & 0b01000000)/64;
			cout << (data[i] & 0b00100000)/32;
			cout << (data[i] & 0b00010000)/16;
			cout << (data[i] & 0b00001000)/8;
			cout << (data[i] & 0b00000100)/4;
			cout << (data[i] & 0b00000010)/2;
			cout << (data[i] & 0b00000001);
		}
		cout << endl << "}" << endl;
	}
}