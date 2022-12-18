

#ifndef TNODE


#define TNODE


using namespace std;

struct tnode                     // узел дерева
{
    int num;                     // указатель на строку (слово)
    int count;                   // число вхождений
    struct tnode* left;          // левый потомок
    struct tnode* right;         // правый потомок
    struct tnode* back;          // родитель
    int level;                   // уровень 
};

// Добавление узла в дерево
tnode* addTree(struct tnode* point, int num);
// Удаление поддерева
void freeMem(tnode* tree);
// Добавление узла
void addPoint(struct tnode* root, int znach);
// Поиск узла
struct tnode* search(struct tnode* root, int key);
// Информация об узле 
void dataPoint(struct tnode* root);
// Удаление узла
void delp(struct tnode** root, struct tnode* point);
// Печать дерева
void printTree(struct tnode* root, int level);
// Прямой обход в глубину
void preOrderTravers(tnode* root, int& mlevel, int& count);
//ХУЕТА!!!
void BotBorder();

void task2(tnode* root, int& gl);


#endif // !TNODE
