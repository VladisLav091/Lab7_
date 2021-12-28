//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

#define N 100

struct deposid {
	int account_number;
	string client_name;
	string client_surname;
	string client_patronymic;
	double amount;
	int date_day;
	int date_month;
	int date_year;
};

int i = 0;  // Глобальная переменная, которая служит для подсчёта кол-ва депозитов.
string check;  //  Эта переменная служит для проверки того, что ввёл пользователь.
time_t now = time(0);
tm* localtm = localtime(&now);

string path = "file.txt";

void save(deposid *deps) {
	int k = 0;
	string msg;
	string tmp;
	fstream fs;
	fs.open(path, fstream::out);
	if (!fs.is_open()) {
		cout << "Ошибка чтения файла!";
	}
	else {
		while (!fs.eof()) {
			tmp = "";
			getline(fs, tmp);
			for (int j = 0; j < i; j++) {
				stringstream ss;
				ss << deps[j].amount;
				msg = to_string(deps[j].account_number) + " " + deps[j].client_name + " " + deps[j].client_surname + " " + deps[j].client_patronymic + " " + ss.str() + " " + to_string(deps[j].date_day) + " " + to_string(deps[j].date_month) + " " + to_string(deps[j].date_year);
				if (tmp == msg) { k++; }
			}
		}
		for (int j = k; j < i; j++) {
			ofstream fout;
			fout.open(path, ofstream::app);
			stringstream ss;
			ss << deps[j].amount;
			msg = to_string(deps[j].account_number) + " " + deps[j].client_name + " " + deps[j].client_surname + " " + deps[j].client_patronymic + " " + ss.str() + " " + to_string(deps[j].date_day) + " " + to_string(deps[j].date_month) + " " + to_string(deps[j].date_year);
			fout << msg << "\n";
			fout.close();
		}
	}
	fs.close();
	k = 0;
}

bool check_deposid(deposid *deps, string buffer_name, string buffer_surname, string buffer_patronymic, int buffer_amount, int i) {
	for (int j = 0; j < i + 1; j++) {
		if ((string)buffer_name == (string)deps[j].client_name) {
			if ((string)buffer_surname == (string)deps[j].client_surname) {
				if ((string)buffer_patronymic == (string)deps[j].client_patronymic) {
					return true;
				}
				else { return false; }
			}
			else { return false; }
		}
		else { return false; }
	}
}

int create_deposid(deposid *deps, int buffer_account_number, string buffer_name, string buffer_surname, string buffer_patronymic, int buffer_amount, int buffer_date_day, int buffer_date_month, int buffer_date_year) {

	bool saved = false;

	cout << "Вы окрыли раздел создания депозита. Для начала работы введите ключевое слово yes. Для возвращения к меню введите menu." << endl;

	cin >> check;  //  В переменную check передаётся то, что ввёл пользователь.
	cout << endl;

	if (check == "yes" or check == "YES" or check == "Yes") {
		cout << "==============================" << endl;
		buffer_account_number = i + 1;
		buffer_date_day = localtm->tm_mday;
		buffer_date_month = localtm->tm_mon + 1;
		buffer_date_year = localtm->tm_year - 100;
		cout << "Введите ваше имя: "; cin >> buffer_name; cin.ignore();
		for (int j = 0; j < buffer_name.length(); j++) {
			if (!isalpha(buffer_name[j])) {
				cout << "Не допустимое значение!" << endl;
				return 1;
			}
		}
		cout << "Введите вашу фамилию: "; cin >> buffer_surname; cin.ignore();
		for (int j = 0; j < buffer_surname.length(); j++) {
			if (!isalpha(buffer_surname[j])) {
				cout << "Не допустимое значение!" << endl << endl;
				return 1;
			}
		}
		cout << "Введите ваше отчество: "; cin >> buffer_patronymic; cin.ignore();
		for (int j = 0; j < buffer_patronymic.length(); j++) {
			if (!isalpha(buffer_patronymic[j])) {
				cout << "Не допустимое значение!" << endl << endl;
				return 1;
			}
		}
		cout << "Введите сумму депозита: "; cin >> buffer_amount; cin.ignore();
		for (int j = 0; j < to_string(buffer_amount).length(); j++) {
			if (!isdigit(to_string(buffer_amount)[j])) {
				cout << "Не допустимое значение!" << endl << endl;
				return 1;
			}
		}
		cout << "==============================" << endl << endl;

		if (check_deposid(deps, buffer_name, buffer_surname, buffer_patronymic, buffer_amount, i)) {
			cout << "Депозит на этого человека существует. Хотите создать новый счёт?." << endl;
			cout << "В случае положительного ответа введите yes, если желаете вернуться к меню, то введите menu." << endl;
			cin >> check;

			if (check == "yes" or check == "YES" or check == "Yes") {
				deps[i].account_number = buffer_account_number;
				deps[i].date_day = buffer_date_day;
				deps[i].date_month = buffer_date_month;
				deps[i].date_year = buffer_date_year;
				deps[i].client_name = buffer_name;
				deps[i].client_surname = buffer_surname;
				deps[i].client_patronymic = buffer_patronymic;
				deps[i].amount = buffer_amount;
				i++;
				cout << endl << "==============================" << endl << endl;
				if (!saved) {
					save(deps);
				}
			}
			else { return 1; }
		}
		else {
			deps[i].account_number = buffer_account_number;
			deps[i].date_day = buffer_date_day;
			deps[i].date_month = buffer_date_month;
			deps[i].date_year = buffer_date_year;
			deps[i].client_name = buffer_name;
			deps[i].client_surname = buffer_surname;
			deps[i].client_patronymic = buffer_patronymic;
			deps[i].amount = buffer_amount;
			i++;
			if (!saved) {
				save(deps);
				saved = true;
			}
		}
		cout << endl;
	}
	else if (check == "menu" or check == "MENU" or check == "Menu") {
		saved = false;
		cin.clear();
		return 1;
	}
	else {
		cout << "Ключевое слово не найдено. Попробуйте снова..." << endl;
		saved = false;
		cin.clear();
		return 1;
	}
	saved = false;
	cin.clear();
}

