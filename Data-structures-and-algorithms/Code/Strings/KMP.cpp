#include <iostream>
#include <vector>  
#include <string>

using namespace std;

vector<int> prefix_function(string s) {
    int n = (int)s.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
        //длина нового префикса не может превышать p[i-1] + 11
        int c = p[i - 1];
        //уменьшаем c, пока не найдём позицию, где символ s[cur] совпадёт с s[i]
        while (s[i] != s[c] && c > 0)
            c = p[c - 1];
        // здесь либо s[i] == s[cur], либо cur == 0
        if (s[i] == s[c])
            p[i] = c + 1; //увеличиваем длину префикса на 1
    }
    return p;
}

vector<int> KMP(string s, string t){
    vector<int> A;

    if (s.empty()) return A;

    int k = 0;  //количество совпавших символов
    vector<int> pi = prefix_function(s);  //префикс-функция от образца S
    int n = s.size();
    int m = t.size();

    for (int i = 0; i < m; i++){
        //пока есть совпадение и текущий символ не совпадает
        while (k > 0 && t[i] != s[k]){
            k = pi[k - 1];
        }
        //если символы совпали
        if (t[i] == s[k]) {
            k++;
        }
        // если нашли полное вхождение
        if (k == n) {
            A.push_back(i - n + 1); //позиция начала вхождения
            k = pi[k - 1];
        }
    }

    return A;
}

int main() {
    setlocale(LC_ALL, "RUS");

    string st, text;
    cout << "строка для поиска: ";
    getline(cin, st);
    cout << "исходная строка: ";
    getline(cin, text);
    vector<int> result = KMP(st, text);

    cout << "результат: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}