

#include <iostream>

#include "Header.h"

using namespace std;




tnode* addTree(struct tnode* node, int w)
{

    if (node == NULL)
    {
        node = new tnode;    // Создаем место

            node->back = NULL;
            node->level = 0;

        node->num = w;                               // Вставляем слово
        node->count = 1;                                       // Счётчик +1
        node->left = node->right = NULL;                          // Ссылки на концы  = 0
    }
    else if (w == node->num)  // Если заданое слово и слово в узле совпадут
        node->count++;
    else if (w < node->num)                          // Иначе если заданое слово больше слова в узле
    {
        node->left = addTree(node->left, w);
        node->left->back = node;
        node->left->level = node->left->back->level + 1;
    }
    else
    {
        node->right = addTree(node->right, w);
        node->right->back = node;
        node->right->level = node->right->back->level + 1;
    }
    return node;
}

// Функция удаления поддерева
void freeMem(tnode* tree) {
    if (tree != NULL) {
        freeMem(tree->left);
        freeMem(tree->right);
        free(tree);
    }
}
// Добавление узла
void addPoint(struct tnode* root, int znach)
{
    root = addTree(root, znach);
}
// Поиск узла по его значению
tnode* search(tnode* root, int key) {
    if (key > root->num) { 
        if (root->right != NULL) {
            search(root->right, key);
        }
        else {
            cout << "Элемент не найден\n";
            return NULL;
        }
    }
    else if (key < root->num) {
        if (root->left != NULL) {
            search(root->left, key);
        }
        else {
            cout << "Элемент не найден\n";
            return NULL;
        }
    }
    else if (key == root->num) {
        return root;
    }

 }
