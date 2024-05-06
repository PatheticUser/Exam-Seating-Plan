#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

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
public:
    string username;
    string password;
    int rollNumber;
    int classNumber;

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

void registerPage()
{
    cout << "-------------------------------------------------" << endl;
    cout << "|               Welcome to the Exam              |" << endl;
    cout << "|               Seating Plan System              |" << endl;
    cout << "|               (Register Page)                  |" << endl;
    cout << "-------------------------------------------------" << endl;
}

void registerUser(string userType)
{
    string name, username, password;
    int age;
    if (userType == "teacher")
    {
        string key;
        cout << "Enter the key for registering as a teacher: ";
        cin >> key;
        if (key != "KEY")
        {
            cout << "Invalid key. Registration failed." << endl;
            return;
        }
    }
    registerPage();
    cout << "Registering as a " << userType << "." << endl;
    cout << "Enter Name: ";
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    ifstream file(userType + "s.txt");
    string line;
    bool userExists = false;
    while (getline(file, line))
    {
        if (line.find(username) != string::npos)
        {
            userExists = true;
            break;
        }
    }
    file.close();

    if (userExists)
    {
        cout << "Username already exists. Please choose a different username." << endl;
    }
    else
    {
        ofstream outFile(userType + "s.txt", ios::app);
        outFile << "Name: " << name << "\nAge: " << age << "\nUsername: " << username << "\nPassword: " << password << endl;
        outFile.close();
        cout << "Registration successful." << endl;
    }
}

char login()
{
    char userType;
    string username, password;
    cout << "-------------------------------------------------" << endl;
    cout << "|               Welcome to the Exam              |" << endl;
    cout << "|               Seating Plan System              |" << endl;
    cout << "|                  (Login Page)                  |" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "| Define your role: (T)eacher or (S)tudent (E)xit: ";
    cin >> userType;

    if (userType == 'E' || userType == 'e')
    {
        return 'E';
    }
    else if (userType == 'T' || userType == 't')
    {
        cout << "| Enter Username: ";
        cin >> username;
        cout << "| Enter Password: ";
        cin >> password;

        ifstream file("teachers.txt");
        string line;
        bool userExists = false;
        while (getline(file, line))
        {
            size_t pos = line.find("Username: ");
            if (pos != string::npos)
            {
                string storedUsername = line.substr(pos + 10);
                if (storedUsername == username)
                {
                    userExists = true;
                    getline(file, line); // Read the next line (Password)
                    pos = line.find("Password: ");
                    string storedPassword = line.substr(pos + 10);
                    if (storedPassword == password)
                    {
                        file.close();
                        return 'T';
                    }
                    else
                    {
                        break; // Password doesn't match, no need to continue checking
                    }
                }
            }
        }
        file.close();
        cout << "Invalid username or password. Please try again." << endl;
    }
    else if (userType == 'S' || userType == 's')
    {
        cout << "| Enter Username: ";
        cin >> username;
        cout << "| Enter Password: ";
        cin >> password;

        ifstream file("students.txt");
        string line;
        bool userExists = false;
        while (getline(file, line))
        {
            size_t pos = line.find("Username: ");
            if (pos != string::npos)
            {
                string storedUsername = line.substr(pos + 10);
                if (storedUsername == username)
                {
                    userExists = true;
                    getline(file, line); // Read the next line (Password)
                    pos = line.find("Password: ");
                    string storedPassword = line.substr(pos + 10);
                    if (storedPassword == password)
                    {
                        file.close();
                        return 'S';
                    }
                    else
                    {
                        break; // Password doesn't match, no need to continue checking
                    }
                }
            }
        }
        file.close();
        cout << "Invalid username or password. Please try again." << endl;
    }
    else
    {
        cout << "Invalid option. Please try again." << endl;
    }

    return 'X';
}

