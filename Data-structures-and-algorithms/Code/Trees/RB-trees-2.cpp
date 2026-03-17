#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

#define RED true
#define BLACK false

//структура узла дерева
struct tree {
    int inf;
    bool color;
    tree* left, * right, * parent;
};

//глобальные переменные для работы с консолью
HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

//прототипы функций
void insert_case1(tree*& tr, tree* n);
void insert_case2(tree*& tr, tree* n);
void insert_case3(tree*& tr, tree* n);
void insert_case4(tree*& tr, tree* n);
void insert_case5(tree*& tr, tree* n);
void delete_node(tree*& tr, int x);
void delete_case1(tree*& tr, tree* n);
void delete_case2(tree*& tr, tree* n);
void delete_case3(tree*& tr, tree* n);
void delete_case4(tree*& tr, tree* n);
void delete_case5(tree*& tr, tree* n);
void delete_case6(tree*& tr, tree* n);
void replace_node(tree*& tr, tree* old_node, tree* new_node);
tree* find_min(tree* node);
tree* find_max(tree* node);

tree* node(tree* p, int x) {
    tree* n = new tree;
    n->inf = x;
    n->color = RED;
    n->parent = p;
    n->left = n->right = NULL;
    return n;
}

tree* root(int x) {
    tree* n = new tree;
    n->inf = x;
    n->color = BLACK;
    n->parent = n->left = n->right = NULL;
    return n;
}

//вспомогательные функции для работы с деревом
tree* grandparent(tree* n) {
    if (n && n->parent && n->parent->parent)
        return n->parent->parent;
    return NULL;
}

tree* uncle(tree* n) {
    tree* g = grandparent(n);
    if (!g) return NULL;
    if (n->parent == g->left)
        return g->right;
    else
        return g->left;
}

tree* sibling(tree* n) {
    if (!n || !n->parent) return NULL;
    if (n == n->parent->left)
        return n->parent->right;
    else
        return n->parent->left;
}

//поворот влево
void rotate_left(tree*& tr, tree* n) {
    if (!n || !n->right) return;

    tree* y = n->right;
    n->right = y->left;

    if (y->left)
        y->left->parent = n;

    y->parent = n->parent;

    if (!n->parent)
        tr = y;
    else if (n == n->parent->left)
        n->parent->left = y;
    else
        n->parent->right = y;

    y->left = n;
    n->parent = y;
}

//поворот вправо
void rotate_right(tree*& tr, tree* n) {
    if (!n || !n->left) return;
    tree* y = n->left;
    n->left = y->right;

    if (y->right)
        y->right->parent = n;

    y->parent = n->parent;

    if (!n->parent)
        tr = y;
    else if (n == n->parent->right)
        n->parent->right = y;
    else
        n->parent->left = y;

    y->right = n;
    n->parent = y;
}

//функции на разные случаи вставки
void insert_case5(tree*& tr, tree* n) {
    tree* g = grandparent(n);
    if (!g) return;

    n->parent->color = BLACK;
    g->color = RED;

    if (n == n->parent->left) {
        rotate_right(tr, g);
    }
    else {
        rotate_left(tr, g);
    }
}

void insert_case4(tree*& tr, tree* n) {
    tree* g = grandparent(n);
    if (!g) return;

    if (n == n->parent->right && n->parent == g->left) {
        rotate_left(tr, n->parent);
        n = n->left;
    }
    else if (n == n->parent->left && n->parent == g->right) {
        rotate_right(tr, n->parent);
        n = n->right;
    }

    insert_case5(tr, n);
}

void insert_case3(tree*& tr, tree* n) {
    tree* u = uncle(n);

    if (u && u->color == RED) {
        n->parent->color = BLACK;
        u->color = BLACK;
        tree* g = grandparent(n);
        if (g) {
            g->color = RED;
            insert_case1(tr, g);
        }
    }
    else {
        insert_case4(tr, n);
    }
}

void insert_case2(tree*& tr, tree* n) {
    if (!n->parent) return;
    if (n->parent->color == BLACK)
        return;
    else
        insert_case3(tr, n);
}

void insert_case1(tree*& tr, tree* n) {
    if (!n->parent) {
        n->color = BLACK;
        tr = n;
    }
    else {
        insert_case2(tr, n);
    }
}

//функция для вставки
void insert(tree*& tr, int x) {
    if (!tr) {
        tr = root(x);
        return;
    }

    tree* y = tr;
    tree* p = nullptr;

    while (y) {
        p = y;
        if (x < y->inf)
            y = y->left;
        else if (x > y->inf)
            y = y->right;
        else
            return;  //элемент уже существует
    }

    tree* n = node(p, x);
    if (x < p->inf)
        p->left = n;
    else
        p->right = n;

    insert_case1(tr, n);
}