// Вывод информации об узле
void dataPoint(struct tnode* root)
{
    struct tnode* point = root;
    if (point)
    {
        cout << " Данные точки " << point->num << " :" << endl;

        cout << " " << point->num << "->point\t: " << point << ", ";
        if (point) cout << point->num; cout << endl;

        cout << " " << point->num << "->left\t: " << point->left << ", ";
        if (point->left) cout << point->left->num; cout << endl;

        cout << " " << point->num << "->right\t: " << point->right << ", ";
        if (point->right) cout << point->right->num; cout << endl;

        cout << " " << point->num << "->back\t: " << point->back << ", ";
        if (point->back) cout << point->back->num; cout << endl;

        cout << " " << point->num << "->level\t: " << point->level << endl;
        cout << " " << point->num << "->count\t: " << point->count << endl << endl;
    }
    else {
        cout << "ХУЕТА" << endl;
    }
}
// Удаление узла
void delp(struct tnode** root, struct tnode* point)
{
    //struct tnode* point = (*root);

    //datapoint(*root);

    if (point == NULL)
    {
        cout << " Удалить невозможно, данного узла не существует" << endl
            << " попробуйте для начала его создать" << endl;
        return;
    }
    cout << " Удаляем: " << point->num << endl;

    if ((point->left == NULL) && (point->right == NULL))                // Если точка конечная
    {
        if (point == point->back->left)
        {
            point->back->left = NULL;
            free(point);
        }
        else
        {
            point->back->right = NULL;
            free(point);
        }
    }
    // Наследник в левой ветви
    else if (point->right == NULL)
    {
        if (point->back != NULL)
            // Предок в правой ветви (Есть)
            if (point == point->back->right)
            {
                point->back->right = point->left;
                point->left->back = point->back;

                point->left->level = point->level;
                //free(point);
            }
        // Предок в левой ветви (есть)
            else
            {
                point->back->left = point->left;
                point->left->back = point->back;

                point->left->level = point->level;
                //free(point);
            }
        else  // Если удаляем корень
        {
            (*root) = point->left;
            point->left->back = NULL;
        }

        free(point);
    }
    // Наследник в правой ветви
    else if (point->left == NULL)
    {
        if (point->back != NULL)
            //  Предок в правой ветви (есть)
            if (point == point->back->right)
            {
                point->back->right = point->right;
                point->right->back = point->back;

                point->right->level = point->level;
                //free(point);
            }
        // Предок в левой ветви 
            else
            {
                point->back->left = point->right;
                point->right->back = point->back;

                point->right->level = point->level;
                //free(point);
            }
        else // Если удаляем корень
        {
            (*root) = point->right;
            point->right->back = NULL;
        }

        free(point);
    }
    else // Третий случай
    {
        struct tnode* target = point;

        int flag = 0;                   // Счётчик и индикатор спускания вниз

        target = target->right;         // Всегда

        while (target->left != NULL)    // Спуск вниз
        {
            target = target->left;      // Самый наименьший из узлов больше удаляемого
            flag++;
        }

        struct tnode* pleft = target->left;
        struct tnode* pright = target->right;
        struct tnode* pback = target->back;

        cout << " Третий случай" << endl;

        cout << " Скопировал target" << endl << endl;

        cout << " Должен равняться target" << endl;
        cout << " pleft \t: " << pleft << endl;
        cout << " pright\t: " << pright << endl;
        cout << " pback \t: " << pback << endl << endl;


        cout << " Это таргет, на эту точку буду заменять: " << endl;
        dataPoint(target);

        cout << " Это поинт, эту точку буду удалять: " << endl;
        dataPoint(point);

        cout << " flag: " << flag << endl << endl;

        // К адресу таргет цепляю все адреса поинт
        if (flag)                           // Цепляю данные таргет
            target->right = point->right;
        else
            target->right = point;
        target->left = point->left;
        target->level = point->level;
        target->back = point->back;
        target->count = point->count;

        cout << " target: " << target;

        if (point->back)                        // Если не корневой
        {
            if (point->back->right == point)    // Цепляю родителей к таргету
                point->back->right = target;
            else
                point->back->left = target;
        }
        else (*root) = target;

        point->left->back = target;         // Цепляю детей к таргету
        if (flag)
            point->right->back = target;
        //______________________________

        cout << " point должен совпадать с target: " << endl;
        cout << " Поинт: " << endl;
        dataPoint(point);
        cout << " Таргет: " << endl;
        dataPoint(target);

        // к поинт цепляю все темп (то что было у таргет)
        point->right = pright;
        point->left = pleft;
        point->back = pback;
        if (flag)
            pback->left = point;
        else
            point->back = target;
        cout << endl;

        cout << " point должен равняться temp: " << endl;

        cout << " temp:" << endl;
        cout << " pleft : " << pleft << endl;
        cout << " pright: " << pright << endl;
        cout << " pback: " << pback << endl << endl;

        cout << " Поинт: " << endl;
        dataPoint(point);

        cout << " Таргет: " << endl;
        dataPoint(target);

        cout << " root: " << endl;
        dataPoint(*root);

        delp(root, point);
    }
}
// Печать дерева
void printTree(struct tnode* root, int level)
{
    if (root)
    {
        printTree(root->right, level + 1);                      // вывод правого поддерева
        for (int i = 0; i < level; i++) cout << "\t";
        cout << " " << root->num << endl;                             // вывод корня поддерева
        printTree(root->left, level + 1);                       // вывод левого поддерева
    }
}
// Прямой обход в глубину
void preOrderTravers(tnode* root, int& mlevel, int& count)
{
    int level = mlevel;
    if (root)
    {
        cout << root->num << " ";              // Вывод узла на экран
        level = root->level;                    // | Поиск 
        if (mlevel < level) mlevel = level;     // | максимального уровня
        count++;                                // Счётчик количества узлов
        preOrderTravers(root->left, mlevel, count);
        preOrderTravers(root->right, mlevel, count);
    }
}
void BotBorder() { cout << "___________________________________________________________________" << endl; }


// Поиск суммы всех элементов, кратных 5
void task2(tnode* root, int& sum)
{
    if (root)
    {
        if (!(root->num % 5)) {
            sum += root->num;
        }
        task2(root->left, sum);
        task2(root->right, sum);
    }
}