#include <bits/stdc++.h>
using namespace std;

class ChuongNgaiVat {
public:
    virtual bool VuotAi(vector<int> ChiSo, int Temp) = 0;
    virtual void EnterInfo() = 0;
    virtual ~ChuongNgaiVat() {}
};

class KhuRungChong : public ChuongNgaiVat {
private:
    vector<int> Chong;
    int ChiSoTao;

public:
    void EnterInfo() override {
        int n;
        cout << "\nNhap 7 chi so chong: ";
        for (int i = 0; i < 7; i++) {
            cin >> n;
            Chong.push_back(n);
        }
        do {
            cout << "Nhap Chi So Tao: ";
            cin >> ChiSoTao;
        } while (ChiSoTao < 0);
    }

    bool VuotAi(vector<int> ChiSo, int) override {
        for (size_t i = 0; i < ChiSo.size(); i++) {
            ChiSo[i] += ChiSoTao;
        }

        for (size_t i = 0; i < ChiSo.size(); i++) {
            if (ChiSo[i] <= Chong[i]) return false;
        }
        return true;
    }
};

class DuongHamNui : public ChuongNgaiVat {
private:
    int ChieuCaoDuongHam;

public:
    void EnterInfo() override {
        do {
            cout << "\nNhap Chieu Cao Duong Ham: ";
            cin >> ChieuCaoDuongHam;
        } while (ChieuCaoDuongHam < 0);
    }

    bool VuotAi(vector<int>, int ChieuCaoNguoiChoi) override {
        return ChieuCaoNguoiChoi <= ChieuCaoDuongHam;
    }
};

class QuaiVat : public ChuongNgaiVat {
private:
    vector<int> SucManh;

public:
    void EnterInfo() override {
        int n;
        cout << "\nNhap 5 chi so suc manh quai vat: ";
        for (int i = 0; i < 5; i++) {
            cin >> n;
            SucManh.push_back(n);
        }
    }

    bool VuotAi(vector<int> ChiSo, int) override {
        int NguoiChoiWin = 0, QuaiVatWin = 0;

        for (size_t i = 0; i < ChiSo.size(); i++) {
            if (ChiSo[i] > SucManh[i])
                NguoiChoiWin++;
            else
                QuaiVatWin++;
        }
        return NguoiChoiWin > QuaiVatWin;
    }
};

class NguoiChoi {
private:
    vector<int> ChiSoNhay;
    vector<int> ChiSoSucManh;
    int ChieuCao;

public:
    void EnterInfo() {
        int n, m;
        cout << "\n=== NHAP THONG TIN NGUOI CHOI ===\n";
        cout << "Nhap 7 chi so suc nhay: ";
        for (int i = 0; i < 7; i++) {
            cin >> n;
            ChiSoNhay.push_back(n);
        }
        cout << "Nhap 5 chi so suc manh: ";
        for (int i = 0; i < 5; i++) {
            cin >> m;
            ChiSoSucManh.push_back(m);
        }
        do {
            cout << "Nhap chieu cao nguoi choi: ";
            cin >> ChieuCao;
        } while (ChieuCao < 0);
    }

    vector<int> getChiSoNhay() { return ChiSoNhay; }
    vector<int> getChiSoSucManh() { return ChiSoSucManh; }
    int getChieuCao() { return ChieuCao; }
};

int main() {
    int N;
    cout << "\n=== GAME VUOT CHUONG NGAI VAT ===\n";
    do {
        cout << "Nhap so luong chuong ngai vat: ";
        cin >> N;
    } while (N < 1);

    vector<ChuongNgaiVat*> v;
    for (int i = 0; i < N; i++) {
        int Type;
        do {
            cout << "\nChon loai chuong ngai vat (1: Khu Rung Chong, 2: Duong Ham Nui, 3: Quai Vat): ";
            cin >> Type;
        } while (Type < 1 || Type > 3);

        ChuongNgaiVat* Temp = nullptr;
        if (Type == 1) Temp = new KhuRungChong();
        else if (Type == 2) Temp = new DuongHamNui();
        else if (Type == 3) Temp = new QuaiVat();

        Temp->EnterInfo();
        v.push_back(Temp);
    }

    NguoiChoi Player;
    Player.EnterInfo();

    bool Win = true;
    for (ChuongNgaiVat* x : v) {
        if (dynamic_cast<KhuRungChong*>(x)) {
            if (!static_cast<KhuRungChong*>(x)->VuotAi(Player.getChiSoNhay(), 0)) {
                Win = false;
                break;
            }
        } else if (dynamic_cast<DuongHamNui*>(x)) {
            if (!static_cast<DuongHamNui*>(x)->VuotAi({0}, Player.getChieuCao())) {
                Win = false;
                break;
            }
        } else if (dynamic_cast<QuaiVat*>(x)) {
            if (!static_cast<QuaiVat*>(x)->VuotAi(Player.getChiSoSucManh(), 0)) {
                Win = false;
                break;
            }
        }
    }

    cout << "\n=== KET QUA CUOC CHOI ===\n";
    if (Win) {
        cout << "Nguoi choi tim thay kho bau!\n";
    } else {
        cout << "Nguoi choi da that bai!\n";
    }

    for (ChuongNgaiVat* x : v) {
        delete x;
    }
}
