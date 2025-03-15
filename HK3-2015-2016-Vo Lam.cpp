#include <bits/stdc++.h>
using namespace std;

class Hanh {
protected:
    string MonPhai;

public:
    virtual void NhapThongTin() = 0;
    virtual ~Hanh() {}
    string GetMonPhai() const { return MonPhai; }
    virtual string GetHeName() const = 0; 
};

class HeKim : public Hanh {
private:
    void NhapThongTin() override {
        cout << "Chon Mon Phai: (1) Thieu Lam (2) Thien Vuong Bang: ";
        int Type;
        cin >> Type;
        MonPhai = (Type == 1) ? "Thieu Lam" : (Type == 2) ? "Thien Vuong Bang" : "";
        if (Type != 1 && Type != 2) cout << "Lua Chon Khong Hop Le!\n";
    }
    string GetHeName() const override { 
        return "Kim"; 
    }
};

class HeThuy : public Hanh {
private:
    void NhapThongTin() override {
        cout << "Chon Mon Phai: (1) Nga My (2) Thuy Yen Mon: ";
        int Type;
        cin >> Type;
        MonPhai = (Type == 1) ? "Nga My" : (Type == 2) ? "Thuy Yen Mon" : "";
        if (Type != 1 && Type != 2) cout << "Lua Chon Khong Hop Le!\n";
    }
    string GetHeName() const override { 
        return "Thuy"; 
    }
};

class HeTho : public Hanh {
private:
    void NhapThongTin() override {
        cout << "Chon Mon Phai: (1) Con Lon (2) Vo Dang: ";
        int Type;
        cin >> Type;
        MonPhai = (Type == 1) ? "Con Lon" : (Type == 2) ? "Vo Dang" : "";
        if (Type != 1 && Type != 2) cout << "Lua Chon Khong Hop Le!\n";
    }
    string GetHeName() const override { 
        return "Tho"; 
    }
};

class HeMoc : public Hanh {
private:
    void NhapThongTin() override {
        cout << "Chon Mon Phai: (1) Ngu Doc Giao (2) Duong Mon: ";
        int Type;
        cin >> Type;
        MonPhai = (Type == 1) ? "Ngu Doc Giao" : (Type == 2) ? "Duong Mon" : "";
        if (Type != 1 && Type != 2) cout << "Lua Chon Khong Hop Le!\n";
    }
    string GetHeName() const override { 
        return "Moc"; 
    }
};

class HeHoa : public Hanh {
private:
    void NhapThongTin() override {
        cout << "Chon Mon Phai: (1) Cai Bang (2) Thien Nhan Giao: ";
        int Type;
        cin >> Type;
        MonPhai = (Type == 1) ? "Cai Bang" : (Type == 2) ? "Thien Nhan Giao" : "";
        if (Type != 1 && Type != 2) cout << "Lua Chon Khong Hop Le!\n";
    }
    string GetHeName() const override { 
        return "Hoa"; 
    }
};

class DoiTuong {
protected:
    Hanh* He;
    double CapDo, SatThuong;

public:
    virtual void EnterInfo() = 0;
    virtual double GetSatThuong() const = 0;
    virtual Hanh* GetHe() const = 0;
    virtual void PrintInfo() const = 0;
    virtual ~DoiTuong() { delete He; }
};

class NhanVat : public DoiTuong {
public:
    void EnterInfo() override {
        cout << "Nhap He (1-Kim, 2-Moc, 3-Thuy, 4-Hoa, 5-Tho): ";
        int Type;
        cin >> Type;
        switch (Type) {
            case 1: He = new HeKim(); break;
            case 2: He = new HeMoc(); break;
            case 3: He = new HeThuy(); break;
            case 4: He = new HeHoa(); break;
            case 5: He = new HeTho(); break;
            default: cout << "Lua chon khong hop le!\n"; return;
        }
        He->NhapThongTin();
        if (He->GetMonPhai().empty()) return;
        cout << "Nhap Cap Do: ";
        cin >> CapDo;
        SatThuong = CapDo * 5;
    }

    double GetSatThuong() const override { return SatThuong; }
    Hanh* GetHe() const override { return He; }
    void PrintInfo() const override {
        if (!He) return;
        cout << setw(15) << left << "Nhan Vat"
             << " He: " << setw(10) << He->GetHeName()
             << " Mon Phai: " << setw(15) << He->GetMonPhai()
             << " Cap Do: " << setw(5) << fixed << setprecision(1) << CapDo
             << " Sat Thuong: " << SatThuong << endl;
    }
};

