#include "Graphics_color.h"
/*������� ���� �������*/
void menu();
/*��������� ��������� �� �����*/
void Print_controls();
/*��������� �� ����� ����������, ���� ������� �����*/
void Print_info();
/*��������� ��������� �� ���������� ������*/
void execution();
/*�������� �� ����������� �����*/
bool is_str_number(string &str);
/*��������� ������� ������*/
vector<pair<int, int>> get_deg(graph& matrix, int& size);
/*�������� �� ��������� ���������� �����/�����*/
vector<int> Hol_print(graph& adj);


void Print_controls()
{
	printf("���� �������� ���������� ��� ����������� ���������� �����/����� � ����������� �����������.\n");
	printf("���������� � ���� ���������� �� ��������� ������ �����/����\n");
}
void Print_info()
{
	printf("������� ������� ��������.\n");
	printf("������� �������� - �� ����� ������������� ����� �� ������� ������� n*n, �� n - ������� ������.\n");
	printf("������� ������� � ��������� ij ������� �� ������ ������ i �� j.\n");
	printf("���� �� ����������� ij ���� 3, �� �� ������, �� � ������� i �������� 3 ����� � ������� j.\n");
}
void menu()
{
	int count = 2;					//�������� ����� - "������"
	int key;
	Print_controls();
	//----------------------------------------------------------����
	while (true)
	{		
		coord(7, 5);				//���� ������� �� �����������
		if (count == 1)  //������ ������ �������
		{
			rcol(rcol_red);
		}
		else 
		{
			rcol(rcol_white);
		}
		printf("1. ����� \n");

		coord(7, 6);
		if (count == 2)
		{
			rcol(rcol_red);
		}
		else
		{
			rcol(rcol_white);
		}
		printf("2. ������ \n");

		coord(7, 7);
		if (count == 3)
		{
			rcol(rcol_red);
		}
		else
		{
			rcol(rcol_white);
		}
		printf("3. ����� \n");

		do {key = _getch();} while (key == 224); //������� ������

		if (key == key_arrow_up && count > 1) //������ ����� 
		{
			count--;
		}
		else if (key == key_arrow_down && count < 3) //������ ����
		{
			count++;
		}
		else if (key == key_enter) //enter
		{

			if (count == 1)
			{
				system("CLS");
				execution();
				Print_controls();
			}
			else if (count == 2) //��������� ������
			{
				system("CLS");
				fstream hist("history.txt", ios::in);
				int s;
				int n;
				string str;
				printf("������ 10 ���������� ������, ��� ���� � ���� ��� ����.\n");
				for (int i = 0; i < 10 && !hist.eof(); ++i)
				{
					printf("---------------------------------------\n");
					hist >> s; //�����
					for (int j = 0; j < s; ++j)
					{
						for (int z = 0; z < s; ++z)
						{
							hist >> n;
							printf("%i ", n);
						}
						printf("\n");
					}
					hist >> n; //���� ��������� �� ��� �����
					if (n == 1)
					{
						printf("������ ����:\n");
					}
					else
					{
						printf("������ ����:\n");
					}
					hist >> str; //����/����
					printf("%s\n", str.c_str());

				}
				hist.close();
				printf("---------------------------------------\n");
				system("pause");
				system("CLS");	
				Print_controls();
				ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
			}
			if (count == 3) //�����
			{
				coord(7, 7);
				printf("�� ��������? (Esc/Enter) \n");
				while (true)
				{
					key = _getch();
					if (key == key_enter)
					{
						rcol(7);
						system("CLS");
						exit(0);
					}
					else if (key == key_esc)
					{
						coord(7, 7);
						printf("                                      ");
						coord(7, 7);
						printf("3. ����� \n");
						coord(7, 8);
						break;
					}
				} 
			}
		}
	}
}
bool is_str_number(string &str)
{
	for (char &c :str)
	{
		if (!('0'<= c && '9' >= c))
		{
			return false;
		}
	}
	return true;
}
vector<pair<int, int>> get_deg(graph& matrix, int& size)		//��������� ������ ������
{
	vector<pair<int, int>> deg(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] != 0)
			{
				deg[i].first += matrix[i][j];
				deg[j].second += matrix[i][j];
			}
		}
	}
	return deg;
}
vector<int> Hol_print(graph& adj)
{
	//adj - ������� ���������� �����
	//edges - ������� �����, �� �������� � �������
	//���� - ��� ���������� ������
	unordered_map<int, int> edges;
	stack<int> path_c;
	vector<int> circuit;
	for (int i = 0; i < adj.size(); i++)
	{
		edges[i] = adj[i].size();					//������ ������ ����� ��� ���������� ��������������
	}

	path_c.push(0);									//�������� � ������� �������
	int curr_v = 0;									//�������, �� ����� ����������
	while (!path_c.empty())
	{
		if (edges[curr_v])							//���� � �� ���������� �����
		{
			path_c.push(curr_v);					//��� ������� � ������
			int next_v = adj[curr_v].back();		//�������� ������� ����� �����
			edges[curr_v]--;						//��������� �������� ����� � �����
			adj[curr_v].pop_back();
			curr_v = next_v;						//�������� �� �������� �������
		}
		else						                //"���-������" ��� ������ ����������� �����								
		{											//� ��� "�����"
			circuit.push_back(curr_v);
			curr_v = path_c.top();					//���-������
			path_c.pop();
		}
	}

	for (int i = circuit.size() - 1; i >= 0; i--)	//�������� ����, ��� ����������� ��������� -
	{												// - ������� � ����������� ������
		printf("%i", circuit[i]);
		if (i)										//����� - ���� �� ������ �� ���������� ��.
		{
			printf(" -> ");
		}
	}
	return circuit;
}
void execution()
{
	string s = "";
	int flag;
	while (true)
	{
		system("CLS");	
		Print_info();
		if (!s.empty())
		{
			printf("�� ����� ���������� ���. ��������� ��.\n");
		}
		printf("������ ������� ������ (��� ������ ������ 0): ");
		s.clear();
		do {
			getline(cin, s);
		} while (s == "");
		if (is_str_number(s))
		{
			if (stoi(s) == 0)
			{	
				system("CLS");
				return;
			}
			break;
		}
	}
	
	int size = stoi(s);
	s.clear();
	graph g(size, vector<int>(size));
	int element = 0;
	bool exit = false;
	bool correct = false;
	vector<int> checker;
	int z;
	z = 0;
	int x = 0;
	while (true)
	{
		exit = false;
		system("CLS");
		printf("������ ������� � "); printf("%i", size * size); printf(" ��������(-��) (��� ������ ������ exit):\n");
		string k;
		printf(" ");
		for (int i = 0; i < size; ++i)
		{
			printf(" "); printf("%i", i);
		}
		printf("\n");
		for (int i = 0; i < size; i++)
		{
			printf("%i ", z);
			for (int j = 0; j < size; j++)
			{	
				
				cin >> k;
				if (k == "exit")
				{
					system("CLS");
					return;
				}
				stringstream ss(k);
				string check;
				while (ss >> check || x == size)
				{
					if (!(is_str_number(check)))
					{
						z = 0;
						exit = true;
						getline(cin, k);
						break;
					}
					g[i][j] = stoi(check);
					x++;
				}
				if (exit == true)
				{
					break;
				}
			}
			x = 0;
			if (exit == true)
			{
				break;
			}
			getline(cin, k);
			
			z++;
			coord(size * 2 + 2, z + 1);
			printf("                                                                               ");
			coord(0, z + 2);
		}
		if (exit == false)
		{
			break;
		}
	}
	vector<pair<int, int>> deg(size);
	deg = get_deg(g, size);
	
	bool minus = false;
	bool plus = false;
	for (int i = 0; i < size; i++)
	{
		int num = deg[i].first - deg[i].second;
		if (num == 0) continue;
		else if (num == -1)
		{
			if (minus == false)
				minus = !minus;
			else
			{
				printf("�� �� ������ ����\n");
				printf("�������� ����-��� ������ ��� �����������.");
				_getch();
				system("CLS");
				return;
			}
		}
		else if (num == 1)
		{
			if (plus == false)
				plus = !plus;
			else
			{
				printf("�� �� ������ ����\n");
				printf("�������� ����-��� ������ ��� �����������.");
				_getch();
				system("CLS");
				return;
			}
		}
		else
		{
			printf("�� �� ������ ����\n");
			printf("�������� ����-��� ������ ��� �����������.");
			_getch();
			system("CLS");
			return;
		}
	}
	bool euler_or_semi_euler = true;				//���� ��� ���� ����������
	if (minus && plus)
	{
		euler_or_semi_euler = !euler_or_semi_euler;
	}
	graph adj(size);
	for (int i = 0; i < size; i++)					//��������� 2� ������ ��� ���������� 
	{												//����� ����� ��� �������� �����
		for (int j = 0; j < size; j++)
		{
			if (g[i][j])
			{
				for (int z = 0; z < g[i][j]; z++)
				{
					adj[i].push_back(j);
				}
			}
		}

	}
	if (euler_or_semi_euler)
	{
		printf("������ ����:\n");
		flag = 1;
	}
	else
	{
		printf("������ ����:\n");
		flag = 0;
	}
	vector<int> circuit = Hol_print(adj);
	printf("\n");
	//----------------------------------------------------------ʳ���� ��������� ------ ����������
	printf("������ �������? (Y/N)\n");
	console_settings();
	char key;
	do
	{
		do { key = _getch(); } while (key == 224);
		if (key == 'n' || key == 'N')
		{
			system("CLS");
			return;
		}
		else if (key == 'y' || key == 'Y')
		{
			fstream history("history.txt", ios::in);
			if (!(history.is_open()))					//���� ����� �� ���� - ��������� � ������ ���������
			{
				history.open("history.txt", ios::out);
				history.close();
				history.open("history.txt", ios::in);
			}
			const int top_n = 9; 
			string buff[top_n];
			string line;
			string buffer;
			for (int i = 0; i < top_n; ++i)					//������� ��� � ����� � ������
			{
				getline(history, buffer);
				if (buffer == "") break;
				buff[i] = buffer;
			}
			history.close();

			history.open("history.txt", ios::out);		//������������ ���� ������ ������
			history << size << " ";
			for (int i = 0; i < size; ++i)
			{
				for (int j = 0; j < size; ++j)
				{
					history << g[i][j] << " ";
				}
			}
			history << flag << " ";
			for (int i = circuit.size() - 1; i >= 0; i--)
			{
				history << circuit[i];
				if (i)
					history << "->";
			}
			history.close();

			history.open("history.txt", ios::app);
			for (int i = 0; i < top_n; ++i)		//�� ���������� ��������. ����� ����� � ��� ������ ������ 10 ������� ������
			{
				if (history.eof()) break;
				history << endl << buff[i];
			}
			history.close();
			system("CLS");
			return;
		}

	} while (!(key == 'n' && key == 'N' && key == 'y' && key == 'Y'));
}