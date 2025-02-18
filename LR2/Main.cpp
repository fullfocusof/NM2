#include "SystemOfLinearEquation.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACKSPACE 8

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleTitle(L"����");
	ConsoleCursorVisible(false, 100);

	SystemOfLinearEquation test;

	int active_menu = 0;
	int keyInput;
	bool exitProg = false;

	while (!exitProg)
	{
		int x = 40, y = 12;
		GoToXY(x, y);

		vector<string> menu =
		{
			"������ ������ �� �����",
			"�������� ������",
			"������� ���� ������� ������",
			"������� ���� ������� ������ � ������� �������� ��������",
			"���������� ������������",
			"����� �������� �������",
			"������� ���� ������� ������� ��������",
			"������� ���� ������� �������",
			"�����"
		};

		for (int i = 0; i < menu.size(); i++)
		{
			if (i == active_menu)
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			GoToXY(x, y++);
			cout << menu[i] << endl;
		}

		keyInput = _getch();
		switch (keyInput)
		{
			case KEY_ESC:
				exit(0);

			case KEY_UP:
			{
				if (active_menu > 0)
				{
					active_menu--;
				}
			}
			break;

			case KEY_DOWN:
			{
				if (active_menu < menu.size() - 1)
				{
					active_menu++;
				}
			}
			break;

			case KEY_ENTER:
			{
				switch (active_menu)
				{
					case 0:
					{
						system("cls");

						test.readFromFile("dataInput.txt");

						test.printQuit();
					}
					break;

					case 1:
					{
						system("cls");

						test.printData();

						test.printQuit();
					}
					break;

					case 2:
					{
						system("cls");

						test.gaussian_solve();

						test.printQuit();
					}
					break;

					case 3:
					{
						system("cls");

						test.gaussian_solveLeadElem();

						test.printQuit();
					}
					break;

					case 4:
					{
						system("cls");

						try
						{
							cout << "������������ = " << test.getDet();
						}
						catch (const exception&)
						{
							cerr << "������ �����������";
						}

						test.printQuit();
					}
					break;

					case 5:
					{
						system("cls");
						
						try
						{
							vector<vector<float>> invMat = test.getMatrix().getInverseMatrix();

							cout << "�������� �������:" << endl;
							for (auto& row : invMat)
							{
								for (auto& el : row)
								{
									cout << el << " \t ";
								}
								cout << endl;
							}
						}
						catch (const exception&)
						{
							cout << "������������ ������� ����� ����, �������� ������� �� ����������";
						}

						test.printQuit();
					}
					break;

					case 6:
					{
						system("cls");

						test.simpleIteration(0);

						test.printQuit();
					}
					break;

					case 7:
					{
						system("cls");

						test.simpleIteration(1);

						test.printQuit();
					}
					break;

					case 8:
					{
						system("cls");
						exitProg = true;
					}
					break;
				}
			}
			break;
		}
	}
}