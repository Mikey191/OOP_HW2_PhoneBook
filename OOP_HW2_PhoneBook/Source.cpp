//Телефонная книга
// ФИО
// Дом тел
// Раб тел
// Моб тел
// Доп инфа
// 
// Добавлять новых абб
// Удвлять аббанентов
// Сохранять инфу
// Загружать инфу
//

#include <iostream>
#include <string>
#include <io.h>
#include <stdio.h>
#include <fstream>
using namespace std;

#define Size1 20

class PhoneBook
{
private:
	char* Name = new char[Size1];
	int SizeName = Size1;
	char Number[20];
	char Info[20];

public:
	PhoneBook()
	{
		char temp[20] = " ";
		Name = temp;
		Number[0] = '\0';
		Info[0] = '\0';
	}

	PhoneBook(const PhoneBook& tempSub)
	{
		Name = new char[tempSub.SizeName + 1];
		SizeName = tempSub.SizeName;
		for (int i = 0; i <= tempSub.SizeName; i++)
		{
			Name[i] = tempSub.Name[i];
		}
		cout << "const copy..." << endl;

		strcpy_s(this->Number, 20, tempSub.Number);

		strcpy_s(this->Info, 20, tempSub.Info);
	}

	void input() 
	{
		cout << "\nEnter Name: ";
		char tempName[20];
		cin >> tempName;
		strcpy_s(this->Name, 20, tempName);
		cout << "\nEnter Number: ";
		cin>>Number;
		cout << "\nEnter Info: ";
		cin >> Info;
	}
	void print()
	{
		cout << "Name: " << Name << "\t";
		cout << "Phone: " << Number << "\t";
		cout << "Info: " << Info << "\t";
		cout << endl;
	}
	void SetName(char* Name) { strcpy_s(this->Name, 20, Name); }
	char* GetName() { return Name; }
};

void loaddata_bin(PhoneBook* arr, int& size)
{
	FILE* file;
	const char* filename = "File.txt";
	struct _finddata_t MyFileInfo;
	intptr_t done = _findfirst(filename, &MyFileInfo);
	if (done == -1)
	{
		fopen_s(&file, filename, "wb");
		fclose(file);
	}
	fopen_s(&file, filename, "rb");
	while (!feof(file))
	{
		fread(&arr[size], sizeof(PhoneBook), 1, file);
		size++;
	}
	fclose(file);
	size--;
}

void savedata_bin(PhoneBook* arr, int& size)
{
	FILE* file;
	const char* filename = "File.txt";
	fopen_s(&file, filename, "wb");
	fwrite(&arr[0], sizeof(PhoneBook), size, file);
	fclose(file);
}

PhoneBook Add()
{
	PhoneBook temp;
	temp.input();
	return temp;
}

void AddSubscruber(PhoneBook* arr, int& size)
{
	arr[size] = Add();
	size++;
}

void DeleteSubscruber(PhoneBook* arr, int& size)
{
	PhoneBook temp;
	int k = -1;
	cout << "Enter name for delete: ";
	char text[20];
	cin >> text;
	temp.SetName(text);
	for (int i = 0; i < size; i++)
	{
		if (strcmp(arr[i].GetName(), temp.GetName()) == 0)
		{
			k = i;
		}
	}
	if (k >= 0)
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] = arr[i + 1];
		}
		size--;
	}
}

void ShowAllSubscruber(PhoneBook* arr, int& size)
{
	cout << "\tPhone book:" << endl;
	for (int i = 0; i < size; i++)
	{
		arr[i].print();
		cout << endl;
	}
	system("pause");
}

int main()
{
	PhoneBook arr[100];
	int size = 0;
	int k;
	//loaddata_bin(arr, size);
	do
	{
		system("cls");
		cout << "\tPhoneBook" << endl;
		cout << "1 - Show all subs;" << endl;
		cout << "2 - Add Sub;" << endl;
		cout << "3 - Delete Sub;" << endl;
		cout << "4 - Load File;" << endl;
		cout << "5 - Save File;" << endl;
		cout << "0 - EXIT;" << endl;
		cout << "Your choise: ";
		cin >> k;
		switch (k)
		{
		case 1:
			ShowAllSubscruber(arr, size);
			break;
		case 2:
			AddSubscruber(arr, size);
			break;
		case 3:
			DeleteSubscruber(arr, size);
			break;
		case 4:
			loaddata_bin(arr, size);
			break;
		case 5:
			savedata_bin(arr, size);
			break;
		}

	} while (k != 0);

	//savedata_bin(arr, size);
	//delete[] arr;

	return 0;
}