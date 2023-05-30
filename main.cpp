#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

static bool checkIfNumber(string var) { // Checks if given string is a number
    if (var[0] == '0')
        return false;
    for (char c: var) {
        if (!isdigit(c))
            return false;
    }
    return true;
}

class Car {
private:
    string make = "N/A";
    string model = "N/A";
    string colour = "N/A";
    string transmission = "N/A";
    unsigned int weight = 0;
    unsigned int productionYear = 0;
    unsigned int power = 0;
public:

    // Constructor for Car class
    Car(string givenMake, string givenModel, string givenColour,
        string givenTransmission, unsigned int givenWeight, unsigned int givenProductionYear, unsigned int givenPower) {
        this->make = givenMake;
        this->model = givenModel;
        this->colour = givenColour;
        this->transmission = givenTransmission;
        this->weight = givenWeight;
        this->productionYear = givenProductionYear;
        this->power = givenPower;
    }

public:

    // getters and setters
    string getMake() const { return this->make; }

    void setMake(string *givenMake) { this->make = *givenMake; }

    string getModel() const { return this->model; }

    void setModel(string *givenModel) { this->model = *givenModel; }

    string getColour() const { return this->colour; }

    void setColour(string *givenColour) { this->colour = *givenColour; }

    string getTransmission() { return this->transmission; }

    void setTransmission(string *givenTransmission) { this->transmission = *givenTransmission; }

    unsigned int getWeight() const { return this->weight; }

    void setWeight(unsigned int *givenWeight) { this->weight = *givenWeight; }

    unsigned int getProductionYear() const { return this->productionYear; }

    void setProductionYear(unsigned int *givenProductionYear) { this->productionYear = *givenProductionYear; }

    unsigned int getPower() const { return this->power; }

    void setPower(unsigned int *givenPower) { this->power = *givenPower; }


    void printCarInfo(int index) { // Prints information about Car object
        cout << index << ".|\t" << this->make << "\t|\t" << this->model << "\t|\t" << this->productionYear << "\t|\t"
             << this->power << " hp \t|\t" << this->weight << " kg \t|\t" << this->colour << "\t|\t"
             << this->transmission << endl;
    }
};


class CarList {
private:
    vector<Car> listOfCars; // List of Car class objects

public:

    bool printSingleCar(int index) { // Prints information about single Car class object in CarList object
        if (!checkIfNumber(to_string(index)))
            return false;
        if (index - 1 < 0 || index - 1 > this->listOfCars.size())
            return false;
        this->listOfCars.at(index - 1).printCarInfo(index - 1);
        return true;
    }


    void printAllCars() { // Prints information about all Car class objects in CarList object
        for (int i = 0; i < this->listOfCars.size(); i++) {
            listOfCars.at(i).printCarInfo(i + 1);
        }
    }