//функция для создания дерева
tree* create_tree() {
    tree* tr = NULL;
    int n, x;
    cout << "введите количество элементов: ";
    cin >> n;

    if (n > 0) {
        cout << "элемент 1: ";
        cin >> x;
        tr = root(x);

        for (int i = 1; i < n; i++) {
            cout << "элемент " << i + 1 << ": ";
            cin >> x;
            insert(tr, x);
        }
    }
    return tr;
}

//функции для удаления
void replace_node(tree*& tr, tree* old_node, tree* new_node) {
    if (!old_node->parent) {
        tr = new_node;
        if (new_node) new_node->parent = NULL;
    }
    else {
        if (old_node == old_node->parent->left)
            old_node->parent->left = new_node;
        else
            old_node->parent->right = new_node;

        if (new_node)
            new_node->parent = old_node->parent;
    }
}

void delete_case6(tree*& tr, tree* n) {
    if (!n || !n->parent) return;

    tree* s = sibling(n);
    if (!s) return;

    s->color = n->parent->color;
    n->parent->color = BLACK;

    if (n == n->parent->left) {
        if (s->right) s->right->color = BLACK;
        rotate_left(tr, n->parent);
    }
    else {
        if (s->left) s->left->color = BLACK;
        rotate_right(tr, n->parent);
    }
}

void delete_case5(tree*& tr, tree* n) {
    if (!n || !n->parent) {
        delete_case6(tr, n);
        return;
    }

    tree* s = sibling(n);
    if (!s) {
        delete_case6(tr, n);
        return;
    }

    if (s->color == BLACK) {
        if ((n == n->parent->left) &&
            (!s->right || s->right->color == BLACK) &&
            (s->left && s->left->color == RED)) {

            s->color = RED;
            s->left->color = BLACK;
            rotate_right(tr, s);
        }
        else if ((n == n->parent->right) &&
            (!s->left || s->left->color == BLACK) &&
            (s->right && s->right->color == RED)) {

            s->color = RED;
            s->right->color = BLACK;
            rotate_left(tr, s);
        }
    }

    delete_case6(tr, n);
}

void delete_case4(tree*& tr, tree* n) {
    if (!n || !n->parent) {
        delete_case5(tr, n);
        return;
    }

    tree* s = sibling(n);
    if (!s) {
        delete_case5(tr, n);
        return;
    }

    if (n->parent->color == RED &&
        s->color == BLACK &&
        (!s->left || s->left->color == BLACK) &&
        (!s->right || s->right->color == BLACK)) {

        s->color = RED;
        n->parent->color = BLACK;
    }
    else {
        delete_case5(tr, n);
    }
}

void delete_case3(tree*& tr, tree* n) {
    if (!n) return;

    tree* s = sibling(n);
    bool parentBlack = (!n->parent || n->parent->color == BLACK);
    bool siblingBlack = (!s || s->color == BLACK);
    bool leftNephewBlack = (!s || !s->left || s->left->color == BLACK);
    bool rightNephewBlack = (!s || !s->right || s->right->color == BLACK);

    if (parentBlack && siblingBlack && leftNephewBlack && rightNephewBlack) {
        if (s) s->color = RED;
        if (n->parent)
            delete_case1(tr, n->parent);
    }
    else {
        delete_case4(tr, n);
    }
}

void delete_case2(tree*& tr, tree* n) {
    if (!n || !n->parent) {
        delete_case3(tr, n);
        return;
    }

    tree* s = sibling(n);

    if (s && s->color == RED) {
        n->parent->color = RED;
        s->color = BLACK;

        if (n == n->parent->left)
            rotate_left(tr, n->parent);
        else
            rotate_right(tr, n->parent);
    }

    delete_case3(tr, n);
}

void delete_case1(tree*& tr, tree* n) {
    if (!n) return;

    if (!n->parent) {
        if (n->left) {
            tr = n->left;
            tr->color = BLACK;
            tr->parent = NULL;
        }
        else if (n->right) {
            tr = n->right;
            tr->color = BLACK;
            tr->parent = NULL;
        }
    }
    else {
        delete_case2(tr, n);
    }
}

tree* find_min(tree* node) {
    if (!node) return NULL;
    while (node->left)
        node = node->left;
    return node;
}

tree* find_max(tree* node) {
    if (!node) return NULL;
    while (node->right)
        node = node->right;
    return node;
}

