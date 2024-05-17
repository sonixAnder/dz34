#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Структура для хранения данных о сотруднике
struct Employee
{
    string lastName;  // Фамилия
    string firstName; // Имя
    int age;         // Возраст
};

// Функция для вывода информации о сотруднике
void printEmployee(const Employee& employee)
{
    cout << "Фамилия: " << employee.lastName << endl;
    cout << "Имя: " << employee.firstName << endl;
    cout << "Возраст: " << employee.age << endl;
    cout << "--------------------" << endl;
}

// Функция для добавления нового сотрудника
void addEmployee(vector<Employee>& employees)
{
    Employee employee;
    cout << "Введите фамилию: ";
    cin >> employee.lastName;
    cout << "Введите имя: ";
    cin >> employee.firstName;
    cout << "Введите возраст: ";
    cin >> employee.age;

    employees.push_back(employee);
}

// Функция для редактирования данных сотрудника
void editEmployee(vector<Employee>& employees)
{
    string lastName;
    cout << "Введите фамилию сотрудника для редактирования: ";
    cin >> lastName;

    for (auto& employee : employees)
    {
        if (employee.lastName == lastName)
        {
            cout << "Введите новую фамилию: ";
            cin >> employee.lastName;
            cout << "Введите новое имя: ";
            cin >> employee.firstName;
            cout << "Введите новый возраст: ";
            cin >> employee.age;
            return;
        }
    }

    cout << "Сотрудник с такой фамилией не найден." << endl;
}

// Функция для удаления сотрудника
void deleteEmployee(vector<Employee>& employees)
{
    string lastName;
    cout << "Введите фамилию сотрудника для удаления: ";
    cin >> lastName;

    for (auto it = employees.begin(); it != employees.end(); ++it)
    {
        if (it->lastName == lastName)
        {
            employees.erase(it);
            return;
        }
    }

    cout << "Сотрудник с такой фамилией не найден." << endl;
}

// Функция для поиска сотрудника по фамилии
void searchByLastName(const vector<Employee>& employees)
{
    string lastName;
    cout << "Введите фамилию для поиска: ";
    cin >> lastName;

    for (const auto& employee : employees)
    {
        if (employee.lastName == lastName)
        {
            printEmployee(employee);
            return;
        }
    }

    cout << "Сотрудник с такой фамилией не найден." << endl;
}

// Функция для вывода информации о сотрудниках указанного возраста
void printByAge(const vector<Employee>& employees)
{
    int age;
    cout << "Введите возраст для поиска: ";
    cin >> age;

    for (const auto& employee : employees)
    {
        if (employee.age == age)
        {
            printEmployee(employee);
        }
    }
}

// Функция для вывода информации о сотрудниках, фамилия которых начинается на указанную букву
void printByFirstLetter(const vector<Employee>& employees)
{
    char letter;
    cout << "Введите первую букву фамилии: ";
    cin >> letter;

    for (const auto& employee : employees)
    {
        if (employee.lastName[0] == letter)
        {
            printEmployee(employee);
        }
    }
}

// Функция для сохранения информации о сотрудниках в файл
void saveToFile(const vector<Employee>& employees, const string& filename)
{
    ofstream outfile(filename);

    if (outfile.is_open())
    {
        for (const auto& employee : employees)
        {
            outfile << employee.lastName << " " << employee.firstName << " " << employee.age << endl;
        }
        outfile.close();
        cout << "Данные сохранены в файл " << filename << endl;
    }
    else
    {
        cout << "Ошибка открытия файла " << filename << endl;
    }
}

// Функция для загрузки информации о сотрудниках из файла
void loadFromFile(vector<Employee>& employees, const string& filename)
{
    ifstream infile(filename);

    if (infile.is_open())
    {
        Employee employee;
        while (infile >> employee.lastName >> employee.firstName >> employee.age)
        {
            employees.push_back(employee);
        }
        infile.close();
        cout << "Данные загружены из файла " << filename << endl;
    }
    else {
        cout << "Ошибка открытия файла " << filename << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    vector<Employee> employees;
    string filename;
    cout << "Введите имя файла для загрузки данных: ";
    cin >> filename;
    loadFromFile(employees, filename);

    int choice;
    do
    {
        cout << "\nМеню:\n";
        cout << "1. Добавить сотрудника\n";
        cout << "2. Редактировать данные сотрудника\n";
        cout << "3. Удалить сотрудника\n";
        cout << "4. Поиск сотрудника по фамилии\n";
        cout << "5. Вывести информацию о сотрудниках указанного возраста\n";
        cout << "6. Вывести информацию о сотрудниках, фамилия которых начинается на указанную букву\n";
        cout << "7. Сохранить данные в файл\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addEmployee(employees);
            break;
        case 2:
            editEmployee(employees);
            break;
        case 3:
            deleteEmployee(employees);
            break;
        case 4:
            searchByLastName(employees);
            break;
        case 5:
            printByAge(employees);
            break;
        case 6:
            printByFirstLetter(employees);
            break;
        case 7:
            cout << "Введите имя файла для сохранения данных: ";
            cin >> filename;
            saveToFile(employees, filename);
            break;
        case 0:
            cout << "Выход из программы...\n";
            break;
        default:
            cout << "Некорректный выбор.\n";
        }
    } while (choice != 0);

    saveToFile(employees, filename); // автоматическое сохранение при выходе
    return 0;
}