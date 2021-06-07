#include "libs.h"
#include "Menu_info.h"
#include "Graphics_color.h"
using namespace std;

int flag;
int size;
vector<int> circuit; //вектор в якому зберігається шлях з фун-ії Hol_print
typedef vector <vector<int>> graph;

bool is_str_number(string str)
{
	for (int i = 0; i < str.length(); ++i)
	{
		if (isdigit(str[i]) == false)
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


void Hol_print(vector<vector<int>> adj)
{
	//adj - матриця суміжностей графу
	//edges - кількість ребер, що виходять з вершини
	//стек - для збереження вершин
	unordered_map<int, int> edges;
	stack<int> path_c;
	for (int i = 0; i < adj.size(); i++)
	{
		edges[i] = adj[i].size();//рахуємо кілкість ребер для моніторингу невикористаних
	}

	path_c.push(0);				 //починаємо з довільної вершини
	int curr_v = 0;				 //вершина, що зараз аналізується
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
}

void save(graph g, int s)
{
	printf("Бажаєте зберігти? (Y/N)\n");
	console_settings();
	char key;
	do
	{
		key = _getch();
		cout << key;
		if (key == 'n' || key == 'N')
		{
			exit(0);
		}
		if (key == 'y' || key == 'Y')
		{

			fstream history("history.txt", ios::in);
			if (!(history.is_open()))					//якщо файле не існує - створюємо і одразу відкриваємо
			{
				history.open("history.txt", ios::out);
				history.close();
				history.open("history.txt", ios::in);
			}

			vector<string> buff;
			string line;
			for (int i = 0; i < 9; ++i)					//копіюємо дані з файлу у баффер
			{
				getline(history, line);
				if (line == "") break;
				else
				{
					buff.push_back(line);
				}
			}
			history.close();
			history.open("history.txt", ios::out);		//перезаписуємо файл новими даними
			history << s << " ";
			for (int i = 0; i < s; ++i)
			{
				for (int j = 0; j < s; ++j)
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
			for (int i = 0; i < buff.size(); ++i)		//та доповнюємо баффером. Таким чином у нас завжди будуть 10 останніх записів
			{
				history << endl << buff[i];
			}
			break;
		}

	} while (!(key == 'n' && key == 'N' && key == 'y' && key == 'Y'));
}

void execute_graph()
{
	string s;
	printf("Задайте матрицю збіжності.\n");
	printf("Введіть кількість вершин: ");
	cin >> s;
	if (!(is_str_number(s)))
	{
		error_det();
		return;
	}
	size = stoi(s);
	printf("Введіть матрицю (допустима кількість ребер 0-9):\n");
	graph g(size, vector<int>(size));
	int k;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			do
			{
				k = _getch();
			} while (!(k >= '0' && k <= '9'));
			printf("%c", (char)k);
			if (k >= '0' && k <= '9')
			{
				g[i][j] = k - '0';
			}
			printf(" ");
		}
		printf("\n");
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

				printf("Это не ейлеров граф\n");
				return;
			}
		}
		else if (num == 1)
		{
			if (plus == false)
				plus = !plus;
			else
			{

				printf("Это не ейлеров граф\n");
				return;
			}
		}
		else
		{

			printf("Это не ейлеров граф\n");
			return;
		}
	}
	bool euler_or_semi_euler = true;				//флаг для типу ейлеровості
	if (minus && plus)
	{
		euler_or_semi_euler = !euler_or_semi_euler;
	}

	vector<vector<int>> adj(size);

	for (int i = 0; i < size; i++)
	{
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
		printf("Ейлеров цикл:\n");
		flag = 1;
	}
	else
	{
		printf("Ейлеров путь:\n");
		flag = 0;
	}
	Hol_print(adj);
	printf("\n");
	save(g, size);
}