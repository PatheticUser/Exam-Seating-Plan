#include "ExamSeatingPlan.h"

// Constructor
ExamSeatingPlan::ExamSeatingPlan(int totalSeats, int totalStudents, int totalClasses)
    : totalSeats(totalSeats), totalStudents(totalStudents), totalClasses(totalClasses)
{
    seatingArrangement = new Student[totalStudents];
}

// Destructor
ExamSeatingPlan::~ExamSeatingPlan()
{
    delete[] seatingArrangement;
}

// Method to save Seating Plan to file
void ExamSeatingPlan::saveToFile(string filename)
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
void ExamSeatingPlan::swapSeats(int seat1, int seat2)
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
void ExamSeatingPlan::changeAssignment(int seatNumber, int newRollNumber)
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
void ExamSeatingPlan::displaySeatingPlanFromFile(string filename)
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
void ExamSeatingPlan::displaySeatingPlan()
{
    cout << "Exam Seating Plan:" << endl;
    for (int i = 0; i < totalStudents; ++i)
    {
        cout << "Seat " << i + 1 << ": Student " << seatingArrangement[i].getRollNumber() << endl;
    }
}

// Method to backup Seating Plan to a new file
// Method to backup seating plan to a new file

int ExamSeatingPlan::getTotalSeats()
{
    return totalSeats;
}

void ExamSeatingPlan::editSeatingPlan(ExamSeatingPlan &seatingPlan, const string &filename)
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
int ExamSeatingPlan::generateRandomSeatingPlan(string filename)
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
int ExamSeatingPlan::generateSequentialSeatingPlan(string filename)
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
int ExamSeatingPlan::generateMixedSeatingPlan(string filename)
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

