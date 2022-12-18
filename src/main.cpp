#include <iostream>
#include <cstring>
#include "tnode.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Ru");

    struct tnode* root = NULL; // Адрес корня дерева
    struct tnode* point = NULL; // Адрес для работы

    int size = 10; // Размер тестового списка
    int *testArr = new int[size]; // Тестовый список
    for (int i = 0; i < size; i++) { // Цикл заполнение списка
        testArr[i] = -50 + (rand() % 100); // Заполнения списка рандомными значениями
    }

    int answ = 1; // Значение для цикла while
    int count; // Количество узлов
    int maxlevel = 0; // Максимальный уровень
    cout << "Чтение узлов с массива..." << endl;
    for (count = 0; count < size; count++) { // Добавление узлов в дерево
        root = addTree(root, testArr[count]);
    }
    count = 0; // Обнуление количества узлов
    BotBorder(); // Отрисовка разделителя
    while (answ != 0)
    {
        cout << "Дерево:" << endl;
        cout << "lvl:0\t" << "lvl:1\t" << "lvl:2\t" << "lvl:3\t" << "lvl:4\t" << "lvl:5\t" << "lvl:6\t" << endl;
        printTree(root, 0); cout << endl;
        cout << "Как же я люблю узлы, вот они слева направо : " << endl << " ";
        preOrderTravers(root, maxlevel, count); cout << endl;
        cout << "Корень: root = " << root->num << endl << endl;

        cout << "Меню:" << endl;
        cout << "1: Поиск и выведение информации о точке" << endl;
        cout << "2: Добавить узел" << endl;
        cout << "3: Удалить узел" << endl;
        cout << "4: Обход дерева, нахождение высоты дерева и количества узлов" << endl;
        cout << "5: Вывод дерева на экран" << endl;
        cout << "6: Задание №2" << endl;
        cout << "0: ВЫХОД" << endl;
        BotBorder(); // Отрисовка разделителя

        cout << " Значение: ";
        cin >> answ;
        cout << endl;

        switch (answ)
        {
        case 1:
        {
            cout << "\tИнформация точки:" << endl;
            cout << " Введите точку: ";
            int info;
            cin >> info;
            dataPoint(search(root, info));
            break;
        }
        case 2: // Добавление узла
        {
            cout << "\t\tДобавление узла:" << endl;
            cout << " Введите значение: ";
            int addp;
            cin >> addp;
            root = addTree(root, addp);
            break;
        }
        case 3: // Удаление
        {
            cout << "\t\tУдаление узла:" << endl;
            cout << " Выберите какой узел удалить: ";
            int delword;
            struct tnode* delpoint;            // Адрес для работы
            cin >> delword;
            delpoint = search(root, delword);
            delp(&root, delpoint);
            break;
        }
        case 4: // Обход
        {
            cout << endl << "\t\t  Прямой обход в глубину"
                << endl << "\t\t нахождение высоты дерева"
                << endl << "\t\tНахождение количества узлов" << endl;
            int count = 0;
            int maxlevel = 0;
            preOrderTravers(root, maxlevel, count);
            cout << endl << " Конец перехода" << endl;
            cout << " Итого: " << endl;
            cout << " Высота дерева:" << maxlevel << endl;
            cout << " Количество узлов: " << count << endl;
            break;
        }
        case 5: // Печать дерева
        {
            cout << " Дерево: ";
            printTree(root, 0); cout << endl;
            break;
        }
        case 6: // Задание 6
        {
            int sum = 0;                     // Счётчик согласных
            task6(root, sum);
            cout << " Сумма: " << sum << endl;
            break;
        }
        default:
        {
            cout << " Введите корректное значение" << endl;
            break;
        }
        }

        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    }
    freeMem(root);
    return 0;
}