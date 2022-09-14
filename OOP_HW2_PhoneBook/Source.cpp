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


class PhoneBook
{
private:
	

public:
	char Number[20];
	char Info[20];
	char* Name;
	int SizeName;

	//PhoneBook(char* name) : Name{ new char[SizeName] }, SizeName{ strlen(name) + 1 }, Number{ '\0' }, Info{ '\0' }{}
	PhoneBook(): SizeName{20}, Name{new char[20]}, Number{ '\0' }, Info{ '\0' }{}

	PhoneBook(const PhoneBook& tempSub)
	{
		Name = new char[tempSub.SizeName+1];
		SizeName = tempSub.SizeName;
		for (int i = 0; i <= tempSub.SizeName; i++)
		{
			Name[i] = tempSub.Name[i];
		}
		//strcpy_s(this->Number, 20, tempSub.Number);
		for (int i = 0; i < 20; i++)
		{
			Number[i] = tempSub.Number[i];
		}
		//strcpy_s(this->Info, 20, tempSub.Info);
		for (int i = 0; i < 20; i++)
		{
			Info[i] = tempSub.Info[i];
		}
	}
	~PhoneBook() { 	delete[] Name; }

	void input() 
	{
		cout << "\nEnter Name: ";
		/*char tempName[20];
		cin >> tempName;
		Name = new char[strlen(tempName)+1];
		for (int i = 0; i < strlen(tempName); i++)
		{
			Name[i] = tempName[i];
		}*/
		//strcpy_s(this->Name, 20, tempName);
		cin >> Name;
		cout << "\nEnter Number: ";
		cin>> Number;
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
		
		//fread(&arr[size], sizeof(PhoneBook), 1, file);
		
		fread(&arr[size].SizeName, sizeof(int), 1, file);
		fread(&arr[size].Number, sizeof(char), 20, file);
		fread(&arr[size].Info, sizeof(char), 20, file);
		arr[size].Name = new char[arr[size].SizeName];
		fread(&arr[size].Name, sizeof(char), arr[size].SizeName, file);
	
		//cout << arr[size].GetName() << endl;

		size++;
	}
	fclose(file);
	size--;
	system("pause");
}

void savedata_bin(PhoneBook* arr, int& size)
{
	FILE* file;
	const char* filename = "File.txt";
	fopen_s(&file, filename, "wb");
	//fwrite(&arr[0], sizeof(PhoneBook), size, file);

	for (size_t i = 0; i < size; i++)
	{
		fwrite(&arr[i].SizeName, sizeof(int), 1, file);
		fwrite(&arr[i].Number, sizeof(char), 20, file);
		fwrite(&arr[i].Info, sizeof(char), 20, file);
		fwrite(&arr[i].Name[0], sizeof(char), arr[i].SizeName, file);
	}

	fclose(file);
}

//PhoneBook Add()
//{
//	PhoneBook temp;
//	temp.input();
//	cout << "Add sub" << endl;
//	system("pause");
//	return temp;
//}

void AddSubscruber(PhoneBook* arr, int& size)
{
	arr[size].input();
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