#include<iostream>
#include<string>
using namespace std;
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include <time.h>
#include<Windows.h>
#include<mmsystem.h>

/*
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
*/
struct info
{
	char user[20];
	char pass[20];
};
class credentials
{
private:
	char str1[20];
	char username[20];
	char password[20];
	char con_pass[20];
	char ch[10];
	char dt[20];
public:
	void menu()
	{
		char user, ch;
		credentials c;
		system("cls");
		c.textColor(5);
		cout << "********************************************************************************" << endl;
		cout << "   ****************************   DAILY DIARY   ****************************" << endl << endl;
		cout << "New User?? Want to Sign Up.....Enter 'n'" << endl;
		cout << "Already a User?Enter 'o' to login\n";
		c.textColor(9);
		cin >> user;

		if (user == 'o' || user == 'O')
		{
			c.old_user();
		}
		else
			if (user == 'n' || user == 'N')
			{
				c.new_user();
			}
			else
			{
				c.textColor(0);
				cout << "Invalid Input" << endl;
				c.textColor(4);
				cout << "Press any key to re-enter";
				_getch();
				menu();
			}
		c.textColor(5);
		cout << "\nThankyou for using our system" << endl;
		cout << "Press C to go to the menu, or \nany other key to exit the program and fill our survey:" << endl;
		ch = _getch();
		if (ch == 'C' || ch == 'c')
			menu();
		else
			ShellExecute(0, 0, "https://docs.google.com/forms/d/e/1FAIpQLSeiEIaVGOwdzJgsEJvUFKCoh0icgD-0HIgs5TeTolIjdbSA2w/viewform?usp=sf_link", 0, 0, SW_SHOW);
	}
	void textColor(int n)
	{
		/*
		#define BLACK 0
		#define BLUE 1
		#define GREEN 2
		#define CYAN 3
		#define RED 4
		#define MAGENTA 5
		#define BROWN 6
		#define LIGHTGREY 7
		#define DARKGREY 8
		#define LIGHTBLUE 9
		#define LIGHTGREEN 10
		#define LIGHTCYAN 11
		#define LIGHTRED 12
		#define LIGHTMAGENTA 13
		#define YELLOW 14
		#define WHITE 15
		*/
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240 + n);//240 for white background(16*15+ color of text)
	}

	void date()
	{
		char day[20], month[20], yr[20];
		time_t now = time(0);

		tm ltm;
		localtime_s(&ltm, &now);

		//a = (1900 + ltm.tm_year) + (10000 * (1 + ltm.tm_mon)) + (1000000 * ltm.tm_mday);
		sprintf_s(day, "%d", ltm.tm_mday);
		sprintf_s(month, "%d", 1 + ltm.tm_mon);
		strcat_s(day, "/");
		strcat_s(day, month);
		sprintf_s(yr, "%d", 1900 + ltm.tm_year);
		strcat_s(day, "/");
		strcat_s(day, yr);
		strcpy_s(dt, day);
	}
	int check()
	{
		if (strcmp(password, con_pass) == 0)
		{
			textColor(5);
			cout << "Password verification done" << endl;
			return 0;
		}
		else
		{
			textColor(0);
			cout << "Password mismatch" << endl;
			return 1;
		}

	}
	void pass_enter(int n)
	{
		char ch;
		char pass[20] = "";
		int i = 0;
		ch = _getch();
		while (ch != 13) //character 13 is enter
		{
			if (ch == 8)//backspace
			{
				if (i == 0)
				{
					ch = _getch();
					continue;
				}
				else
				{
					i--;
					cout << "\b" << " " << "\b";
					ch = _getch();
					continue;
				}
			}
			pass[i] = ch;
			textColor(9);
			cout << '*';
			ch = _getch();
			i++;
		}
		cout << endl;
		if (n == 1)
			strcpy_s(password, pass);
		else if (n == 2)
			strcpy_s(con_pass, pass);
	}

	char* encrypt(char data[],char key[])
	{
		for (int i = 0;i < strlen(data);i++)
		{
			data[i] += key[0];
		}
		return data;
	}
	char* decrypt(char data[], char key[])
	{
		for (int i = 0;i < strlen(data);i++)
		{
			data[i] -= key[0];
		}
		return data;
	}

	/*string XOR(string data, char key[])
	{
		string xorstring = data; //initialize new variable for our xordata
		for (int i = 0; i < xorstring.size(); i++) //for loop for scrambling bits in the string
		{
			xorstring[i] = data[i] ^ key[i % (sizeof(key) / sizeof(char))]; //scrambling the string/descrambling it
		}
		return xorstring;
	}*/

	void write()
	{
		system("cls");
		char entry[100];
		int c = 0;
		char e[20];
		char key[20];
		date();
		ifstream f(username);
		if (f.good())
		{
			while (!f.eof())
			{
				f.getline(str1, 20, '!');
				if (strcmp(str1, dt) == 0)
				{
					textColor(0);
					cout << "Today's diary has already been written!\n";
					c = 1;
					break;
				}
			}
			f.close();
		}
		if (c == 0)
		{
			textColor(5);
			cout << "Lets start, write your today's Diary:\n" << endl;
			textColor(0);
			//getchar();
			gets_s(entry);
			ofstream of(username, ios::app);
			of << dt << "!";
			strcpy_s(key, password);
			int i = 0, j = 0;
			int len = strlen(entry);
			firse:
			char arr[50] = { 0 };
			char arr1[50] = { 0 };
			while(i<=len)
			{
				if (i == len)
				{
					strcpy_s(e,encrypt(arr, key));
					of << e << "!";
					i++;
				}
				else
				if (entry[i] != ' ')
				{
					arr[j] = entry[i];
					j++;
					i++;
				}
				else 
			    if(entry[i]==' ')
				{	
					strcpy_s(e, encrypt(arr, key));
					of << e << "!";
					j = 0;
					i++;
					goto firse;
				}	
			}
			of << dt << "!";
			of.close();
			textColor(5);
			cout << "\nSuccessfuly written" << endl;
		}
	}
	void read(int c)
	{
		system("cls");
		char arr[20] = "";
		int a = 0;
		char ab[20];
		char key[20];
		ifstream f(username);
		if (f.good())
		{
			textColor(5);
			cout << "Date of the diary you wanna read(DD/MM/YYYY) : \n";
			if (c)
			{
				getchar();
			}
			textColor(9);
			gets_s(arr);
			while (!f.eof())
			{
				f.getline(str1, 20, '!');
				if (strcmp(arr, str1) == 0)
				{
					char str2[20];
					a = 1;
					f.getline(str1, 20, '!');
					cout << endl;
					textColor(0);
					do
					{
						strcpy_s(key, password);
						strcpy_s(ab, decrypt(str1, key));
						cout << ab << " ";
						f.getline(str1, 20, '!');
					} while (strcmp(arr, str1) != 0);
					break;
				}
			}
			if (a == 0)
			{
				textColor(0);
				cout << "Please check the date!\n";
				textColor(4);
				cout << "Press any key to re-enter";
				_getch();
				f.close();
				read(0);
			}
			cout << endl;
			f.close();
		}
		else
		{
			textColor(0);
			cout << "No diary exist for you, please write a diary first\n";
			textColor(4);
			cout << "Press any key to enter menu again";
			_getch();
			olduser_menu();
		}
	}
	void olduser_menu()
	{
		system("cls");
		char entry;
		textColor(5);
		cout << "Do you want to write today's Diary(W) or read a previous one(R)" << endl;
		cout << "Enter (W)/(R)";
		textColor(9);
		cin >> entry;
		if (entry == 'w' || entry == 'W')
		{
			write();
		}
		else
			if (entry == 'r' || entry == 'R')
			{
				read(1);
			}
	}
	void old_user()
	{
		system("cls");
		info j;
		char compare[20];
		bool value = false;
		textColor(5);
		cout << "Enter your Username:" << endl;
		textColor(9);
		cin >> username;
		ifstream f3("Credent.dat", ios::binary | ios::in);
		f3.seekg(0);
		while (f3.read((char *)& j, sizeof(info)))
		{
			if (strcmp(username, j.user) == 0)
			{
				value = true;
				strcpy_s(compare, j.pass);
			}
		}
		if (value == false)
		{
			char ch;
			textColor(0);
			cout << "No username with this name found" << endl;
			textColor(4);
			cout << "Press M to go to the main menu again or any other key to re-enter username";
			ch = _getch();
			if (ch == 'M' || ch == 'm')
				menu();
			else
				old_user();
		}
		f3.close();

		textColor(5);
		cout << "Enter your password:" << endl;
		pass_enter(1);
		if (strcmp(password, compare) == 0)
		{
			textColor(2);
			cout << "Access Granted" << endl;
			textColor(4);
			cout << "Press any key to continue.......";
			_getch();
			olduser_menu();
		}
		else
		{
			textColor(0);
			cout << "Username and password mismatch" << endl;
			textColor(4);
			cout << "Press any key to re-enter";
			_getch();
			old_user();
		}
	}

	void new_user()
	{
		system("cls");
		textColor(5);
		cout << "Enter desired username(no spaces allowed):" << endl;
		textColor(9);
		getchar();
		gets_s(username);
		for (int i = 0;i < strlen(username);i++)
		{
			if (username[i] == ' ')
			{
				textColor(0);
				cout << "Invalid Username-space encountered\n";
				textColor(4);
				cout << "Press any key to re-enter";
				_getch();
				new_user();
			}
		}

		ifstream f("Usernames.txt");
		if (f.good())
		{
			while (!f.eof())
			{
				f.getline(ch, 20, ' ');
				if (strcmp(ch, username) == 0)
				{
					char ch;
					textColor(0);
					cout << "A User with this username exists, kindly enter a new username" << endl;
					textColor(4);
					cout << "Press M to go to the main menu again or any other key to re-enter username";
					ch=_getch();
					if (ch == 'M' || ch == 'm')
						menu();
					else
						new_user();
					f.close();
				}
			}
		}

	label3:
		textColor(5);
		cout << "Enter your password:" << endl;
		pass_enter(1);
		textColor(5);
		cout << "Confirm your password:" << endl;
		pass_enter(2);
		if (check())
		{
			goto label3;
		}
		else
		{
			ofstream f1("Usernames.txt", ios::app | ios::out);
			f1 << " " << username;
			f1.close();
			info i;

			strcpy_s(i.user, username);
			strcpy_s(i.pass, password);
			ofstream f2("Credent.dat", ios::binary | ios::out | ios::app);
			f2.write((char *)&i, sizeof(info));
			f2.close();
			textColor(4);
			cout << "Press any key to continue..." << endl;
			_getch();
			write();
		}
	}
};
/*
void gotoXY(int x, int y)
{
	CursorPosition.X = x; // Locates column
	CursorPosition.Y = y; // Locates Row
	SetConsoleCursorPosition(console, CursorPosition); // Sets position for next thing to be printed 
}
*/

void textSize()
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 30;
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Courier New");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}


void main()
{
	char f;
	credentials c;
	textSize();
	system("color F7");//white background of console
	c.textColor(5);
	cout << "Do you want background music in your program?(Y/N)";
	c.textColor(9);
	cin >> f;
	if (f == 'y' || f == 'Y')
		PlaySound("C:\\Users\\namansaini\\Documents\\Visual Studio 2017\\Projects\\Diary\\Diary\\Interstellar.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	c.menu();
	exit(0);
}