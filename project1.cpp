#include <iostream>
#include <iomanip>
using namespace std;

// Structure to store course details
struct Course {
    string grade;
    float credits;
    int gradePoint;
};

// Function to convert grade to grade point
int calculateGradePoint(string grade) {
    if (grade == "O") return 10;
    if (grade == "A+") return 9;
    if (grade == "A") return 8;
    if (grade == "B+") return 7;
    if (grade == "B") return 6;
    if (grade == "C") return 5;
    return 0; // For F or invalid grade
}

int main() {
    int n;
    cout << "Enter number of courses: ";
    cin >> n;

    Course courses[n];
    float totalCredits = 0, totalGradePoints = 0;

    for (int i = 0; i < n; i++) {
        cout << "\nCourse " << i + 1 << endl;
        cout << "Enter Grade (O, A+, A, B+, B, C, F): ";
        cin >> courses[i].grade;
        cout << "Enter Credit Hours: ";
        cin >> courses[i].credits;

        courses[i].gradePoint =
            calculateGradePoint(courses[i].grade);

        totalCredits += courses[i].credits;
        totalGradePoints +=
            courses[i].gradePoint * courses[i].credits;
    }

    float cgpa = totalGradePoints / totalCredits;

    cout << "\n==============================";
    cout << "\nCourse-wise Performance";
    cout << "\n==============================\n";

    cout << left << setw(10) << "Course"
         << setw(10) << "Grade"
         << setw(10) << "Credits"
         << setw(15) << "Grade Points" << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << i + 1
             << setw(10) << courses[i].grade
             << setw(10) << courses[i].credits
             << setw(15)
             << courses[i].gradePoint * courses[i].credits
             << endl;
    }

    cout << "\nTotal Credits: " << totalCredits;
    cout << "\nTotal Grade Points: " << totalGradePoints;
    cout << "\nFinal CGPA: " << fixed << setprecision(2)
         << cgpa;

    cout << "\n==============================";

    return 0;
}