class QuaiVat : public DoiTuong {
public:
    virtual Hanh* GetHe() const = 0;
    virtual ~QuaiVat() {}
};

class ThongThuong : public QuaiVat {
public:
    void EnterInfo() override {
        cout << "Nhap He (1-Kim, 2-Moc, 3-Thuy, 4-Hoa, 5-Tho): ";
        int Type;
        cin >> Type;
        switch (Type) {
            case 1: He = new HeKim(); break;
            case 2: He = new HeMoc(); break;
            case 3: He = new HeThuy(); break;
            case 4: He = new HeHoa(); break;
            case 5: He = new HeTho(); break;
            default: cout << "Lua chon khong hop le!\n"; return;
        }
        He->NhapThongTin();
        if (He->GetMonPhai().empty()) return;
        cout << "Nhap Cap Do: ";
        cin >> CapDo;
        SatThuong = CapDo * 3;
    }

    double GetSatThuong() const override { return SatThuong; }
    Hanh* GetHe() const override { return He; }
    void PrintInfo() const override {
        if (!He) return;
        cout << setw(15) << left << "Quai (Thuong)"
             << " He: " << setw(10) << He->GetHeName()
             << " Mon Phai: " << setw(15) << He->GetMonPhai()
             << " Cap Do: " << setw(5) << fixed << setprecision(1) << CapDo
             << " Sat Thuong: " << SatThuong << endl;
    }
};

class DauLinh : public QuaiVat {
public:
    void EnterInfo() override {
        cout << "Nhap He (1-Kim, 2-Moc, 3-Thuy, 4-Hoa, 5-Tho): ";
        int Type;
        cin >> Type;
        switch (Type) {
            case 1: He = new HeKim(); break;
            case 2: He = new HeMoc(); break;
            case 3: He = new HeThuy(); break;
            case 4: He = new HeHoa(); break;
            case 5: He = new HeTho(); break;
            default: cout << "Lua chon khong hop le!\n"; return;
        }
        He->NhapThongTin();
        if (He->GetMonPhai().empty()) return;
        cout << "Nhap Cap Do: ";
        cin >> CapDo;
        SatThuong = CapDo * 7;
    }

    double GetSatThuong() const override { return SatThuong; }
    Hanh* GetHe() const override { return He; }
    void PrintInfo() const override {
        if (!He) return;
        cout << setw(15) << left << "Quai (Dau Linh)"
             << " He: " << setw(10) << He->GetHeName()
             << " Mon Phai: " << setw(15) << He->GetMonPhai()
             << " Cap Do: " << setw(5) << fixed << setprecision(1) << CapDo
             << " Sat Thuong: " << SatThuong << endl;
    }
};

