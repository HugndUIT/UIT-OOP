#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Color {
    int Do, XanhLa, XanhDuong, STT;
    string MauSac;
public:
    void Nhap();
    int getSTT();
};

void Color::Nhap() {
    cin >> Do >> XanhLa >> XanhDuong;
    if (Do == 255 && XanhLa == 0 && XanhDuong == 0) {
        MauSac = "Red";
        STT = 1;
    } else if (Do == 255 && XanhLa == 125 && XanhDuong == 0) {
        MauSac = "Orange";
        STT = 2;
    } else if (Do == 255 && XanhLa == 255 && XanhDuong == 0) {
        MauSac = "Yellow";
        STT = 3;
    } else if (Do == 125 && XanhLa == 255 && XanhDuong == 0) {
        MauSac = "Spring Green";
        STT = 4;
    } else if (Do == 0 && XanhLa == 255 && XanhDuong == 0) {
        MauSac = "Green";
        STT = 5;
    } else if (Do == 0 && XanhLa == 255 && XanhDuong == 125) {
        MauSac = "Turquoise";
        STT = 6;
    } else if (Do == 0 && XanhLa == 255 && XanhDuong == 255) {
        MauSac = "Cyan";
        STT = 7;
    } else if (Do == 0 && XanhLa == 125 && XanhDuong == 255) {
        MauSac = "Ocean";
        STT = 8;
    } else if (Do == 0 && XanhLa == 0 && XanhDuong == 255) {
        MauSac = "Blue";
        STT = 9;
    } else if (Do == 125 && XanhLa == 0 && XanhDuong == 255) {
        MauSac = "Violet";
        STT = 10;
    } else if (Do == 255 && XanhLa == 0 && XanhDuong == 255) {
        MauSac = "Magenta";
        STT = 11;
    } else {
        MauSac = "Raspberry";
        STT = 12;
    }
}

int Color::getSTT() {
    return STT;
}

class GiaoDien {
protected:
    int HoanhDo, TungDo, Dai, Rong;
    vector<Color> MauChu;
    vector<Color> MauNen;
public:
    virtual void Nhap();
    vector<Color> GetMauChu();
    vector<Color> GetMauNen();
    bool IsPhoiMauDonSac(vector<Color>);
    bool IsBoTucTrucTiep(vector<Color>);
    bool IsTuongDong(vector<Color>);
    virtual ~GiaoDien();
};

void GiaoDien::Nhap() {
    cin >> HoanhDo >> TungDo >> Dai >> Rong;
    int SoLuongMauNen; cin >> SoLuongMauNen;
    for (int i = 0; i < SoLuongMauNen; i++) {
        Color Temp;
        Temp.Nhap();
        MauNen.push_back(Temp);
    }
    int SoLuongMauChu; cin >> SoLuongMauChu;
    for (int i = 0; i < SoLuongMauChu; i++) {
        Color Temp;
        Temp.Nhap();
        MauChu.push_back(Temp);
    }
}

bool GiaoDien::IsPhoiMauDonSac(vector<Color> Mau) {
    for (size_t i = 1; i < Mau.size(); i++) {
        if (Mau[i].getSTT() != Mau[0].getSTT()) return false;
    }
    return true;
}

bool GiaoDien::IsBoTucTrucTiep(vector<Color> Mau) {
    if (Mau.size() % 2 != 0) return false;
    for (size_t i = 0; i < Mau.size(); i += 2) {
        int d1 = Mau[i].getSTT();
        int d2 = Mau[i + 1].getSTT();
        if ((abs(d1 - d2) != 6) && (abs(d1 - d2) != 6 % 12)) return false;
    }
    return true;
}

bool GiaoDien::IsTuongDong(vector<Color> Mau) {
    if (Mau.size() < 3) return false;
    for (size_t i = 0; i + 2 < Mau.size(); i += 3) {
        int d1 = Mau[i].getSTT();
        int d2 = Mau[i + 1].getSTT();
        int d3 = Mau[i + 2].getSTT();
        if (!((d2 == d1 + 1 || (d1 == 12 && d2 == 1)) &&
              (d3 == d2 + 1 || (d2 == 12 && d3 == 1)))) return false;
    }
    return true;
}

vector<Color> GiaoDien::GetMauChu() { return MauChu; }
vector<Color> GiaoDien::GetMauNen() { return MauNen; }
GiaoDien::~GiaoDien() {}

class Button : public GiaoDien {
    string Text, Picture;
public:
    void Nhap();
};

void Button::Nhap() {
    GiaoDien::Nhap();
    cin >> Text >> Picture;
}

class Label : public GiaoDien {
    string Text;
public:
    void Nhap();
};

void Label::Nhap() {
    GiaoDien::Nhap();
    cin.ignore();
    getline(cin, Text);
}

class Website {
    vector<GiaoDien*> ThanhPhan;
public:
    void Nhap();
    void KiemTraDau();
    void KiemTraNen();
};

void Website::Nhap() {
    int SoLuong; cin >> SoLuong;
    for (int i = 0; i < SoLuong; i++) {
        int Loai; cin >> Loai;
        GiaoDien* tp = nullptr;
        if (Loai == 1) tp = new Label;
        else tp = new Button;
        tp->Nhap();
        ThanhPhan.push_back(tp);
    }
}

void Website::KiemTraDau() {
    if (ThanhPhan.empty()) return;
    auto* tp = ThanhPhan[0];
    if (tp->IsBoTucTrucTiep(tp->GetMauNen()) && tp->IsBoTucTrucTiep(tp->GetMauChu()))
        cout << "Phu Hop\n";
    else
        cout << "Khong Phu Hop\n";
}

void Website::KiemTraNen() {
    for (auto* tp : ThanhPhan) {
        if (tp->IsBoTucTrucTiep(tp->GetMauNen()))
            cout << "Phoi Mau Bo Tuc Truc Tiep\n";
        else if (tp->IsPhoiMauDonSac(tp->GetMauNen()))
            cout << "Phoi Mau Don Sac\n";
        else if (tp->IsTuongDong(tp->GetMauNen()))
            cout << "Phoi Mau Tuong Dong\n";
        else
            cout << "Khong Xac Dinh Duoc\n";
    }
}

int main() {
    Website web;
    web.Nhap();
    web.KiemTraDau();
    web.KiemTraNen();
    return 0;
}