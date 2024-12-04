#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <limits>
#include <iomanip>


using namespace std;

// Student class representing a student in the registration system
class Student {
public:
    string firstName;  // First name of the student
    string lastName;   // Last name of the student
    string studentID;  // Unique identifier for the student
    int gradeLevel;    // Grade level (1: Freshman, 2: Sophomore, 3: Junior, 4: Senior)
    string courseChoice; // Course the student wishes to enroll in
    set<string> registeredCourses; // Tracks courses the student has registered for

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

    // returns true if node is removed and false if node doesn't exist
    bool remove(string student_ID) {
        if (head == nullptr) {   // Checks if the head is a nullptr
            return false;
        }
        Node* current = head;
        while (current->next != nullptr && current->next->student->studentID != student_ID) { // Searching the list for the node
            current = current->next;
        }
        // Deleting the node
        if (current->next != nullptr) {
            Node* temp = current->next; // sets current node to temp
            current->next = current->next->next;    // Changing the pointers to the next nodes
            delete temp;    // Deleting node
            return true;    // Returning true
        }
        else {
            return false;   // Return false if node is not found
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
    void enqueue(Student* student) {
        queue.push_back(student);   // Adds item to the back of the vector
    }

    // Method for removing an item from the front of the queue
    void dequeue() {
        if (!isEmpty()) {
            queue.erase(queue.begin());
        }
    }
    // Viewing the item in front of the queue
    Student* front() {
        return queue[0];
    }

    // Method for checking if the queue is empty
    bool isEmpty() {
        return queue.empty();
    }

    // Method for displaying items in the queue
    void display() {
        for (int i = 0; i < queue.size(); i++) {
            cout << queue[i]->firstName << " " << queue[i]->lastName << " (ID: "
                 << queue[i]->studentID << ", Grade: " << queue[i]->gradeLevel << ")\n";
        }
    }

    // Method for checking the size of the queue
    int size() {
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
        }
        else if (waitlist.size() < maxWaitlistCapacity) {
            waitlist.enqueue(student); // Add to waitlist if the course is full
            cout << "Course is full. " << student->firstName << " " << student->lastName << " added to waitlist.\n";
        }
        else {
            cout << "Course & Waitlist is full \n";
        }
    }

// Method to add a student to the waitlist
public:
    void addToWaitlist(Student* student) {
        waitlist.enqueue(student); // Add student to the waitlist
    }

    //Method to drop a student from the course
    void dropStudent(string student_ID) {
        if (enrolledStudents.remove(student_ID) == true) {
            cout << "Student with ID " << student_ID << " has been unenrolled." << endl;
            enrolledCount--;
            if (waitlist.size() > 0) {
                enrollStudent(waitlist.front());
                waitlist.dequeue();
            }
        }
        else {
            cout << "Student with ID " << student_ID << " is not enrolled." << endl;
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

    // Getter for max capacity
    int getMaxCapacity() const {
        return maxCapacity;
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

// Function to generate a unique student ID
string generateStudentID(set<string>& usedIDs) {
    string studentID;
    do {
        int randomPart = rand() % 1000000; // Generate a random number with up to 6 digits
        studentID = "002" + string(6 - to_string(randomPart).length(), '0') + to_string(randomPart); // Format ID as 002XXXXXX
    } while (usedIDs.find(studentID) != usedIDs.end()); // Ensure ID is unique
    usedIDs.insert(studentID);
    return studentID;
}

// Function to generate a random number of students to enroll in each course
void fillCoursesRandomly(vector<Course>& courses, int userGradeLevel) {
    srand(time(0)); // Seed for random number generation

    // Lists of names for generating unique student details
    vector<string> firstNames = {"John", "Jane", "Alex", "Emily", "Chris", "Katie", "Max", "Sarah", "Ryan", "Sophia",
                                 "Anna", "Meghan", "Rachel", "Eric", "Carlos", "Jack", "Michael", "Maggie", "Olivia",
                                 "Amelia", "Emma", "Mia", "Ellie", "Elijah", "Liam", "Noah", "Mateo", "Leo", "Harper",
                                 "James", "Ethan", "Violet", "Scarlett"};
    vector<string> lastNames = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Miller", "Davis", "Garcia",
                                "Martinez", "Hernandez", "Scott", "Gilligan", "Carlisle", "Finns", "Blunt", "Anderson",
                                "Taylor", "Thomas", "Moore", "Martin", "Thompson", "Clark", "Robinson", "Lewis",
                                "Allen", "Wright", "Scott", "Baker", "Nelson"};
    set<string> usedIDs; // Set to track used student IDs for uniqueness

    // Determine course filling range based on user grade level
    int minFill, maxFill;
    switch (userGradeLevel) {
        case 1: // Freshman
            minFill = 16;
            maxFill = 20;
            break;
        case 2: // Sophomore
            minFill = 12;
            maxFill = 16;
            break;
        case 3: // Junior
            minFill = 8;
            maxFill = 12;
            break;
        case 4: // Senior
            minFill = 4;
            maxFill = 8;
            break;
        default:
            minFill = 10;
            maxFill = 15;
            break;
    }

    // Populate courses
    for (int i = 0; i < courses.size(); ++i) {
        // Randomly decide the number of students to enroll within grade-level limits
        int randomStudentCount = rand() % (maxFill - minFill + 1) + minFill;

        // Enroll random students
        for (int j = 0; j < randomStudentCount; ++j) {
            string firstName = firstNames[rand() % firstNames.size()];
            string lastName = lastNames[rand() % lastNames.size()];

            string studentID = generateStudentID(usedIDs); // Generate a unique student ID

            usedIDs.insert(studentID);

            int gradeLevel = rand() % 4 + 1; // Random grade level between 1 and 4
            string courseChoice = courses[i].getCourseName(i); // Assign course to student

            Student *newStudent = new Student(firstName, lastName, studentID, gradeLevel, courseChoice);
            courses[i].enrollStudent(newStudent);
        }

        // If the course is full, randomly add 0 to 3 students to the waitlist
        if (courses[i].getEnrolledCount() == courses[i].getMaxCapacity()) {
            int waitlistCount = rand() % 4; // Randomly choose between 0 to 3 students to add to the waitlist

            for (int j = 0; j < waitlistCount; ++j) {
                string firstName = firstNames[rand() % firstNames.size()];
                string lastName = lastNames[rand() % lastNames.size()];

                string studentID = generateStudentID(usedIDs); // Generate a unique student ID

                int studentGradeLevel = rand() % 4 + 1; // Random grade level between 1 and 4
                string courseChoice = courses[i].getCourseName(i); // Assign course to student

                Student* waitlistedStudent = new Student(firstName, lastName, studentID, studentGradeLevel, courseChoice);
                courses[i].addToWaitlist(waitlistedStudent); // Use the new method to add to the waitlist
            }
        }
    }
}



int main() {
    // Create courses with max capacity of 20 students and waitlist capacity of 5
    vector<Course> courses;
    for (int i = 0; i < 20; i++) {
        courses.push_back(Course(20, 5));
    }

    string firstName, lastName, studentID;
    int gradeLevel;

    // Get user details
    cout << "Enter your first name: ";
    cin >> firstName;
    cout << "Enter your last name: ";
    cin >> lastName;
    cout << "Enter your student ID: ";
    cin >> studentID;
    cout << "Enter your grade level (1: Freshman, 2: Sophomore, 3: Junior, 4: Senior): ";
    cin >> gradeLevel;

    Student* newStudent = new Student(firstName, lastName, studentID, gradeLevel, "");

    // Fill courses based on user grade level
    fillCoursesRandomly(courses, gradeLevel);

    int choice;

// Display options menu
    do {
        cout << "\n1. View Course List\n2. Register for a Course\n3. Drop a Course\n";
        cout << "4. View Registered Students in a Course\n5. View Registered Courses\n6. Exit Registration\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Check if the input is valid (i.e., an integer)
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input in the buffer
            cout << "Invalid input. Please enter a valid number (1-6).\n";
            continue; // Skip the rest of the loop and ask for input again
        }

        if (choice == 1) {
            cout << "\nAvailable Courses:\n";
            cout << "------------------------------------------------------\n";
            cout << left << setw(10) << "Index " << setw(24) << "Course Name" << "Seats Filled\n";
            cout << "------------------------------------------------------\n";

            for (int i = 0; i < courses.size(); ++i) {
                cout << setw(11) << i + 1  // Display the course index
                     << setw(20) << courses[i].getCourseName(i)  // Display the course name with proper spacing
                     << courses[i].getEnrolledCount() << "/" << courses[i].getMaxCapacity() << " Seats Filled\n";
            }
            cout << "------------------------------------------------------\n";
        }

        if (choice == 2) {
            // Register for a course
            cout << "\nEnter the name of the course you want to register in (ex: ENGL 1000): ";
            string courseName;
            cin.ignore();
            getline(cin, courseName);

            bool courseFound = false;

            for (int i = 0; i < 20; ++i) {
                if (courses[i].getCourseName(i) == courseName) {
                    if (newStudent->registeredCourses.count(courseName) == 0) {
                        courses[i].enrollStudent(newStudent);
                        newStudent->registeredCourses.insert(courseName); // Track course registration
                        courseFound = true;
                        cout << "Enrollment successful for " << newStudent->firstName << " " << newStudent->lastName << ".\n";
                    } else {
                        cout << "You are already registered for " << courseName << ".\n";
                    }
                    break;
                }
            }

            if (!courseFound) {
                cout << "Course not found. Please check the course name and try again.\n";
            }
        }

        else if (choice == 3) {
            // Drop a course
            cout << "\nEnter the name of the course you want to drop: ";
            string courseName;
            cin.ignore();
            getline(cin, courseName);

            bool courseFound = false;

            for (int i = 0; i < 20; ++i) {
                if (courses[i].getCourseName(i) == courseName) {
                    if (newStudent->registeredCourses.count(courseName) > 0) {
                        courses[i].dropStudent(newStudent->studentID);
                        newStudent->registeredCourses.erase(courseName); // Remove course from user's registrations
                        cout << "You have successfully dropped " << courseName << ".\n";
                        courseFound = true;
                    } else {
                        cout << "You are not registered for " << courseName << ".\n";
                    }
                    break;
                }
            }

            if (!courseFound) {
                cout << "Course not found. Please check the course name and try again.\n";
            }
        }

        else if (choice == 4) {
            // View registered students in a course
            cout << "\nEnter the name of the course to view registered students (ex: ENGL 1000): ";
            string courseName;
            cin.ignore(); // Ignore the newline character
            getline(cin, courseName); // Get the full course name

            bool courseFound = false;

            for (int i = 0; i < 20; ++i) {
                if (courses[i].getCourseName(i) == courseName) {
                    cout << "\nRegistered Students in " << courseName << ":\n";
                    courses[i].showStudents(); // Show enrolled and waitlisted students
                    courseFound = true;
                    break;
                }
            }

            if (!courseFound) {
                cout << "Course not found. Please check the course name and try again.\n";
            }
        }

        else if (choice == 5) {
            // View registered courses
            if (newStudent->registeredCourses.empty()) {
                cout << "You are not registered for any courses.\n";
            } else {
                cout << "\nCourses you are registered for:\n";
                for (const string& course : newStudent->registeredCourses) {
                    cout << "- " << course << "\n";
                }
            }
        }

        else if (choice == 6) {
            // Exit the system
            cout << "Exiting Registration System.\n";
        }

    } while (choice != 6);

    return 0;
}