void SinhKhac(const DoiTuong* attacker, const DoiTuong* defender, double& damageAttacker, double& damageDefender) {
    if (!attacker || !defender || !attacker->GetHe() || !defender->GetHe()) {
        damageAttacker = 0;
        damageDefender = 0;
        return;
    }

    double baseAttacker = attacker->GetSatThuong();
    double baseDefender = defender->GetSatThuong();
    const Hanh* heAttacker = attacker->GetHe();
    const Hanh* heDefender = defender->GetHe();

    if (dynamic_cast<const HeKim*>(heAttacker)) {
        if (dynamic_cast<const HeThuy*>(heDefender)) damageAttacker = baseAttacker * 1.1;
        else if (dynamic_cast<const HeMoc*>(heDefender)) damageAttacker = baseAttacker * 1.2;
        else if (dynamic_cast<const HeHoa*>(heDefender)) damageAttacker = baseAttacker * 0.8;
        else damageAttacker = baseAttacker;
    } else if (dynamic_cast<const HeThuy*>(heAttacker)) {
        if (dynamic_cast<const HeMoc*>(heDefender)) damageAttacker = baseAttacker * 1.1;
        else if (dynamic_cast<const HeHoa*>(heDefender)) damageAttacker = baseAttacker * 1.2;
        else if (dynamic_cast<const HeTho*>(heDefender)) damageAttacker = baseAttacker * 0.8;
        else damageAttacker = baseAttacker;
    } else if (dynamic_cast<const HeMoc*>(heAttacker)) {
        if (dynamic_cast<const HeHoa*>(heDefender)) damageAttacker = baseAttacker * 1.1;
        else if (dynamic_cast<const HeTho*>(heDefender)) damageAttacker = baseAttacker * 1.2;
        else if (dynamic_cast<const HeKim*>(heDefender)) damageAttacker = baseAttacker * 0.8;
        else damageAttacker = baseAttacker;
    } else if (dynamic_cast<const HeHoa*>(heAttacker)) {
        if (dynamic_cast<const HeTho*>(heDefender)) damageAttacker = baseAttacker * 1.1;
        else if (dynamic_cast<const HeKim*>(heDefender)) damageAttacker = baseAttacker * 1.2;
        else if (dynamic_cast<const HeThuy*>(heDefender)) damageAttacker = baseAttacker * 0.8;
        else damageAttacker = baseAttacker;
    } else if (dynamic_cast<const HeTho*>(heAttacker)) {
        if (dynamic_cast<const HeKim*>(heDefender)) damageAttacker = baseAttacker * 1.1;
        else if (dynamic_cast<const HeThuy*>(heDefender)) damageAttacker = baseAttacker * 1.2;
        else if (dynamic_cast<const HeMoc*>(heDefender)) damageAttacker = baseAttacker * 0.8;
        else damageAttacker = baseAttacker;
    } else {
        damageAttacker = baseAttacker;
    }

    if (dynamic_cast<const HeKim*>(heDefender)) {
        if (dynamic_cast<const HeThuy*>(heAttacker)) damageDefender = baseDefender * 1.1;
        else if (dynamic_cast<const HeMoc*>(heAttacker)) damageDefender = baseDefender * 1.2;
        else if (dynamic_cast<const HeHoa*>(heAttacker)) damageDefender = baseDefender * 0.8;
        else damageDefender = baseDefender;
    } else if (dynamic_cast<const HeThuy*>(heDefender)) {
        if (dynamic_cast<const HeMoc*>(heAttacker)) damageDefender = baseDefender * 1.1;
        else if (dynamic_cast<const HeHoa*>(heAttacker)) damageDefender = baseDefender * 1.2;
        else if (dynamic_cast<const HeTho*>(heAttacker)) damageDefender = baseDefender * 0.8;
        else damageDefender = baseDefender;
    } else if (dynamic_cast<const HeMoc*>(heDefender)) {
        if (dynamic_cast<const HeHoa*>(heAttacker)) damageDefender = baseDefender * 1.1;
        else if (dynamic_cast<const HeTho*>(heAttacker)) damageDefender = baseDefender * 1.2;
        else if (dynamic_cast<const HeKim*>(heAttacker)) damageDefender = baseDefender * 0.8;
        else damageDefender = baseDefender;
    } else if (dynamic_cast<const HeHoa*>(heDefender)) {
        if (dynamic_cast<const HeTho*>(heAttacker)) damageDefender = baseDefender * 1.1;
        else if (dynamic_cast<const HeKim*>(heAttacker)) damageDefender = baseDefender * 1.2;
        else if (dynamic_cast<const HeThuy*>(heAttacker)) damageDefender = baseDefender * 0.8;
        else damageDefender = baseDefender;
    } else if (dynamic_cast<const HeTho*>(heDefender)) {
        if (dynamic_cast<const HeKim*>(heAttacker)) damageDefender = baseDefender * 1.1;
        else if (dynamic_cast<const HeThuy*>(heAttacker)) damageDefender = baseDefender * 1.2;
        else if (dynamic_cast<const HeMoc*>(heAttacker)) damageDefender = baseDefender * 0.8;
        else damageDefender = baseDefender;
    } else {
        damageDefender = baseDefender;
    }
}

