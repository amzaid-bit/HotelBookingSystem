#include "operations.h"

void fillArray(Room roomType[], int arraySize, std::ifstream& file) {
    for (int i = 0; i < arraySize; ++i) {
        file >> roomType[i].roomNumber;
        file >> roomType[i].isAvailable;
        file >> roomType[i].guest.firstName;
        file >> roomType[i].guest.lastName;
        file >> roomType[i].guest.phoneNumber;
        file >> roomType[i].daysStay;
        file >> roomType[i].roomPrice;
    }
}

void outputFile(Room roomType[], int arraySize, std::ofstream& file) {
    for (int i = 0; i < arraySize; ++i) {
        file << roomType[i].roomNumber << " ";
        file << roomType[i].isAvailable << " ";
        file << roomType[i].guest.firstName << " ";
        file << roomType[i].guest.lastName << " ";
        file << roomType[i].guest.phoneNumber << " ";
        file << roomType[i].daysStay << " ";
        file << roomType[i].roomPrice << "\n";
    }
}

int roomMenu() {
    int roomChoice = 0;

    std::cout << "Welcome to the Zaidan Inn!\n\n";
    std::cout << "Standard rooms include a bathroom with a toilet and shower. \nGuests are welcome to enjoy a continental breakfast in the hotel's cafeteria.\n\n";
    std::cout << "Luxury rooms are more spacious, include a whirlpool tub in the bathroom, and have a greater view. \nGuests have access to the hotel spa, fine dining options, and room service.\n\n";
    std::cout << "Which room would you like to book?\n";
    std::cout << "1) Standard room with one bed.\n";
    std::cout << "   Rooms 101-312; $99.99 for 1-3 days / \n   $94.99 for 4-7 days / $89.99 for 8-14 days.\n\n";
    std::cout << "2) Standard room with two beds.\n";
    std::cout << "   Rooms 401-610; $129.99 for 1-3 days / \n   $124.99 for 4-7 days / $119.99 for 8-14 days.\n\n";
    std::cout << "3) Luxury room with one bed.\n";
    std::cout << "   Rooms 701-810; $149.99 for 1-3 days / \n   $144.99 for 4-7 days / $139.99 for 8-14 days.\n\n";
    std::cout << "4) Luxury room with two beds.\n";
    std::cout << "   Rooms 901-1008; $179.99 for 1-3 days / \n   $174.99 for 4-7 days / $169.99 for 8-14 days.\n\n";
    std::cout << "Your choice: ";
    std::cin >> roomChoice;
    std::cout << "\n";
    return roomChoice;
}

std::string askGuestFirstName() {
    std::string guestFirst = "None";

    std::cout << "Please enter your first name: ";
    std::cin >> guestFirst;

    return guestFirst;
}

std::string askGuestLastName() {
    std::string guestLast = "None";

    std::cout << "Please enter your last name: ";
    std::cin >> guestLast;

    return guestLast;
}

std::string askGuestPhoneNum() {
    std::string guestPhone = "None";

    std::cout << "Please enter your phone number (format: 000-000-0000): ";
    std::cin >> guestPhone;

    return guestPhone;
}

int askGuestStay() {
    int guestStay = 0;

    std::cout << "How many days do you intend to stay?: ";
    std::cin >> guestStay;
    while ((guestStay < 1) || (guestStay > 14)) {
        std::cout << "Sorry, we only allow for stays from 1-14 days. \nPlease enter how many days you intend to stay: ";
        std::cin >> guestStay;
    }

    return guestStay;
}

int askGuestAge() {
    int guestAge = 0;

    std::cout << "How old are you?: ";
    std::cin >> guestAge;

    return guestAge;
}

void seniorDiscount(double& price, int age) {
    if (age < 65) {
        return;
    }
    else {
        std::cout << "You apply for the senior discount!\n";
        price = price - (price * .05);
        return;
    }
}

void roundToHundreths(double& price) {
    price = round(price * 100) / 100;
    return;
}

double selectRateSOB(int daysStay) {
    if (daysStay <= 3) {
        return 99.99;
    }
    else if (daysStay <= 7) {
        return 94.99;
    }
    else {
        return 89.99;
    }
}

double selectRateSTB(int daysStay) {
    if (daysStay <= 3) {
        return 129.99;
    }
    else if (daysStay <= 7) {
        return 124.99;
    }
    else {
        return 119.99;
    }
}

double selectRateLOB(int daysStay) {
    if (daysStay <= 3) {
        return 149.99;
    }
    else if (daysStay <= 7) {
        return 144.99;
    }
    else {
        return 139.99;
    }
}

double selectRateLTB(int daysStay) {
    if (daysStay <= 3) {
        return 179.99;
    }
    else if (daysStay <= 7) {
        return 174.99;
    }
    else {
        return 169.99;
    }
}

int searchAvailableRoom(Room roomType[], int arraySize) {
    int availableRoom = -1;

    for (int i = 0; i < arraySize; ++i) {
        if (roomType[i].isAvailable == false) {
            continue;
        }
        else {
            availableRoom = i;
            break;
        }
    }

    return availableRoom;
}

void bookRoom(Room roomType[], int roomIndex, Room booking) {
    roomType[roomIndex].isAvailable = false;
    roomType[roomIndex].guest.firstName = booking.guest.firstName;
    roomType[roomIndex].guest.lastName = booking.guest.lastName;
    roomType[roomIndex].guest.phoneNumber = booking.guest.phoneNumber;
    roomType[roomIndex].daysStay = booking.daysStay;
    roomType[roomIndex].roomPrice = booking.roomPrice;
}

void printReceipt(Room roomType[], int roomIndex) {
    std::cout << "\n----Receipt----\n";
    std::cout << "Room: " << roomType[roomIndex].roomNumber << "\n";
    std::cout << "Guest: " << roomType[roomIndex].guest.firstName << " " << roomType[roomIndex].guest.lastName << "\n";
    std::cout << "Price of booking for " << roomType[roomIndex].daysStay << std::fixed << std::setprecision(2) << " days: $" << roomType[roomIndex].roomPrice << "\n";
    std::cout << "Enjoy your stay!\n";
}
