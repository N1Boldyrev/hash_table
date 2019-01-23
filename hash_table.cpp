#include <iostream>
#include <string>
#include <vector>

#define REHASH_INDEX 0.5
#define DEFAULT_TABLE_SIZE 4
using namespace std;

int hash_function(int key, int buffer_size)//мультипликативная хеш-функция 
{
	double A = 0.618033;//основанно на методах золтого сечения 
	return buffer_size * fmod(key*A, 1);
}

template <class T>
class Hash_table
{
protected:
	int key;
	int buffer_size = DEFAULT_TABLE_SIZE;
	int size;
	vector<T>buffer;
public:
	Hash_table()
	{
		buffer.resize(buffer_size);
	}
	~Hash_table()
	{
		buffer.clear();
	}

	bool isEmpty(int key)
	{
		if (buffer[key] == "")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	void rehash()
	{
		buffer_size *= 2;
		buffer.resize(buffer_size);
	}


	bool add_element(T value,int key)
	{
		if ((double)size/(double)buffer_size>=REHASH_INDEX)
		{
			rehash();
		}

		if (key>buffer_size)
		{
			return false;
		}
		int hash;
		hash = hash_function(key, buffer_size);
		if (!isEmpty(hash))
		{
			while (!isEmpty(hash))
			{
				hash++;
				if (hash==buffer_size)
					return false;
			}
		}
		buffer[hash] = value;
		size++;
		return true;
	}
	bool find_element(T value) const
	{
		for (int i = 0; i < buffer_size; i++)
		{
			if (buffer[i] == value)
			{
				return true;
			}
		}
		return false;
	}
};

int main()
{
	Hash_table<string>hash_map;
	char command=' ';
	string value;
	int key;
	int auto_key = DEFAULT_TABLE_SIZE;
	bool status = false;
	cout << "input command(+,?), than input value: \n" << endl;
	while (cin>>command>>value)
	{
		switch (command)
		{
		case'+':
			key = rand()%auto_key ;
			status = hash_map.add_element(value, key);
			auto_key++;
			break;
		case'?':
			status = hash_map.find_element(value);
			break;
		}
		if (status)
		{
			cout << "OK \n" << endl;
		}
		else
		{
			cout << "NO \n" << endl;
		}
	}
    return 0;
}