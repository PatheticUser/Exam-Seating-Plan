#include "functions.h"

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