/************************************************************
* FINAL PROJECT CSC-240-200: Hotel Booking System.          *
* Allows user to book a room in my hotel. There are various *
* room types the user can choose from, with various rates,  *
* and even a senior discount if the guest applies.          *
* - Ahmad Zaidan.                                           *
* **********************************************************/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "operations.h"

int main()
{

    /*********************************************
    * Setting up program before user input       *
    * Declaring arrays to represent room options *
    * Declaring corresponding files              *
    * ********************************************/

     //10 floors, 102 rooms total
    Room standardOneBed[36];    //3 floors, 12 rooms each
    std::ifstream sobFile;
    sobFile.open("StandardOneBed.txt");

    Room standardTwoBed[30];    //3 floors, 10 rooms each
    std::ifstream stbFile;
    stbFile.open("StandardTwoBed.txt");

    Room luxuryOneBed[20];      //2 floors, 10 rooms each
    std::ifstream lobFile;
    lobFile.open("LuxuryOneBed.txt");

    Room luxuryTwoBed[16];      //2 floors, 8 rooms each
    std::ifstream ltbFile;
    ltbFile.open("LuxuryTwoBed.txt");


    if (sobFile.fail() || stbFile.fail() || lobFile.fail() || ltbFile.fail()) {
        std::cout << "File failure \n";
        sobFile.close();
        stbFile.close();
        lobFile.close();
        ltbFile.close();
        return 1;
    }

    //Filling rooms with relevant data before user input
    fillArray(standardOneBed, 36, sobFile);
    fillArray(standardTwoBed, 30, stbFile);
    fillArray(luxuryOneBed, 20, lobFile);
    fillArray(luxuryTwoBed, 16, ltbFile);

    sobFile.close();
    stbFile.close();
    lobFile.close();
    ltbFile.close();

    std::ofstream sobFileUpdate;
    sobFileUpdate.open("StandardOneBedUpdate.txt");

    std::ofstream stbFileUpdate;
    stbFileUpdate.open("StandardTwoBedUpdate.txt");

    std::ofstream lobFileUpdate;
    lobFileUpdate.open("LuxuryOneBedUpdate.txt");

    std::ofstream ltbFileUpdate;
    ltbFileUpdate.open("LuxuryTwoBedUpdate.txt");

    if (sobFileUpdate.fail() || stbFileUpdate.fail() || lobFileUpdate.fail() || ltbFileUpdate.fail()) {
        std::cout << "File failure \n";
        sobFileUpdate.close();
        stbFileUpdate.close();
        lobFileUpdate.close();
        ltbFileUpdate.close();
        return 1;
    }

    /*******************************************
    * User input section:                      *
    * Opening menu, getting guest information. *
    * ******************************************/

    int roomChoice = 0;
    roomChoice = roomMenu();

    /*****************************************
    * Preparing data for booking operations. *
    * ****************************************/

    //Making sure there are available rooms for each type.
    int availableRoom = -1;    //used later on in booking operations
    switch (roomChoice) {
        case STANDARD_ONE_BED:
            availableRoom = searchAvailableRoom(standardOneBed, 36);
            break;
        case STANDARD_TWO_BED:
            availableRoom = searchAvailableRoom(standardTwoBed, 30);
            break;
        case LUXURY_ONE_BED:
            availableRoom = searchAvailableRoom(luxuryOneBed, 20);
            break;
        case LUXURY_TWO_BED:
            availableRoom = searchAvailableRoom(luxuryTwoBed, 16);
            break;
        default:
            break;
    }

    Room newBooking;
    if ((availableRoom == -1)) {
        std::cout << "Sorry, but those rooms are all occupied";
        sobFileUpdate.close();
        stbFileUpdate.close();
        lobFileUpdate.close();
        ltbFileUpdate.close();
        return 1;
    }
    else {    //If there are available rooms, the program continues
        newBooking.guest.firstName = askGuestFirstName();
        newBooking.guest.lastName = askGuestLastName();
        newBooking.guest.phoneNumber = askGuestPhoneNum();
        newBooking.daysStay = askGuestStay();
        newBooking.guest.age = askGuestAge();    //for booking eligibility and possible senior discount
    }
    

    //Checking to make sure guest is eligible for service
    if (newBooking.guest.age < 18) {
        std::cout << "Sorry, but we cannot help you book a room. Have a nice day.";
        sobFileUpdate.close();
        stbFileUpdate.close();
        lobFileUpdate.close();
        ltbFileUpdate.close();
        return 1;
    }

    /*********************************************
    * Booking operations; using case switches to *
    * perform the booking option of the program  *
    * depending on previous user input.          *
    * ********************************************/

    double standardRate = 0;
    switch (roomChoice) {
        case STANDARD_ONE_BED:
            standardRate = selectRateSOB(newBooking.daysStay);
            newBooking.roomPrice = standardRate * newBooking.daysStay;
            seniorDiscount(newBooking.roomPrice, newBooking.guest.age);    //checks if age qualifies for senior discount. If so, then room price is adjusted
            roundToHundreths(newBooking.roomPrice);
            bookRoom(standardOneBed, availableRoom, newBooking);
            printReceipt(standardOneBed, availableRoom);
            break;
        case STANDARD_TWO_BED:
            standardRate = selectRateSTB(newBooking.daysStay);
            newBooking.roomPrice = standardRate * newBooking.daysStay;
            seniorDiscount(newBooking.roomPrice, newBooking.guest.age);    //checks if age qualifies for senior discount. If so, then room price is adjusted
            roundToHundreths(newBooking.roomPrice);
            bookRoom(standardTwoBed, availableRoom, newBooking);
            printReceipt(standardTwoBed, availableRoom);
            break;
        case LUXURY_ONE_BED:
            standardRate = selectRateLOB(newBooking.daysStay);
            newBooking.roomPrice = standardRate * newBooking.daysStay;
            seniorDiscount(newBooking.roomPrice, newBooking.guest.age);    //checks if age qualifies for senior discount. If so, then room price is adjusted
            roundToHundreths(newBooking.roomPrice);
            bookRoom(luxuryOneBed, availableRoom, newBooking);
            printReceipt(luxuryOneBed, availableRoom);
            break;
        case LUXURY_TWO_BED:
            standardRate = selectRateLTB(newBooking.daysStay);
            newBooking.roomPrice = standardRate * newBooking.daysStay;
            seniorDiscount(newBooking.roomPrice, newBooking.guest.age);    //checks if age qualifies for senior discount. If so, then room price is adjusted
            roundToHundreths(newBooking.roomPrice);
            bookRoom(luxuryTwoBed, availableRoom, newBooking);
            printReceipt(luxuryTwoBed, availableRoom);
            break;
        default:
            break;
    }
    
    //outputting altered data to data files
    outputFile(standardOneBed, 36, sobFileUpdate);
    outputFile(standardTwoBed, 30, stbFileUpdate);
    outputFile(luxuryOneBed, 20, lobFileUpdate);
    outputFile(luxuryTwoBed, 16, ltbFileUpdate);

    //Closing files before exiting program
    sobFileUpdate.close();
    stbFileUpdate.close();
    lobFileUpdate.close();
    ltbFileUpdate.close();

    return 0;
}