    void importDataFromFile(string *inputFile) { // Imports Car class objects from .car file
        ifstream file(*inputFile);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                string data[7];
                for (string s: data)
                    s = "";
                int dataArrayIndex = 0;
                for (char c: line) {
                    if (isspace(c)) {
                        dataArrayIndex++;
                    } else {
                        data[dataArrayIndex] += c;
                    }
                }
                bool output;
                output = this->addCarToDatabase(data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
                if (output)
                    cout << "Successfully added car to database {" << data[0] << " " << data[1] << "}" << endl;
                else
                    cout << "Failed to add car to database {" << data[0] << " " << data[1] << "}" << endl;
            }
        }
        file.close();
    }


    void exportDataToFile(string *outputFile) { // Exports Car class objects to a .car file
        ofstream file(*outputFile);
        for (int i = 0; i < this->listOfCars.size(); i++) {
            ostringstream oss;
            oss << this->listOfCars.at(i).getMake() << "\t" << this->listOfCars.at(i).getModel() << "\t"
                << this->listOfCars.at(i).getColour() <<
                "\t" << this->listOfCars.at(i).getTransmission() << "\t" << this->listOfCars.at(i).getWeight() << "\t"
                << this->listOfCars.at(i).getProductionYear() <<
                "\t" << this->listOfCars.at(i).getPower() << "\n";
            if (file.is_open())
                file << oss.str() << endl;
            cout << "Successfully exported {" << this->listOfCars.at(i).getMake() << " "
                 << this->listOfCars.at(i).getModel() << "} data to " << *outputFile << endl;
        }
        file.close();
    }


    bool addCarToDatabase(const string &givenMake, const string &givenModel,
                          const string &givenColour, // Adds Car class object to a listOfCars member in CarList class object
                          const string &givenTransmission, const string &givenWeight, const string &givenProductionYear,
                          const string &givenPower) {
        if (!checkIfNumber(givenWeight)) {
            cout << "Wrong type of data: weight" << endl;
            return false;
        }

        if (!checkIfNumber(givenProductionYear)) {
            cout << "Wrong type of data: production year" << endl;
            return false;
        } else if (stoi(givenProductionYear) > 2023) {
            cout << "Wrong value of data: maximum production date is 2023" << endl;
            return false;
        }

        if (!checkIfNumber(givenPower)) {
            cout << "Wrong type of data: power" << endl;
            return false;
        }
        this->listOfCars.emplace_back(givenMake, givenModel, givenColour, givenTransmission, stoi(givenWeight),
                                      stoi(givenProductionYear), stoi(givenPower));
        return true;
    }


    bool
    deleteCarFromList(int index) { // Deletes chosen Car class object from listOfCars member of CarList class object
        vector<Car> tempList;
        if (!checkIfNumber(to_string(index)))
            return false;
        if (index - 1 < 0 || index - 1 > this->listOfCars.size())
            return false;
        for (int i = 0; i < this->listOfCars.size(); i++) {
            if (i + 1 != index) {
                tempList.push_back(this->listOfCars.at(i));
            }
        }
        this->listOfCars = std::move(tempList);
        return true;
    }


    bool printPowerInRange(int lowerBound,
                           int upperBound) { // Prints information about Car class objects in CarList object which power is in given range
        if (!checkIfNumber(to_string(lowerBound)) || !checkIfNumber(to_string(upperBound)))
            return false;

        if (lowerBound > upperBound)
            return false;

        for (int i = 0; i < this->listOfCars.size(); i++) {
            if (this->listOfCars.at(i).getPower() >= lowerBound && this->listOfCars.at(i).getPower() <= upperBound) {
                this->listOfCars.at(i).printCarInfo(i + 1);
            }
        }
        return true;
    }


    bool printProductionYearInRange(int lowerBound,
                                    int upperBound) { // Prints information about Car class objects in CarList object which production year is in given range
        if (!checkIfNumber(to_string(lowerBound)) || !checkIfNumber(to_string(upperBound)))
            return false;

        if (lowerBound > upperBound)
            return false;

        for (int i = 0; i < this->listOfCars.size(); i++) {
            if (this->listOfCars.at(i).getProductionYear() >= lowerBound &&
                this->listOfCars.at(i).getProductionYear() <= upperBound) {
                this->listOfCars.at(i).printCarInfo(i + 1);
            }
        }
        return true;
    }


    bool printWeightInRange(int lowerBound,
                            int upperBound) { // Prints information about Car class objects in CarList object which weight is in given range
        if (!checkIfNumber(to_string(lowerBound)) || !checkIfNumber(to_string(upperBound)))
            return false;

        if (lowerBound > upperBound)
            return false;

        for (int i = 0; i < this->listOfCars.size(); i++) {
            if (this->listOfCars.at(i).getWeight() >= lowerBound && this->listOfCars.at(i).getWeight() <= upperBound) {
                this->listOfCars.at(i).printCarInfo(i + 1);
            }
        }
        return true;
    }


    void printCarsInColour(
            const string &givenColour) { // Prints information about Car class objects in CarList object which colour is the same as the one given
        for (int i = 0; i < this->listOfCars.size(); i++) {
            if (this->listOfCars.at(i).getColour() == givenColour) {
                this->listOfCars.at(i).printCarInfo(i + 1);
            }
        }
    }


    void printCarsWithTransmissionType(
            const string &givenTransmission) { // Prints information about Car class objects in CarList object which transmission type is the same as the one given
        for (int i = 0; i < this->listOfCars.size(); i++) {
            if (this->listOfCars.at(i).getTransmission() == givenTransmission) {
                this->listOfCars.at(i).printCarInfo(i + 1);
            }
        }
    }

};


