#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale>
#include <windows.h>

using namespace std;

class String {
public:

    String() : str(nullptr), length(0) {}

    String(const char* str) {
        length = strlen(str);
        this->str = new char[length + 1];
        strcpy(this->str, str);
    }

    ~String() {
        delete[] str;
    }

    String(const String& other) : length(other.length) {
        str = new char[length + 1];
        strcpy(str, other.str);
    }

    String& operator=(const String& other) {
        if (this == &other) return *this;
        delete[] str;
        length = other.length;
        str = new char[length + 1];
        strcpy(str, other.str);
        return *this;
    }

    String(String&& other) noexcept : str(other.str), length(other.length) {
        other.str = nullptr;
        other.length = 0;
    }

    String& operator=(String&& other) noexcept {
        if (this == &other) return *this;
        delete[] str;
        str = other.str;
        length = other.length;
        other.str = nullptr;
        other.length = 0;
        return *this;
    }

  
    String& operator+=(const String& other) {
        char* newStr = new char[length + other.length + 1];
        strcpy(newStr, str);
        strcat(newStr, other.str);
        delete[] str;
        str = newStr;
        length += other.length;
        return *this;
    }

  
    String& operator+=(const char* cstr) {
        int cstrLength = strlen(cstr);
        char* newStr = new char[length + cstrLength + 1];
        strcpy(newStr, str);
        strcat(newStr, cstr);
        delete[] str;
        str = newStr;
        length += cstrLength;
        return *this;
    }

    friend String operator+(const String& lhs, const String& rhs) {
        String result(lhs);
        result += rhs;
        return result;
    }

    friend String operator+(const String& lhs, const char* rhs) {
        String result(lhs);
        result += rhs;
        return result;
    }

    bool operator==(const String& other) const {
        return strcmp(str, other.str) == 0;
    }

    void Print() const {
        cout << str;
    }

    int Length() const {
        return length;
    }

    const char* GetStr() const {
        return str;
    }

private:
    char* str;
    int length;
};

bool reverseCaseInsensitiveCompare(const String& a, const String& b) {
    string lowerA = a.GetStr();
    string lowerB = b.GetStr();
    transform(lowerA.begin(), lowerA.end(), lowerA.begin(), ::tolower);
    transform(lowerB.begin(), lowerB.end(), lowerB.begin(), ::tolower);
    return lowerA > lowerB;
}

int main() {
    setlocale(LC_ALL,"Russian_Russia.1251"); 
    SetConsoleCP(1251);                       
    SetConsoleOutputCP(CP_UTF8);              

    vector<String> strings;
    int n;

    cout << "Введите количество строк: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {
		cout << "Введите строку " << i + 1 << ": ";
        char input[256];
        cin.getline(input, 256);
        strings.emplace_back(input);
    }

    sort(strings.begin(), strings.end(), reverseCaseInsensitiveCompare);

    cout << "\nСтроки в обратном лексикографическом порядке:\n";
    for (const auto& str : strings) {
        str.Print();
        cout << endl;
    }

    if (strings.size() > 1) {
        String combinedString = strings[0];
        combinedString += " и ";
        combinedString += strings[1];
        combinedString += " вместе.";

        cout << "\nПример конкатенации строк с использованием оператора +=:\n";
        combinedString.Print();
        cout << endl;
    }
    else {
        cout << "\nНедостаточно строк для демонстрации оператора +=.\n";
    }

    return 0;
}
