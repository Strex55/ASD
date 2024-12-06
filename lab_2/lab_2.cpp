#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Spy {
    int id;
    int max_queue_time;
    int watch_time;
    int time_in_queue;
    bool observation_done;
    bool has_left_queue;
    Spy* next;
};

// Функция для добавления шпиона в конец очереди
void enqueue(Spy*& head, Spy*& tail, Spy* spy) {
    spy->next = nullptr;
    spy->observation_done = false;
    spy->has_left_queue = false;
    if (tail) {
        tail->next = spy;
    }
    else {
        head = spy;
    }
    tail = spy;
}

// Функция для удаления шпиона из начала очереди
Spy* dequeue(Spy*& head, Spy*& tail) {
    if (!head) return nullptr;
    Spy* temp = head;
    head = head->next;
    if (!head) tail = nullptr;
    return temp;
}

// Основная функция для обработки очереди наблюдений
void processQueue(Spy*& head, Spy*& tail) {
    int currentTime = 0;
    Spy* currentSpy = nullptr;
    int observationEndTime = 0;

    while (head || currentSpy) {
        Spy* temp = head;
        Spy* prev = nullptr;

        // Проверка на превышение времени ожидания
        while (temp) {
            if (temp->time_in_queue >= temp->max_queue_time && !temp->has_left_queue) {
                cout << currentTime << " мин.: Шпион #" << temp->id
                    << " покинул очередь (превышено время ожидания).\n";
                temp->has_left_queue = true;

                if (temp == head) {
                    head = head->next;
                    delete temp;
                    temp = head;
                }
                else {
                    prev->next = temp->next;
                    delete temp;
                    temp = prev->next;
                }
            }
            else {
                prev = temp;
                temp = temp->next;
            }
        }

        // Завершение наблюдения текущим шпионом
        if (currentSpy && currentTime == observationEndTime) {
            cout << currentTime << " мин.: Шпион #" << currentSpy->id
                << " закончил наблюдение.\n";
            currentSpy->observation_done = true;
            enqueue(head, tail, currentSpy);
            currentSpy = nullptr;
        }

        // Начало наблюдения следующим шпионом в очереди
        if (!currentSpy && head) {
            currentSpy = dequeue(head, tail);
            cout << currentTime << " мин.: Шпион #" << currentSpy->id
                << " начал наблюдение за объектом.\n";
            observationEndTime = currentTime + currentSpy->watch_time;
        }

        // Увеличиваем время ожидания для всех оставшихся шпионов
        temp = head;
        while (temp) {
            temp->time_in_queue += 1;
            temp = temp->next;
        }

        // Увеличиваем текущее время
        currentTime++;
    }
}

// Функция для загрузки данных о шпионах
void loadSpies(const string& filename, Spy*& head, Spy*& tail) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка: Не удалось открыть файл.\n";
        return;
    }

    int id, max_queue_time, watch_time;
    while (file >> id >> max_queue_time >> watch_time) {
        Spy* newSpy = new Spy;
        newSpy->id = id;
        newSpy->max_queue_time = max_queue_time;
        newSpy->watch_time = watch_time;
        newSpy->time_in_queue = 0;
        enqueue(head, tail, newSpy);
    }
    file.close();
}

// Функция для освобождения памяти
void clearQueue(Spy*& head, Spy*& tail) {
    while (head) {
        Spy* temp = dequeue(head, tail);
        delete temp;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    char repeat = 'Y';
    while (repeat == 'Y' || repeat == 'y') {
        Spy* head = nullptr;
        Spy* tail = nullptr;
        string filename;

        cout << "Введите имя файла с данными о шпионах: ";
        cin >> filename;

        loadSpies(filename, head, tail);

        if (!head) {
            cout << "Очередь пуста или не удалось открыть файл. Попробуйте снова.\n";
        }
        else {
            cout << "\nПротокол наблюдения:\n";
            processQueue(head, tail);
            cout << "Все шпионы покинули очередь.\n";
        }

        clearQueue(head, tail);

        cout << "Повторить программу? (Y/y - да, N/n - нет): ";
        cin >> repeat;
    }

    return 0;
}
