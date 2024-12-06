#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
using namespace std;

struct TreeNode {
    string name; 
    vector<TreeNode*> children; 
    bool isDepartment; // ����, �������� �� �������

    TreeNode(const string& nodeName) : name(nodeName), isDepartment(false) {}
};

void displayTree(TreeNode* root, int level = 0) {
    if (!root) return;

    for (int i = 0; i < level; i++) cout << "  ";
    cout << root->name << endl;

    for (TreeNode* child : root->children) {
        displayTree(child, level + 1);
    }
}

TreeNode* loadTreeFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "������: �� ������� ������� ���� " << filename << endl;
        return nullptr;
    }

    string line;
    vector<TreeNode*> nodeStack; 
    TreeNode* root = nullptr;

    while (getline(file, line)) {
        size_t level = 0;
        while (level < line.size() && line[level] == '_') {
            level++;
        }

        string nodeName = line.substr(level);
        TreeNode* currentNode = new TreeNode(nodeName);

        if (level == 0) {
            root = currentNode;
            nodeStack.clear();
            nodeStack.push_back(currentNode);
        }
        else {
            while (nodeStack.size() > level / 2) {
                nodeStack.pop_back();
            }

            nodeStack.back()->children.push_back(currentNode);
            if (nodeStack.back()->name.find("�������") != string::npos) {
                nodeStack.back()->isDepartment = true;
            }
            nodeStack.push_back(currentNode);
        }
    }

    file.close();
    return root;
}

void findProfessors(TreeNode* root, unordered_map<string, set<string>>& professorDepartments, string currentDepartment = "") {
    if (!root) return;

    if (root->children.empty()) {
        if (!currentDepartment.empty()) {
            professorDepartments[root->name].insert(currentDepartment);
        }
    }
    else {
        string department = currentDepartment;
        if (root->isDepartment) {
            department = root->name;
        }

        for (TreeNode* child : root->children) {
            findProfessors(child, professorDepartments, department);
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    string filename = "tree.txt"; 

    TreeNode* root = loadTreeFromFile(filename);
    if (!root) {
        return 1;
    }

    while (true) {
        cout << "\n����:\n";
        cout << "1. �������� ������\n";
        cout << "2. ����� ��������������, ������� ������� �� ���� � ����� ��������\n";
        cout << "3. �����\n";
        cout << "������� ����� ��������: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            displayTree(root);
        }
        else if (choice == 2) {
            unordered_map<string, set<string>> professorDepartments;
            findProfessors(root, professorDepartments);

            cout << "�������������, ���������� �� ���� � ����� ��������:\n";
            bool found = false;
            for (const auto& entry : professorDepartments) {
                if (entry.second.size() >= 3) {
                    found = true;
                    cout << entry.first << " (�������: ";
                    for (const string& dept : entry.second) {
                        cout << dept << " ";
                    }
                    cout << ")\n";
                }
            }
            if (!found) {
                cout << "����� �������������� ���.\n";
            }
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "�������� �����. ���������� �����.\n";
        }
    }

    return 0;
}
