#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int roll;
    string name;
    int marks;
};

const int MAX_STUDENTS = 100;

void addStudent(Student students[], int &count) {
    if(count >= MAX_STUDENTS) {
        cout << "Student limit reached!\n";
        return;
    }
    Student s;
    cout << "Enter roll: ";
    cin >> s.roll;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, s.name);
    cout << "Enter marks: ";
    cin >> s.marks;
    students[count++] = s;
    cout << "Student added successfully!\n";
}

void displayStudents(Student students[], int count) {
    for(int i=0; i<count; i++) {
        cout << "Roll: " << students[i].roll
             << ", Name: " << students[i].name
             << ", Marks: " << students[i].marks << endl;
    }
}

void searchStudent(Student students[], int count) {
    int roll;
    cout << "Enter roll to search: ";
    cin >> roll;
    for(int i=0; i<count; i++) {
        if(students[i].roll == roll) {
            cout << "Found: " << students[i].name
                 << ", Marks: " << students[i].marks << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

void updateStudent(Student students[], int count) {
    int roll;
    cout << "Enter roll to update: ";
    cin >> roll;
    for(int i=0; i<count; i++) {
        if(students[i].roll == roll) {
            cout << "Enter new marks: ";
            cin >> students[i].marks;
            cout << "Marks updated.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void deleteStudent(Student students[], int &count) {
    int roll;
    cout << "Enter roll to delete: ";
    cin >> roll;
    for(int i=0; i<count; i++) {
        if(students[i].roll == roll) {
            for(int j=i; j<count-1; j++) {
                students[j] = students[j+1];
            }
            count--;
            cout << "Student deleted.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void saveToFile(Student students[], int count) {
    ofstream file("students.txt");
    for(int i=0; i<count; i++) {
        file << students[i].roll << "\n"
             << students[i].name << "\n"
             << students[i].marks << "\n";
    }
}

void loadFromFile(Student students[], int &count) {
    ifstream file("students.txt");
    if(!file) return;
    count = 0;
    while(file >> students[count].roll) {
        file.ignore();
        getline(file, students[count].name);
        file >> students[count].marks;
        file.ignore();
        count++;
        if(count >= MAX_STUDENTS) break;
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    loadFromFile(students, count);

    int choice;
    do {
        cout << "\n1.Add Student\n2.Display Students\n3.Search Student\n4.Update Marks\n5.Delete Student\n6.Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addStudent(students, count); break;
            case 2: displayStudents(students, count); break;
            case 3: searchStudent(students, count); break;
            case 4: updateStudent(students, count); break;
            case 5: deleteStudent(students, count); break;
            case 6: saveToFile(students, count); cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 6);

    return 0;
}