char startingPage()
{
    char choice;
    cout << "-------------------------------------------------" << endl;
    cout << "|               Welcome to the Exam              |" << endl;
    cout << "|               Seating Plan System              |" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "| Choose an option:                              |" << endl;
    cout << "| (L)ogin                                        |" << endl;
    cout << "| (R)egister                                     |" << endl;
    cout << "| (E)xit                                         |" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

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

    // Method to swap seats
    void swapSeats(int seat1, int seat2)
    {
        if (seat1 < 1 || seat1 > totalStudents || seat2 < 1 || seat2 > totalStudents)
        {
            cout << "Invalid seat numbers. Seats out of range." << endl;
            return;
        }

        Student temp = seatingArrangement[seat1 - 1];
        seatingArrangement[seat1 - 1] = seatingArrangement[seat2 - 1];
        seatingArrangement[seat2 - 1] = temp;

        cout << "Seats swapped successfully." << endl;
    }

    // Method to change assignment
    void changeAssignment(int seatNumber, int newRollNumber)
    {
        if (seatNumber < 1 || seatNumber > totalStudents)
        {
            cout << "Invalid seat number. Seat out of range." << endl;
            return;
        }
        seatingArrangement[seatNumber - 1].rollNumber = newRollNumber;
        cout << "Assignment changed successfully." << endl;
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

    int getTotalSeats()
    {
        return totalSeats;
    }

    void editSeatingPlan(ExamSeatingPlan &seatingPlan, const string &filename)
    {
        cout << "Editing Seating Plan..." << endl;

        // Display the current seating plan
        seatingPlan.displaySeatingPlan();

        // Menu for editing options
        int editChoice;
        do
        {
            cout << "\nEditing Options:" << endl;
            cout << "1. Swap Seats" << endl;
            cout << "2. Change Assignment" << endl;
            cout << "3. Exit Editing" << endl;
            cout << "Enter your choice: ";
            cin >> editChoice;

            switch (editChoice)
            {
            case 1:
            {
                // Swap seats
                int seat1, seat2;
                cout << "Enter seat numbers to swap: ";
                cin >> seat1 >> seat2;
                if (seat1 < 1 || seat1 > seatingPlan.getTotalSeats() || seat2 < 1 || seat2 > seatingPlan.getTotalSeats())
                {
                    cout << "Invalid seat numbers. Please try again." << endl;
                    break;
                }

                // Perform swap operation on seatingPlan
                seatingPlan.swapSeats(seat1, seat2);
                break;
            }
            case 2:
            {
                // Change assignment
                int seatNumber, newRollNumber;
                cout << "Enter seat number and new roll number: ";
                cin >> seatNumber >> newRollNumber;
                if (seatNumber < 1 || seatNumber > seatingPlan.getTotalSeats())
                {
                    cout << "Invalid seat number. Please try again." << endl;
                    break;
                }

                // Perform assignment change operation on seatingPlan
                seatingPlan.changeAssignment(seatNumber, newRollNumber);
                break;
            }
            case 3:
                cout << "Exiting editing mode." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        } while (editChoice != 3);

        // After editing, display the modified seating plan
        cout << "Modified Seating Plan:" << endl;
        seatingPlan.displaySeatingPlan();

        // Ask the user if they want to save the modified seating plan
        char saveChoice;
        cout << "Do you want to save the modified seating plan? (Y/N): ";
        cin >> saveChoice;

        if (saveChoice == 'Y' || saveChoice == 'y')
        {
            // Save the modified seating plan to the same file
            seatingPlan.saveToFile(filename);
            cout << "Modified seating plan saved successfully." << endl;
        }
        else
        {
            cout << "Modified seating plan not saved." << endl;
        }
    }

    // Method to generate seating plan with random arrangement
int generateRandomSeatingPlan(string filename)
{
    int choice,editChoice;
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
        
        cout << "Do you want to edit this seating plan? (1: Yes, 0: No) ";
        cin >> editChoice;
        
        if (editChoice == 1)
        {
            editSeatingPlan(*this, filename); // Edit the seating plan
        }

        cout << "Do you want to generate another Random Seating Plan? (1: Yes, 0: No): ";
        cin >> choice;
    } while (choice != 0);
    
    return editChoice;
}

    // Method to generate seating plan with sequential arrangement
int generateSequentialSeatingPlan(string filename)
{
    int choice, editChoice;
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
        
        cout << "Do you want to edit this seating plan? (1: Yes, 0: No) ";
        cin >> editChoice;
        
        if (editChoice == 1)
        {
            editSeatingPlan(*this, filename); // Edit the seating plan
        }

        cout << "Do you want to generate another Sequential Seating Plan? (1: Yes, 0: No): ";
        cin >> choice;
    } while (choice != 0);
    return editChoice;
}


    /// Method to generate seating plan with Mixed arrangement
int generateMixedSeatingPlan(string filename)
{
    int choice, editChoice;
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
        
        cout << "Do you want to edit this seating plan? (1: Yes, 0: No) ";
        cin >> editChoice;
        
        if (editChoice == 1)
        {
            editSeatingPlan(*this, filename); // Edit the seating plan
        }

        cout << "Do you want to generate another Mixed Seating Plan? (1: Yes, 0: No): ";
        cin >> choice;
    } while (choice != 0);
    return editChoice;
}

};

int main()
{
    char choice;
    do
    {
        choice = startingPage();
        switch (choice)
        {
        case 'L':
        case 'l':
            char userType;
            do
            {
                userType = login();
                if (userType == 'T')
                {
                    cout << "Logged in as Teacher." << endl;
                    int choice;
                    do
                    {
                        cout << "Teacher logged in. Choose an option:" << endl;
                        cout << "1. Generate Seating Plan" << endl;
                        cout << "2. Backup Seating Plan" << endl;
                        cout << "3. Logout" << endl;
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
                                int result = seatingPlan.generateRandomSeatingPlan(filename);
                                if (result == 1)
                                {
                                    seatingPlan.editSeatingPlan(seatingPlan, filename);
                                }
                            }
                            else if (choice == 2)
                            {
                                int result = seatingPlan.generateSequentialSeatingPlan(filename);
                                if (result == 1)
                                {
                                    seatingPlan.editSeatingPlan(seatingPlan, filename);
                                }
                            }
                            else if (choice == 3)
                            {
                                int result = seatingPlan.generateMixedSeatingPlan(filename);
                                if (result == 1)
                                {
                                    seatingPlan.editSeatingPlan(seatingPlan, filename);
                                }
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
                } // Implement teacher's functionality
                else if (userType == 'S')
                {
                    cout << "Logged in as Student." << endl;
                    int choice;
                    do
                    {
                        cout << "Student logged in. Choose an option:" << endl;
                        cout << "1. Display Seating Plan" << endl;
                        cout << "2. Logout" << endl;
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
            } while (userType != 'E');
            break;
        case 'R':
        case 'r':
            char userRole;
            cout << "Register as (T)eacher or (S)tudent: ";
            cin >> userRole;
            if (userRole == 'T' || userRole == 't')
            {
                registerUser("teacher");
            }
            else if (userRole == 'S' || userRole == 's')
            {
                registerUser("student");
            }
            else
            {
                cout << "Invalid option. Please try again." << endl;
            }
            break;
        case 'E':
        case 'e':
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    } while (choice != 'E' && choice != 'e');

    return 0;
}
