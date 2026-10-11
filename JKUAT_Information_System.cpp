#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

struct Student {
    string id, name, password;
    vector<string> units;
};

struct Lecturer {
    string id, name, password;
    vector<string> units;
};

struct Staff {
    string id, name, password;
};

struct Unit {
    string code, name, lecturerId;
};

struct MarkRecord {
    string studentId, unitCode;
    int assignment, cat, exam;
};

struct Note {
    string unitCode, title, content;
};

struct Assignment {
    string unitCode, title, description;
};

struct CAT {
    string unitCode, title, date, description;
};

vector<Student> students;
vector<Lecturer> lecturers;
vector<Staff> staffMembers;
vector<Unit> units;
vector<MarkRecord> marks;
vector<Note> notes;
vector<Assignment> assignments;
vector<CAT> cats;

// ---------- General helper functions ----------

string trim(const string &text) {
    size_t first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

string readLine(const string &prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return trim(value);
}

int readInt(const string &prompt, int minimum, int maximum) {
    while (true) {
        cout << prompt;
        int value;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= minimum && value <= maximum) return value;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Invalid input. Enter a number from "
             << minimum << " to " << maximum << ".\n";
    }
}

vector<string> split(const string &line, char delimiter) {
    vector<string> parts;
    string part;
    stringstream stream(line);

    while (getline(stream, part, delimiter)) {
        parts.push_back(part);
    }
    return parts;
}

string join(const vector<string> &items, char delimiter) {
    string result;
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) result += delimiter;
        result += items[i];
    }
    return result;
}

bool contains(const vector<string> &items, const string &value) {
    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i] == value) return true;
    }
    return false;
}

int findStudent(const string &id) {
    for (size_t i = 0; i < students.size(); ++i)
        if (students[i].id == id) return static_cast<int>(i);
    return -1;
}

int findLecturer(const string &id) {
    for (size_t i = 0; i < lecturers.size(); ++i)
        if (lecturers[i].id == id) return static_cast<int>(i);
    return -1;
}

int findStaff(const string &id) {
    for (size_t i = 0; i < staffMembers.size(); ++i)
        if (staffMembers[i].id == id) return static_cast<int>(i);
    return -1;
}

int findUnit(const string &code) {
    for (size_t i = 0; i < units.size(); ++i)
        if (units[i].code == code) return static_cast<int>(i);
    return -1;
}

int findMark(const string &studentId, const string &unitCode) {
    for (size_t i = 0; i < marks.size(); ++i)
        if (marks[i].studentId == studentId &&
            marks[i].unitCode == unitCode) return static_cast<int>(i);
    return -1;
}

bool lecturerTeaches(const Lecturer &lecturer, const string &unitCode) {
    return contains(lecturer.units, unitCode);
}

bool studentRegistered(const Student &student, const string &unitCode) {
    return contains(student.units, unitCode);
}

bool validTextField(const string &value) {
    return value.find('|') == string::npos;
}

string gradeFor(int total) {
    // Demonstration grading bands; confirm official course rules before use.
    if (total >= 70) return "A";
    if (total >= 60) return "B";
    if (total >= 50) return "C";
    if (total >= 40) return "D";
    return "E";
}

// ---------- File storage ----------

void saveStudents() {
    ofstream file("students.txt");
    for (size_t i = 0; i < students.size(); ++i)
        file << students[i].id << "|" << students[i].name << "|"
             << students[i].password << "|" << join(students[i].units, ',') << "\n";
}

void saveLecturers() {
    ofstream file("lecturers.txt");
    for (size_t i = 0; i < lecturers.size(); ++i)
        file << lecturers[i].id << "|" << lecturers[i].name << "|"
             << lecturers[i].password << "|" << join(lecturers[i].units, ',') << "\n";
}

void saveStaff() {
    ofstream file("staff.txt");
    for (size_t i = 0; i < staffMembers.size(); ++i)
        file << staffMembers[i].id << "|" << staffMembers[i].name << "|"
             << staffMembers[i].password << "\n";
}

void saveUnits() {
    ofstream file("units.txt");
    for (size_t i = 0; i < units.size(); ++i)
        file << units[i].code << "|" << units[i].name << "|"
             << units[i].lecturerId << "\n";
}

