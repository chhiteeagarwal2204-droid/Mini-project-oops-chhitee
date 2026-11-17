/**
 * ============================================================================
 * @file hospital_system.cpp
 * @brief Hospital Management System - BTech 2nd Year OOP Mini Project
 * @features Inheritance, Polymorphism, Encapsulation, Abstraction, ANSI Colors,
 *           Interactive Menus, Patient/Doctor/Appointment/Billing Management.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
#include <algorithm>

// ==========================================
// ANSI COLOR CODES FOR CONSOLE DESIGN
// ==========================================
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define BG_BLUE "\033[44m"

using namespace std;

// ==========================================
// UTILITY FUNCTIONS FOR UI DESIGN
// ==========================================
void printHeader(const string& title) {
    cout << CYAN << BOLD << "\n========================================================" << RESET << endl;
    cout << BG_BLUE << WHITE << BOLD << "       " << title << "       " << RESET << endl;
    cout << CYAN << BOLD << "========================================================" << RESET << endl;
}

void printSubHeader(const string& subtitle) {
    cout << YELLOW << BOLD << "\n--- " << subtitle << " ---" << RESET << endl;
}

// ==========================================
// 1. ABSTRACTION & ENCAPSULATION: BASE CLASS
// ==========================================
class Person {
protected:
    int id;
    string name;
    int age;
    string gender;

public:
    Person(int id, string name, int age, string gender)
        : id(id), name(name), age(age), gender(gender) {}

    virtual ~Person() {} // Virtual destructor for polymorphism

    // Pure virtual function demonstrating Abstraction
    virtual void displayDetails() const = 0;

    // Getters for Encapsulated data
    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }

    // Setters
    void setName(const string& n) { name = n; }
    void setAge(int a) { age = a; }
    void setGender(const string& g) { gender = g; }
};

// ==========================================
// 2. INHERITANCE: PATIENT CLASS
// ==========================================
class Patient : public Person {
private:
    string disease;
    int roomNumber;
    string admissionDate;
    double billAmount;

public:
    Patient(int id, string name, int age, string gender, string disease, int roomNumber, string admissionDate, double billAmount)
        : Person(id, name, age, gender), disease(disease), roomNumber(roomNumber), admissionDate(admissionDate), billAmount(billAmount) {}

    // Polymorphic override
    void displayDetails() const override {
        cout << GREEN << "| ID: " << setw(4) << id 
             << " | Name: " << setw(15) << name 
             << " | Age: " << setw(3) << age 
             << " | Gender: " << setw(6) << gender 
             << " | Disease: " << setw(12) << disease 
             << " | Room: " << setw(4) << roomNumber 
             << " | Bill: $" << setw(6) << fixed << setprecision(2) << billAmount 
             << " |" << RESET << endl;
    }

    // Patient specific getters & setters
    string getDisease() const { return disease; }
    int getRoomNumber() const { return roomNumber; }
    double getBillAmount() const { return billAmount; }
    void setBillAmount(double amount) { billAmount = amount; }
};

// ==========================================
// 3. INHERITANCE: DOCTOR CLASS
// ==========================================
class Doctor : public Person {
private:
    string specialization;
    double consultationFee;
    int maxPatientsPerDay;

public:
    Doctor(int id, string name, int age, string gender, string specialization, double fee, int maxPatients)
        : Person(id, name, age, gender), specialization(specialization), consultationFee(fee), maxPatientsPerDay(maxPatients) {}

    // Polymorphic override
    void displayDetails() const override {
        cout << MAGENTA << "| ID: " << setw(4) << id 
             << " | Name: " << setw(15) << name 
             << " | Age: " << setw(3) << age 
             << " | Spec: " << setw(15) << specialization 
             << " | Fee: $" << setw(6) << fixed << setprecision(2) << consultationFee 
             << " | Max Patients: " << setw(3) << maxPatientsPerDay 
             << " |" << RESET << endl;
    }

    string getSpecialization() const { return specialization; }
    double getConsultationFee() const { return consultationFee; }
};

// ==========================================
// APPOINTMENT CLASS
// ==========================================
class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string date;
    string timeSlot;

public:
    Appointment(int apptId, int pId, int dId, string dt, string slot)
        : appointmentId(apptId), patientId(pId), doctorId(dId), date(dt), timeSlot(slot) {}

    void displayAppointment() const {
        cout << YELLOW << "| Appt ID: " << setw(3) << appointmentId 
             << " | Patient ID: " << setw(3) << patientId 
             << " | Doctor ID: " << setw(3) << doctorId 
             << " | Date: " << setw(10) << date 
             << " | Slot: " << setw(8) << timeSlot 
             << " |" << RESET << endl;
    }

    int getAppointmentId() const { return appointmentId; }
};

// ==========================================
// HOSPITAL MANAGEMENT SYSTEM CONTROLLER
// ==========================================
class HospitalSystem {
private:
    vector<shared_ptr<Patient>> patients;
    vector<shared_ptr<Doctor>> doctors;
    vector<Appointment> appointments;
    int nextPatientId;
    int nextDoctorId;
    int nextApptId;

public:
    HospitalSystem() : nextPatientId(101), nextDoctorId(201), nextApptId(1) {
        // Preload some default data for demonstration
        doctors.push_back(make_shared<Doctor>(nextDoctorId++, "Dr. Robert Smith", 45, "Male", "Cardiologist", 150.0, 10));
        doctors.push_back(make_shared<Doctor>(nextDoctorId++, "Dr. Sarah Jenkins", 38, "Female", "Pediatrician", 100.0, 12));
        
        patients.push_back(make_shared<Patient>(nextPatientId++, "Alice Johnson", 28, "Female", "Flu", 301, "2026-11-15", 250.0));
        patients.push_back(make_shared<Patient>(nextPatientId++, "Michael Brown", 42, "Male", "Hypertension", 302, "2026-11-16", 400.0));
    }

    // Add Patient Module
    void addPatient() {
        printSubHeader("REGISTER NEW PATIENT");
        string name, gender, disease, date;
        int age, room;
        double bill;

        cout << WHITE << "Enter Patient Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Gender: ";
        cin >> gender;
        cout << "Enter Disease/Diagnosis: ";
        cin.ignore();
        getline(cin, disease);
        cout << "Enter Room Number: ";
        cin >> room;
        cout << "Enter Admission Date (YYYY-MM-DD): ";
        cin >> date;
        cout << "Enter Initial Bill Amount ($): ";
        cin >> bill;

        patients.push_back(make_shared<Patient>(nextPatientId++, name, age, gender, disease, room, date, bill));
        cout << GREEN << "\n[Success] Patient registered successfully! Assigned ID: " << (nextPatientId - 1) << RESET << endl;
    }

    // Add Doctor Module
    void addDoctor() {
        printSubHeader("ADD NEW DOCTOR");
        string name, gender, specialization;
        int age, maxPatients;
        double fee;

        cout << WHITE << "Enter Doctor Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Gender: ";
        cin >> gender;
        cout << "Enter Specialization (e.g., Neurologist): ";
        getline(cin, specialization);
        cout << "Enter Consultation Fee ($): ";
        cin >> fee;
        cout << "Enter Max Patients Per Day: ";
        cin >> maxPatients;

        doctors.push_back(make_shared<Doctor>(nextDoctorId++, name, age, gender, specialization, fee, maxPatients));
        cout << GREEN << "\n[Success] Doctor added successfully! Assigned ID: " << (nextDoctorId - 1) << RESET << endl;
    }

    // Display All Patients (Polymorphism in action)
    void displayAllPatients() const {
        printSubHeader("PATIENT RECORDS DIRECTORY");
        if (patients.empty()) {
            cout << RED << "No patient records found." << RESET << endl;
            return;
        }
        for (const auto& p : patients) {
            p->displayDetails(); // Dynamic dispatch / polymorphic call
        }
    }

    // Display All Doctors (Polymorphism in action)
    void displayAllDoctors() const {
        printSubHeader("DOCTOR DIRECTORY");
        if (doctors.empty()) {
            cout << RED << "No doctor records found." << RESET << endl;
            return;
        }
        for (const auto& d : doctors) {
            d->displayDetails(); // Dynamic dispatch / polymorphic call
        }
    }

    // Schedule Appointment
    void scheduleAppointment() {
        printSubHeader("SCHEDULE APPOINTMENT");
        if (patients.empty() || doctors.empty()) {
            cout << RED << "Error: Need at least one patient and one doctor to schedule an appointment." << RESET << endl;
            return;
        }

        int pId, dId;
        string date, slot;

        displayAllPatients();
        cout << WHITE << "\nEnter Patient ID: ";
        cin >> pId;

        displayAllDoctors();
        cout << WHITE << "Enter Doctor ID: ";
        cin >> dId;

        cout << "Enter Appointment Date (YYYY-MM-DD): ";
        cin >> date;
        cout << "Enter Time Slot (e.g., 10:30AM): ";
        cin >> slot;

        // Verify IDs exist
        auto pIt = find_if(patients.begin(), patients.end(), [pId](const shared_ptr<Patient>& p) { return p->getId() == pId; });
        auto dIt = find_if(doctors.begin(), doctors.end(), [dId](const shared_ptr<Doctor>& d) { return d->getId() == dId; });

        if (pIt != patients.end() && dIt != doctors.end()) {
            appointments.emplace_back(nextApptId++, pId, dId, date, slot);
            cout << GREEN << "\n[Success] Appointment booked successfully! Appt ID: " << (nextApptId - 1) << RESET << endl;
        } else {
            cout << RED << "\n[Error] Invalid Patient ID or Doctor ID entered." << RESET << endl;
        }
    }

    // View Appointments
    void displayAppointments() const {
        printSubHeader("SCHEDULED APPOINTMENTS");
        if (appointments.empty()) {
            cout << YELLOW << "No appointments currently scheduled." << RESET << endl;
            return;
        }
        for (const auto& appt : appointments) {
            appt.displayAppointment();
        }
    }

    // Billing Management
    void processBilling() {
        printSubHeader("PATIENT BILLING & DISCHARGE");
        if (patients.empty()) {
            cout << RED << "No patients available for billing." << RESET << endl;
            return;
        }

        int pId;
        displayAllPatients();
        cout << WHITE << "\nEnter Patient ID for billing/discharge: ";
        cin >> pId;

        auto pIt = find_if(patients.begin(), patients.end(), [pId](const shared_ptr<Patient>& p) { return p->getId() == pId; });

        if (pIt != patients.end()) {
            cout << CYAN << "Current Outstanding Bill for " << (*pIt)->getName() << ": $" << (*pIt)->getBillAmount() << RESET << endl;
            cout << "1. Add charges\n2. Clear bill & Discharge patient\nChoose option: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                double addAmount;
                cout << "Enter additional charges to add ($): ";
                cin >> addAmount;
                double newTotal = (*pIt)->getBillAmount() + addAmount;
                (*pIt)->setBillAmount(newTotal);
                cout << GREEN << "[Success] Updated Bill Amount: $" << newTotal << RESET << endl;
            } else if (choice == 2) {
                cout << GREEN << "[Discharged] Patient " << (*pIt)->getName() << " has been discharged successfully." << RESET << endl;
                patients.erase(pIt);
            } else {
                cout << RED << "Invalid choice." << RESET << endl;
            }
        } else {
            cout << RED << "[Error] Patient ID not found." << RESET << endl;
        }
    }
};

// ==========================================
// MAIN FUNCTION & INTERACTIVE CONSOLE LOOP
// ==========================================
int main() {
    HospitalSystem hms;
    int choice = 0;

    while (choice != 8) {
        printHeader("HOSPITAL MANAGEMENT SYSTEM (OPD & IPD)");
        cout << BLUE << "1. " << WHITE << "Register New Patient" << endl;
        cout << BLUE << "2. " << WHITE << "Add New Doctor" << endl;
        cout << BLUE << "3. " << WHITE << "View All Patients" << endl;
        cout << BLUE << "4. " << WHITE << "View All Doctors" << endl;
        cout << BLUE << "5. " << WHITE << "Schedule Appointment" << endl;
        cout << BLUE << "6. " << WHITE << "View All Appointments" << endl;
        cout << BLUE << "7. " << WHITE << "Manage Billing & Discharge" << endl;
        cout << RED  << "8. " << WHITE << "Exit System" << endl;
        cout << CYAN << "========================================================" << RESET << endl;
        cout << YELLOW << "Enter your choice (1-8): " << RESET;
        
        if (!(cin >> choice)) {
            cout << RED << "\n[Error] Invalid input. Please enter a number between 1 and 8." << RESET << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                hms.addPatient();
                break;
            case 2:
                hms.addDoctor();
                break;
            case 3:
                hms.displayAllPatients();
                break;
            case 4:
                hms.displayAllDoctors();
                break;
            case 5:
                hms.scheduleAppointment();
                break;
            case 6:
                hms.displayAppointments();
                break;
            case 7:
                hms.processBilling();
                break;
            case 8:
                cout << GREEN << "\nThank you for using Hospital Management System. Exiting program...\n" << RESET << endl;
                break;
            default:
                cout << RED << "\n[Error] Invalid choice! Please select between 1 and 8." << RESET << endl;
        }

        if (choice != 8) {
            cout << "\nPress Enter to return to the main menu...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}