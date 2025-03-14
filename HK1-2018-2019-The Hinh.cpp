#include <bits/stdc++.h>
using namespace std;

class ServiceMTK {
protected:
    string ServicePack;
    double BasicFee, PTsupport;
public:
    ServiceMTK(){}
    virtual void EnterInfo() = 0;
    virtual void DisplayInfo() = 0;
    virtual double TotalMoney() = 0;
    virtual ~ServiceMTK(){}
};

class Premium : public ServiceMTK {
private:
    double ClassFee, SaunaService;
public:
    Premium() : ServiceMTK(), ClassFee(0), SaunaService(0) {
        ServicePack = "Premium";
        BasicFee = 1000;
        PTsupport = 0;
    }
    void EnterInfo() override {
        cout << "Premium Package: Lop hoc duoc mien phi nen khong can nhap so luong.\n";
    }
    double TotalMoney() override {
        return BasicFee;
    }
    void DisplayInfo() override {
        cout << ServicePack << " Phi Co Ban: " << BasicFee << " Chi Phi Lop Hoc: " << ClassFee << " Dich Vu Xong Hoi: " << SaunaService << " Ho Tro PT: " << PTsupport << endl;
    }
};

class Basic : public ServiceMTK {
private:
    double Quantity, ClassFee;
public:
    Basic() : ServiceMTK(), Quantity(0), ClassFee(0) {
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
    double TotalMoney() override {
        return BasicFee + PTsupport + ClassFee;
    }
    void DisplayInfo() override {
        cout << ServicePack << " Phi Co Ban: " << BasicFee << " Chi Phi Lop Hoc: " << ClassFee << " Ho Tro PT: " << PTsupport << endl;
    }
};

class Non_Member : public ServiceMTK {
public:
    Non_Member() : ServiceMTK(){
        ServicePack = "Non - Member";
        BasicFee = 200;
        PTsupport = 200;
    }
    void EnterInfo() override {}
    double TotalMoney() override {
        return BasicFee + PTsupport;
    }
    void DisplayInfo() override {
        cout << ServicePack << " Phi Co Ban: " << BasicFee << " Ho Tro PT: " << PTsupport << endl;
    }
};

class Customer {
private:
    ServiceMTK* DichVu;     
    string Hoten, CMND, LuaChon;
    double TotalMoney;
public:
    Customer() : DichVu(nullptr), TotalMoney(0){}
    double getTotalMoney(){
        return this->TotalMoney;
    }
    void EnterInfo(){
        cout << "Nhap Ho Ten Khach Hang: ";
        getline(cin, Hoten);
        cout << "Nhap CMND Khach Hang: ";
        getline(cin, CMND);
        cout << "Nhap Lua Chon Cua Khach Hang: ";
        getline(cin, LuaChon);
        if (LuaChon == "Premium") DichVu = new Premium();
        else if (LuaChon == "Basic") DichVu = new Basic();
        else if (LuaChon == "Non - Member") DichVu = new Non_Member();
        DichVu->EnterInfo();
        TotalMoney = DichVu->TotalMoney();
    }
    void DisplayInfo(){
        cout << "Ho Ten: " << Hoten << " CMND: " << CMND << " ";
        DichVu->DisplayInfo();
    }
    ~Customer(){
        DichVu = nullptr;
    }
};

int main(){
    int Quantity;
    cout << "Nhap So Luong Khach Hang: ";
    cin >> Quantity;
    cin.ignore();
    vector<Customer> Customers;
    for(int i = 0; i<Quantity; i++){
        Customer Temp;
        Temp.EnterInfo();
        Customers.push_back(Temp);
    }
    for (Customer& cust : Customers){
        cust.DisplayInfo();
    }
    if (!Customers.empty()) {
        sort(Customers.begin(), Customers.end(), [](Customer x, Customer y) {
            return x.getTotalMoney() > y.getTotalMoney();
        });
        double maxTotal = Customers[0].getTotalMoney(); 
        cout << "\nKhach hang chi tieu nhieu nhat:\n";
        for (Customer cust : Customers) {
            if (cust.getTotalMoney() == maxTotal) {
                cust.DisplayInfo(); 
            }
        }
    } else {
        cout << "\nKhong co khach hang nao!\n";
    }
}