#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

class Student
{
private:
    int rollNumber;
    int classNumber;

public:
    // Constructor
    Student() = default;
    Student(int roll, int cls) : rollNumber(roll), classNumber(cls) {}

    // Getter methods
    int getRollNumber() { return rollNumber; }
    int getClassNumber() { return classNumber; }
};

class ExamSeatingPlan
{
private:
    int totalSeats;
    int totalStudents;
    Student *seatingArrangement;

public:
    // Constructor
    ExamSeatingPlan(int totalSeats, int totalStudents)
        : totalSeats(totalSeats), totalStudents(totalStudents)
    {
        seatingArrangement = new Student[totalStudents];
    }

    // Method to randomly assign students to seats
    void generateSeatingPlan()
    {
        int rollNumber = 1;
        for (int i = 0; i < totalStudents; ++i)
        {
            seatingArrangement[i] = Student(rollNumber, 1); // All students in one class
            rollNumber++;
        }

        // Shuffle the seating arrangement randomly
        srand(time(0));
        for (int i = 0; i < totalStudents; ++i)
        {
            int randomSeat = rand() % totalStudents;

            // Swap students
            Student temp = seatingArrangement[i];
            seatingArrangement[i] = seatingArrangement[randomSeat];
            seatingArrangement[randomSeat] = temp;
        }
    }

    // Method to display the seating arrangement
    void displaySeatingPlan()
    {
        cout << "Exam Seating Plan:" << endl;
        for (int i = 0; i < totalStudents; ++i)
        {
            cout << "Seat " << i + 1 << ": Student " << seatingArrangement[i].getRollNumber()<< endl;
        }
    }

    // Method to save seating arrangement to a file
    void saveToFile(string filename)
    {
        ofstream file(filename, ios::app); // Open file in append mode
        if (file.is_open())
        {
            file << "Exam Seating Plan:" << endl;
            for (int i = 0; i < totalStudents; ++i)
            {
                file << "Seat " << i + 1 << ": Student " << seatingArrangement[i].getRollNumber()
                << endl;
            }
            file.close();
            cout << "Seating plan appended to " << filename << endl;
        }
        else
        {
            cout << "Unable to open file " << filename << " for writing." << endl;
        }
    }

    // Destructor to free memory
    ~ExamSeatingPlan()
    {
        delete[] seatingArrangement;
    }
};

int main()
{
    int totalClasses;
    cout << "Enter the number of classes: ";
    cin >> totalClasses;

    // Dynamically allocate memory for classStrength array
    int *classStrength = new int[totalClasses];

    // Input class strengths and check for non-numeric input
    int totalStudents = 0;
    for (int i = 0; i < totalClasses; ++i)
    {
        cout << "Enter strength of class " << i + 1 << ": ";
        if (!(cin >> classStrength[i]))
        {
            cout << "Invalid input. Please enter a numeric value." << endl;
            delete[] classStrength; // Free allocated memory
            return 1;               // Exit program with error code
        }
        totalStudents += classStrength[i];
    }

    // Calculate total number of seats
    int totalSeats = totalStudents;

    ExamSeatingPlan seatingPlan(totalSeats, totalStudents);
    seatingPlan.generateSeatingPlan();
    seatingPlan.displaySeatingPlan();

    char saveChoice;
    cout << "Do you want to save this seating plan to a file? (Y/N): ";
    cin >> saveChoice;

    if (saveChoice == 'Y' || saveChoice == 'y')
    {
        string filename = "seating_plan.txt";
        seatingPlan.saveToFile(filename);
    }
    else
    {
        cout << "Seating plan not saved." << endl;
    }

    // Free allocated memory
    delete[] classStrength;

    return 0;
}
