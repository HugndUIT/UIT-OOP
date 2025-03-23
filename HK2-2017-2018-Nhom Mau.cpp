#include <bits/stdc++.h>
using namespace std;

class BloodType {
private:
    string abo;
    bool rh;
public:
    BloodType(const string& abo = "O", bool rh = true) : abo(abo), rh(rh) {}
    string getABO() const { return abo; }
    bool getRh() const { return rh; }
    string toString() const {
        return abo + (rh ? "+" : "-");
    }
    bool canDonateTo(const BloodType& other) const {
        if (abo == "O") {
        } else if (abo == "A" && other.abo != "A" && other.abo != "AB") {
            return false;
        } else if (abo == "B" && other.abo != "B" && other.abo != "AB") {
            return false;
        } else if (abo == "AB" && other.abo != "AB") {
            return false;
        }
        if (!rh && other.rh) {
            return false;
        }
        return true;
    }
};

class Person {
private:
    string name;
    BloodType bloodType;
public:
    Person(const string& name, const string& abo, bool rh) : name(name), bloodType(abo, rh) {}
    string getName() const { return name; }
    BloodType getBloodType() const { return bloodType; }
    void display() const {
        cout << name << ": " << bloodType.toString() << endl;
    }
};

class BloodGroupManager {
private:
    vector<Person> people;
    bool isValidChildABO(const string& fatherABO, const string& motherABO, const string& childABO) const {
        string fABO = fatherABO, mABO = motherABO, cABO = childABO;
        transform(fABO.begin(), fABO.end(), fABO.begin(), ::toupper);
        transform(mABO.begin(), mABO.end(), mABO.begin(), ::toupper);
        transform(cABO.begin(), cABO.end(), cABO.begin(), ::toupper);
        if (fABO == "A" && mABO == "A") {
            return cABO == "A" || cABO == "O";
        }
        if ((fABO == "A" && mABO == "B") || (fABO == "B" && mABO == "A")) {
            return cABO == "A" || cABO == "B" || cABO == "AB" || cABO == "O";
        }
        if ((fABO == "A" && mABO == "AB") || (fABO == "AB" && mABO == "A")) {
            return cABO == "A" || cABO == "B" || cABO == "AB";
        }
        if ((fABO == "A" && mABO == "O") || (fABO == "O" && mABO == "A")) {
            return cABO == "A" || cABO == "O";
        }
        if (fABO == "B" && mABO == "B") {
            return cABO == "B" || cABO == "O";
        }
        if ((fABO == "B" && mABO == "AB") || (fABO == "AB" && mABO == "B")) {
            return cABO == "A" || cABO == "B" || cABO == "AB";
        }
        if ((fABO == "B" && mABO == "O") || (fABO == "O" && mABO == "B")) {
            return cABO == "B" || cABO == "O";
        }
        if (fABO == "AB" && mABO == "AB") {
            return cABO == "A" || cABO == "B" || cABO == "AB";
        }
        if ((fABO == "AB" && mABO == "O") || (fABO == "O" && mABO == "AB")) {
            return cABO == "A" || cABO == "B";
        }
        if (fABO == "O" && mABO == "O") {
            return cABO == "O";
        }
        return false;
    }
    bool isValidChildRh(bool fatherRh, bool motherRh, bool childRh) const {
        if (!fatherRh && !motherRh) {
            return !childRh;
        }
        return true;
    }
    void checkRhIncompatibility(bool motherRh, bool childRh) const {
        if (!motherRh && childRh) {
            cout << "Canh bao: Me Rh- sinh con Rh+. Lan dau khong co van de, nhung tu lan thu 2 tro di co the nguy hiem.\n";
        } else {
            cout << "Khong co bat dong Rh giua me va con.\n";
        }
    }
public:
    void addPerson(const Person& person) {
        people.push_back(person);
    }
    void displayPeople() const {
        if (people.empty()) {
            cout << "Danh sach trong!\n";
            return;
        }
        cout << "Danh sach nguoi:\n";
        for (size_t i = 0; i < people.size(); i++) {
            cout << i << ". ";
            people[i].display();
        }
    }
    void checkFamily(int fatherIdx, int motherIdx, int childIdx) const {
        if (fatherIdx < 0 || fatherIdx >= static_cast<int>(people.size()) ||
            motherIdx < 0 || motherIdx >= static_cast<int>(people.size()) ||
            childIdx < 0 || childIdx >= static_cast<int>(people.size())) {
            cout << "Chi so khong hop le!\n";
            return;
        }
        const Person& father = people[fatherIdx];
        const Person& mother = people[motherIdx];
        const Person& child = people[childIdx];
        cout << "Kiem tra bo 3:\n";
        cout << "Cha: " << father.getName() << " (" << father.getBloodType().toString() << ")\n";
        cout << "Me: " << mother.getName() << " (" << mother.getBloodType().toString() << ")\n";
        cout << "Con: " << child.getName() << " (" << child.getBloodType().toString() << ")\n";
        bool validABO = isValidChildABO(
            father.getBloodType().getABO(),
            mother.getBloodType().getABO(),
            child.getBloodType().getABO()
        );
        bool validRh = isValidChildRh(
            father.getBloodType().getRh(),
            mother.getBloodType().getRh(),
            child.getBloodType().getRh()
        );
        if (validABO && validRh) {
            cout << "Nhom mau cua con phu hop voi quy luat di truyen.\n";
        } else {
            cout << "Nhom mau cua con KHONG phu hop voi quy luat di truyen.\n";
            if (!validABO) cout << "Ly do: Nhom ABO khong phu hop.\n";
            if (!validRh) cout << "Ly do: Yeu to Rh khong phu hop.\n";
        }
        checkRhIncompatibility(mother.getBloodType().getRh(), child.getBloodType().getRh());
    }
    void checkDonation(int receiverIdx) const {
        if (receiverIdx < 0 || receiverIdx >= static_cast<int>(people.size())) {
            cout << "Chi so khong hop le!\n";
            return;
        }
        const Person& receiver = people[receiverIdx];
        cout << "Nguoi nhan: " << receiver.getName() << " (" << receiver.getBloodType().toString() << ")\n";
        cout << "Danh sach nguoi co the cho mau:\n";
        bool hasDonor = false;
        for (size_t i = 0; i < people.size(); i++) {
            if (static_cast<int>(i) == receiverIdx) continue;
            const Person& donor = people[i];
            if (donor.getBloodType().canDonateTo(receiver.getBloodType())) {
                cout << i << ". " << donor.getName() << " (" << donor.getBloodType().toString() << ")\n";
                hasDonor = true;
            }
        }
        if (!hasDonor) {
            cout << "Khong co nguoi nao co the cho mau.\n";
        }
    }
    void inputPeople() {
        int n;
        cout << "Nhap so luong nguoi: ";
        while (!(cin >> n) || n <= 0) {
            cout << "So luong phai la so nguyen duong! Vui long nhap lai: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int i = 0; i < n; i++) {
            string name, abo;
            char rhChar;
            cout << "Nhap thong tin nguoi thu " << (i + 1) << ":\n";
            cout << "Ten: ";
            getline(cin, name);
            if (name.empty()) {
                name = "Nguoi " + to_string(i + 1);
            }
            while (true) {
                cout << "Nhom mau ABO (A, B, AB, O): ";
                cin >> abo;
                transform(abo.begin(), abo.end(), abo.begin(), ::toupper);
                if (abo == "A" || abo == "B" || abo == "AB" || abo == "O") {
                    break;
                }
                cout << "Nhom mau khong hop le! Vui long nhap lai (A, B, AB, O).\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            while (true) {
                cout << "Yeu to Rh (+ hoac -): ";
                cin >> rhChar;
                rhChar = toupper(rhChar);
                if (rhChar == '+' || rhChar == '-') {
                    break;
                }
                cout << "Yeu to Rh khong hop le! Vui long nhap lai (+ hoac -).\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            bool rh = (rhChar == '+');
            people.emplace_back(name, abo, rh);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
};

int main() {
    BloodGroupManager manager;
    cout << "Nhap danh sach nguoi:\n";
    manager.inputPeople();
    manager.displayPeople();
    if (manager.displayPeople(), false) {
        cout << "Danh sach trong, khong the tiep tuc!\n";
        return 1;
    }
    int fatherIdx = -1, motherIdx = -1, childIdx = -1;
    cout << "\nNhap chi so cua bo 3 cha-me-con de kiem tra:\n";
    cout << "Chi so cha: ";
    while (!(cin >> fatherIdx) || fatherIdx < 0) {
        cout << "Chi so phai la so nguyen khong am! Vui long nhap lai: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Chi so me: ";
    while (!(cin >> motherIdx) || motherIdx < 0) {
        cout << "Chi so phai la so nguyen khong am! Vui long nhap lai: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Chi so con: ";
    while (!(cin >> childIdx) || childIdx < 0) {
        cout << "Chi so phai la so nguyen khong am! Vui long nhap lai: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    manager.checkFamily(fatherIdx, motherIdx, childIdx);
    int receiverIdx = -1;
    cout << "\nNhap chi so cua nguoi nhan mau de kiem tra kha nang truyen mau:\n";
    cout << "Chi so nguoi nhan: ";
    while (!(cin >> receiverIdx) || receiverIdx < 0) {
        cout << "Chi so phai la so nguyen khong am! Vui long nhap lai: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    manager.checkDonation(receiverIdx);
}
