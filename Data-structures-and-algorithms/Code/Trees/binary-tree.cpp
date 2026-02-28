#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

struct tree {
    int inf;
    tree* left;
    tree* right;
    tree* parent;
};

//создание узла
tree* node(int x) {
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = n->parent = NULL;
    return n;
}

//вставка элемента в дерево бинарного поиска
void insert(tree*& tr, int x) {
    tree* n = node(x);
    if (!tr) tr = n; //если дерево пустое - корень
    else {
        tree* y = tr;
        while (y) { //ищем куда вставл¤ть
            if (n->inf > y->inf) { //права¤ ветка
                if (y->right) y = y->right;
                else {
                    n->parent = y; //узел становитс¤ правым ребенком
                    y->right = n;
                    break;
                }
            }
            else if (n->inf < y->inf) { //лева¤ ветка
                if (y->left) y = y->left;
                else {
                    n->parent = y; //узел становитс¤ левым ребенком
                    y->left = n;
                    break;
                }
            }
            else {
                delete n;
                break;
            }
        }
    }
}

//поиск элемента в дереве бинарного поиска
tree* find(tree* tr, int x) {
    if (!tr || tr->inf == x) return tr; //нашли или дошли до конца ветки
    if (x < tr->inf)
        return find(tr->left, x); //ищем по левой ветке
    else
        return find(tr->right, x); //ищем по правой ветке
}

//поиск минимального элемента
tree* Min(tree* tr) {
    if (!tr->left) return tr; //нет левого ребенка
    else return Min(tr->left); //идем по левой ветке до конца
}

//поиск максимального элемента
tree* Max(tree* tr) {
    if (!tr->right) return tr; //нет правого ребенка
    else return Max(tr->right); //идем по правой ветке до конца
}

//поиск следующего элемента
tree* Next(tree* tr, int x) {
    tree* n = find(tr, x);
    if (!n) return NULL;

    if (n->right) //если есть правый ребенок
        return Min(n->right); //min по правой ветке

    tree* y = n->parent; //родитель
    while (y && n == y->right) { //пока не дошли до корн¤ или узел - правый ребенок
        n = y; //идем вверх по дереву
        y = y->parent;
    }
    return y; //возвращаем родител¤
}

//удаление узла из дерева бинарного поиска
void Delete(tree*& tr, tree* v) {
    if (!v) return;

    tree* p = v->parent;

    //1.удаление листа
    if (!v->left && !v->right) {
        if (!p) tr = NULL;
        else {
            if (p->left == v) p->left = NULL;
            else p->right = NULL;
        }
        delete v;
    }
    //2.удаление узла с одним ребенком
    else if (!v->left || !v->right) {
        tree* child = v->left ? v->left : v->right;
        if (p) {
            if (p->left == v) p->left = child;
            else p->right = child;
            child->parent = p;
        }
        else {
            tr = child;
            child->parent = NULL;
        }
        delete v;
    }
    //3.удаление узла с двум¤ детьми
    else {
        tree* succ = Min(v->right); //следующий за удал¤емым узлом
        v->inf = succ->inf; //присваиваем значение
        Delete(tr, succ);
    }
}

//определение максимальной высоты дерева
void max_height(tree* x, short& max, short deepness = 1) {
    if (deepness > max) max = deepness;
    if (x->left) max_height(x->left, max, deepness + 1);
    if (x->right) max_height(x->right, max, deepness + 1);
}

//проверка размера консоли
bool isSizeOfConsoleCorrect(const short& width, const short& height) {
    GetConsoleScreenBufferInfo(outp, &csbInfo);
    COORD szOfConsole = csbInfo.dwSize;
    if (szOfConsole.X < width || szOfConsole.Y < height) {
        cout << "Please increase the size of the terminal. Size now: "
            << szOfConsole.X << "x" << szOfConsole.Y
            << ". Minimum required: " << width << "x" << height << ".\n";
        return false;
    }
    return true;
}

//вспомогательна¤ функци¤ дл¤ вывода дерева
void print_helper(tree* x, const COORD pos, const short offset) {
    SetConsoleCursorPosition(outp, pos);
    cout << right << setw(offset + 1) << x->inf;
    if (x->left) print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right) print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

//вывод дерева в консоль
void printTree(tree* tr) {
    if (tr) {
        short max = 1;
        max_height(tr, max);
        short width = 1 << (max + 1);
        short max_w = 128;
        if (width > max_w) width = max_w;

        while (!isSizeOfConsoleCorrect(width, max)) {
            system("pause");
        }

        for (short i = 0; i < max; ++i) cout << '\n';

        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD endPos = csbInfo.dwCursorPosition;

        print_helper(tr, { 0, short(endPos.Y - max) }, width >> 1);

        SetConsoleCursorPosition(outp, endPos);
    }
    else {
        cout << "The tree is empty." << endl;
    }
}

//пр¤мой обход (корень-левый-правый)
void preorder(tree* tr) {
    if (tr) {
        cout << tr->inf << " "; //корень
        preorder(tr->left); //левое поддерево
        preorder(tr->right); //правое поддерево
    }
}

//симметричный обход (левый-корень-правый)
void inorder(tree* tr) {
    if (tr) {
        inorder(tr->left); //левое поддерево
        cout << tr->inf << " "; //корень
        inorder(tr->right); //правое поддерево
    }
}

//обратный обход (Ћевый-ѕравый- орень)
void postorder(tree* tr) {
    if (tr) {
        postorder(tr->left); //левое поддерево
        postorder(tr->right); //правое поддерево
        cout << tr->inf << " "; //корень
    }
}

void callOrder(tree* tr) {
    cout << "пр¤мой обход (preorder): ";
    preorder(tr);
    cout << endl;

    cout << "симметричный обход (inorder): ";
    inorder(tr);
    cout << endl;

    cout << "обратный обход (postorder): ";
    postorder(tr);
    cout << endl;
}


int main() {
    setlocale(LC_ALL, "RUS");
    tree* tr = NULL;
    int n, x;
    cout << "n: ";
    cin >> n;
    cout << "enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        insert(tr, x);
    }

    cout << "tree:" << endl;
    printTree(tr);
    cout << endl;

    callOrder(tr);
    cout << endl;

    cout << "=== вставка элемента ===" << endl;
    cout << "¬ведите элемент дл¤ вставки: ";
    cin >> x;
    insert(tr, x);
    cout << "Ёлемент " << x << " вставлен в дерево." << endl;
    cout << "ƒерево после вставки:" << endl;
    printTree(tr);
    cout << endl;
    cout << endl;
    callOrder(tr);

    cout << "=== удаление элемента ===" << endl;
    cout << "¬ведите элемент дл¤ удалени¤: ";
    cin >> x;

    tree* toDelete = find(tr, x);
    if (toDelete) {
        Delete(tr, toDelete);
        cout << "Ёлемент " << x << " удален из дерева." << endl;
        cout << "ƒерево после удалени¤:" << endl;
        printTree(tr);
        cout << endl;
    }
    else {
        cout << "Ёлемент " << x << " не найден в дереве!" << endl;
    }
    cout << endl;

    callOrder(tr);

    return 0;
}