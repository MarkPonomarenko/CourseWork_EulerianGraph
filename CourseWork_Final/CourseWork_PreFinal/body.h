#include "Graphics_color.h"
/*головне меню проекту*/
void menu();
/*виведеняя управління на екран*/
void Print_controls();
/*виведення на екран інформації, щодо вхідних даних*/
void Print_info();
/*виконання обчислень та збереження архіву*/
void execution();
/*перевірка на правильність вводу*/
bool is_str_number(string &str);
/*отримання ступенів вершин*/
vector<pair<int, int>> get_deg(graph& matrix, int& size);
/*побудова та виведення ейлерового шляху/циклу*/
vector<int> Hol_print(graph& adj);


void Print_controls()
{
	printf("Дана програма призначена для знаходження ейлеревого циклу/шляху в орієнтованому мультиграфі.\n");
	printf("Орієнтування в меню відбувається за допомогою стрілок вверх/вниз\n");
}
void Print_info()
{
	printf("Задайте матрицю суміжності.\n");
	printf("Матриця суміжності - це спосіб представлення графа як матрицю розміром n*n, де n - кількість вершин.\n");
	printf("Елемент матриці з індексами ij відповідає за звязок вершин i та j.\n");
	printf("Якщо на координатах ij буде 3, то це означає, що з вершини i виходять 3 ребра в вершину j.\n");
}
void menu()
{
	int count = 2;					//стартова точка - "журнал"
	int key;
	Print_controls();
	//----------------------------------------------------------Меню
	while (true)
	{		
		coord(7, 5);				//вивід функцій на координатах
		if (count == 1)  //трекінг обраної функції
		{
			rcol(rcol_red);
		}
		else 
		{
			rcol(rcol_white);
		}
		printf("1. Старт \n");

		coord(7, 6);
		if (count == 2)
		{
			rcol(rcol_red);
		}
		else
		{
			rcol(rcol_white);
		}
		printf("2. Журнал \n");

		coord(7, 7);
		if (count == 3)
		{
			rcol(rcol_red);
		}
		else
		{
			rcol(rcol_white);
		}
		printf("3. Вихід \n");

		do {key = _getch();} while (key == 224); //зчитуємо клавішу

		if (key == key_arrow_up && count > 1) //стрілка вверх 
		{
			count--;
		}
		else if (key == key_arrow_down && count < 3) //стрілка вниз
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
			else if (count == 2) //виведення архіву
			{
				system("CLS");
				fstream hist("history.txt", ios::in);
				int s;
				int n;
				string str;
				printf("Останні 10 збережених графів, для яких є шлях або цикл.\n");
				for (int i = 0; i < 10 && !hist.eof(); ++i)
				{
					printf("---------------------------------------\n");
					hist >> s; //розмір
					for (int j = 0; j < s; ++j)
					{
						for (int z = 0; z < s; ++z)
						{
							hist >> n;
							printf("%i ", n);
						}
						printf("\n");
					}
					hist >> n; //флаг відповідний за тип графу
					if (n == 1)
					{
						printf("Ейлерів цикл:\n");
					}
					else
					{
						printf("Ейлерів шлях:\n");
					}
					hist >> str; //шлях/цикл
					printf("%s\n", str.c_str());

				}
				hist.close();
				printf("---------------------------------------\n");
				system("pause");
				system("CLS");	
				Print_controls();
				ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
			}
			if (count == 3) //вихід
			{
				coord(7, 7);
				printf("Ви впевненні? (Esc/Enter) \n");
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
						printf("3. Вихід \n");
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
vector<pair<int, int>> get_deg(graph& matrix, int& size)		//знаходимо степені вершин
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
	//adj - матриця суміжностей графу
	//edges - кількість ребер, що виходять з вершини
	//стек - для збереження вершин
	unordered_map<int, int> edges;
	stack<int> path_c;
	vector<int> circuit;
	for (int i = 0; i < adj.size(); i++)
	{
		edges[i] = adj[i].size();					//рахуємо кілкість ребер для моніторингу невикористаних
	}

	path_c.push(0);									//починаємо з довільної вершини
	int curr_v = 0;									//вершина, що зараз аналізується
	while (!path_c.empty())
	{
		if (edges[curr_v])							//поки є не використані ребра
		{
			path_c.push(curr_v);					//пуш вершини в вектор
			int next_v = adj[curr_v].back();		//наступна вершина через ребро
			edges[curr_v]--;						//видаляємо пройдене ребро з стеку
			adj[curr_v].pop_back();
			curr_v = next_v;						//рухаємося до наступної вершини
		}
		else						                //"бек-трекінг" щоб знайти продовження шляху								
		{											//у разі "тупіку"
			circuit.push_back(curr_v);
			curr_v = path_c.top();					//бек-трекінг
			path_c.pop();
		}
	}

	for (int i = circuit.size() - 1; i >= 0; i--)	//отримали шлях, для корректного виведення -
	{												// - друкуємо в зворотньому порядкі
		printf("%i", circuit[i]);
		if (i)										//умова - поки не дійдемо до останнього ел.
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
			printf("Ви ввели некорректні дані. Спробуйте ще.\n");
		}
		printf("Введіть кількість вершин (для виходу введіть 0): ");
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
		printf("Введіть матрицю в "); printf("%i", size * size); printf(" елементи(-ів) (для виходу введіть exit):\n");
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
				printf("Це не ейлерів граф\n");
				printf("Натисніть будь-яку клавішу для продовження.");
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
				printf("Це не ейлерів граф\n");
				printf("Натисніть будь-яку клавішу для продовження.");
				_getch();
				system("CLS");
				return;
			}
		}
		else
		{
			printf("Це не ейлерів граф\n");
			printf("Натисніть будь-яку клавішу для продовження.");
			_getch();
			system("CLS");
			return;
		}
	}
	bool euler_or_semi_euler = true;				//флаг для типу ейлеровості
	if (minus && plus)
	{
		euler_or_semi_euler = !euler_or_semi_euler;
	}
	graph adj(size);
	for (int i = 0; i < size; i++)					//створюємо 2д вектор для збереження 
	{												//ребер графу для побудови шляху
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
		printf("Ейлерів цикл:\n");
		flag = 1;
	}
	else
	{
		printf("Ейлерів шлях:\n");
		flag = 0;
	}
	vector<int> circuit = Hol_print(adj);
	printf("\n");
	//----------------------------------------------------------Кінець будування ------ Збереження
	printf("Бажаєте зберігти? (Y/N)\n");
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
			if (!(history.is_open()))					//якщо файле не існує - створюємо і одразу відкриваємо
			{
				history.open("history.txt", ios::out);
				history.close();
				history.open("history.txt", ios::in);
			}
			const int top_n = 9; 
			string buff[top_n];
			string line;
			string buffer;
			for (int i = 0; i < top_n; ++i)					//копіюємо дані з файлу у баффер
			{
				getline(history, buffer);
				if (buffer == "") break;
				buff[i] = buffer;
			}
			history.close();

			history.open("history.txt", ios::out);		//перезаписуємо файл новими даними
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
			for (int i = 0; i < top_n; ++i)		//та доповнюємо баффером. Таким чином у нас завжди будуть 10 останніх записів
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