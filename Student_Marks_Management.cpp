#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure to hold student data
struct Student {
    int rollNumber;
    string name;
    float mathMarks = 0;
    float physicsMarks = 0;
    float computerMarks = 0;
    float totalMarks = 0;

    void calculateTotal() {
        totalMarks = mathMarks + physicsMarks + computerMarks;
    }
};

class StudentDatabase {
private:
    vector<Student> records;

public:
    // Initialize with some dummy data
    StudentDatabase() {
        records = {
            {1001, "Alice"},
            {1002, "Bob"},
            {1003, "Charlie"}
        };
    }

    // Displays names and rolls (Read-only for teachers)
    void displayStudentList() {
        cout << "\n--- Student List ---" << endl;
        cout << left << setw(10) << "Roll" << setw(15) << "Name" << endl;
        for (const auto& s : records) {
            cout << left << setw(10) << s.rollNumber << setw(15) << s.name << endl;
        }
    }

    // Permission-based editing
    void updateMarks(string subject) {
        int roll;
        float marks;
        cout << "\nEnter Student Roll Number to update " << subject << " marks: ";
        cin >> roll;

        for (auto& s : records) {
            if (s.rollNumber == roll) {
                cout << "Current student: " << s.name << ". Enter new marks: ";
                cin >> marks;
                
                if (subject == "Math") s.mathMarks = marks;
                else if (subject == "Physics") s.physicsMarks = marks;
                else if (subject == "Computer") s.computerMarks = marks;
                
                s.calculateTotal();
                cout << "Marks updated successfully!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    // Sorting by total marks for final view
    void finalizeAndDisplay() {
        sort(records.begin(), records.end(), [](const Student& a, const Student& b) {
            return a.totalMarks > b.totalMarks;
        });

        cout << "\n--- Final Merged Leaderboard ---" << endl;
        cout << left << setw(10) << "Rank" << setw(10) << "Roll" << setw(15) << "Name" 
             << setw(10) << "Math" << setw(10) << "Phys" << setw(10) << "Comp" << setw(10) << "Total" << endl;
        
        int rank = 1;
        for (const auto& s : records) {
            cout << left << setw(10) << rank++ << setw(10) << s.rollNumber << setw(15) << s.name 
                 << setw(10) << s.mathMarks << setw(10) << s.physicsMarks << setw(10) << s.computerMarks 
                 << setw(10) << s.totalMarks << endl;
        }
    }
};

int main() {
    StudentDatabase db;
    int choice;
    string subjects[] = {"Math", "Physics", "Computer"};

    while (true) {
        cout << "\n--- Marks Management System ---";
        cout << "\n1. Math Teacher Login\n2. Physics Teacher Login\n3. Computer Teacher Login";
        cout << "\n4. Final Submission (View Results)\n5. Exit\nSelect option: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            db.displayStudentList();
            db.updateMarks(subjects[choice - 1]);
        } else if (choice == 4) {
            db.finalizeAndDisplay();
            break; 
        } else {
            break;
        }
    }

    return 0;
}