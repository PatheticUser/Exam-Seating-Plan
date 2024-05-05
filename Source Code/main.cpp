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
    int totalClasses;
    Student *seatingArrangement;

public:
    // Constructor
    ExamSeatingPlan(int totalSeats, int totalStudents, int totalClasses)
        : totalSeats(totalSeats), totalStudents(totalStudents), totalClasses(totalClasses)
    {
        seatingArrangement = new Student[totalStudents];
    }

    // Destructor
    ~ExamSeatingPlan()
    {
        delete[] seatingArrangement;
    }

    // Method to save seating plan to file
    void saveToFile(string filename)
    {
        // Get current time
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Open file in append mode
        ofstream file(filename, ios::app);
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
            cout << "Seating plan appended to " << filename << endl;
        }
        else
        {
            cout << "Unable to open file " << filename << " for writing." << endl;
        }
    }

    // Method to display the most recent seating plan from the file
    void displaySeatingPlanFromFile(string filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Unable to open file '" << filename << "' for reading." << endl;
            return;
        }

        string line;
        string recentSeatingPlan;
        while (getline(file, line))
        {
            if (line.find("Exam Seating Plan") != string::npos)
            {
                recentSeatingPlan = line + "\n";
                while (getline(file, line) && !line.empty())
                {
                    recentSeatingPlan += line + "\n";
                }
            }
        }

        if (!recentSeatingPlan.empty())
        {
            cout << recentSeatingPlan << endl;
        }
        else
        {
            cout << "No seating plan found." << endl;
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

    // Method to backup seating plan to a new file
    void backupToFile(string newFilename)
    {
        ifstream originalFile("Seating Plan.txt");
        if (!originalFile.is_open())
        {
            cout << "Unable to open file 'Seating Plan.txt' for reading." << endl;
            return;
        }

        ofstream backupFile(newFilename);
        if (!backupFile.is_open())
        {
            cout << "Unable to open file " << newFilename << " for writing." << endl;
            originalFile.close();
            return;
        }

        backupFile << originalFile.rdbuf();

        originalFile.close();
        backupFile.close();

        cout << "Seating plan backed up to " << newFilename << endl;
    }

    // Method to generate seating plan with random arrangement
    void generateRandomSeatingPlan(string filename)
    {
        int choice;
        do
        {
            // Assign roll numbers to students in increasing order
            for (int i = 0; i < totalStudents; ++i)
            {
                seatingArrangement[i] = Student(i + 1, (i / (totalStudents / totalClasses)) + 1);
            }

            // Shuffle the seating arrangement randomly
            srand(time(0));
            for (int i = 0; i < totalStudents; ++i)
            {
                int randomSeat = rand() % totalStudents;

                Student temp = seatingArrangement[i];
                seatingArrangement[i] = seatingArrangement[randomSeat];
                seatingArrangement[randomSeat] = temp;
            }

            // Display generated seating plan
            displaySeatingPlan();

            // Save seating plan to file
            saveToFile(filename);

            cout << "Do you want to generate another random seating plan? (1: Yes, 0: No): ";
            cin >> choice;
        } while (choice != 0);
    }

    // Method to generate seating plan with sequential arrangement
    void generateSequentialSeatingPlan(string filename)
    {
        int choice;
        do
        {
            int rollNumber = 1;
            for (int i = 0; i < totalStudents; ++i)
            {
                seatingArrangement[i] = Student(rollNumber, 0);
                rollNumber++;
            }

            // Display generated seating plan
            displaySeatingPlan();

            // Save seating plan to file
            saveToFile(filename);

            cout << "Do you want to generate another sequential seating plan? (1: Yes, 0: No): ";
            cin >> choice;
        } while (choice != 0);
    }

    // Method to generate seating plan with mixed arrangement
    void generateMixedSeatingPlan(string filename)
    {
        int choice;
        do
        {
            int evenStepSize = totalStudents / 4;
            int oddStepSize = totalStudents / 4;
            int randomStepSize = totalStudents / 2;

            int evenIndex = 0;
            int oddIndex = 0;
            int randomIndex = evenStepSize + oddStepSize;

            for (int i = 0; i < evenStepSize; ++i)
            {
                seatingArrangement[i] = Student(evenIndex * 2 + 1, 0);
                evenIndex++;
            }

            for (int i = 0; i < oddStepSize; ++i)
            {
                seatingArrangement[evenStepSize + i] = Student(oddIndex * 2 + 2, 0);
                oddIndex++;
            }

            srand(time(0));
            for (int i = randomIndex; i < totalStudents; ++i)
            {
                int randomSeat = rand() % (totalStudents - randomIndex) + randomIndex;
                while (seatingArrangement[randomSeat].getRollNumber() != 0)
                {
                    randomSeat = rand() % (totalStudents - randomIndex) + randomIndex;
                }

                seatingArrangement[randomSeat] = Student(i + 1, 0);
            }

            // Display generated seating plan
            displaySeatingPlan();

            // Save seating plan to file
            saveToFile(filename);

            cout << "Do you want to generate another mixed seating plan? (1: Yes, 0: No): ";
            cin >> choice;
        } while (choice != 0);
    }
};

