#ifndef EXAMSEATINGPLAN_H
#define EXAMSEATINGPLAN_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Student.h"

using namespace std;

class ExamSeatingPlan
{
private:
    int totalSeats;
    int totalStudents;
    int totalClasses;
    Student *seatingArrangement;

public:
    // Constructor
    ExamSeatingPlan(int totalSeats, int totalStudents, int totalClasses);

    // Destructor
    ~ExamSeatingPlan();

    // Method to save Seating Plan to file
    void saveToFile(string filename);

    // Method to swap seats
    void swapSeats(int seat1, int seat2);

    // Method to change assignment
    void changeAssignment(int seatNumber, int newRollNumber);

    // Method to display the most recent Seating Plan from the file
    void displaySeatingPlanFromFile(string filename);

    // Method to display the seating arrangement
    void displaySeatingPlan();

    // Method to backup Seating Plan to a new file

    int getTotalSeats();

    void editSeatingPlan(ExamSeatingPlan &seatingPlan, const string &filename);

    // Method to generate Seating Plan with random arrangement
    int generateRandomSeatingPlan(string filename);

    // Method to generate Seating Plan with sequential arrangement
    int generateSequentialSeatingPlan(string filename);

    // Method to generate Seating Plan with Mixed arrangement
    int generateMixedSeatingPlan(string filename);
};

#endif // EXAMSEATINGPLAN_H
