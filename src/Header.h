

#ifndef TNODE


#define TNODE


using namespace std;

struct tnode                     // ���� ������
{
    int num;                     // ��������� �� ������ (�����)
    int count;                   // ����� ���������
    struct tnode* left;          // ����� �������
    struct tnode* right;         // ������ �������
    struct tnode* back;          // ��������
    int level;                   // ������� 
};

// ���������� ���� � ������
tnode* addTree(struct tnode* point, int num);
// �������� ���������
void freeMem(tnode* tree);
// ���������� ����
void addPoint(struct tnode* root, int znach);
// ����� ����
struct tnode* search(struct tnode* root, int key);
// ���������� �� ���� 
void dataPoint(struct tnode* root);
// �������� ����
void delp(struct tnode** root, struct tnode* point);
// ������ ������
void printTree(struct tnode* root, int level);
// ������ ����� � �������
void preOrderTravers(tnode* root, int& mlevel, int& count);
//�����!!!
void BotBorder();

void task2(tnode* root, int& gl);


#endif // !TNODE
