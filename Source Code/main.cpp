#include <iostream>
#include <fstream>
#include <ctime>
#include<limits>

using namespace std;

class Teacher
{
private:
    string username;
    string password;

public:
    Teacher(string uname, string pwd) : username(uname), password(pwd) {}
};

class Student
{
public:
    string username;
    string password;
    int rollNumber;
    int classNumber;

    Student() : rollNumber(0), classNumber(0) {}

    Student(int roll, int cls) : rollNumber(roll), classNumber(cls) {}

    int getRollNumber()
    {
        return rollNumber;
    }
    int getClassNumber()
    {
        return classNumber;
    }
};

    void backupToFile()
{
    string originalFilename = "Seating Plan.txt";
    ifstream originalFile(originalFilename);

    if (!originalFile.is_open())
    {
        cout << "Unable to open file '" << originalFilename << "' for reading." << endl;
        return;
    }

    string newFilename;
    cout << "Enter the name of the new file: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, newFilename);

    ofstream backupFile(newFilename);
    if (!backupFile.is_open())
    {
        cout << "Unable to open file '" << newFilename << "' for writing." << endl;
        originalFile.close(); // Close the original file
        return;
    }

    backupFile << originalFile.rdbuf();

    originalFile.close(); // Close the original file
    backupFile.close();

    cout << "Seating Plan backed up to '" << newFilename << "'." << endl;
}

void registerPage()
{
    cout << "-------------------------------------------------" << endl;
    cout << "|            (Registeration Page)                |" << endl;
    cout << "-------------------------------------------------" << endl;
}

void registerUser(string userType)
{
    string name, username, password;
    int age;

    if (userType == "teacher")
    {
        string key;
        do
        {
            cout << "Enter the key for registering as a teacher: ";
            cin >> key;
            if (key != "KEY")
            {
                cout << "Invalid key. Please try again." << endl;
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of the line
            }
        } while (key != "KEY");
    }

    cout << "Registering as a " << userType << "." << endl;

    cout << "Enter Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    getline(cin, name);

    bool validAge = false;
    do
    {
        cout << "Enter Age: ";
        if (!(cin >> age))
        {
            cerr << "Invalid input. Please enter a valid number for age." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (age <= 0 || age >= 100)
        {
            cerr << "Age must be a positive number less than 100." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            validAge = true;
        }
    } while (!validAge);

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
        cout << "Registration Successful." << endl;
    }
}