void saveMarks() {
    ofstream file("marks.txt");
    for (size_t i = 0; i < marks.size(); ++i)
        file << marks[i].studentId << "|" << marks[i].unitCode << "|"
             << marks[i].assignment << "|" << marks[i].cat << "|"
             << marks[i].exam << "\n";
}

void saveNotes() {
    ofstream file("notes.txt");
    for (size_t i = 0; i < notes.size(); ++i)
        file << notes[i].unitCode << "|" << notes[i].title << "|"
             << notes[i].content << "\n";
}

void saveAssignments() {
    ofstream file("assignments.txt");
    for (size_t i = 0; i < assignments.size(); ++i)
        file << assignments[i].unitCode << "|" << assignments[i].title << "|"
             << assignments[i].description << "\n";
}

void saveCATs() {
    ofstream file("cats.txt");
    for (size_t i = 0; i < cats.size(); ++i)
        file << cats[i].unitCode << "|" << cats[i].title << "|"
             << cats[i].date << "|" << cats[i].description << "\n";
}

void saveAll() {
    saveStudents();
    saveLecturers();
    saveStaff();
    saveUnits();
    saveMarks();
    saveNotes();
    saveAssignments();
    saveCATs();
}

void loadStudents() {
    ifstream file("students.txt");
    string line;
    while (getline(file, line)) {
        vector<string> p = split(line, '|');
        if (p.size() >= 3) {
            Student s;
            s.id = p[0]; s.name = p[1]; s.password = p[2];
            if (p.size() >= 4 && !p[3].empty()) s.units = split(p[3], ',');
            students.push_back(s);
        }
    }
}

void loadLecturers() {
    ifstream file("lecturers.txt");
    string line;
    while (getline(file, line)) {
        vector<string> p = split(line, '|');
        if (p.size() >= 3) {
            Lecturer l;
            l.id = p[0]; l.name = p[1]; l.password = p[2];
            if (p.size() >= 4 && !p[3].empty()) l.units = split(p[3], ',');
            lecturers.push_back(l);
        }
    }
}

void loadStaff() {
    ifstream file("staff.txt");
    string line;
    while (getline(file, line)) {
        vector<string> p = split(line, '|');
        if (p.size() >= 3) {
            Staff s;
            s.id = p[0]; s.name = p[1]; s.password = p[2];
            staffMembers.push_back(s);
        }
    }
}

void loadUnits() {
    ifstream file("units.txt");
    string line;
    while (getline(file, line)) {
        vector<string> p = split(line, '|');
        if (p.size() >= 3) {
            Unit u;
            u.code = p[0]; u.name = p[1]; u.lecturerId = p[2];
            units.push_back(u);
        }
    }
}

void loadMarks() {
    ifstream file("marks.txt");
    string line;
    while (getline(file, line)) {
        vector<string> p = split(line, '|');
        if (p.size() == 5) {
            MarkRecord m;
            m.studentId = p[0]; m.unitCode = p[1];
            try {
                m.assignment = stoi(p[2]);
                m.cat = stoi(p[3]);
                m.exam = stoi(p[4]);
                marks.push_back(m);
            } catch (...) {
                // Skip malformed records instead of stopping the program.
            }
        }
    }
}

void loadNotes() {
    ifstream file("notes.txt");
    string line;
    while (getline(file, line)) {
        vector<string> p = split(line, '|');
        if (p.size() >= 3) {
            Note n; n.unitCode = p[0]; n.title = p[1]; n.content = p[2];
            notes.push_back(n);
        }
    }
}

void loadAssignments() {
    ifstream file("assignments.txt");
    string line;
    while (getline(file, line)) {
        vector<string> p = split(line, '|');
        if (p.size() >= 3) {
            Assignment a; a.unitCode = p[0]; a.title = p[1]; a.description = p[2];
            assignments.push_back(a);
        }
    }
}

void loadCATs() {
    ifstream file("cats.txt");
    string line;
    while (getline(file, line)) {
        vector<string> p = split(line, '|');
        if (p.size() >= 4) {
            CAT c; c.unitCode = p[0]; c.title = p[1];
            c.date = p[2]; c.description = p[3];
            cats.push_back(c);
        }
    }
}

