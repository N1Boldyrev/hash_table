#include <iostream>
#include <string>
#include <vector>

#define REHASH_INDEX 0.5//коэффициент заполнения таблицы 
#define DEFAULT_TABLE_SIZE 4//первоначальный размер таблицы
#define GOLDEN_RATIO 0.618033//золотое сечение
using namespace std;

int hash_function(int key, int buffer_size)//мультипликативная хеш-функция 
{ 
	return buffer_size * fmod(key*GOLDEN_RATIO, 1);
}

template <class T>
class Hash_table
{
protected:
	int buffer_size = DEFAULT_TABLE_SIZE;//размер таблицы
	int size;//реальное кол-во элементов в таблице
	vector<T>buffer;
public:
	Hash_table()
	{
		buffer.resize(buffer_size);//задание первоначального размера таблицы
	}
	~Hash_table()
	{
		buffer.clear();//очистка памяти
	}

	bool isEmpty(int key)//проверка на пустоту ячейки 
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
	
	void resize()//расширение таблицы
	{
		buffer_size *= 2;
		buffer.resize(buffer_size);
	}


	bool add_element(T value,int key)//вставка элемента в таблицу
	{
		if (find_element(value) == true)//если элемент уже есть в таблице
			return true;//возвращаем ОК
		if ((double)size/(double)buffer_size>=REHASH_INDEX)//если заполненность таблицы составляет 1/2 от размера таблицы
		{
			resize();//то расширить таблицу 
		}

		int hash;
		hash = hash_function(key, buffer_size);//вычисление хеш-значения для элемента 
		if (!isEmpty(hash))//если элемент не пуст
		{
			while (!isEmpty(hash))//переходим к следующему элементу,пока не будет найдена пустая ячейка
			{
				hash++;
				if (hash==buffer_size)//если в конце таблицы не осталось свободных ячеек
					return false;//возвращаем FAIL
			}
		}
		buffer[hash] = value;//если все условия удовлетворены-заносим запись в таблицу 
		size++;//увеличиваем количество элементов
		return true;//возвращаем ОК
	}
	bool find_element(T value) const//поиск элемента в таблице
	{
		for (int i = 0; i < buffer_size; i++)//сравниваем значения в таблице с искомым 
		{
			if (buffer[i] == value)//если находим
			{
				return true;//возвращаем OK
			}
		}
		return false;//если элемент отсутствует в таблице-возвращаем FAIL
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	Hash_table<string>hash_map;
	char command=' ';
	string value;
	int key;
	int auto_key = DEFAULT_TABLE_SIZE;
	bool status = false;
	cout << "Ведите одну из доступных комманд(+,?) \n '+'-добавить элемент \n '?'-найти элемент \n Затем введите элемент" << endl;
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
			cout << "FAIL \n" << endl;
		}
	}
	return 0;
}
	