void PrintAll(const vector<DoiTuong*>& DanhSach) {
    cout << "\n" << string(70, '=') << "\n";
    cout << setw(30) << right << "THONG TIN TAT CA DOI TUONG" << "\n";
    cout << string(70, '=') << "\n";
    cout << left << setw(5) << "STT" << setw(15) << "Loai"
         << " He: " << setw(10) << "He"
         << " Mon Phai: " << setw(15) << "Mon Phai"
         << " Cap Do: " << setw(5) << "Cap Do"
         << " Sat Thuong: " << setw(15) << "Sat Thuong" << endl;
    cout << string(70, '-') << "\n";
    for (size_t i = 0; i < DanhSach.size(); i++) {
        if (DanhSach[i] && DanhSach[i]->GetHe()) {
            cout << left << setw(5) << (i + 1) << ".";
            DanhSach[i]->PrintInfo();
        }
    }
    cout << string(70, '=') << "\n";
    if (DanhSach.empty()) return;
    auto maxDamageObj = *max_element(DanhSach.begin(), DanhSach.end(),
        [](const DoiTuong* a, const DoiTuong* b) {
            return a->GetSatThuong() < b->GetSatThuong();
        });
    cout << "\nDoi tuong co sat thuong cao nhat:\n";
    maxDamageObj->PrintInfo();
}

int main() {
    vector<DoiTuong*> DanhSach; int n;

    cout << "Nhap so luong nhan vat: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "\nNhan vat " << i + 1 << ":\n";
        auto* nv = new NhanVat();
        nv->EnterInfo();
        if (nv->GetHe() && !nv->GetHe()->GetMonPhai().empty())
            DanhSach.push_back(nv);
        else
            delete nv;
    }

    cout << "\nNhap so luong quai vat: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "\nQuai vat " << i + 1 << ":\n";
        cout << "Chon loai (1-Thong Thuong, 2-Dau Linh): ";
        int Type;
        cin >> Type;
        DoiTuong* qv = nullptr;
        if (Type == 1) qv = new ThongThuong();
        else if (Type == 2) qv = new DauLinh();
        else {
            cout << "Lua chon khong hop le!\n";
            continue;
        }
        qv->EnterInfo();
        if (qv->GetHe() && !qv->GetHe()->GetMonPhai().empty())
            DanhSach.push_back(qv);
        else
            delete qv;
    }

    PrintAll(DanhSach);

    while (true) {
        if (DanhSach.empty()) break;
        cout << "\n" << string(40, '-') << "\n";
        cout << "CHON DOI TUONG DANH NHAU\n";
        cout << string(40, '-') << "\n";

        vector<NhanVat*> Players;
        vector<QuaiVat*> Monsters;
        for (auto* obj : DanhSach) {
            if (auto* nv = dynamic_cast<NhanVat*>(obj)) Players.push_back(nv);
            else if (auto* qv = dynamic_cast<QuaiVat*>(obj)) Monsters.push_back(qv);
        }

        if (Players.empty() || Monsters.empty()) {
            cout << "Khong du doi tuong de danh nhau!\n";
            break;
        }

        cout << "\nDanh sach nhan vat:\n";
        for (size_t i = 0; i < Players.size(); i++) {
            cout << i + 1 << ". ";
            Players[i]->PrintInfo();
        }

        cout << "\nDanh sach quai vat:\n";
        for (size_t i = 0; i < Monsters.size(); i++) {
            cout << i + 1 << ". ";
            Monsters[i]->PrintInfo();
        }

        size_t choiceNv, choiceQv;
        cout << "\nChon nhan vat (1-" << Players.size() << "): ";
        cin >> choiceNv;
        cout << "Chon quai vat (1-" << Monsters.size() << "): ";
        cin >> choiceQv;

        if (choiceNv < 1 || choiceNv > Players.size() || choiceQv < 1 || choiceQv > Monsters.size()) {
            cout << "Lua chon khong hop le!\n";
            continue;
        }

        auto* player = Players[choiceNv - 1];
        auto* monster = Monsters[choiceQv - 1];
        double damagePlayer, damageMonster;
        SinhKhac(player, monster, damagePlayer, damageMonster); 

        cout << "\n" << string(40, '=') << "\n";
        cout << "KET QUA TRAN CHIEN\n";
        cout << string(40, '=') << "\n";
        player->PrintInfo();
        cout << "Sat thuong nhan vat: " << damagePlayer << "\n\n";
        monster->PrintInfo();
        cout << "Sat thuong quai vat: " << damageMonster << "\n";
        cout << string(40, '=') << "\n";

        char continueFight;
        cout << "Tiep tuc? (y/n): ";
        cin >> continueFight;
        if (continueFight == 'n' || continueFight == 'N') break;
    }

    for (auto* obj : DanhSach) delete obj;
}