void seedSampleData() {
    // Add demonstration records only when no saved records exist.
    if (students.empty()) {
        Student a; a.id = "ST001"; a.name = "John Kamau"; a.password = "1234";
        students.push_back(a);
        Student b; b.id = "ST002"; b.name = "Mary Wanjiku"; b.password = "1234";
        students.push_back(b);
    }

    if (lecturers.empty()) {
        Lecturer l; l.id = "L001"; l.name = "Dr Mwangi"; l.password = "1234";
        l.units.push_back("CSC210");
        l.units.push_back("SAD220");
        l.units.push_back("NET210");
        lecturers.push_back(l);
    }

    if (staffMembers.empty()) {
        Staff s; s.id = "STAFF001"; s.name = "Jane Njeri"; s.password = "1234";
        staffMembers.push_back(s);
    }

    if (units.empty()) {
        Unit u1; u1.code = "CSC210"; u1.name = "Object Oriented Programming"; u1.lecturerId = "L001";
        Unit u2; u2.code = "SAD220"; u2.name = "Systems Analysis and Design"; u2.lecturerId = "L001";
        Unit u3; u3.code = "NET210"; u3.name = "Computer Networks"; u3.lecturerId = "L001";
        units.push_back(u1); units.push_back(u2); units.push_back(u3);
    }

    saveAll();
}

void loadAll() {
    loadStudents();
    loadLecturers();
    loadStaff();
    loadUnits();
    loadMarks();
    loadNotes();
    loadAssignments();
    loadCATs();
    seedSampleData();
}

// ---------- Shared display functions ----------

void displayAllUnits() {
    cout << "\nAVAILABLE UNIVERSITY UNITS\n";
    if (units.empty()) {
        cout << "No units have been added.\n";
        return;
    }
    for (size_t i = 0; i < units.size(); ++i) {
        cout << units[i].code << " - " << units[i].name
             << " (Lecturer ID: " << units[i].lecturerId << ")\n";
    }
}

void viewStudentUnits(int studentIndex) {
    const Student &student = students[studentIndex];
    cout << "\nREGISTERED UNITS FOR " << student.name << "\n";

    if (student.units.empty()) {
        cout << "You have not registered any units yet.\n";
        return;
    }

    for (size_t i = 0; i < student.units.size(); ++i) {
        int unitIndex = findUnit(student.units[i]);
        if (unitIndex >= 0)
            cout << student.units[i] << " - " << units[unitIndex].name << "\n";
        else
            cout << student.units[i] << "\n";
    }
}

void registerUnit(int studentIndex) {
    displayAllUnits();
    string code = readLine("\nEnter the unit code to register (or 0 to cancel): ");
    if (code == "0") return;

    int unitIndex = findUnit(code);
    if (unitIndex < 0) {
        cout << "That unit code does not exist.\n";
        return;
    }

    if (studentRegistered(students[studentIndex], code)) {
        cout << "You have already registered for this unit.\n";
        return;
    }

    students[studentIndex].units.push_back(code);
    saveStudents();
    cout << "Unit registered successfully. It is now available in your LMS.\n";
}

void viewStudentMarks(int studentIndex) {
    bool found = false;
    cout << "\nYOUR ACADEMIC MARKS\n";

    for (size_t i = 0; i < marks.size(); ++i) {
        if (marks[i].studentId == students[studentIndex].id) {
            found = true;
            int total = marks[i].assignment + marks[i].cat + marks[i].exam;
            cout << "\nUnit: " << marks[i].unitCode << "\n"
                 << "Assignment: " << marks[i].assignment << "/20\n"
                 << "CAT: " << marks[i].cat << "/20\n"
                 << "Exam: " << marks[i].exam << "/60\n"
                 << "Total: " << total << "/100\n"
                 << "Grade: " << gradeFor(total) << "\n";
        }
    }

    if (!found) cout << "No marks have been entered for you yet.\n";
}

bool studentCanSeeUnit(const Student &student, const string &code) {
    return studentRegistered(student, code);
}

