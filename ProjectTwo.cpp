/*
 * Project Two
 * CS-300 Data Structures and Algorithms
 * Cody Sparks
 * June 2026
 *
 * Advising Assistance Program
 *
 * This program stores course information in a Binary Search Tree.
 * Users can load course data, print a sorted course list, and
 * search for individual course information and prerequisites.
 */

#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Structure used to store course information
struct Course {
    string courseId;
    string courseTitle;
    vector<string> preRequisite;
};

// Display menu options
void DisplayMenu() {
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do?" << endl;
}

// Node used by the Binary Search Tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Initialize node with course data
    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree used to store course information
class BinarySearchTree {
private:
    Node* root;

    // Helper function used during insertion
    void addNode(Node* node, Course course);

    // Helper function used during inorder traversal
    void inOrder(Node* node);

public:

    // Constructor creates an empty tree
    BinarySearchTree() {
        root = nullptr;
    }

    // Insert a course into the tree
    void Insert(Course course);

    // Search for a course by course ID
    Course Search(string courseId);

    // Display courses in alphanumeric order
    void InOrder();
};

// Insert a course into the Binary Search Tree
void BinarySearchTree::Insert(Course course) {

    // If tree is empty, make course the root
    if (root == nullptr) {
        root = new Node(course);
    }

    // Otherwise find correct location
    else {
        addNode(root, course);
    }
}

// Recursively locate the correct position and add a course
void BinarySearchTree::addNode(Node* node, Course course) {

    // Move left if course ID is smaller
    if (course.courseId < node->course.courseId) {

        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }

    // Move right if course ID is larger
    else {

        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}

// Search the tree for a specific course ID
Course BinarySearchTree::Search(string courseId) {

    // Start at the root node
    Node* current = root;

    // Continue until course is found or tree ends
    while (current != nullptr) {

        // Return course if IDs match
        if (current->course.courseId == courseId) {
            return current->course;
        }

        // Move left if target is smaller
        if (courseId < current->course.courseId) {
            current = current->left;
        }

        // Move right if target is larger
        else {
            current = current->right;
        }
    }

    // Return empty course if not found
    Course course;
    return course;
}

// Display courses in alphanumeric order
void BinarySearchTree::InOrder() {
    inOrder(root);
}

// Recursive inorder traversal
void BinarySearchTree::inOrder(Node* node) {

    if (node != nullptr) {

        // Visit left subtree
        inOrder(node->left);

        // Display current course
        cout << node->course.courseId
            << ", "
            << node->course.courseTitle
            << endl;

        // Visit right subtree
        inOrder(node->right);
    }
}

// Load course data from file into the Binary Search Tree
void LoadCourses(string csvPath, BinarySearchTree* bst) {

    // Open input file
    ifstream file(csvPath);

    // Verify file opened successfully
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;

    // Read each line from the file
    while (getline(file, line)) {

        Course course;
        string token;
        stringstream ss(line);

        // Read course ID
        getline(ss, course.courseId, ',');

        // Read course title
        getline(ss, course.courseTitle, ',');

        // Read prerequisites
        while (getline(ss, token, ',')) {
            course.preRequisite.push_back(token);
        }

        // Insert course into BST
        bst->Insert(course);
    }

    file.close();

    cout << "Courses loaded successfully." << endl;
}

int main() {

    BinarySearchTree bst;

    int choice = 0;

    while (choice != 9) {

        DisplayMenu();
        cin >> choice;

        switch (choice) {

        case 1:
        {

            LoadCourses("CS 300 ABCU_Advising_Program_Input.csv", &bst);
            break;
        }

        case 2:
            cout << endl;
            bst.InOrder();
            cout << endl;
            break;

       
        case 3:
        {
            string courseId;

            cout << "Enter course number: ";
            cin >> courseId;

            Course course = bst.Search(courseId);

            if (course.courseId.empty()) {
                cout << "Course not found." << endl;
            }
            else {
                cout << course.courseId
                    << ", "
                    << course.courseTitle << endl;

                cout << "Prerequisites: ";

                if (course.preRequisite.empty()) {
                    cout << "None";
                }
                else {
                    for (unsigned int i = 0; i < course.preRequisite.size(); i++) {
                        cout << course.preRequisite[i];

                        if (i < course.preRequisite.size() - 1) {
                            cout << ", ";
                        }
                    }
                }

                cout << endl;
            }

            break;
        }

        case 9:
            cout << "Goodbye." << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}

