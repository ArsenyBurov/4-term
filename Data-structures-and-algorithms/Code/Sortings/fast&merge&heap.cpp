#include <iostream>
#include <chrono>
using namespace std;

//быстрая сортировка
void quickSort(int arr[], int L, int R) {
    //начальные индексы
    int i = L;
    int j = R;

    //выбираем опорный элемент из середины
    int op = arr[(L + R) / 2];

    //основной цикл разделения
    while (i <= j) {
        //двигаем i вправо, пока элементы меньше опорного
        while (arr[i] < op) {
            i++;
        }

        //двигаем j влево, пока элементы больше опорного
        while (arr[j] > op) {
            j--;
        }

        //если индексы не пересеклись, меняем элементы
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    //рекурсивно сортируем левую часть
    if (L < j) {
        quickSort(arr, L, j);
    }

    //рекурсивно сортируем правую часть
    if (i < R) {
        quickSort(arr, i, R);
    }
}

void merge(int arr[], int l, int r, int m) {
    if (l > r || m < l || m > r) {
        return;
    }
    //если в массиве 2 элемента
    if (r - l == 1) {
        if (arr[l] > arr[r]) {
            swap(arr[l], arr[r]);
        }
        return;
    }

    int size = r - l + 1;
    int* buf = new int[size];
    int cur = 0;
    int i = l;
    int j = m + 1;

    while (r - l + 1 != cur) {
        //дописываем в buf оставшиеся элементы от j до r
        if (i > m) {
            while (j <= r) {
                buf[cur++] = arr[j++];
            }
        }
        //иначе дописываем в buf оставшиеся элементы от i до m
        else if (j > r) {
            while (i <= m) {
                buf[cur++] = arr[i++];
            }
        }
        else if (arr[i] > arr[j]) {
            buf[cur++] = arr[j++];
        }
        else {
            buf[cur++] = arr[i++];
        }
    }

    for (int k = 0; k < size; k++) {
        arr[l + k] = buf[k];
    }

    delete[] buf;
}

//сортировка слиянием
void mergeSort(int arr[], int l, int r) {
    if (l > r) {
        return;
    }
    if (l == r) return;

    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, r, m);
}

void heapify(int arr[], int i, int N) {
    //полагаем, что i-тый элемент является максимальным
    int parent = i;

    while (true) {
        int leftChild = 2 * i + 1; //левый ребенок
        int rightChild = 2 * i + 2; //правый ребенок
        int maxElement = parent;

        //если существует левый ребенок и он больше текущего максимума
        if (leftChild < N && arr[leftChild] > arr[maxElement]) {
            maxElement = leftChild;
        }

        //если существует правый ребенок и он больше текущего максимума
        if (rightChild < N && arr[rightChild] > arr[maxElement]) {
            maxElement = rightChild;
        }

        //если максимум - это родитель, прекращаем цикл
        if (maxElement == parent) {
            break;
        }

        //иначе меняем местами максимум и родителя
        swap(arr[parent], arr[maxElement]);

        //продолжаем просеивание с позиции maxElement
        i = maxElement;
        parent = i;
    }
}

//пирамидальная сортировка
void heapSort(int arr[], int N) {
    for (int i = N / 2 - 1; i >= 0; i--) {
        heapify(arr, i, N);
    }

    for (int i = N - 1; i >= 1; i--) {
        //меняем местами корень с последним
        swap(arr[0], arr[i]);

        heapify(arr, 0, i);
    }
}

//вывод массива
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(nullptr));

    int choice_size, choice_sort;
    int size = 0;

    cout << "Выберите размер массива:\n";
    cout << "1. 50 000\n";
    cout << "2. 100 000\n";
    cout << "3. 500 000\n";
    cout << "4. 1 000 000\n";
    cout << "5. 15\n";
    cout << "Ваш выбор: ";
    cin >> choice_size;

    switch (choice_size) {
    case 1:
        size = 50000;
        break;
    case 2:
        size = 100000;
        break;
    case 3:
        size = 500000;
        break;
    case 4:
        size = 1000000;
        break;
    case 5:
        size = 15;
        break;
    default:
        cout << "Неверный выбор. Используем 50 000 элементов.\n";
        size = 50000;
    }

    cout << "\nРазмер массива: " << size << " элементов\n\n";

    cout << "Выберите алгоритм сортировки:\n";
    cout << "1. Быстрая сортировка (quickSort)\n";
    cout << "2. Сортировка слиянием (mergeSort)\n";
    cout << "3. Пирамидальная сортировка (heapSort)\n";
    cout << "Ваш выбор: ";
    cin >> choice_sort;

    int* arr = new int[size];


    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    if (choice_size == 5) {
        cout << "исходный массив:\n";
        printArray(arr, size);
    }

    //замер времени начала
    auto start = chrono::high_resolution_clock::now();

    switch (choice_sort) {
    case 1:
        cout << "\nбыстрая сортировка\n";
        quickSort(arr, 0, size - 1);
        break;
    case 2:
        cout << "\nсортировка слиянием\n";
        mergeSort(arr, 0, size - 1);
        break;
    case 3:
        cout << "\nпирамидальная сортировка\n";
        heapSort(arr, size);
        break;
    default:
        cout << "\nНеверный выбор. Используем быструю сортировку.\n";
        quickSort(arr, 0, size - 1);
    }

    if (choice_size == 5) {
        cout << "отсортированный массив:\n";
        printArray(arr, size);
    }
    //замер времени окончания
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> dur = end - start;
    cout << "Время исполнения: " << dur.count() << " секунд\n";

    delete[] arr;

    return 0;
}