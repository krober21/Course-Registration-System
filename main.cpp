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
    // returns true if node is removed and false if
    bool remove(string student_ID){
        if (head == nullptr){
            return false;
        }
        Node* current = head;
        while(current->next != nullptr && current->next->student->studentID != student_ID){
            current = current->next;
        }
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return true;
        }
        else{
            return false;
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

class Queue {
private:
    vector<Student *> queue;
public:
    void enqueue(Student* student){
        queue.push_back(student);
    }
    void dequeue(){
        if(!isEmpty()){
            queue.erase(queue.begin());
        }
    }

    Student* front(){
        return queue[0];
    }

    bool isEmpty(){
        return queue.empty();
    }

    void display(){
        for(int i = 0; i < queue.size(); i++){
            cout << queue[i]->firstName << " " << queue[i]->lastName << " (ID: "
                 << queue[i]->studentID << ", Grade: " << queue[i]->gradeLevel << ")\n";
        }

    }

    int size(){
        return queue.size();
    }

};



// Course class representing a course in the registration system
class Course {
private:
    LinkedList enrolledStudents; // List of students enrolled in the course
    Queue waitlist;         // List of students on the waitlist
    int maxCapacity;             // Maximum number of students allowed in the course
    int maxWaitlistCapacity;
    int enrolledCount = 0;       // Tracks the current number of enrolled students

public:
    // Constructor to set the maximum capacity of the course
    Course(int capacity, int waitlistCapacity) : maxCapacity(capacity), maxWaitlistCapacity(waitlistCapacity) {}

    // Method to enroll a student in the course
    void enrollStudent(Student* student) {
        if (enrolledCount < maxCapacity) {
            enrolledStudents.insert(student); // Enroll student directly if there's space
            enrolledCount++;
            cout << "Enrollment successful for " << student->firstName << " " << student->lastName << ".\n";
        }
        else if (waitlist.size() < maxWaitlistCapacity)
        {
            waitlist.enqueue(student); // Add to waitlist if the course is full
            cout << "Course is full. " << student->firstName << " " << student->lastName << " added to waitlist.\n";
        }
        else {
            cout << "Course & Waitlist is full \n";
        }
    }

    //Method to drop a student from the course
    void dropStudent(string student_ID){
        if (enrolledStudents.remove(student_ID) == true){
            cout << "Student with ID " << student_ID << " has been unenrolled." << endl;
            enrolledCount--;
            if (waitlist.size() > 0){
                enrollStudent(waitlist.front());
                waitlist.dequeue();
            }
        }
        else {
            cout << "Student with ID " << student_ID << "is not enrolled." <<endl;
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

    Course course(2, 4);
    Student* s1 = new Student("Steve", "Nketiah", "12312", 4, "math");
    Student* s2 = new Student("S", "Nketiah", "123", 4, "math");
    Student* s3 = new Student("B", "Nketiah", "13", 4, "math");
    Student* s4 = new Student("C", "Nketiah", "12312", 4, "math");
    Student* s5 = new Student("D", "Nketiah", "123182", 4, "math");
    Student* s6 = new Student("S", "Nketiah", "12256", 4, "math");
    Student* s7 = new Student("A", "Nketiah", "122", 4, "math");
    course.enrollStudent(s1);
    course.enrollStudent(s2);
    course.enrollStudent(s3);
    course.enrollStudent(s4);

    course.dropStudent("123");

    course.enrollStudent(s5);
    course.enrollStudent(s6);
    course.enrollStudent(s7);

    course.showStudents();

    return 0;
}
