/*In a hospital Emergency Room (ER), patients arrive with different severity levels. The doctor must always treat the most critical patient 
first. You must implement an Emergency Room Scheduler using a Priority Queue implemented with a simple array (no STL allowed).
Each patient has:
Patient ID
Name
Severity Level (Priority)
5 → Critical
4 → Very Serious
3 → Serious
2 → Moderate
1 → Minor
Higher severity means higher priority.
You must implement the following operations:
1.	Add Patient:
Insert a patient into the priority queue.
2.	Treat Patient
Remove and display the patient with highest severity.
3.	Increase Severity
Sometimes a waiting patient becomes more critical. Update the severity of a patient already in the queue.
4.	Display Waiting List
Display all patients in the queue.
5.	Treat All Patients
Simulate treatment until queue becomes empty.
*/
#include <iostream>
using namespace std;

#define MAX 100

class EmergencyRoom {
private:
    int id[6][MAX];
    string name[6][MAX];
    int front[6];
    int rear[6];

public:
    EmergencyRoom() {
        for (int i = 1; i <= 5; i++) {
            front[i] = -1;
            rear[i] = -1;
        }
    }
    void addPatient(int pid, string pname, int severity) {
        if (severity < 1 || severity > 5) {
            cout << "Invalid severity level!" << endl;
            return;
        }

        if (rear[severity] == MAX - 1) {
            cout << "Queue overflow for severity " << severity << endl;
            return;
        }

        if (front[severity] == -1)
            front[severity] = 0;

        rear[severity]++;
        id[severity][rear[severity]] = pid;
        name[severity][rear[severity]] = pname;

        cout << "Patient added successfully." << endl;
    }
    void treatPatient() {
        for (int s = 5; s >= 1; s--) {
            if (front[s] != -1 && front[s] <= rear[s]) {
                cout << endl;
                cout << "Treating Patient: "
                     << name[s][front[s]]
                     << " | ID: " << id[s][front[s]]
                     << " | Severity: " << s << endl;

                front[s]++;

                if (front[s] > rear[s])
                    front[s] = rear[s] = -1;

                return;
            }
        }
        cout << "No patients in queue." << endl;
    }
    void increaseSeverity(int pid, int newSeverity) {
        if (newSeverity < 1 || newSeverity > 5) {
            cout << "Invalid severity level!" << endl;
            return;
        }

        for (int s = 1; s <= 5; s++) {
            if (front[s] == -1) continue;

            for (int i = front[s]; i <= rear[s]; i++) {
                if (id[s][i] == pid) {
                    string pname = name[s][i];

                    for (int j = i; j < rear[s]; j++) {
                        id[s][j] = id[s][j + 1];
                        name[s][j] = name[s][j + 1];
                    }

                    rear[s]--;

                    if (front[s] > rear[s])
                        front[s] = rear[s] = -1;

                    addPatient(pid, pname, newSeverity);

                    cout << "Severity updated successfully." << endl;
                    return;
                }
            }
        }
        cout << "Patient not found." << endl;
    }
    void displayPatients() {
        cout << endl << "--- Waiting Patients ---" << endl;

        bool empty = true;

        for (int s = 5; s >= 1; s--) {
            if (front[s] != -1) {
                empty = false;
                cout << endl << "Severity Level " << s << ":" << endl;

                for (int i = front[s]; i <= rear[s]; i++) {
                    cout << "ID: " << id[s][i]
                         << " | Name: " << name[s][i] << endl;
                }
            }
        }

        if (empty)
            cout << "No patients in queue." << endl;
    }

    void treatAllPatients() {
        cout << endl << "--- Treating All Patients ---" << endl;

        while (true) {
            bool empty = true;

            for (int i = 1; i <= 5; i++) {
                if (front[i] != -1)
                    empty = false;
            }

            if (empty) break;

            treatPatient();
        }

        cout << "All patients treated." << endl;
    }
};

int main() {
    EmergencyRoom er;
    int choice;

    do {
        cout << endl;
        cout << "===== Emergency Room Menu =====" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Treat Patient" << endl;
        cout << "3. Increase Severity" << endl;
        cout << "4. Display Patients" << endl;
        cout << "5. Treat All Patients" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, severity;
            string name;

            cout << "Enter Patient ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Severity (1-5): ";
            cin >> severity;

            er.addPatient(id, name, severity);
        }

        else if (choice == 2) {
            er.treatPatient();
        }

        else if (choice == 3) {
            int id, newSeverity;
            cout << "Enter Patient ID: ";
            cin >> id;
            cout << "Enter New Severity: ";
            cin >> newSeverity;

            er.increaseSeverity(id, newSeverity);
        }

        else if (choice == 4) {
            er.displayPatients();
        }

        else if (choice == 5) {
            er.treatAllPatients();
        }

    } while (choice != 0);

    return 0;
}