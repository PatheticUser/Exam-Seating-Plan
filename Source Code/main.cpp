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
            cout << "Seat " << i + 1 << ": Student " << seatingArrangement[i].getRollNumber() << endl;
        }
    }

    // Method to save seating arrangement to a file with timestamp
    void saveToFile()
    {
        // Get current time
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Open file in append mode
        ofstream file("seating_plan.txt", ios::app);
        if (file.is_open())
        {
            // Append seating plan with timestamp
            file << "Exam Seating Plan (Generated at "
                 << ltm->tm_hour << ":" << ltm->tm_min << " on "
                 << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << "):" << endl;
            for (int i = 0; i < totalStudents; ++i)
            {
                file << "Seat " << i + 1 << ": Student " << seatingArrangement[i].getRollNumber() << endl;
            }
            file << endl;
            file.close();
            cout << "Seating plan appended to seating_plan.txt" << endl;
        }
        else
        {
            cout << "Unable to open file seating_plan.txt for writing." << endl;
        }
    }

    // Method to backup seating plan to a new file
    void backupToFile(string newFilename)
    {
        // Open original file for reading
        ifstream originalFile("seating_plan.txt");
        if (!originalFile.is_open())
        {
            cout << "Unable to open file seating_plan.txt for reading." << endl;
            return;
        }

        // Open new file for writing
        ofstream backupFile(newFilename);
        if (!backupFile.is_open())
        {
            cout << "Unable to open file " << newFilename << " for writing." << endl;
            originalFile.close();
            return;
        }

        // Copy contents from original file to backup file
        backupFile << originalFile.rdbuf();

        // Close files
        originalFile.close();
        backupFile.close();

        cout << "Seating plan backed up to " << newFilename << endl;
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

int choice;
do
{
    cout << "Choose an option:" << endl;
    cout << "1. Save Seating Plan" << endl;
    cout << "2. Backup Seating Plan" << endl;
    cout << "3. Exit Seating Plan" << endl;
    cin >> choice;

    if (choice == 1)
    {
        seatingPlan.saveToFile();
    }
    else if (choice == 2)
    {
        string newFilename;
        cout << "Enter the name of the new file: ";
        cin >> newFilename;
        seatingPlan.backupToFile(newFilename);
    }
    else if (choice == 3)
    {
        cout << "Exiting program." << endl;
    }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
    }
} while (choice != 3);


    // Free allocated memory
    delete[] classStrength;

    return 0;
}
