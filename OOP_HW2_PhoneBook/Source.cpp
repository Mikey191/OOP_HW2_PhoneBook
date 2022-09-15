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
	char Number[20];

	char* Name;
	int SizeName;

	char Info[20];

public:
	PhoneBook()
	{
		SizeName = 80;
		Name = new char[80];
		

		//char temp[20] = "\0";
		//Name = temp;

		Number[0] = '\0';

		Info[0] = '\0';

		cout << "Constr#1 " << this << endl;
	}

	PhoneBook(const PhoneBook& tempSub)
	{
		SizeName = tempSub.SizeName;
		Name = new char[SizeName + 1];
		
		for (int i = 0; i <= SizeName; i++)
		{
			Name[i] = tempSub.Name[i];
		}
		cout << "const copy..."<< this << endl;
		cout << "TempSub Name: " << tempSub.Name << endl;
		cout << "This Name: " << Name << endl;
		system("pause");

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
	~PhoneBook() { cout << "Destruct..."<< this << endl;
	//system("pause");
	delete[] Name; }

	void input() 
	{
		cout << "Enter Name: ";
		cin >> Name;

		/*cout << "\nEnter Name: ";
		char tempName[20];
		cin >> tempName;
		Name = new char[strlen(tempName)+1];
		for (int i = 0; i < strlen(tempName); i++)
		{
			Name[i] = tempName[i];
		}*/

		//strcpy_s(this->Name, 20, tempName);

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

void AddSubscruber(PhoneBook* arr, int& size)
{
	/*PhoneBook temp;
	temp.input();
	cout << "Add sub" << endl;
	system("pause");*/
	arr[size++].input();
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
	cout<<"Size of: "<< sizeof(PhoneBook) << endl;
	system("pause");
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