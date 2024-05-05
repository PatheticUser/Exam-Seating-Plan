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
    ExamSeatingPlan(int totalSeats, int totalStudents, int totalClasess)
        : totalSeats(totalSeats), totalStudents(totalStudents), totalClasses(totalClasess) 
    {
        seatingArrangement = new Student[totalStudents];
    }

    // Method to display the most recent seating plan from the file
    void displaySeatingPlanFromFile()
    {
        ifstream file("Seating Plan.txt");
        if (!file.is_open())
        {
            cout << "Unable to open file 'Seating Plan.txt' for reading." << endl;
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
            cout << "Unable to open file 'Seating Plan.txt' for writing." << endl;
        }
    }

    // Method to backup seating plan to a new file
    void backupToFile(string newFilename)
    {
        // Open original file for reading
        ifstream originalFile("Seating Plan.txt");
        if (!originalFile.is_open())
        {
            cout << "Unable to open file 'Seating Plan.txt' for reading." << endl;
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

    // Method to generate seating plan with random arrangement
    void generateRandomSeatingPlan()
    {
        // Assign roll numbers to students in increasing order
        for (int i = 0; i < totalStudents; ++i)
        {
            // Assign roll numbers starting from 1 up to the total number of students
            // Also, assign class numbers sequentially based on the number of students per class
            seatingArrangement[i] = Student(i + 1, (i / (totalStudents / totalClasses)) + 1);
        }

        // Shuffle the seating arrangement randomly
        srand(time(0));
        for (int i = 0; i < totalStudents; ++i)
        {
            // Generate a random index within the range of totalStudents
            int randomSeat = rand() % totalStudents;

            // Swap the current student with a randomly selected student
            Student temp = seatingArrangement[i];
            seatingArrangement[i] = seatingArrangement[randomSeat];
            seatingArrangement[randomSeat] = temp;
        }
    }

    void generateMixedSeatingPlan()
    {
        // Determine the number of students to assign in each step
        int evenStepSize = totalStudents / 4;   // Assign even roll numbers
        int oddStepSize = totalStudents / 4;    // Assign odd roll numbers
        int randomStepSize = totalStudents / 2; // Assign remaining randomly

        int evenIndex = 0;
        int oddIndex = 0;
        int randomIndex = evenStepSize + oddStepSize;

        // Assign even roll numbers
        for (int i = 0; i < evenStepSize; ++i)
        {
            seatingArrangement[i] = Student(evenIndex * 2 + 1, 0); 
            evenIndex++;
        }

        // Assign odd roll numbers
        for (int i = 0; i < oddStepSize; ++i)
        {
            seatingArrangement[evenStepSize + i] = Student(oddIndex * 2 + 2, 0); 
            oddIndex++;
        }

        // Assign remaining students randomly
        srand(time(0));
        for (int i = randomIndex; i < totalStudents; ++i)
        {
            // Find an unassigned seat randomly
            int randomSeat = rand() % (totalStudents - randomIndex) + randomIndex;
            while (seatingArrangement[randomSeat].getRollNumber() != 0)
            {
                randomSeat = rand() % (totalStudents - randomIndex) + randomIndex;
            }

            // Assign roll number
            seatingArrangement[randomSeat] = Student(i + 1, 0); 
        }
    }

    // Method to generate seating plan with sequential arrangement
    void generateSequentialSeatingPlan()
    {
        int rollNumber = 1;
        for (int i = 0; i < totalStudents; ++i)
        {
            seatingArrangement[i] = Student(rollNumber, 0); 
            rollNumber++;
        }
    }

    // Destructor to free-ing memory
    ~ExamSeatingPlan()
    {
        delete[] seatingArrangement;
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

    return 'X'; // Invalid user type or credentials
}

int main()
{
    // Create objects for Teacher and Student
    Teacher teacher("t", "p");
    Student student("s", "p");

    // Declare seatingPlan object
    ExamSeatingPlan seatingPlan(0, 0, 0); // Dummy object to access member functions ;)

    char userType;
    do
    {
        userType = login();
        if (userType == 'T')
        {
            // Teacher logged in
            int choice;
            cout << "Teacher logged in. Choose an option:" << endl;
            cout << "1. Generate Seating Plan" << endl;
            cout << "3. Backup Seating Plan" << endl;
            cout << "4. Exit" << endl;
            cin >> choice;

            if (choice == 1)
            {
                // Generate seating plan
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
                        delete[] classStrength; // Free-ing allocated memory
                        return 1;               // Exit program with error code
                    }
                    totalStudents += classStrength[i];
                }

                // Calculate total number of seats
                int totalSeats = totalStudents;

                // Create seatingPlan object
                seatingPlan = ExamSeatingPlan(totalSeats, totalStudents, totalClasses);
                cout << "Choose an option:" << endl;
                cout << "1. Generate Random Seating Plan" << endl;
                cout << "2. Generate Sequential Seating Plan" << endl;
                cout << "3. Generate mixed Seating Plan" << endl;
                cout << "4. Save Seating Plan" << endl;
                cout << "5. Exit" << endl;
                cin >> choice;

                if (choice == 1)
                {
                    // Generate random seating plan
                    seatingPlan.generateRandomSeatingPlan();
                    seatingPlan.displaySeatingPlan();
                }
                else if (choice == 2)
                {
                    // Generate sequential seating plan
                    seatingPlan.generateSequentialSeatingPlan();
                    seatingPlan.displaySeatingPlan();
                }
                else if (choice == 3)
                {
                    seatingPlan.generateMixedSeatingPlan();
                    seatingPlan.displaySeatingPlan();
                }
                else if (choice == 4)
                {
                    seatingPlan.saveToFile();
                }
                else if (choice == 5)
                {
                    cout << "Exiting program." << endl;
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                }

                // Free-ing allocated memory
                delete[] classStrength;
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
        else if (userType == 'S')
        {
            // Student logged in
            cout << "Student logged in. Displaying Most Recent Seating Plan:" << endl;
            seatingPlan.displaySeatingPlanFromFile();
        }
        else
        {
            cout << "Invalid user type or credentials. Please try again." << endl;
        }
    } while (userType != 'T' && userType != 'S');

    return 0;
}
