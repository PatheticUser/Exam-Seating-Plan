#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student
{
public:
    string username;
    string password;
    int rollNumber;
    int classNumber;

    Student();
    Student(int roll, int cls);

    int getRollNumber();
    int getClassNumber();
};

#endif // STUDENT_H

