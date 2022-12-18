#include <iostream>
#include "tnode.h"
using namespace std;

tnode* addTree(struct tnode* root, int num)
{
    if (root == NULL)
    {
        root = new tnode;    // ������� �����

            root->back = NULL;
            root->level = 0;

        root->num = num;                               // ��������� �����
        root->count = 1;                                       // ������� +1
        root->left = root->right = NULL;                          // ������ �� �����  = 0
    }
    else if (num == root->num)  // ���� ������� ����� � ����� � ���� ��������
        root->count++;
    else if (num < root->num)                          // ����� ���� ������� ����� ������ ����� � ����
    {
        root->left = addTree(root->left, num);
        root->left->back = root;
        root->left->level = root->left->back->level + 1;
    }
    else
    {
        root->right = addTree(root->right, num);
        root->right->back = root;
        root->right->level = root->right->back->level + 1;
    }
    return root;
}

// ������� �������� ���������
void freeMem(tnode* tree) {
    if (tree != NULL) {
        freeMem(tree->left);
        freeMem(tree->right);
        free(tree);
    }
}
// ���������� ����
void addPoint(struct tnode* root, int num)
{
    root = addTree(root, num);
}
// ����� ���� �� ��� ��������
tnode* search(tnode* root, int key) {
    if (key > root->num) { 
        if (root->right != NULL) {
            search(root->right, key);
        }
        else {
            cout << "������� �� ������\n";
            return NULL;
        }
    }
    else if (key < root->num) {
        if (root->left != NULL) {
            search(root->left, key);
        }
        else {
            cout << "������� �� ������\n";
            return NULL;
        }
    }
    else if (key == root->num) {
        return root;
    }

 }
// ����� ���������� �� ����
void dataPoint(struct tnode* root)
{
    struct tnode* point = root;
    if (point)
    {
        cout << " ������ ����� " << point->num << " :" << endl;

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
        cout << "�����" << endl;
    }
}
// �������� ����
void delp(struct tnode** root, struct tnode* point)
{
    //struct tnode* point = (*root);

    //datapoint(*root);

    if (point == NULL)
    {
        cout << " ������� ����������, ������� ���� �� ����������" << endl
            << " ���������� ��� ������ ��� �������" << endl;
        return;
    }
    cout << " �������: " << point->num << endl;

    if ((point->left == NULL) && (point->right == NULL))                // ���� ����� ��������
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
    // ��������� � ����� �����
    else if (point->right == NULL)
    {
        if (point->back != NULL)
            // ������ � ������ ����� (����)
            if (point == point->back->right)
            {
                point->back->right = point->left;
                point->left->back = point->back;

                point->left->level = point->level;
                //free(point);
            }
        // ������ � ����� ����� (����)
            else
            {
                point->back->left = point->left;
                point->left->back = point->back;

                point->left->level = point->level;
                //free(point);
            }
        else  // ���� ������� ������
        {
            (*root) = point->left;
            point->left->back = NULL;
        }

        free(point);
    }
    // ��������� � ������ �����
    else if (point->left == NULL)
    {
        if (point->back != NULL)
            //  ������ � ������ ����� (����)
            if (point == point->back->right)
            {
                point->back->right = point->right;
                point->right->back = point->back;

                point->right->level = point->level;
                //free(point);
            }
        // ������ � ����� ����� 
            else
            {
                point->back->left = point->right;
                point->right->back = point->back;

                point->right->level = point->level;
                //free(point);
            }
        else // ���� ������� ������
        {
            (*root) = point->right;
            point->right->back = NULL;
        }

        free(point);
    }
    else // ������ ������
    {
        struct tnode* target = point;

        int flag = 0;                   // ������� � ��������� ��������� ����

        target = target->right;         // ������

        while (target->left != NULL)    // ����� ����
        {
            target = target->left;      // ����� ���������� �� ����� ������ ����������
            flag++;
        }

        struct tnode* pleft = target->left;
        struct tnode* pright = target->right;
        struct tnode* pback = target->back;

        cout << " ������ ������" << endl;

        cout << " ���������� target" << endl << endl;

        cout << " ������ ��������� target" << endl;
        cout << " pleft \t: " << pleft << endl;
        cout << " pright\t: " << pright << endl;
        cout << " pback \t: " << pback << endl << endl;


        cout << " ��� ������, �� ��� ����� ���� ��������: " << endl;
        dataPoint(target);

        cout << " ��� �����, ��� ����� ���� �������: " << endl;
        dataPoint(point);

        cout << " flag: " << flag << endl << endl;

        // � ������ ������ ������ ��� ������ �����
        if (flag)                           // ������ ������ ������
            target->right = point->right;
        else
            target->right = point;
        target->left = point->left;
        target->level = point->level;
        target->back = point->back;
        target->count = point->count;

        cout << " target: " << target;

        if (point->back)                        // ���� �� ��������
        {
            if (point->back->right == point)    // ������ ��������� � �������
                point->back->right = target;
            else
                point->back->left = target;
        }
        else (*root) = target;

        point->left->back = target;         // ������ ����� � �������
        if (flag)
            point->right->back = target;
        //______________________________

        cout << " point ������ ��������� � target: " << endl;
        cout << " �����: " << endl;
        dataPoint(point);
        cout << " ������: " << endl;
        dataPoint(target);

        // � ����� ������ ��� ���� (�� ��� ���� � ������)
        point->right = pright;
        point->left = pleft;
        point->back = pback;
        if (flag)
            pback->left = point;
        else
            point->back = target;
        cout << endl;

        cout << " point ������ ��������� temp: " << endl;

        cout << " temp:" << endl;
        cout << " pleft : " << pleft << endl;
        cout << " pright: " << pright << endl;
        cout << " pback: " << pback << endl << endl;

        cout << " �����: " << endl;
        dataPoint(point);

        cout << " ������: " << endl;
        dataPoint(target);

        cout << " root: " << endl;
        dataPoint(*root);

        delp(root, point);
    }
}
// ������ ������
void printTree(struct tnode* root, int level)
{
    if (root)
    {
        printTree(root->right, level + 1);                      // ����� ������� ���������
        for (int i = 0; i < level; i++) cout << "\t";
        cout << " " << root->num << endl;                             // ����� ����� ���������
        printTree(root->left, level + 1);                       // ����� ������ ���������
    }
}
// ������ ����� � �������
void preOrderTravers(tnode* root, int& mlevel, int& count)
{
    int level = mlevel;
    if (root)
    {
        cout << root->num << " ";              // ����� ���� �� �����
        level = root->level;                    // | ����� 
        if (mlevel < level) mlevel = level;     // | ������������� ������
        count++;                                // ������� ���������� �����
        preOrderTravers(root->left, mlevel, count);
        preOrderTravers(root->right, mlevel, count);
    }
}
void BotBorder() { cout << "___________________________________________________________________" << endl; }


// ����� ����� ���� ���������, ������� 5
void task6(tnode* root, int& sum)
{
    if (root)
    {
        if (!(root->num % 5)) {
            sum += root->num;
        }
        task6(root->left, sum);
        task6(root->right, sum);
    }
}