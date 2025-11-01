#include <iostream>
#include <fstream>
using namespace std;

// Base Class
class Student {
public:
    int roll;
    char name[30];
    char course[30];
public:
    Student() {
        roll = 0;
    }

    void inputStudent() {
        cout << "\nEnter Roll No: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Course: ";
        cin >> course;
    }

    void showStudent() {
        cout << "\nRoll No: " << roll;
        cout << "\nName: " << name;
        cout << "\nCourse: " << course;
    }

    ~Student() {}
};

// Derived Class - Single Inheritance
class Marks : public Student {
protected:
    int oop, dsa, de, maths, se;
public:
    void inputMarks() {
        cout << "Enter marks in OOP, DSA, DE, Maths, SE: ";
        cin >> oop >> dsa >> de >> maths >> se;
    }

    int totalMarks() {
        return oop + dsa + de + maths + se;
    }

    // Function overloading
    void showMarks() {
        cout << "\nOOP: " << oop << "  DSA: " << dsa << "  DE: " << de
             << "  Maths: " << maths << "  SE: " << se;
    }

    void showMarks(int total) {
        cout << "\nTotal Marks: " << total;
    }

    // Friend Function
    friend float percentage(Marks m);
};

float percentage(Marks m) {
    return (m.totalMarks() / 500.0f) * 100;
}

// Derived Class - Multilevel Inheritance
class Result : public Marks {
    char grade;
    static int count;
public:
    Result() { count++; }

    void generateResult() {
        float per = percentage(*this);
        if (per >= 85) grade = 'A';
        else if (per >= 70) grade = 'B';
        else if (per >= 55) grade = 'C';
        else if (per >= 40) grade = 'D';
        else grade = 'F';
    }

    void showResult() {
        showStudent();
        showMarks();
        showMarks(totalMarks());
        cout << "\nPercentage: " << percentage(*this);
        cout << "\nGrade: " << grade << endl;
    }

    // Static Function
    static void totalStudents() {
        cout << "\nTotal Results Generated: " << count;
    }

    // Operator Overloading
    bool operator>(Result &r2) {
        return percentage(*this) > percentage(r2);
    }

    // File Handling with Exception Handling
    void saveToFile() {
        ofstream fout("Result.txt", ios::app);
        if (!fout)
            throw runtime_error("File could not be opened!");
        fout << "Roll No: " << roll << "\tName: " << name
             << "\tCourse: " << course
             << "\tTotal: " << totalMarks()
             << "\tPercentage: " << percentage(*this)
             << "\tGrade: " << grade << endl;
        fout.close();
    }

    ~Result() {}
};
int Result::count = 0;

// Template Function
template <class T>
void showInfo(T msg) {
    cout << "\n[Info]: " << msg;
}

int main() {
    try {
        // Dynamic Memory Allocation
        Result *r1 = new Result;
        Result *r2 = new Result;

        cout << "\n--- Enter Student 1 Details ---";
        r1->inputStudent();
        r1->inputMarks();
        r1->generateResult();

        cout << "\n--- Enter Student 2 Details ---";
        r2->inputStudent();
        r2->inputMarks();
        r2->generateResult();

        cout << "\n\n===== RESULT DETAILS =====";
        r1->showResult();
        r2->showResult();

        // Operator Overloading
        if (*r1 > *r2)
            cout << "\n" << r1->name << " scored higher.";
        else
            cout << "\n" << r2->name << " scored higher.";

        Result::totalStudents();

        r1->saveToFile();
        r2->saveToFile();

        showInfo("Results saved successfully!");

        delete r1;
        delete r2; // Dynamic memory deallocation
    }
    catch (exception &e) {
        cout << "\nException: " << e.what();
    }

    return 0;
}