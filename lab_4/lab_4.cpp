/*Кутюков Никита ПС-22 В общежитии живет  N  студентов.  При  поселении  каждый
студент  представил список своих знакомых.  Каждое воскресение
организуется вечер знакомств,  когда знакомые любого  студента
знакомятся   между   собой.  Выяснить,  через  сколько  недель
познакомятся два указанных студента (8).*/
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <locale>

using namespace std; 

unordered_map<int, string> readStudentNames(const string& filename) {
    unordered_map<int, string> studentNames;
    ifstream file(filename);

    if (!file) {
        throw runtime_error("Не удалось открыть файл с именами студентов.");
    }

    int studentID;
    string studentName;
    while (file >> studentID) {
        file.ignore(); 
        getline(file, studentName); 
        studentNames[studentID] = studentName;
    }

    file.close();
    return studentNames;
}

unordered_map<int, unordered_set<int>> readGraphFromFile(const string& filename) {
    unordered_map<int, unordered_set<int>> graph;
    ifstream file(filename);

    if (!file) {
        throw runtime_error("Не удалось открыть файл с графом.");
    }

    int student;
    while (file >> student) {
        int acquaintance;
        while (file.peek() != '\n' && file >> acquaintance) {
            graph[student].insert(acquaintance);
            graph[acquaintance].insert(student); 
        }
    }

    file.close();
    return graph;
}

// Функция для определения количества недель до знакомства двух студентов
int calculateWeeksToMeet(unordered_map<int, unordered_set<int>> graph, int studentA, int studentB) {
    if (studentA == studentB) {
        return -2; 
    }

    if (graph.find(studentA) == graph.end() || graph.find(studentB) == graph.end()) {
        throw invalid_argument("Один или оба студента не существуют в графе.");
    }

    if (graph[studentA].count(studentB) > 0) {
        return 0; 
    }

    int weeks = 0;
    while (true) {
        unordered_map<int, unordered_set<int>> newConnections;
        for (auto it = graph.begin(); it != graph.end(); ++it) {
            int student = it->first;
            const unordered_set<int>& friends = it->second;
            for (int friendStudent : friends) {
                newConnections[student].insert(graph[friendStudent].begin(), graph[friendStudent].end());
            }
        }

        for (auto it = newConnections.begin(); it != newConnections.end(); ++it) {
            int student = it->first;
            const unordered_set<int>& friends = it->second;
            graph[student].insert(friends.begin(), friends.end());
        }

        weeks++;
        if (graph[studentA].count(studentB) > 0) {
            return weeks;
        }

        if (weeks > static_cast<int>(graph.size())) {
            break; 
        }
    }

    return -1; 
}

int main() {
    setlocale(LC_ALL, "RU"); 

    try {
        string graphFilename, namesFilename;
        cout << "Введите имя файла с графом: ";
        cin >> graphFilename;
        cout << "Введите имя файла с фамилиями студентов: ";
        cin >> namesFilename;

        auto graph = readGraphFromFile(graphFilename);
        auto studentNames = readStudentNames(namesFilename);

        while (true) {
            int studentA, studentB;
            cout << "Введите номера двух студентов для проверки (или 0 для выхода): ";
            cin >> studentA;
            if (studentA == 0) break;
            cin >> studentB;

            try {
                int weeks = calculateWeeksToMeet(graph, studentA, studentB);
                string nameA = studentNames.count(studentA) ? studentNames[studentA] : "Неизвестный";
                string nameB = studentNames.count(studentB) ? studentNames[studentB] : "Неизвестный";

                if (weeks == -2) {
                    cout << nameA << " не может познакомиться сам с собой." << endl;
                }
                else if (weeks == -1) {
                    cout << nameA << " и " << nameB << " не смогут познакомиться." << endl;
                }
                else if (weeks == 0) {
                    cout << nameA << " и " << nameB << " уже знакомы." << endl;
                }
                else {
                    cout << nameA << " и " << nameB << " познакомятся через " << weeks << " недель." << endl;
                }
            }
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        }

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    return 0;
}
