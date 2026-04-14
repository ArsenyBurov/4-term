#include <iostream>
#include <vector>
#include <string>

using namespace std;

// функция для создания таблицы плохих символов
// запоминает последнее вхождение каждого символа в паттерн
vector<int> buildBadCharTable(const string& pattern) {
    const int ALPHABET_SIZE = 256;
    vector<int> badCharTable(ALPHABET_SIZE, -1);

    for (int i = 0; i < pattern.size(); i++) {
        unsigned char currentChar = pattern[i];  //явно преобразуем в unsigned char
        int asciiCode = currentChar;              //получаем ascii код от 0 до 255
        badCharTable[asciiCode] = i;              //используем ascii код как индекс
    }

    return badCharTable;
}

// алгоритм бойера-мура только с эвристикой плохого символа
// возвращает вектор позиций всех вхождений паттерна в текст
vector<int> boyerMoore(const string& text, const string& pattern) {
    vector<int> result;  // вектор для хранения позиций совпадений
    int n = text.size();  // длина текста
    int m = pattern.size();  // длина паттерна

    if (m == 0 || n < m) return result;  // если паттерн пуст или длиннее текста

    vector<int> badChar = buildBadCharTable(pattern);  // строим таблицу плохих символов
    int shift = 0;  // текущее смещение паттерна относительно текста

    while (shift <= n - m) {  // пока паттерн помещается в оставшийся текст
        int j = m - 1;  // начинаем сравнение с конца паттерна

        // сравниваем символы справа налево
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;  // при совпадении двигаемся к началу
        }

        // если прошли весь паттерн, значит нашли совпадение
        if (j < 0) {
            result.push_back(shift);  // сохраняем позицию совпадения

            // вычисляем сдвиг для поиска следующего вхождения
            if (shift + m < n) {
                // получаем символ из текста, следующий сразу после паттерна
                char nextCharAfterPattern = text[shift + m];
                // преобразуем в unsigned char для безопасного индекса
                unsigned char unsignedNextChar = (unsigned char)nextCharAfterPattern;
                // получаем последнюю позицию этого символа в паттерне
                int lastPosInPattern = badChar[unsignedNextChar];
                // сдвигаем так чтобы этот символ совпал с его последним вхождением
                shift += m - lastPosInPattern;
            }
            else {
                shift += 1;  // если паттерн в конце текста, сдвигаем на 1
            }
        }
        else {
            // вычисляем сдвиг по эвристике плохого символа
            // получаем символ из текста на позиции несовпадения
            char mismatchChar = text[shift + j];
            unsigned char unsignedMismatchChar = (unsigned char)mismatchChar;
            int lastPos = badChar[unsignedMismatchChar]; // получаем последнюю позицию этого символа в паттерне
            // вычисляем на сколько можно сдвинуться
            int badCharShift = j - lastPos;
            // сдвигаем минимум на 1, чтобы не зациклиться
            shift += max(1, badCharShift);
        }
    }

    return result;
}

int main() {
    string text, pattern;

    cout << "введите текст для поиска: ";
    getline(cin, text);

    cout << "введите шаблон для поиска: ";
    getline(cin, pattern);

    vector<int> matches = boyerMoore(text, pattern);

    if (matches.empty()) {
        cout << "шаблон не найден в тексте" << endl;
    }
    else {
        cout << "найденные позиции: ";
        for (int i = 0; i < matches.size(); i++) {
            int pos = matches[i];
            cout << pos << " ";
        }
        cout << endl;
    }

    return 0;
}