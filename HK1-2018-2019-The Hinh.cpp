#include <bits/stdc++.h>
using namespace std;

class ServiceMTK {
protected:
    string ServicePack;
    double BasicFee, PTsupport;

public:
    ServiceMTK() : BasicFee(0), PTsupport(0) {}
    virtual void EnterInfo() = 0;
    virtual void DisplayInfo() const = 0;
    virtual double TotalMoney() const = 0;
    virtual ~ServiceMTK() {}
};

class Premium : public ServiceMTK {
public:
    Premium() {
        ServicePack = "Premium";
        BasicFee = 1000;
        PTsupport = 0;
    }

    void EnterInfo() override {
        cout << "Premium Package: Lop hoc duoc mien phi nen khong can nhap so luong.\n";
    }

    double TotalMoney() const override {
        return BasicFee;
    }

    void DisplayInfo() const override {
        cout << setw(15) << left << ServicePack
             << " | Phi Co Ban: " << setw(5) << BasicFee
             << " | Chi Phi Lop Hoc: 0 | Dich Vu Xong Hoi: 0 | Ho Tro PT: " << PTsupport << endl;
    }
};

class Basic : public ServiceMTK {
private:
    double Quantity, ClassFee;

public:
    Basic() : Quantity(0), ClassFee(0) {
        ServicePack = "Basic";
        BasicFee = 500;
        PTsupport = 100;
    }

    void EnterInfo() override {
        cout << "Enter Quantity: ";
        cin >> Quantity;
        cin.ignore();
        ClassFee = 100 * Quantity;
    }

    double TotalMoney() const override {
        return BasicFee + PTsupport + ClassFee;
    }

    void DisplayInfo() const override {
        cout << setw(15) << left << ServicePack
             << " | Phi Co Ban: " << setw(5) << BasicFee
             << " | Chi Phi Lop Hoc: " << setw(5) << ClassFee
             << " | Ho Tro PT: " << PTsupport << endl;
    }
};

class Non_Member : public ServiceMTK {
public:
    Non_Member() {
        ServicePack = "Non-Member";
        BasicFee = 200;
        PTsupport = 200;
    }

    void EnterInfo() override {}

    double TotalMoney() const override {
        return BasicFee + PTsupport;
    }

    void DisplayInfo() const override {
        cout << setw(15) << left << ServicePack
             << " | Phi Co Ban: " << setw(5) << BasicFee
             << " | Ho Tro PT: " << PTsupport << endl;
    }
};

class Customer {
private:
    ServiceMTK* DichVu;
    string Hoten, CMND, LuaChon;
    double TotalMoney;

public:
    Customer() : DichVu(nullptr), TotalMoney(0) {}

    double getTotalMoney() const {
        return TotalMoney;
    }

    void EnterInfo() {
        cout << "Nhap Ho Ten Khach Hang: ";
        getline(cin, Hoten);
        cout << "Nhap CMND Khach Hang: ";
        getline(cin, CMND);
        cout << "Nhap Lua Chon Cua Khach Hang (Premium/Basic/Non-Member): ";
        getline(cin, LuaChon);

        if (LuaChon == "Premium") 
            DichVu = new Premium();
        else if (LuaChon == "Basic") 
            DichVu = new Basic();
        else if (LuaChon == "Non-Member") 
            DichVu = new Non_Member();
        else {
            cout << "Lua chon khong hop le! Mac dinh chon Non-Member.\n";
            DichVu = new Non_Member();
        }

        DichVu->EnterInfo();
        TotalMoney = DichVu->TotalMoney();
    }

    void DisplayInfo() const {
        cout << setw(20) << left << Hoten
             << " | CMND: " << setw(12) << CMND << " | ";
        DichVu->DisplayInfo();
    }

    ~Customer() {
        delete DichVu;
    }
};

int main() {
    int Quantity;
    cout << "Nhap So Luong Khach Hang: ";
    cin >> Quantity;
    cin.ignore();

    vector<Customer> Customers(Quantity);
    for (int i = 0; i < Quantity; i++) {
        cout << "\nNhap thong tin khach hang thu " << i + 1 << ":\n";
        Customers[i].EnterInfo();
    }

    cout << "\nDanh sach khach hang:\n";
    for (const auto& cust : Customers) {
        cust.DisplayInfo();
    }

    if (!Customers.empty()) {
        sort(Customers.begin(), Customers.end(), [](const Customer& x, const Customer& y) {
            return x.getTotalMoney() > y.getTotalMoney();
        });

        double maxTotal = Customers[0].getTotalMoney();
        cout << "\nKhach hang chi tieu nhieu nhat:\n";
        for (const auto& cust : Customers) {
            if (cust.getTotalMoney() == maxTotal) {
                cust.DisplayInfo();
            }
        }
    } else {
        cout << "\nKhong co khach hang nao!\n";
    }
}
