#include <iostream>
#include <fstream>
#include <cstring>


struct Patient {
    int id;
    char name[50];
    int age;
    char gender;
    char disease[50];
    char appointment[50];
};


class Hospital {
private:
    static const int MAX_PATIENTS = 100;
    Patient patients[MAX_PATIENTS];
    int numPatients;

public:
    Hospital() : numPatients(0) {}

    void acceptPatientInformation();
    void searchAndDisplayPatient(int patientId);
    void deletePatient(int patientId);
    void showPatientList();
    void saveDataToFile();
    void loadDataFromFile();
};

void Hospital::acceptPatientInformation() {
    if (numPatients < MAX_PATIENTS) {
        std::cout << "Enter patient information:" << std::endl;

        patients[numPatients].id = numPatients + 1;
        std::cout << "ID: " << patients[numPatients].id << std::endl;
        std::cout << "Name: ";
        std::cin.ignore();
        std::cin.getline(patients[numPatients].name, sizeof(patients[numPatients].name));
        std::cout << "Age: ";
        std::cin >> patients[numPatients].age;
        std::cout << "Gender (M/F): ";
        std::cin >> patients[numPatients].gender;
        std::cout << "Disease: ";
        std::cin.ignore();
        std::cin.getline(patients[numPatients].disease, sizeof(patients[numPatients].disease));

        std::cout << "Do you want to schedule an appointment? (Y/N): ";
        char choice;
        std::cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            std::cout << "Enter appointment date and time: ";
            std::cin.ignore();
            std::cin.getline(patients[numPatients].appointment, sizeof(patients[numPatients].appointment));
        } else {

            patients[numPatients].appointment[0] = '\0';
        }

        numPatients++;
        std::cout << "Patient added successfully!" << std::endl;


        saveDataToFile();
    } else {
        std::cout << "Hospital is full, cannot accept more patients." << std::endl;
    }
}


void Hospital::searchAndDisplayPatient(int patientId) {
    for (int i = 0; i < numPatients; ++i) {
        if (patients[i].id == patientId) {
            std::cout << "Patient Information:" << std::endl;
            std::cout << "ID: " << patients[i].id << std::endl;
            std::cout << "Name: " << patients[i].name << std::endl;
            std::cout << "Age: " << patients[i].age << std::endl;
            std::cout << "Gender: " << patients[i].gender << std::endl;
            std::cout << "Disease: " << patients[i].disease << std::endl;
            std::cout << "Appointment: " << patients[i].appointment << std::endl;
            return;
        }
    }
    std::cout << "Patient not found." << std::endl;
}

void Hospital::deletePatient(int patientId) {
    for (int i = 0; i < numPatients; ++i) {
        if (patients[i].id == patientId) {

            for (int j = i; j < numPatients - 1; ++j) {
                patients[j] = patients[j + 1];
            }
            numPatients--;
            std::cout << "Patient deleted successfully!" << std::endl;


            saveDataToFile();
            return;
        }
    }
    std::cout << "Patient not found." << std::endl;
}
void Hospital::showPatientList() {
    if (numPatients > 0) {
        std::cout << "Patient List:" << std::endl;
        for (int i = 0; i < numPatients; ++i) {
            std::cout << "Name: " << patients[i].name <<std::endl
            <<"ID: " << patients[i].id << std::endl
            <<"Gender: "<<patients[i].gender<<std::endl
            <<"Disease: "<<patients[i].disease<<std::endl
            <<"schedule: "<<patients[i].appointment<<std::endl;
        }
    } else {
        std::cout << "No patients in the hospital." << std::endl;
    }
}

void Hospital::saveDataToFile() {
    std::ofstream file("patient_data.txt", std::ios::out|std::ios::app);

    if (file.is_open()) {
        for (int i = 0; i < numPatients; ++i) {
            file << patients[i].id << ","
                 << patients[i].name << ","
                 << patients[i].age << ","
                 << patients[i].gender << ","
                 << patients[i].disease <<","
                 << patients[i].appointment<<std::endl;
        }


        std::cout << "Data saved to file." << std::endl;
    } else {
        std::cout << "Error opening file for writing." << std::endl;
    }
    file.close();
}

void Hospital::loadDataFromFile() {
    std::ifstream file("patient_data.txt", std::ios::in);

    if (file.is_open()) {
        while (!file.eof()) {
            file >> patients[numPatients].id;
            file.ignore();
            file.getline(patients[numPatients].name, sizeof(patients[numPatients].name), ',');
            file >> patients[numPatients].age;
            file.ignore();
            file >> patients[numPatients].gender;
            file.ignore();
            file.getline(patients[numPatients].disease, sizeof(patients[numPatients].disease));
            file.ignore();
            file.getline(patients[numPatients].appointment, sizeof(patients[numPatients].appointment));

            if (file.eof()) {
                break;
            }

            numPatients++;
        }

        file.close();
        std::cout << "Data loaded from file." << std::endl;
    } else {
        std::cout << "No existing data file found. Starting with an empty hospital." << std::endl;
    }
}

int main() {
    Hospital hospital;
    hospital.loadDataFromFile();

    int choice, patientId;

    do {
        std::cout << "\nHospital Management System" << std::endl;
        std::cout << "1. Accept Patient Information" << std::endl;
        std::cout << "2. Search and Display Patient" << std::endl;
        std::cout << "3. Delete Patient" << std::endl;
        std::cout << "4. Show Patient List" << std::endl;

        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                hospital.acceptPatientInformation();
                break;
            case 2:
                std::cout << "Enter patient ID to search: ";
                std::cin >> patientId;
                hospital.searchAndDisplayPatient(patientId);
                break;
            case 3:
                std::cout << "Enter patient ID to delete: ";
                std::cin >> patientId;
                hospital.deletePatient(patientId);
                break;
            case 4:
                hospital.showPatientList();
                break;
            case 5:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != 5);

    return 0;
}