void viewStudentNotes(int studentIndex) {
    bool found = false;
    cout << "\nNOTES FOR YOUR REGISTERED UNITS\n";
    for (size_t i = 0; i < notes.size(); ++i) {
        if (studentCanSeeUnit(students[studentIndex], notes[i].unitCode)) {
            found = true;
            cout << "\nUnit: " << notes[i].unitCode << "\nTitle: " << notes[i].title
                 << "\nDetails: " << notes[i].content << "\n";
        }
    }
    if (!found) cout << "No notes are available for your registered units.\n";
}

void viewStudentAssignments(int studentIndex) {
    bool found = false;
    cout << "\nASSIGNMENTS FOR YOUR REGISTERED UNITS\n";
    for (size_t i = 0; i < assignments.size(); ++i) {
        if (studentCanSeeUnit(students[studentIndex], assignments[i].unitCode)) {
            found = true;
            cout << "\nUnit: " << assignments[i].unitCode
                 << "\nTitle: " << assignments[i].title
                 << "\nInstructions: " << assignments[i].description << "\n";
        }
    }
    if (!found) cout << "No assignments are available for your registered units.\n";
}

void viewStudentCATs(int studentIndex) {
    bool found = false;
    cout << "\nCATS FOR YOUR REGISTERED UNITS\n";
    for (size_t i = 0; i < cats.size(); ++i) {
        if (studentCanSeeUnit(students[studentIndex], cats[i].unitCode)) {
            found = true;
            cout << "\nUnit: " << cats[i].unitCode
                 << "\nTitle: " << cats[i].title
                 << "\nDate: " << cats[i].date
                 << "\nDetails: " << cats[i].description << "\n";
        }
    }
    if (!found) cout << "No CATs are available for your registered units.\n";
}

// ---------- Student LMS and portal ----------

void studentLMS(int studentIndex) {
    int choice;
    do {
        cout << "\n========== STUDENT LMS ==========\n"
             << "1. View registered units\n"
             << "2. View notes\n"
             << "3. View assignments\n"
             << "4. View CATs\n"
             << "5. View marks\n"
             << "6. Return to Student Portal\n";

        choice = readInt("Select an option: ", 1, 6);

        switch (choice) {
            case 1: viewStudentUnits(studentIndex); break;
            case 2: viewStudentNotes(studentIndex); break;
            case 3: viewStudentAssignments(studentIndex); break;
            case 4: viewStudentCATs(studentIndex); break;
            case 5: viewStudentMarks(studentIndex); break;
            case 6: cout << "Returning to Student Portal...\n"; break;
        }
    } while (choice != 6);
}

void studentPortal(int studentIndex) {
    int choice;
    do {
        cout << "\n========== STUDENT PORTAL ==========\n"
             << "Welcome, " << students[studentIndex].name << "\n"
             << "1. Register unit\n"
             << "2. View registered units\n"
             << "3. View marks\n"
             << "4. Access LMS\n"
             << "5. Logout\n";

        choice = readInt("Select an option: ", 1, 5);

        switch (choice) {
            case 1: registerUnit(studentIndex); break;
            case 2: viewStudentUnits(studentIndex); break;
            case 3: viewStudentMarks(studentIndex); break;
            case 4: studentLMS(studentIndex); break;
            case 5: cout << "Logging out...\n"; break;
        }
    } while (choice != 5);
}

void studentLogin() {
    cout << "\n========== STUDENT LOGIN ==========\n";
    string id = readLine("Student ID: ");
    string password = readLine("Password: ");

    int index = findStudent(id);
    if (index < 0 || students[index].password != password) {
        cout << "Incorrect student ID or password.\n";
        return;
    }
    studentPortal(index);
}

// ---------- Lecturer functions ----------

void viewLecturerUnits(int lecturerIndex) {
    cout << "\nYOUR ASSIGNED UNITS\n";
    if (lecturers[lecturerIndex].units.empty()) {
        cout << "No units are assigned to you.\n";
        return;
    }

    for (size_t i = 0; i < lecturers[lecturerIndex].units.size(); ++i) {
        string code = lecturers[lecturerIndex].units[i];
        int unitIndex = findUnit(code);
        if (unitIndex >= 0)
            cout << code << " - " << units[unitIndex].name << "\n";
        else
            cout << code << "\n";
    }
}

