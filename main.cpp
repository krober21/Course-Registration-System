#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Student class representing a student in the registration system
class Student {
public:
    string firstName;  // First name of the student
    string lastName;   // Last name of the student
    string studentID;  // Unique identifier for the student
    int gradeLevel;    // Grade level (1: Freshman, 2: Sophomore, 3: Junior, 4: Senior)
    string courseChoice; // Course the student wishes to enroll in

    // Constructor to initialize student details
    Student(string first, string last, string id, int grade, string course)
            : firstName(first), lastName(last), studentID(id), gradeLevel(grade), courseChoice(course) {}
};

// Node class representing each element in the linked list
class Node {
public:
    Student* student; // Pointer to the student data
    Node* next;       // Pointer to the next node in the linked list

    // Constructor to initialize node with student data
    Node(Student* s) : student(s), next(nullptr) {}
};

// LinkedList class for managing a list of students
class LinkedList {
private:
    Node* head; // Pointer to the first node in the list

public:
    // Constructor to initialize the linked list
    LinkedList() : head(nullptr) {}

    // Method to insert a new student into the linked list in sorted order by last name
    void insert(Student* newStudent) {
        Node* newNode = new Node(newStudent); // Create a new node for the student

        // If the list is empty or the new student comes before the head
        if (!head || newStudent->lastName < head->student->lastName) {
            newNode->next = head; // Insert at the beginning
            head = newNode;       // Update head to new node
        } else {
            Node* current = head; // Start at the head
            // Find the correct position to insert the new student
            while (current->next && current->next->student->lastName < newStudent->lastName) {
                current = current->next; // Move to the next node
            }
            newNode->next = current->next; // Link new node to the next node
            current->next = newNode;       // Insert the new node
        }
    }

    // Method to display all students in the list
    void display() {
        Node* current = head;
        while (current) {
            cout << current->student->firstName << " " << current->student->lastName << " (ID: "
                 << current->student->studentID << ", Grade: " << current->student->gradeLevel << ")\n";
            current = current->next;
        }
    }
};

// Course class representing a course in the registration system
class Course {
private:
    LinkedList enrolledStudents; // List of students enrolled in the course
    LinkedList waitlist;         // List of students on the waitlist
    int maxCapacity;             // Maximum number of students allowed in the course
    int enrolledCount = 0;       // Tracks the current number of enrolled students

public:
    // Constructor to set the maximum capacity of the course
    Course(int capacity) : maxCapacity(capacity) {}

    // Method to enroll a student in the course
    void enrollStudent(Student* student) {
        if (enrolledCount < maxCapacity) {
            enrolledStudents.insert(student); // Enroll student directly if there's space
            enrolledCount++;
            cout << "Enrollment successful for " << student->firstName << " " << student->lastName << ".\n";
        } else {
            waitlist.insert(student); // Add to waitlist if the course is full
            cout << "Course is full. " << student->firstName << " " << student->lastName << " added to waitlist.\n";
        }
    }

    // Method to display enrolled and waitlisted students
    void showStudents() {
        cout << "\nEnrolled Students:\n";
        enrolledStudents.display();
        cout << "\nWaitlisted Students:\n";
        waitlist.display();
    }
};

int main() {
    // Create a course with a specified capacity
    Course math101(2); // Max capacity of 2 for demonstration

    // Vector to store created students
    vector<Student*> students;

    // Loop for user input
    char choice;
    do {
        // Get student information
        string firstName, lastName, studentID, courseChoice;
        int gradeLevel;

        cout << "Enter your first name: ";
        cin >> firstName;
        cout << "Enter your last name: ";
        cin >> lastName;
        cout << "Enter your student ID: ";
        cin >> studentID;
        cout << "Enter your grade level (1: Freshman, 2: Sophomore, 3: Junior, 4: Senior): ";
        cin >> gradeLevel;
        cout << "Enter course choice: ";
        cin.ignore(); // Clear newline character from input buffer
        getline(cin, courseChoice);

        // Create a new student and store it in the list
        Student* newStudent = new Student(firstName, lastName, studentID, gradeLevel, courseChoice);
        students.push_back(newStudent);

        // Enroll student in the selected course
        math101.enrollStudent(newStudent);

        // Display enrolled and waitlisted students
        math101.showStudents();

        // Ask if the user wants to add another student
        cout << "\nWould you like to register another student? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    // Clean up allocated memory
    for (Student* student : students) {
        delete student;
    }

    return 0;
}