char login()
{
    char userType;
    string username, password;
    cout << "-------------------------------------------------" << endl;
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
        cout << "Invalid Username or Password. Please try again." << endl;
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
        cout << "Invalid Username or Password. Please try again." << endl;
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

    // Method to save Seating Plan to file
    void saveToFile(string filename)
    {
        // Get current time
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Open file in append mode
        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            // Append Seating Plan with timestamp
            file << "Exam Seating Plan (Generated at "
                 << ltm->tm_hour << ":" << ltm->tm_min << " on "
                 << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << "):" << endl;
            for (int i = 0; i < totalStudents; ++i)
            {
                file << "Seat " << i + 1 << ": Student " << seatingArrangement[i].getRollNumber() << endl;
            }
            file << endl;
            file.close();
            cout << "Seating Plan appended to " << filename << endl;
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

    // Method to display the most recent Seating Plan from the file
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
            cout << "No Seating Plan found." << endl;
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

    // Method to backup Seating Plan to a new file
    // Method to backup seating plan to a new file

    int getTotalSeats()
    {
        return totalSeats;
    }

    void editSeatingPlan(ExamSeatingPlan &seatingPlan, const string &filename)
    {
        cout << "Entering Editing Mode..." << endl;

        // Display the current Seating Plan
        seatingPlan.displaySeatingPlan();

        // Menu for editing options
        int editChoice;
        do
        {
            cout << "\nEditing Options:" << endl;
            cout << "1. Swap Seats" << endl;
            cout << "2. Change Assignment" << endl;
            cout << "3. Exit Editing" << endl;
            bool validChoice = false;
            do
            {
                cout << "Enter your choice: ";
                if (!(cin >> editChoice))
                {
                    cerr << "Invalid input. Please enter a valid integer choice." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else
                {
                    validChoice = true;
                }
            } while (!validChoice);

            switch (editChoice)
            {
            case 1:
            {
                // Swap seats
                int seat1, seat2;
                bool validInput = false;
                do
                {
                    cout << "Enter seat numbers to swap: ";
                    if (!(cin >> seat1 >> seat2))
                    {
                        cerr << "Invalid input. Please enter valid seat numbers." << endl;
                    }
                    else if (seat1 <= 0 || seat2 <= 0)
                    {
                        cerr << "Seat numbers must be positive integers." << endl;
                    }
                    else
                    {
                        validInput = true;
                    }
                } while (!validInput);
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
                bool validInput = false;

                do
                {
                    cout << "Enter seat number and new roll number: ";
                    if (!(cin >> seatNumber >> newRollNumber))
                    {
                        cerr << "Invalid input. Please enter valid seat number and roll number." << endl;
                    }
                    else if (seatNumber <= 0 || newRollNumber <= 0)
                    {
                        cerr << "Seat number and roll number must be positive integers." << endl;
                    }
                    else
                    {
                        validInput = true;
                    }
                } while (!validInput);
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
                cout << "Exiting editing mode..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        } while (editChoice != 3);

        // After editing, display the modified Seating Plan
        cout << "Modified Seating Plan:" << endl;
        seatingPlan.displaySeatingPlan();

        // Ask the user if they want to save the modified Seating Plan
        char saveChoice;
        cout << "Do you want to save the modified Seating Plan? (Y/N): ";
        cin >> saveChoice;

        if (saveChoice == 'Y' || saveChoice == 'y')
        {
            // Save the modified Seating Plan to the same file
            seatingPlan.saveToFile(filename);
            cout << "Modified Seating Plan saved successfully." << endl;
        }
        else
        {
            cout << "Modified Seating Plan not saved." << endl;
        }
    }

    // Method to generate Seating Plan with random arrangement
    int generateRandomSeatingPlan(string filename)
    {
        int choice, editChoice;
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

            // Display generated Seating Plan
            displaySeatingPlan();

            // Save Seating Plan to file
            saveToFile(filename);

            cout << "Do you want to edit this Seating Plan? (1: Yes, 0: No) ";
            bool validChoice = false;
            do
            {
                cout << "Enter your choice: ";
                if (!(cin >> editChoice))
                {
                    cerr << "Invalid input. Please enter a valid integer choice." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else
                {
                    validChoice = true;
                }
            } while (!validChoice);

            if (editChoice == 1)
            {
                editSeatingPlan(*this, filename); // Edit the Seating Plan
            }

            cout << "Do you want to generate another Random Seating Plan? (1: Yes, 0: No): ";
            cin >> choice;
        } while (choice != 0);

        return editChoice;
    }

    // Method to generate Seating Plan with sequential arrangement
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

            // Display generated Seating Plan
            displaySeatingPlan();

            // Save Seating Plan to file
            saveToFile(filename);

            cout << "Do you want to edit this Seating Plan? (1: Yes, 0: No) ";
            bool validChoice = false;
            do
            {
                cout << "Enter your choice: ";
                if (!(cin >> editChoice))
                {
                    cerr << "Invalid input. Please enter a valid integer choice." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else
                {
                    validChoice = true;
                }
            } while (!validChoice);

            if (editChoice == 1)
            {
                editSeatingPlan(*this, filename); // Edit the Seating Plan
            }

            cout << "Do you want to generate another Sequential Seating Plan? (1: Yes, 0: No): ";
            cin >> choice;
        } while (choice != 0);
        return editChoice;
    }

    /// Method to generate Seating Plan with Mixed arrangement
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

            // Display generated Seating Plan
            displaySeatingPlan();

            // Save Seating Plan to file
            saveToFile(filename);

            cout << "Do you want to edit this Seating Plan? (1: Yes, 0: No) ";
            bool validChoice = false;
            do
            {
                cout << "Enter your choice: ";
                if (!(cin >> editChoice))
                {
                    cerr << "Invalid input. Please enter a valid integer choice." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else
                {
                    validChoice = true;
                }
            } while (!validChoice);

            if (editChoice == 1)
            {
                editSeatingPlan(*this, filename); // Edit the Seating Plan
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
                        bool validChoice = false;

                        do
                        {
                            cout << "Enter your choice: ";
                            if (!(cin >> choice))
                            {
                                cerr << "Invalid input. Please enter a valid integer choice." << endl;
                            }
                            else
                            {
                                validChoice = true;
                            }
                        } while (!validChoice);

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
                            bool validChoice = false;

                            do
                            {
                                cout << "Enter your choice: ";
                                if (!(cin >> choice))
                                {
                                    cerr << "Invalid input. Please enter a valid integer choice." << endl;
                                }
                                else
                                {
                                    validChoice = true;
                                }
                            } while (!validChoice);

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
                            backupToFile();
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
                        bool validChoice = false;

                        do
                        {
                            cout << "Enter your choice: ";
                            if (!(cin >> choice))
                            {
                                cerr << "Invalid input. Please enter a valid integer choice." << endl;
                            }
                            else
                            {
                                validChoice = true;
                            }
                        } while (!validChoice);

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
