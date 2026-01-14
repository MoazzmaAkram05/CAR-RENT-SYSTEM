#include <iostream>
#include <string>
using namespace std;

struct Driver {
	int id;
	string name;
	string phone;
	string cnic;
	int experience;
	int dailyProfit = 0; // Profit for each driver
};

struct User {
	int id;
	string name;
	int age;
	string phone;
};

// Max 10 drivers
Driver drivers[10];
int driverCount = 0;

User users[10];
int userCount = 0;

// Cars
string carNames[10] = { "Toyota", "Suzuki", "Mercedes", "Honda", "BMW", "Audi", "Kia", "MG", "Prado", "Alto" };
int carRates[10] = { 400, 300, 5000, 350, 6000, 5500, 320, 370, 800, 200 };

// Function declarations
void managerMenu();
void userMenu();
void addDriver();
void removeDriver();
void viewDriver();
void checkProfit();
void reportDamage();

int main() {
	int mainChoice;
	string username, password;

	do {
		cout << "\n===== MAIN MENU =====\n";
		cout << "1. Manager Login\n2. User\n3. Exit\nChoice: ";
		cin >> mainChoice;

		switch (mainChoice) {
		case 1:
			cout << "\nUsername: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;

			if (username == "manager" && password == "123") {
				cout << "\nLogin Successful!\n";
				managerMenu();
			}
			else {
				cout << "\nInvalid credentials!\n";
			}
			break;

		case 2:
			userMenu();
			break;

		case 3:
			cout << "\nExiting program...\n";
			break;

		default:
			cout << "\nInvalid Choice!\n";
		}

	} while (mainChoice != 3);

	return 0;
}

// ================== MANAGER MENU ==================
void managerMenu() {
	int choice, driverID;
	do {
		cout << "\n===== MANAGER MENU =====\n";
		cout << "1. Add Driver\n2. Remove Driver\n3. View Driver\n4. Check Profit\n5. Logout\n6. Report Damage\nChoice: ";
		cin >> choice;

		switch (choice) {
		case 1: addDriver(); break;
		case 2: removeDriver(); break;
		case 3: viewDriver(); break;
		case 4: checkProfit(); break;
		case 5: cout << "\nLogging out...\n"; break;
		case 6: reportDamage(); break;
		default: cout << "\nInvalid Choice!\n";
		}

	} while (choice != 5);
}

void addDriver() {
	if (driverCount >= 10) {
		cout << "\nDriver list full!\n";
		return;
	}
	Driver d;
	cout << "\nEnter ID: "; cin >> d.id;
	cin.ignore(); // To ignore newline
	cout << "Name: "; getline(cin, d.name);
	cout << "Phone (11 digits): "; getline(cin, d.phone);
	cout << "CNIC (13 digits): "; getline(cin, d.cnic);
	cout << "Experience (years): "; cin >> d.experience;

	d.dailyProfit = 0;
	drivers[driverCount++] = d;

	cout << "\nDriver Registered Successfully!\n";
}

void removeDriver() {
	int id, found = -1;
	cout << "\nEnter ID to remove: ";
	cin >> id;

	for (int i = 0; i < driverCount; i++) {
		if (drivers[i].id == id) {
			found = i;
			break;
		}
	}

	if (found != -1) {
		for (int i = found; i < driverCount - 1; i++)
			drivers[i] = drivers[i + 1];
		driverCount--;
		cout << "\nDriver removed!\n";
	}
	else {
		cout << "\nDriver not found!\n";
	}
}

void viewDriver() {
	int id, found = -1;
	cout << "\nEnter Driver ID: ";
	cin >> id;

	for (int i = 0; i < driverCount; i++) {
		if (drivers[i].id == id) {
			found = i;
			break;
		}
	}

	if (found != -1) {
		Driver d = drivers[found];
		cout << "\nID: " << d.id << "\nName: " << d.name
			<< "\nPhone: " << d.phone << "\nCNIC: " << d.cnic
			<< "\nExperience: " << d.experience
			<< "\nDaily Profit: " << d.dailyProfit << endl;
	}
	else {
		cout << "\nDriver not found!\n";
	}
}

void checkProfit() {
	int id, found = -1;
	cout << "\nEnter Driver ID: ";
	cin >> id;

	for (int i = 0; i < driverCount; i++) {
		if (drivers[i].id == id) {
			found = i;
			break;
		}
	}

	if (found != -1) {
		cout << "\nDriver ID: " << drivers[found].id
			<< " Profit: " << drivers[found].dailyProfit << endl;
	}
	else {
		cout << "\nDriver not found!\n";
	}
}

void reportDamage() {
	int id, found = -1, damage;
	cout << "\nEnter Driver ID: ";
	cin >> id;

	for (int i = 0; i < driverCount; i++) {
		if (drivers[i].id == id) {
			found = i;
			break;
		}
	}

	if (found != -1) {
		cout << "Enter Damage Cost: ";
		cin >> damage;
		drivers[found].dailyProfit -= damage;
		cout << "\nDamage reported!\n";
	}
	else {
		cout << "\nDriver not found!\n";
	}
}

// ================== USER MENU ==================
void userMenu() {
	int carChoice, km;
	cout << "\n===== CAR MENU =====\n";
	for (int i = 0; i < 10; i++)
		cout << i + 1 << ". " << carNames[i] << " (" << carRates[i] << "/km)\n";

	cout << "Choice: ";
	cin >> carChoice;

	if (carChoice < 1 || carChoice > 10) {
		cout << "\nInvalid car choice!\n";
		return;
	}

	cout << "Enter Kilometers: ";
	cin >> km;

	int totalBill = carRates[carChoice - 1] * km;
	cout << "\nTotal Bill: " << totalBill << endl;

	// Assign driver (simple logic: first driver in list)
	if (driverCount > 0) {
		drivers[0].dailyProfit += totalBill;
		cout << "Driver " << drivers[0].name << " assigned.\n";
	}
	else {
		cout << "No driver available!\n";
	}

	// User Registration
	User u;
	u.id = userCount + 1;
	cin.ignore();
	cout << "\n===== USER REGISTRATION =====\n";
	cout << "Name: "; getline(cin, u.name);
	cout << "Age: "; cin >> u.age;
	cin.ignore();
	cout << "Phone (11 digits): "; getline(cin, u.phone);

	users[userCount++] = u;

	cout << "\n===== USER CARD =====\n";
	cout << "ID: " << u.id << "\nName: " << u.name
		<< "\nAge: " << u.age
		<< "\nPhone: " << u.phone << "\n=====================\n";
}