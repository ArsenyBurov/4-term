#include <iostream>

using namespace std;

void countingSort(int A[], int n, int k) {
    //массив счетчиков размера k, заполняем 0
    int* C = new int[k]();
    //количество каждого числа
    for (int i = 0; i < n; i++) {
        C[A[i]]++;
    }
    //восстанавливаем отсортированный массив
    int pos = 0;
    for (int number = 0; number < k; number++) {
        for (int i = 0; i < C[number]; i++) {
            A[pos] = number;
            pos++;
        }
    }
    delete[] C;
}

int digit(int x, int i) {
    for (int p = 1; p < i; p++) {
        x /= 10;
    }
    return x % 10;
}


void radixSortLSD(int A[], int N, int m, int P = 10) {
    //создаем P дополнительных массивов
    int** dop = new int* [P];
    for (int i = 0; i < P; i++) {
        dop[i] = new int[N];
    }

    //массив размеров дополнительных массивов
    int* dopSizes = new int[P]();

    //проходим по всем разрядам от 1 до m
    for (int i = 1; i <= m; i++) {
        //очищаем доп массивы
        for (int b = 0; b < P; b++) {
            dopSizes[b] = 0;
        }

        //распределяем элементы по доп массивам
        for (int j = 0; j < N; j++) {
            int d = digit(A[j], i);
            dop[d][dopSizes[d]] = A[j];
            dopSizes[d]++;
        }

        //перезаписываем массив A из доп массивов
        int pos = 0;
        for (int b = 0; b < P; b++) {
            for (int j = 0; j < dopSizes[b]; j++) {
                A[pos] = dop[b][j];
                pos++;
            }
        }
    }

    for (int i = 0; i < P; i++) {
        delete[] dop[i];
    }
    delete[] dop;
    delete[] dopSizes;
}

void printArr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int findMaxRazryad(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    int razryad = 0;
    while (maxVal > 0) {
        maxVal /= 10;
        razryad++;
    }
    return razryad;
}

int findk(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal + 1;
}

int main() {
    setlocale(LC_ALL, "RUS");
    cout << "сортировка подсчетом" << endl;
    int arr[] = { 4, 2, 2, 8, 3, 3, 1, 0, 4, 0, 5, 7 };
    int n1 = sizeof(arr) / sizeof(arr[0]);
    int k1 = findk(arr, n1);

    cout << "исходный массив: ";
    printArr(arr, n1);

    countingSort(arr, n1, k1);

    cout << "результат countingSort: ";
    printArr(arr, n1);
    cout << endl;

    cout << "поразрядная сортировка LSD" << endl;
    int arr2[] = { 160, 60, 144, 12, 78, 56, 2, 122 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 10; 
    int m = findMaxRazryad(arr2, n2);

    cout << "исходный массив: ";
    printArr(arr2, n2);

    radixSortLSD(arr2, n2, m, k2);

    cout << "результат radixSortLSD: ";
    printArr(arr2, n2);

    return 0;
}