//основная функция удаления
void delete_node(tree*& tr, int x) {
    if (!tr) return;  //дерево пустое

    //поиск удаляемого узла
    tree* n = tr;
    while (n) {
        if (x < n->inf)
            n = n->left;
        else if (x > n->inf)
            n = n->right;
        else
            break;
    }
    if (!n) {
        cout << "Узел не найден!" << endl;
        return;
    }

    //случай 1: удаляемый узел имеет двух реальных детей
    if (n->left && n->right) {
        tree* buf;

        //выбор замены
        if (n->inf >= tr->inf) {
            buf = find_max(n->left);
        }
        else {
            buf = find_min(n->right);
        }

        if (!buf) return;

        n->inf = buf->inf;
        n = buf;
    }

    //определяем ребенка
    tree* child = n->left ? n->left : n->right;

    //случай 2: удаляемый узел имеет одного ребенка
    if (child) {
        //заменяем узел его ребенком
        replace_node(tr, n, child);

        //если удаляемый узел черный
        if (n->color == BLACK) {
            //если ребенок красный перекрашиваем в черный
            if (child->color == RED) {
                child->color = BLACK;
            }
            //если ребенок черный вызываем балансировку для ребенка
            else {
                delete_case1(tr, child);
            }
        }
        //если удаляемый узел красный удаляем

        delete n;
    }
    //случай 3: удаляемый узел не имеет детей
    else {
        //если узел черный вызываем балансировку
        if (n->color == BLACK) {
            delete_case1(tr, n);
        }

        //удаляем узел
        if (n->parent) {
            if (n == n->parent->left)
                n->parent->left = NULL;
            else
                n->parent->right = NULL;
        }
        else {
            tr = NULL;  //удаляем корень
        }

        delete n;
    }
}


void max_height(tree* x, short& max, short deepness = 1) {
    if (!x) return;
    if (deepness > max) max = deepness;
    if (x->left) max_height(x->left, max, deepness + 1);
    if (x->right) max_height(x->right, max, deepness + 1);
}

bool isSizeOfConsoleCorrect(const short& width, const short& height) {
    GetConsoleScreenBufferInfo(outp, &csbInfo);
    COORD szOfConsole = csbInfo.dwSize;
    if (szOfConsole.X < width && szOfConsole.Y < height)
        cout << "Please increase the height and width of the terminal. ";
    else if (szOfConsole.X < width)
        cout << "Please increase the width of the terminal. ";
    else if (szOfConsole.Y < height)
        cout << "Please increase the height of the terminal. ";

    if (szOfConsole.X < width || szOfConsole.Y < height) {
        cout << "Size of your terminal now: " << szOfConsole.X << ' ' << szOfConsole.Y
            << ". Minimum required: " << width << ' ' << height << ".\n";
        return false;
    }
    return true;
}

void print_helper(tree* x, const COORD pos, const short offset) {
    if (!x) return;

    SetConsoleTextAttribute(outp, x->color == RED ? 12 : 8);
    SetConsoleCursorPosition(outp, pos);
    cout << setw(offset + 1) << x->inf;

    if (x->left)
        print_helper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
    if (x->right)
        print_helper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
}

void print(tree* tr) {
    if (!tr) {
        cout << "Дерево пустое!" << endl;
        return;
    }

    short max = 1;
    max_height(tr, max);
    short width = 1 << (max + 1);
    short max_w = 128;
    if (width > max_w) width = max_w;

    system("cls");
    for (short i = 0; i < max; ++i)
        cout << '\n';

    GetConsoleScreenBufferInfo(outp, &csbInfo);
    COORD endPos = csbInfo.dwCursorPosition;

    print_helper(tr, { 0, short(endPos.Y - max) }, width >> 1);
    SetConsoleCursorPosition(outp, endPos);
    SetConsoleTextAttribute(outp, 7);
}

int main() {
    setlocale(LC_ALL, "RUS");
    int x;
    //создание дерева
    cout << "=== СОЗДАНИЕ КРАСНО-ЧЕРНОГО ДЕРЕВА ===\n";
    tree* tr = create_tree();
    cout << "\nисходное дерево:\n";
    print(tr);
    ////вставка нового элемента
    //cout << "\n=== ВСТАВКА НОВОГО ЭЛЕМЕНТА ===\n";
    //cout << "введите элемент для вставки: ";
    //cin >> x;
    //insert(tr, x);
    //cout << "\nдерево после вставки элемента " << x << ":\n";
    //print(tr);
    //удаление элемента
    cout << "\n=== УДАЛЕНИЕ ЭЛЕМЕНТА ===\n";
    cout << "введите элемент для удаления: ";
    cin >> x;
    delete_node(tr, x);
    cout << "\nдерево после удаления элемента " << x << ":\n";
    print(tr);
    return 0;
}