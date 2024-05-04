#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// Teacher class
class Teacher
{
private:
    string username;
    string password;

public:
    // Constructor
    Teacher(string uname, string pwd) : username(uname), password(pwd) {}

    // Method to verify login credentials
    bool verifyLogin(string uname, string pwd)
    {
        return (username == uname && password == pwd);
    }
};

class Student
{
private:
    string username;
    string password;
    int rollNumber;
    int classNumber;

public:
    // Default constructor
    Student() : rollNumber(0), classNumber(0) {}

    // Parameterized constructor
    Student(int roll, int cls) : rollNumber(roll), classNumber(cls) {}

    // Getter methods
    int getRollNumber() { return rollNumber; }
    int getClassNumber() { return classNumber; }

    // Constructor with username and password
    Student(string uname, string pwd) : username(uname), password(pwd) {}

    // Method to verify login credentials
    bool verifyLogin(string uname, string pwd)
    {
        return (username == uname && password == pwd);
    }
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
            seatingArrangement[i] = Student(to_string(rollNumber), "password123"); // All students in one class
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

    // Method to display the most recent seating plan from the file
    void displaySeatingPlanFromFile()
    {
        ifstream file("Seating Plan.txt");
        if (!file.is_open())
        {
            cout << "Unable to open file Seating Plan.txt for reading." << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
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
        ofstream file("Seating Plan.txt", ios::app);
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
            cout << "Seating plan appended to Seating Plan.txt" << endl;
        }
        else
        {
            cout << "Unable to open file Seating Plan.txt for writing." << endl;
        }
    }

    // Method to backup seating plan to a new file
    void backupToFile(string newFilename)
    {
        // Open original file for reading
        ifstream originalFile("Seating Plan.txt");
        if (!originalFile.is_open())
        {
            cout << "Unable to open file Seating Plan.txt for reading." << endl;
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

// Login function
char login()
{
    char userType;
    cout << "Login as (T)eacher or (S)tudent: ";
    cin >> userType;
    return toupper(userType);
}

int main()
{
    // Create objects for Teacher and Student
    Teacher teacher("teacher123", "password123");
    Student student("student123", "password123");

    ExamSeatingPlan seatingPlan(50, 50); // Initialize with some values

    char userType;
    do
    {
        userType = login();
        if (userType == 'T')
        {
            // Teacher logged in
            if (teacher.verifyLogin("teacher123", "password123"))
            {
                int choice;
                cout << "Teacher logged in. Choose an option:" << endl;
                cout << "1. Generate Seating Plan" << endl;
                cout << "2. Save Seating Plan" << endl;
                cout << "3. Backup Seating Plan" << endl;
                cout << "4. Exit" << endl;
                cin >> choice;

                if (choice == 1)
                {
                    // Generate seating plan
                    seatingPlan.generateSeatingPlan();
                    seatingPlan.displaySeatingPlan();
                }
                else if (choice == 2)
                {
                    // Save seating plan
                    seatingPlan.saveToFile();
                }
                else if (choice == 3)
                {
                    // Backup seating plan
                    string newFilename;
                    cout << "Enter the name of the new file: ";
                    cin >> newFilename;
                    seatingPlan.backupToFile(newFilename);
                }
                else if (choice == 4)
                {
                    // Exit
                    cout << "Exiting program." << endl;
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
            else
            {
                cout << "Invalid credentials. Please try again." << endl;
            }
        }
        else if (userType == 'S')
        {
            // Student logged in
            if (student.verifyLogin("student123", "password123"))
            {
                cout << "Student logged in. Displaying Most Recent Seating Plan:" << endl;
                seatingPlan.displaySeatingPlanFromFile();
            }
            else
            {
                cout << "Invalid credentials. Please try again." << endl;
            }
        }
        else
        {
            cout << "Invalid user type. Please try again." << endl;
        }
    } while (userType != 'T' && userType != 'S');

    return 0;
}