void show_deposid(deposid *deps, string name, string surname, string patronymic, int amount, int buffer_date_day, int buffer_date_month, int buffer_date_year) {
	int check_user = 0;  // Кол-во найденных пользователей.

	cout << "==============================" << endl;
	cout << "Имя: " << name << endl;
	cout << "Фамилия: " << surname << endl;
	cout << "Отчество: " << patronymic << endl;

	for (int j = 0; j < i; j++) {
		if ((string)name == (string)deps[j].client_name) {
			if ((string)surname == (string)deps[j].client_surname) {
				if ((string)patronymic == (string)deps[j].client_patronymic) {
					if (amount == deps[j].amount) {
						check_user++;
						cout << "Номер депозита: " << deps[j].account_number << endl;
						cout.precision(2);
						cout << "Сумма депозита: " << fixed << deps[j].amount << " руб." << endl;
						cout << "Дата депозита: " << deps[j].date_day << "." << deps[j].date_month << "." << deps[j].date_year << endl;
					}
				}
			}
		}
	}

	if (check_user == 0) {
		cout << "Депозит на этого человека не найден." << endl;
	}
	cout << "==============================" << endl << endl;
	cin.clear();
}

void find_amount_all(deposid *deps, int sum) {
	int count = 0;
	for (int j = 0; j < i; j++) {
		if (deps[j].amount >= sum) {
			cout << "Номер депозита: " << deps[j].account_number << endl;
			cout << "Имя: " << deps[j].client_name << endl;
			cout << "Фамилия: " << deps[j].client_surname << endl;
			cout << "Отчество: " << deps[j].client_patronymic << endl;
			cout.precision(2);
			cout << "Сумма депозита: " << fixed << deps[j].amount << " руб." << endl;
			cout << "Дата депозита: " << deps[j].date_day << "." << deps[j].date_month << "." << deps[j].date_year << endl << endl;
			cout << "=======================================" << endl << endl;
			count++;
		}
	}
	if (count == 0) {
		cout << "Депозитов выше указанной суммы не найдено!" << endl;
	}

	count = 0;
	cin.clear();
}

void find_all_deposid(deposid *deps, string name, string surname, string patronymic) {
	cout << endl;
	cout << "==============================" << endl;
	cout << "Имя: " << name << endl;
	cout << "Фамилия: " << surname << endl;
	cout << "Отчество: " << patronymic << endl;

	for (int j = 0; j < i; j++) {
		if ((string)name == (string)deps[j].client_name) {
			if ((string)surname == (string)deps[j].client_surname) {
				if ((string)patronymic == (string)deps[j].client_patronymic) {
					cout << "--------------------" << endl;
					cout << "Номер депозита: " << deps[j].account_number << endl;
					cout.precision(2);
					cout << "Сумма депозита: " << fixed << deps[j].amount << " руб." << endl;
					cout << "Дата депозита: " << deps[j].date_day << "." << deps[j].date_month << "." << deps[j].date_year << endl << endl;
					cout << "--------------------" << endl;
				}
			}
		}
	}
	cin.clear();
}

