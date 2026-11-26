#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

struct Person {
    std::string firstName = "None";
    std::string lastName = "None";
    std::string phoneNumber = "None";
    int age = 0;
};

struct Room {
    int roomNumber = 0;
    bool isAvailable = true;
    Person guest;
    int daysStay = 0;
    double roomPrice = 0;
};

enum roomMenuChoice { STANDARD_ONE_BED = 1, STANDARD_TWO_BED, LUXURY_ONE_BED, LUXURY_TWO_BED };

void fillArray(Room roomType[], int arraySize, std::ifstream& file);

void outputFile(Room roomType[], int arraySize, std::ofstream& file);

//int welcomeMenu();

int roomMenu();

std::string askGuestFirstName();

std::string askGuestLastName();

std::string askGuestPhoneNum();

int askGuestStay();

int askGuestAge();

double selectRateSOB(int daysStay);

double selectRateSTB(int daysStay);

double selectRateLOB(int daysStay);

double selectRateLTB(int daysStay);

void seniorDiscount(double& price, int age);

void roundToHundreths(double& price);

int searchAvailableRoom(Room roomType[], int arraySize);

void bookRoom(Room roomType[], int roomIndex, Room booking);

void printReceipt(Room roomType[], int roomIndex);

#endif
