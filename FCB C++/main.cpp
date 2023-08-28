#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Define constants for class sizes and number of subjects
const int NUM_CLASSES_BIO = 3;
const int NUM_CLASSES_MATH = 5;
const int STUDENTS_PER_CLASS = 40;
const int NUM_SUBJECTS = 3;

// Structure to store student information
struct Student {
    std::string name;
    int marks[NUM_SUBJECTS];
    int totalMarks;
    int schoolRank;
    int classRank;
};

// Function to calculate total marks for a student
int calculateTotalMarks(const Student& student) {
    int total = 0;
    for (int i = 0; i < NUM_SUBJECTS; ++i) {
        total += student.marks[i];
    }
    return total;
}

// Function to read student data from a file
void readStudentData(std::vector<Student>& students, const std::string& fileName) {
    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(1);
    }

    Student student;
    while (inFile >> student.name) {
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            inFile >> student.marks[i];
        }
        student.totalMarks = calculateTotalMarks(student);
        students.push_back(student);
    }

    inFile.close();
}

// Function to rank students
void rankStudents(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.totalMarks > b.totalMarks;
    });

    int rank = 1;
    for (size_t i = 0; i < students.size(); ++i) {
        students[i].schoolRank = rank++;
    }

    for (int classIndex = 0; classIndex < NUM_CLASSES_BIO + NUM_CLASSES_MATH; ++classIndex) {
        rank = 1;
        for (size_t i = 0; i < students.size(); ++i) {
            if (i / STUDENTS_PER_CLASS == classIndex) {
                students[i].classRank = rank++;
            }
        }
    }
}

// Function to display and write ranks to a file
void displayAndWriteRanks(const std::vector<Student>& students, const std::string& outputFileName) {
    std::ofstream outFile(outputFileName);
    if (!outFile) {
        std::cerr << "Error opening file: " << outputFileName << std::endl;
        exit(1);
    }

    for (const Student& student : students) {
        std::cout << "Student: " << student.name
                  << " | Total Marks: " << student.totalMarks
                  << " | School Rank: " << student.schoolRank
                  << " | Class Rank: " << student.classRank << std::endl;

        outFile << student.name << " " << student.totalMarks << " " << student.schoolRank << " " << student.classRank << std::endl;
    }

    outFile.close();
}

int main() {
    std::vector<Student> students;

    // Read student data from file
    readStudentData(students, "student_data.txt");

    // Rank students
    rankStudents(students);

    // Display and write ranks to file
    displayAndWriteRanks(students, "rank_output.txt");

    return 0;
}