bool lecturerSelectsUnit(int lecturerIndex, string &code) {
    viewLecturerUnits(lecturerIndex);
    code = readLine("Enter unit code (or 0 to cancel): ");
    if (code == "0") return false;

    if (!lecturerTeaches(lecturers[lecturerIndex], code)) {
        cout << "You are not assigned to that unit.\n";
        return false;
    }
    return true;
}

void addNote(int lecturerIndex) {
    string code;
    if (!lecturerSelectsUnit(lecturerIndex, code)) return;

    Note n;
    n.unitCode = code;
    n.title = readLine("Note title: ");
    n.content = readLine("Note content or file reference: ");

    if (n.title.empty() || n.content.empty() ||
        !validTextField(n.title) || !validTextField(n.content)) {
        cout << "Title/content cannot be empty or contain the | character.\n";
        return;
    }

    notes.push_back(n);
    saveNotes();
    cout << "Note saved and made available to students registered for " << code << ".\n";
}

void createAssignment(int lecturerIndex) {
    string code;
    if (!lecturerSelectsUnit(lecturerIndex, code)) return;

    Assignment a;
    a.unitCode = code;
    a.title = readLine("Assignment title: ");
    a.description = readLine("Assignment instructions: ");

    if (a.title.empty() || a.description.empty() ||
        !validTextField(a.title) || !validTextField(a.description)) {
        cout << "Title/instructions cannot be empty or contain the | character.\n";
        return;
    }

    assignments.push_back(a);
    saveAssignments();
    cout << "Assignment saved and published to the LMS.\n";
}

void createCAT(int lecturerIndex) {
    string code;
    if (!lecturerSelectsUnit(lecturerIndex, code)) return;

    CAT c;
    c.unitCode = code;
    c.title = readLine("CAT title: ");
    c.date = readLine("CAT date (e.g. 2026-10-25): ");
    c.description = readLine("CAT details: ");

    if (c.title.empty() || c.date.empty() || c.description.empty() ||
        !validTextField(c.title) || !validTextField(c.date) ||
        !validTextField(c.description)) {
        cout << "Fields cannot be empty or contain the | character.\n";
        return;
    }

    cats.push_back(c);
    saveCATs();
    cout << "CAT saved and published to the LMS.\n";
}

void enterMarks(int lecturerIndex) {
    string code;
    if (!lecturerSelectsUnit(lecturerIndex, code)) return;

    string studentId = readLine("Student ID: ");
    int studentIndex = findStudent(studentId);

    if (studentIndex < 0) {
        cout << "Student not found.\n";
        return;
    }

    if (!studentRegistered(students[studentIndex], code)) {
        cout << "This student is not registered for " << code
             << ". Register the unit before entering marks.\n";
        return;
    }

    cout << "Enter marks. Assignment is out of 20, CAT out of 20, exam out of 60.\n";
    MarkRecord record;
    record.studentId = studentId;
    record.unitCode = code;
    record.assignment = readInt("Assignment mark (0-20): ", 0, 20);
    record.cat = readInt("CAT mark (0-20): ", 0, 20);
    record.exam = readInt("Exam mark (0-60): ", 0, 60);

    int existingIndex = findMark(studentId, code);
    if (existingIndex >= 0) {
        marks[existingIndex] = record;
        cout << "Existing marks updated successfully.\n";
    } else {
        marks.push_back(record);
        cout << "Marks entered successfully.\n";
    }

    saveMarks();
    cout << "The student can now view these marks in the Student Portal/LMS.\n";
}

void lecturerLMS(int lecturerIndex) {
    int choice;
    do {
        cout << "\n========== LECTURER LMS ==========\n"
             << "Welcome, " << lecturers[lecturerIndex].name << "\n"
             << "1. View assigned units\n"
             << "2. Add/upload note details\n"
             << "3. Create assignment\n"
             << "4. Create CAT\n"
             << "5. Enter/update student marks\n"
             << "6. Logout\n";

        choice = readInt("Select an option: ", 1, 6);

        switch (choice) {
            case 1: viewLecturerUnits(lecturerIndex); break;
            case 2: addNote(lecturerIndex); break;
            case 3: createAssignment(lecturerIndex); break;
            case 4: createCAT(lecturerIndex); break;
            case 5: enterMarks(lecturerIndex); break;
            case 6: cout << "Logging out...\n"; break;
        }
    } while (choice != 6);
}