void printCarsInterface(CarList *listOfCars) { // Runs interface for choosing printing list option
    bool con = true;
    while (con) {
        cout
                << "\nChoose option:\n1. Print all cars\n2. Print cars filtered by power\n3. Print cars filtered by production year\n"
                   "4. Print cars filtered by transmission type\n5. Print cars filtered by colour\n6. Print cars filtered by weight\n7. Go back"
                << endl;
        char input;
        cin >> input;
        int inputInt = 0;
        if (isdigit(input))
            inputInt = (int) input - 48;
        switch (inputInt) {
            case 1:
                cout << endl;
                listOfCars->printAllCars();
                break;
            case 2: {
                cout << endl;
                string boundInput;
                int lowerBound;
                int upperBound;
                cout << "Provide lower power bound:" << endl;
                cin >> boundInput;
                if (checkIfNumber(boundInput))
                    lowerBound = stoi(boundInput);
                else
                    lowerBound = 0;
                cout << "Provide upper power bound:" << endl;
                cin >> boundInput;
                if (checkIfNumber(boundInput))
                    upperBound = stoi(boundInput);
                else
                    upperBound = 0;
                listOfCars->printPowerInRange(lowerBound, upperBound);
                break;
            }
            case 3: {
                cout << endl;
                string boundInput;
                int lowerBound;
                int upperBound;
                cout << "Provide lower production year bound:" << endl;
                cin >> boundInput;
                if (checkIfNumber(boundInput))
                    lowerBound = stoi(boundInput);
                else
                    lowerBound = 0;
                cout << "Provide upper production year bound:" << endl;
                cin >> boundInput;
                if (checkIfNumber(boundInput))
                    upperBound = stoi(boundInput);
                else
                    upperBound = 0;
                listOfCars->printProductionYearInRange(lowerBound, upperBound);
                break;
            }
            case 4: {
                cout << endl;
                cout << "Provide transmission type filter: " << endl;
                string givenTransmissionType;
                cin >> givenTransmissionType;
                listOfCars->printCarsWithTransmissionType(givenTransmissionType);
                break;
            }
            case 5: {
                cout << endl;
                cout << "Provide colour filter: " << endl;
                string givenColour;
                cin >> givenColour;
                listOfCars->printCarsInColour(givenColour);
                break;
            }
            case 6: {
                cout << endl;
                string boundInput;
                int lowerBound;
                int upperBound;
                cout << "Give lower power bound:" << endl;
                cin >> boundInput;
                if (checkIfNumber(boundInput))
                    lowerBound = stoi(boundInput);
                else
                    lowerBound = 0;
                cout << "Give upper power bound:" << endl;
                cin >> boundInput;
                if (checkIfNumber(boundInput))
                    upperBound = stoi(boundInput);
                else
                    upperBound = 0;
                listOfCars->printWeightInRange(lowerBound, upperBound);
                break;
            }
            case 7:
                con = false;
                break;
            case 0:
                cout << "Invalid data provided" << endl;
                break;
            default:
                break;
        }
    }
}

void addCarInterface(CarList *listOfCars) { // Runs interface for adding car to database
    bool output;
    string carMake;
    cout << "Car make: " << endl;
    cin >> carMake;

    string carModel;
    cout << "Model: " << endl;
    cin >> carModel;

    string carColour;
    cout << "Colour: " << endl;
    cin >> carColour;

    string carTransmission;
    cout << "Transmission type: " << endl;
    cin >> carTransmission;

    string carWeight;
    cout << "Weight: " << endl;
    cin >> carWeight;

    string carPrYear;
    cout << "Production year: " << endl;
    cin >> carPrYear;

    string carPower;
    cout << "Power: " << endl;
    cin >> carPower;

    output = listOfCars->addCarToDatabase(carMake, carModel, carColour, carTransmission, carWeight, carPrYear,
                                          carPower);
    if (output)
        cout << "\nCar added successfully\n" << endl;
    else
        cout << "\nFailed to add car to database\n" << endl;
}

void deleteCarInterface(CarList *listOfCars) { // Runs interface for deleting car from database
    bool output;
    char input;
    int index = 999;
    cout << "Which car would you like to delete? (ID): " << endl;
    cin >> input;
    if (isdigit(input))
        index = (int) input - 48;
    output = listOfCars->deleteCarFromList(index);
    if (output)
        cout << "\nCar deleted successfully\n" << endl;
    else
        cout << "\nFailed to delete car from database\n" << endl;
}

int main() {

    CarList carList;
//    carList.addCarToDatabase("Lancia", "Lybra", "Gray", "Manual", "1400", "2003", "116");
//    carList.addCarToDatabase("Fiat", "Bravo", "Red", "Manual", "1300", "2013", "120");
//    carList.addCarToDatabase("Peugeot", "208", "Black", "Manual", "1050", "2014", "82");
//    carList.addCarToDatabase("BMW", "E38", "Blue", "Auto", "1500", "1999", "200");

    cout << endl;
    cout << "Welcome!" << endl;
    cout << endl;
    cout << endl;
    bool con = true;
    while (con) {
        cout << "\nChoose option:\n1. Add car to database\n2. Delete car from database\n3. Print cars list\n"
                "4. Export to a .car file\n5. Import cars list from a .car file\n6. Close program" << endl;
        char input;
        cin >> input;
        int inputInt = 0;
        if (isdigit(input))
            inputInt = (int) input - 48;
        switch (inputInt) {
            case 1:
                addCarInterface(&carList);
                break;
            case 2:
                deleteCarInterface(&carList);
                break;
            case 3:
                printCarsInterface(&carList);
                break;
            case 4: {
                cout << "\nProvide path for .car file to export data to:";
                string path;
                cin >> path;
                carList.exportDataToFile(&path);
                break;
            }
            case 5: {
                cout << "\nProvide path for .car file to import data from:";
                string path;
                cin >> path;
                cout << (path) << endl;
                carList.importDataFromFile(&path);
                break;
            }
            case 6:
                con = false;
                break;
            case 0:
                cout << "Invalid data provided" << endl;
                break;
            default:
                break;
        }
    }
    return 0;
}
