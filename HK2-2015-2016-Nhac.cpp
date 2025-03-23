#include <bits/stdc++.h>

using namespace std;

class NotNhac {
protected:
    string CaoDo;
    double TruongDo;
    string LoaiNot;
public:
    NotNhac(string c, double t, string l) : CaoDo(c), TruongDo(t), LoaiNot(l) {}
    virtual void HienThi() {
        cout << CaoDo << " (" << LoaiNot << ", " << TruongDo << " phach)" << endl;
    }
    string GetCaoDo() { 
        return CaoDo; 
    }
    double GetTruongDo() { 
        return TruongDo; 
    }
};

class DauLang : public NotNhac {
public:
    DauLang(double t) : NotNhac("Z", t, "Dau lang") {}
    void HienThi() override {
        cout << "Dau lang (" << TruongDo << " phach)" << endl;
    }
};

class BanNhac {
private:
    vector<NotNhac*> DanhSachNot;
public:
    void ThemNotNhac(NotNhac* n) {
        DanhSachNot.push_back(n);
    }
    void HienThiBanNhac() {
        for (auto n : DanhSachNot) {
            n->HienThi();
        }
    }
    int DemDauLang() {
        int Count = 0;
        for (auto n : DanhSachNot) {
            if (dynamic_cast<DauLang*>(n)) {
                Count++;
            }
        }
        return Count;
    }
    NotNhac* TimNotCaoNhat() {
        NotNhac* MaxNot = nullptr;
        string ThuTuCaoDo = "CDEFGAB";
        for (auto n : DanhSachNot) {
            if (n->GetCaoDo() == "Z") {
                continue;
            }
            if (!MaxNot || ThuTuCaoDo.find(n->GetCaoDo()) > ThuTuCaoDo.find(MaxNot->GetCaoDo())) {
                MaxNot = n;
            }
        }
        return MaxNot;
    }
    void NhapBanNhac() {
        while (true) {
            cout << "\nNhap not nhac: ";
            string CaoDo;
            cin >> CaoDo;
            if (CaoDo == "X") {
                break;
            }
            double TruongDo;
            cout << "Nhap truong do: ";
            cin >> TruongDo;
            if (CaoDo == "Z") {
                ThemNotNhac(new DauLang(TruongDo));
            } else {
                string LoaiNot;
                cout << "Nhap loai not: ";
                cin >> LoaiNot;
                ThemNotNhac(new NotNhac(CaoDo, TruongDo, LoaiNot));
            }
        }
    }
};

int main() {
    BanNhac banNhac;
    cout << "Nhap ban nhac:\n";
    banNhac.NhapBanNhac();
    cout << "\nBan nhac da nhap:\n";
    banNhac.HienThiBanNhac();
    cout << "\nSo luong dau lang: " << banNhac.DemDauLang() << endl;
    NotNhac* MaxNot = banNhac.TimNotCaoNhat();
    if (MaxNot) {
        cout << "Not cao nhat: ";
        MaxNot->HienThi();
    }
}