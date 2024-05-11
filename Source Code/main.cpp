#include <iostream>
#include "functions.h"
#include "ExamSeatingPlan.h"

using namespace std;

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