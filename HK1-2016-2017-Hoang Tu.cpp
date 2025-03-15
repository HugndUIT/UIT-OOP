#include <bits/stdc++.h>
using namespace std;

class Prince {
private:
    double Money, IQ, Power;

public:
    void setMoney(double Money) { this->Money = Money; }
    void setPower(double Power) { this->Power = Power; }
    
    double getMoney() const { return Money; }
    double getPower() const { return Power; }
    double getIQ() const { return IQ; }

    void EnterInfo() {
        cout << "Nhập thông tin Hoàng tử (Tiền TríTuệ SứcMạnh): ";
        cin >> Money >> IQ >> Power;
    }

    void DisplayInfo() const {
        cout << "Thông tin Hoàng tử sau khi vượt cổng:\n"
             << "Tiền: " << Money << " | Trí tuệ: " << IQ << " | Sức mạnh: " << Power << endl;
    }
};

class Gate {
protected:
    string Keeper;

public:
    virtual bool PassGate(Prince& HoangTu) = 0;
    virtual void EnterInfo() = 0;
    virtual void DisplayInfo() const = 0;
    virtual ~Gate() {}
};

class BusinessGate : public Gate {
private:
    double Price, Quantity;

public:
    BusinessGate() { Keeper = "Merchant"; }

    bool PassGate(Prince& HoangTu) override {
        double TotalCost = Price * Quantity;
        if (HoangTu.getMoney() >= TotalCost) {
            HoangTu.setMoney(HoangTu.getMoney() - TotalCost);
            return true;
        }
        return false;
    }

    void EnterInfo() override {
        cout << "Nhập thông tin cổng giao thương (Giá một món hàng, Số lượng hàng): ";
        cin >> Price >> Quantity;
    }

    void DisplayInfo() const override {
        cout << "Cổng Giao Thương | Người gác: " << Keeper
             << " | Giá: " << Price << " | Số lượng: " << Quantity << endl;
    }
};

class AcademicGate : public Gate {
private:
    double IQquestion;

public:
    AcademicGate() { Keeper = "Sage"; }

    bool PassGate(Prince& HoangTu) override {
        return HoangTu.getIQ() >= IQquestion;
    }

    void EnterInfo() override {
        cout << "Nhập thông tin cổng học thuật (Chỉ số IQ yêu cầu): ";
        cin >> IQquestion;
    }

    void DisplayInfo() const override {
        cout << "Cổng Học Thuật | Người gác: " << Keeper
             << " | IQ yêu cầu: " << IQquestion << endl;
    }
};

class PowerGate : public Gate {
private:
    double Strength;

public:
    PowerGate() { Keeper = "Warrior"; }

    bool PassGate(Prince& HoangTu) override {
        if (HoangTu.getPower() >= Strength) {
            HoangTu.setPower(HoangTu.getPower() - Strength);
            return true;
        }
        return false;
    }

    void EnterInfo() override {
        cout << "Nhập thông tin cổng sức mạnh (Chỉ số sức mạnh của dũng sĩ): ";
        cin >> Strength;
    }

    void DisplayInfo() const override {
        cout << "Cổng Sức Mạnh | Người gác: " << Keeper
             << " | Sức mạnh yêu cầu: " << Strength << endl;
    }
};

void Display(const vector<Gate*>& Gates) {
    for (const Gate* gate : Gates) {
        gate->DisplayInfo();
    }
}

int main() {
    Prince HoangTu;
    HoangTu.EnterInfo();
    
    int Quantity;
    cout << "Nhập số lượng cổng: ";
    cin >> Quantity;

    vector<Gate*> Gates;
    for (int i = 0; i < Quantity; i++) {
        int Type;
        cout << "Nhập loại cổng thứ " << i + 1 << " (1 - Giao Thương, 2 - Học Thuật, 3 - Sức Mạnh): ";
        cin >> Type;

        Gate* Temp = nullptr;
        if (Type == 1) Temp = new BusinessGate();
        else if (Type == 2) Temp = new AcademicGate();
        else if (Type == 3) Temp = new PowerGate();
        
        if (Temp) {
            Temp->EnterInfo();
            Gates.push_back(Temp);
        }
    }

    bool SavedPrincess = true;
    for (size_t i = 0; i < Gates.size(); ) {
        if (Gates[i]->PassGate(HoangTu)) {
            delete Gates[i];
            Gates.erase(Gates.begin() + i);
        } else {
            SavedPrincess = false;
            break;
        }
    }

    if (SavedPrincess) {
        HoangTu.DisplayInfo();
        cout << "Hoàng tử đã cứu được công chúa thành công!\n";
    } else {
        cout << "Hoàng tử không thể cứu công chúa. Các cổng chưa qua:\n";
        Display(Gates);
    }

    for (Gate* gate : Gates) {
        delete gate;
    }

    return 0;
}