void lecturerLogin() {
    cout << "\n========== LECTURER LOGIN ==========\n";
    string id = readLine("Lecturer ID: ");
    string password = readLine("Password: ");

    int index = findLecturer(id);
    if (index < 0 || lecturers[index].password != password) {
        cout << "Incorrect lecturer ID or password.\n";
        return;
    }
    lecturerLMS(index);
}

// ---------- Staff module ----------

void viewAllStudents() {
    cout << "\n========== STUDENTS ==========\n";
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }

    for (size_t i = 0; i < students.size(); ++i) {
        cout << "\nID: " << students[i].id << "\nName: " << students[i].name
             << "\nRegistered units: ";
        if (students[i].units.empty()) cout << "None";
        else cout << join(students[i].units, ',');
        cout << "\n";
    }
}

void viewAllLecturers() {
    cout << "\n========== LECTURERS ==========\n";
    if (lecturers.empty()) {
        cout << "No lecturers found.\n";
        return;
    }

    for (size_t i = 0; i < lecturers.size(); ++i) {
        cout << "\nID: " << lecturers[i].id << "\nName: " << lecturers[i].name
             << "\nAssigned units: ";
        if (lecturers[i].units.empty()) cout << "None";
        else cout << join(lecturers[i].units, ',');
        cout << "\n";
    }
}

void viewAcademicRecords() {
    cout << "\n========== ACADEMIC RECORDS ==========\n";
    if (marks.empty()) {
        cout << "No academic records are available.\n";
        return;
    }

    for (size_t i = 0; i < marks.size(); ++i) {
        int total = marks[i].assignment + marks[i].cat + marks[i].exam;
        cout << "\nStudent ID: " << marks[i].studentId
             << "\nUnit: " << marks[i].unitCode
             << "\nAssignment: " << marks[i].assignment
             << "\nCAT: " << marks[i].cat
             << "\nExam: " << marks[i].exam
             << "\nTotal: " << total << "/100"
             << "\nGrade: " << gradeFor(total) << "\n";
    }
}

void staffMenu(int staffIndex) {
    int choice;
    do {
        cout << "\n========== STAFF MODULE ==========\n"
             << "Welcome, " << staffMembers[staffIndex].name << "\n"
             << "1. View students\n"
             << "2. View lecturers\n"
             << "3. View university units\n"
             << "4. View academic records\n"
             << "5. Logout\n";

        choice = readInt("Select an option: ", 1, 5);

        switch (choice) {
            case 1: viewAllStudents(); break;
            case 2: viewAllLecturers(); break;
            case 3: displayAllUnits(); break;
            case 4: viewAcademicRecords(); break;
            case 5: cout << "Logging out...\n"; break;
        }
    } while (choice != 5);
}

void staffLogin() {
    cout << "\n========== STAFF LOGIN ==========\n";
    string id = readLine("Staff ID: ");
    string password = readLine("Password: ");

    int index = findStaff(id);
    if (index < 0 || staffMembers[index].password != password) {
        cout << "Incorrect staff ID or password.\n";
        return;
    }
    staffMenu(index);
}

// ---------- Main program ----------

int main() {
    loadAll();

    int choice;
    do {
        cout << "\n========================================\n"
             << "        JKUAT INFORMATION SYSTEM\n"
             << "========================================\n"
             << "1. Student Login\n"
             << "2. Lecturer Login\n"
             << "3. Staff Login\n"
             << "4. Exit\n";

        choice = readInt("Select an option: ", 1, 4);

        switch (choice) {
            case 1: studentLogin(); break;
            case 2: lecturerLogin(); break;
            case 3: staffLogin(); break;
            case 4:
                saveAll();
                cout << "Data saved. Thank you for using the JKUAT Information System.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