void menu(deposid *deps) {
	int sum;  // Сумма, больше которой программа будет искать депозиты в функции под номером 3.
	int action;  // Номер, который введёт пользователь.

	int buffer_account_number=0;                 // | В эти переменные будут помещены данные, которые введёт пользователь.
	string buffer_name;          // | Затем программа проверит есть ли у этого человека депозит в нашем банке.
	string buffer_surname;       // | Если депозит есть, то программа предложит создать новый счёт в банке.
	string buffer_patronymic;   // | Если у пользователя это первый депозит в этом банке, то данные с этих переменных уйдут в массив deps.
	int buffer_amount =0;
	int buffer_date_day=0;
	int buffer_date_month=0;
	int buffer_date_year=0;

	cout << "==============================" << endl;
	cout << "Доступные действия:" << endl;
	cout << "\t" << "1) Добавить новый счёт." << endl;
	cout << "\t" << "2) Распечатать информацию о счете в табличном виде." << endl;
	cout << "\t" << "3) определить все счета с суммой больше заданной." << endl;
	cout << "\t" << "4) Найти все счета заданного клиента (по имени и фамилии)." << endl;
	cout << "\t" << "5) Выйти из программы." << endl;
	cout << "==============================" << endl;
	cout << "Введите цифру от 1 до 5: "; cin >> action;
	cout << "==============================" << endl << endl;

	if (action == 1) {
		if (create_deposid(deps, buffer_account_number, buffer_name, buffer_surname, buffer_patronymic, buffer_amount, buffer_date_day, buffer_date_month, buffer_date_year) == 1) {
			menu(deps);
		}
		menu(deps);
	}
	else if (action == 2) {
		cout << "Введите имя, фамилию, отчество и сумму депозита для вывода данных." << endl;
		cout << "\tИмя: "; cin >> buffer_name; cin.ignore();
		cout << "\tФамилию: "; cin >> buffer_surname; cin.ignore();
		cout << "\tОтчество: "; cin >> buffer_patronymic; cin.ignore();
		cout << "\tСумма депозита: "; cin >> buffer_amount; cin.ignore();
		cout << endl;
		show_deposid(deps, buffer_name, buffer_surname, buffer_patronymic, buffer_amount, buffer_date_day, buffer_date_month, buffer_date_year);
		menu(deps);
	}
	else if (action == 3) {
		cout << "Введите сумму, выше либо равной которой необходимо найти депозиты:" << endl;
		cout << "\tСумма: "; cin >> sum; cin.ignore();
		find_amount_all(deps, sum);
		menu(deps);
	}
	else if (action == 4) {
		cout << "Введите имя, фамилию и отчество для вывода данных." << endl;
		cout << "Имя: "; cin >> buffer_name; cin.ignore();
		cout << "Фамилию: "; cin >> buffer_surname; cin.ignore();
		cout << "Отчество: "; cin >> buffer_patronymic; cin.ignore();
		find_all_deposid(deps, buffer_name, buffer_surname, buffer_patronymic);
		menu(deps);
	}
	else if (action == 5) {
		cout << "Завершение программы..." << endl;
		exit(0);
	}
	else {
		cin.clear(); //clear bad input flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
		cout << "Действие не найдено. Введите корректное значение..." << endl;
		menu(deps);
	}
}

int main() {
	setlocale(LC_ALL, "Rus");

	// Кол-во строк в загруженном файле
	ifstream in(path);
	string s;
	while (in.peek() != EOF) {
		getline(in, s);
		i++;
	}

	int err_year = 0;

	deposid *deps = new deposid[N];  //  Основной массив, содержащий все депозиты.

	int line_count = 0;
	string buffer; // буфер для строк из файла
	string tmp;
	int pos = 0;

	ifstream ff;
	ff.open(path);
	for (int j = 0; j < i; j++) {
		tmp = "";
		getline(ff, buffer);
		for (int k = 0; k < buffer.length(); k++) {
			if (!isspace(buffer[k])) {
				tmp += buffer[k];
				if (pos == 7) {
					istringstream iss(tmp, istringstream::in);
					iss >> deps[j].date_year;
					err_year++;
					if (err_year == 2) {
						pos = 0;
						tmp = "";
						err_year = 0;
					}
				}
			}
			else {
				if (pos == 0) {
					istringstream iss(tmp, istringstream::in);
					iss >> deps[j].account_number;
					pos++;
					tmp = "";
				}
				else if (pos == 1) {
					deps[j].client_name = tmp;
					pos++;
					tmp = "";
				}
				else if (pos == 2) {
					deps[j].client_surname = tmp;
					pos++;
					tmp = "";
				}
				else if (pos == 3) {
					deps[j].client_patronymic = tmp;
					pos++;
					tmp = "";
				}
				else if (pos == 4) {
					istringstream iss(tmp, istringstream::in);
					iss >> deps[j].amount;
					pos++;
					tmp = "";
				}
				else if (pos == 5) {
					istringstream iss(tmp, istringstream::in);
					iss >> deps[j].date_day;
					pos++;
					tmp = "";
				}
				else if (pos == 6) {
					istringstream iss(tmp, istringstream::in);
					iss >> deps[j].date_month;
					pos++;
					tmp = "";
				}
			}
		}
	}

	ff.close();

	cout << endl << "Добро пожаловать в программу - Банк." << endl << endl;

	menu(deps);

	delete[] deps;

	return 0;
}