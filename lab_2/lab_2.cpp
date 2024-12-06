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

// ������� ��� ���������� ������ � ����� �������
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

// ������� ��� �������� ������ �� ������ �������
Spy* dequeue(Spy*& head, Spy*& tail) {
    if (!head) return nullptr;
    Spy* temp = head;
    head = head->next;
    if (!head) tail = nullptr;
    return temp;
}

// �������� ������� ��� ��������� ������� ����������
void processQueue(Spy*& head, Spy*& tail) {
    int currentTime = 0;
    Spy* currentSpy = nullptr;
    int observationEndTime = 0;

    while (head || currentSpy) {
        Spy* temp = head;
        Spy* prev = nullptr;

        // �������� �� ���������� ������� ��������
        while (temp) {
            if (temp->time_in_queue >= temp->max_queue_time && !temp->has_left_queue) {
                cout << currentTime << " ���.: ����� #" << temp->id
                    << " ������� ������� (��������� ����� ��������).\n";
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

        // ���������� ���������� ������� �������
        if (currentSpy && currentTime == observationEndTime) {
            cout << currentTime << " ���.: ����� #" << currentSpy->id
                << " �������� ����������.\n";
            currentSpy->observation_done = true;
            enqueue(head, tail, currentSpy);
            currentSpy = nullptr;
        }

        // ������ ���������� ��������� ������� � �������
        if (!currentSpy && head) {
            currentSpy = dequeue(head, tail);
            cout << currentTime << " ���.: ����� #" << currentSpy->id
                << " ����� ���������� �� ��������.\n";
            observationEndTime = currentTime + currentSpy->watch_time;
        }

        // ����������� ����� �������� ��� ���� ���������� �������
        temp = head;
        while (temp) {
            temp->time_in_queue += 1;
            temp = temp->next;
        }

        // ����������� ������� �����
        currentTime++;
    }
}

// ������� ��� �������� ������ � �������
void loadSpies(const string& filename, Spy*& head, Spy*& tail) {
    ifstream file(filename);
    if (!file) {
        cerr << "������: �� ������� ������� ����.\n";
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

// ������� ��� ������������ ������
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

        cout << "������� ��� ����� � ������� � �������: ";
        cin >> filename;

        loadSpies(filename, head, tail);

        if (!head) {
            cout << "������� ����� ��� �� ������� ������� ����. ���������� �����.\n";
        }
        else {
            cout << "\n�������� ����������:\n";
            processQueue(head, tail);
            cout << "��� ������ �������� �������.\n";
        }

        clearQueue(head, tail);

        cout << "��������� ���������? (Y/y - ��, N/n - ���): ";
        cin >> repeat;
    }

    return 0;
}
