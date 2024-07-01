//============================================================================
// Name        : CS300ProjectM7.cpp
// Author      : Liam O'Brien
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Project 2 7-1
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;

// Structure to store course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to convert a string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Function to load course data from a CSV file into an unordered_map
void loadData(unordered_map<string, Course>& courseTable) {
    string fileName = "CS 300 ABCU_Advising_Program_Input.csv"; // File name to open

    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file. Please ensure the file is in the correct directory and try again." << endl;
        cerr << "Attempted to open file: " << fileName << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string part;
        vector<string> parts;

        // Split the line by commas
        while (getline(ss, part, ',')) {
            parts.push_back(part);
        }

        // Ensure the line has at least a course number and title
        if (parts.size() < 2) {
            cerr << "Error: Invalid format in line: " << line << endl;
            return;
        }

        // Extract course information
        string courseNumber = parts[0];
        string courseTitle = parts[1];
        vector<string> prerequisites(parts.begin() + 2, parts.end());

        // Create a Course object and add it to the map
        Course course = { courseNumber, courseTitle, prerequisites };
        courseTable[courseNumber] = course;
    }

    file.close();
    cout << "Data loaded successfully." << endl;
}

// Function to print the list of courses in alphanumeric order
void printSortedCourses(const unordered_map<string, Course>& courseTable) {
    vector<Course> courseList;

    // Copy courses from the map to a vector
    for (const auto& pair : courseTable) {
        courseList.push_back(pair.second);
    }

    // Sort the courses by course number
    sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    // Print the sorted list of courses
    cout << "Here is a sample schedule:" << endl;
    for (const Course& course : courseList) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Function to print information about a specific course
void printCourseInformation(const unordered_map<string, Course>& courseTable) {
    string courseNumber;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    courseNumber = toLower(courseNumber); // Convert to lowercase for case-insensitive comparison

    auto it = courseTable.find(courseNumber);
    if (it != courseTable.end()) {
        const Course& course = it->second;
        cout << course.courseNumber << ", " << course.courseTitle << endl;
        if (!course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                if (i != 0) cout << ", ";
                cout << course.prerequisites[i];
            }
            cout << endl;
        }
        else {
            cout << "Prerequisites: None" << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}

// Main menu function to interact with the user
void displayMenu() {
    unordered_map<string, Course> courseTable;
    int choice;

    do {
        // Display menu options
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit." << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        // Handle user's menu choice
        switch (choice) {
        case 1:
            loadData(courseTable);
            break;
        case 2:
            printSortedCourses(courseTable);
            break;
        case 3:
            printCourseInformation(courseTable);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    } while (choice != 9);
}

// Main function to start the program
int main() {
    cout << "Welcome to the course planner." << endl;
    displayMenu();
    return 0;
}