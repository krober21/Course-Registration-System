#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

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
    // returns true if node is removed and false if node doesnt exist
    bool remove(string student_ID){
        if (head == nullptr){   //Checks if the head is a nullptr
            return false;
        }
        Node* current = head;
        while(current->next != nullptr && current->next->student->studentID != student_ID){ //Searching the list for the node
            current = current->next;
        }
        // Deleting the node
        if (current->next != nullptr) {
            Node* temp = current->next; // sets current node to temp
            current->next = current->next->next;    //Changing the pointers to the next nodes
            delete temp;    // Deleting node
            return true;    //Returning true
        }
        else{
            return false;   //Return false if node is not found
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

    // Method to get the number of students in the list
    int getCount() {
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }
};

class Queue {
private:
    // Vector for queue
    vector<Student *> queue;
public:
    // Method for adding item to the queue
    void enqueue(Student* student){
        queue.push_back(student);   // Adds item to the back of the vector
    }

    // Method for removing an item from the front of the queue
    void dequeue(){
        if(!isEmpty()){
            queue.erase(queue.begin());
        }
    }
    // Viewing the item in front of the queue
    Student* front(){
        return queue[0];
    }

    // Method for checking if the queue is empty
    bool isEmpty(){
        return queue.empty();
    }

    // Method for displaying items in the queue.
    void display(){
        for(int i = 0; i < queue.size(); i++){
            cout << queue[i]->firstName << " " << queue[i]->lastName << " (ID: "
                 << queue[i]->studentID << ", Grade: " << queue[i]->gradeLevel << ")\n";
        }

    }

    // Method for chekcing the size of the queue
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

    // Method to display enrolled and waitlisted students
    void showSeatsStatus() {
        cout << enrolledStudents.getCount() << "/" << maxCapacity << " Seats Filled\n";
    }

    // Method to get the number of enrolled students
    int getEnrolledCount() {
        return enrolledStudents.getCount();
    }

    // Method to get the name of the course based on its index
    string getCourseName(int index) {
        static const vector<string> courseNames = {
                "ENGL 1000", "ENGL 2101", "ENGL 3610", "ENGL 4695",
                "MATH 1000", "MATH 2331", "MATH 3081", "MATH 4270",
                "BIOL 1000", "BIOL 2110", "BIOL 3050", "BIOL 4823",
                "HIST 1000", "HIST 2071", "HIST 3631", "HIST 4120",
                "ECON 1000", "ECON 2440", "ECON 3811", "ECON 4921"
        };
        return courseNames[index];
    }
};

// Function to generate a random number of students to enroll in each course
void fillCoursesRandomly(vector<Course>& courses) {
    srand(time(0)); // Seed for random number generation

    // Lists of names for generating unique student details
    vector<string> firstNames = {"John", "Jane", "Alex", "Emily", "Chris", "Katie", "Max", "Sarah", "Ryan", "Sophia"};
    vector<string> lastNames = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Miller", "Davis", "Garcia", "Martinez", "Hernandez"};
    set<string> usedIDs; // Set to track used student IDs for uniqueness

    // For each course, randomly enroll students
    for (int i = 0; i < courses.size(); ++i) {
        // Randomly decide the number of students (between 0 and 18)
        int randomNumStudents = rand() % 19; // Max 18 students per course
        for (int j = 0; j < randomNumStudents; ++j) {
            // Generate unique student data
            string firstName = firstNames[rand() % firstNames.size()];
            string lastName = lastNames[rand() % lastNames.size()];
            string studentID;

            // Ensure the student ID is unique
            do {
                studentID = "ID" + to_string(rand() % 10000);
            } while (usedIDs.find(studentID) != usedIDs.end()); // Keep generating until unique ID

            usedIDs.insert(studentID); // Add the ID to the used set

            // Create a unique full name by appending a random number to the student's name
            string uniqueFirstName = firstName + to_string(rand() % 100);
            string uniqueLastName = lastName + to_string(rand() % 100);

            // Random grade level (between 1 and 4)
            int gradeLevel = rand() % 4 + 1;

            // Enroll the student in the course
            Student* randomStudent = new Student(uniqueFirstName, uniqueLastName, studentID, gradeLevel, courses[i].getCourseName(i));
            courses[i].enrollStudent(randomStudent);
        }
    }
}



int main() {

// List of available courses
    vector<Course> courses;
    for (int i = 0; i < 20; ++i) {
        courses.push_back(Course(18,5)); // Create each course with a max capacity of 18 students
    }

    // Randomly fill courses with students
    fillCoursesRandomly(courses);

    // Display the course list with the current seat status for each course
    cout << "Available courses:\n";
    for (int i = 0; i < courses.size(); ++i) {
        cout << courses[i].getCourseName(i) << " Seats Filled: ";
        courses[i].showSeatsStatus();
    }

    // Ask the user for information
    string firstName, lastName, studentID, courseChoice;
    int gradeLevel;

    cout << "\nEnter your first name: ";
    cin >> firstName;
    cout << "Enter your last name: ";
    cin >> lastName;
    cout << "Enter your student ID: ";
    cin >> studentID;
    cout << "Enter your grade level (1: Freshman, 2: Sophomore, 3: Junior, 4: Senior): ";
    cin >> gradeLevel;

    // Get the course name from the user
    cout << "Enter the full name of the course you want to register for (e.g., 'ENGL 1000'): ";
    cin.ignore();  // To ignore the newline left in the buffer
    getline(cin, courseChoice);

    // Find the course matching the user's input
    bool courseFound = false;
    for (int i = 0; i < courses.size(); ++i) {
        if (courses[i].getCourseName(i) == courseChoice) {
            courseFound = true;
            // Create a new student and enroll them in the selected course
            Student* newStudent = new Student(firstName, lastName, studentID, gradeLevel, courseChoice);
            courses[i].enrollStudent(newStudent);
            cout << "\nYou have been successfully registered for " << courseChoice << "!\n";
            break;
        }
    }

    if (!courseFound) {
        cout << "\nCourse not found.\n";
    }

    // Display the updated list of students enrolled for each course
    cout << "\nUpdated list of students enrolled:\n";
    for (int i = 0; i < courses.size(); ++i) {
        cout << courses[i].getCourseName(i) << " Seats Filled: ";
        courses[i].showSeatsStatus();
    }

    // Unenrolling students
    cout << "Enter ID of student you want to unenroll: ";
    cin >> studentID;
    cout << "Enter the name of the course you wish to unenroll student from (e.g., 'ENGL 1000'):";
    cin.ignore();   // To ignore the newline left in the buffer
    getline(cin, courseChoice);

    courseFound = false;
    for (int i = 0; i < courses.size(); ++i) {
        if (courses[i].getCourseName(i) == courseChoice) {
            courseFound = true;
            courses[i].dropStudent(studentID);  //Dropping student from the course
            break;
        }
    }
    if (!courseFound) {
        cout << "\nCourse not found.\n";
    }

    // Display the updated list of students enrolled for each course
    cout << "\nUpdated list of students enrolled:\n";
    for (int i = 0; i < courses.size(); ++i) {
        cout << courses[i].getCourseName(i) << " Seats Filled: ";
        courses[i].showSeatsStatus();
    }

    return 0;
}
