#include "Student.h"

Student::Student() : rollNumber(0), classNumber(0) {}

Student::Student(int roll, int cls) : rollNumber(roll), classNumber(cls) {}

int Student::getRollNumber()
{
    return rollNumber;
}

int Student::getClassNumber()
{
    return classNumber;
}