char login()
{
    char userType;
    string username, password;
    cout << "-------------------------------------------------" << endl;
    cout << "|               Welcome to the Exam              |" << endl;
    cout << "|               Seating Plan System              |" << endl;
    cout << "|                  (Login Page)                  |" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "|Define your role: (T)eacher or (S)tudent ";
    cin >> userType;

    cout << "|Enter Username: ";
    cin >> username;

    cout << "|Enter Password: ";
    cin >> password;

    cout << "-------------------------------------------------" << endl;

    if ((userType == 'T' || userType == 't') && username == "t" && password == "p")
    {
        return 'T';
    }
    else if ((userType == 'S' || userType == 's') && username == "s" && password == "p")
    {
        return 'S';
    }

    return 'X';
}

int main()
{
    // Create objects for Teacher and Student
    Teacher teacher("t", "p");
    Student student("s", "p");

    char userType;
    do
    {
        userType = login();
        if (userType == 'T')
        {
            int choice;
            do
            {
                cout << "Teacher logged in. Choose an option:" << endl;
                cout << "1. Generate Seating Plan" << endl;
                cout << "2. Backup Seating Plan" << endl;
                cout << "3. Logout" << endl;
                cout << "4. Exit" << endl;
                cin >> choice;

                if (choice == 1)
                {
                    int totalClasses;
                    cout << "Enter the number of classes: ";
                    cin >> totalClasses;

                    int *classStrength = new int[totalClasses];
                    int totalStudents = 0;
                    for (int i = 0; i < totalClasses; ++i)
                    {
                        cout << "Enter strength of class " << i + 1 << ": ";
                        if (!(cin >> classStrength[i]))
                        {
                            cout << "Invalid input. Please enter a numeric value." << endl;
                            delete[] classStrength;
                            return 1;
                        }
                        totalStudents += classStrength[i];
                    }

                    int totalSeats = totalStudents;
                    string filename = "Seating Plan.txt";
                    ExamSeatingPlan seatingPlan(totalSeats, totalStudents, totalClasses);

                    cout << "Choose an option:" << endl;
                    cout << "1. Generate Random Seating Plan" << endl;
                    cout << "2. Generate Sequential Seating Plan" << endl;
                    cout << "3. Generate Mixed Seating Plan" << endl;
                    cout << "4. Exit" << endl;
                    cin >> choice;

                    if (choice == 1)
                    {
                        seatingPlan.generateRandomSeatingPlan(filename);
                    }
                    else if (choice == 2)
                    {
                        seatingPlan.generateSequentialSeatingPlan(filename);
                    }
                    else if (choice == 3)
                    {
                        seatingPlan.generateMixedSeatingPlan(filename);
                    }
                    else if (choice == 4)
                    {
                        cout << "Exiting program." << endl;
                        break;
                    }
                    else
                    {
                        cout << "Invalid choice. Please try again." << endl;
                    }

                    delete[] classStrength;
                }
                else if (choice == 2)
                {
                    string newFilename;
                    cout << "Enter the name of the new file: ";
                    cin >> newFilename;
                    ExamSeatingPlan seatingPlan(0, 0, 0);
                    seatingPlan.backupToFile(newFilename);
                }
                else if (choice == 3)
                {
                    cout << "Exiting program." << endl;
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (true);
        }
        else if (userType == 'S')
        {
            int choice;
            do
            {
                cout << "Student logged in. Choose an option:" << endl;
                cout << "1. Display Most Recent Seating Plan" << endl;
                cout << "2. Logout" << endl;
                cout << "3. Exit" << endl;
                cin >> choice;

                if (choice == 1)
                {
                    ExamSeatingPlan seatingPlan(0, 0, 0);
                    seatingPlan.displaySeatingPlanFromFile("Seating Plan.txt");
                }
                else if (choice == 2)
                {
                    cout << "Logging out..." << endl;
                    break;
                }
                else if (choice == 3)
                {
                    cout << "Exiting program." << endl;
                    return 0;
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (true);
        }
        else
        {
            cout << "Invalid user type or credentials. Please try again." << endl;
        }
    } while (true);

    return 0;
}
