#include <bits/stdc++.h>
using namespace std;

class OCEAN {
protected:
    string Personality, Information;
    int Score;
public:
    int GetScore() {
        return this->Score;
    }
    void SetScore(int score) {
        this->Score = score;
    }
    virtual void DisplayInformation() = 0;
    virtual ~OCEAN() {};
};

class Openness : public OCEAN {
public:
    Openness() : OCEAN() {
        Personality = "O";
        if (Score >= 70) {
            Information = "Nguoi co diem cao o yeu to nay thuong la nguoi thich nhung y tuong moi, thich hieu biet nhieu linh vuc nhung dong thoi cung thich tu do, khong thich bi rang buoc...";
        }
        else if (Score <= 30) {
            Information = "Nguoi co diem thap o yeu to nay thuong kha bao thu, kho tiep nhan nhung y tuong moi, la. Ho thich su on dinh, quen thuoc va thuc te.";
        }
        else {
            Information = "Khong xac dinh";
        }
    }
    void DisplayInformation() override {
        cout << Personality << " " << Score << " " << Information << endl;
    }
};

class Conscientiousness : public OCEAN {
public:
    Conscientiousness() : OCEAN() {
        Personality = "C";
        if (Score >= 70) {
            Information = "Nguoi co diem cao o yeu to nay thuong la nguoi cham chi, co kha nang chiu ap luc tot. Ho thuong la nguoi gan bo, trung thanh voi to chuc.";
        }
        else if (Score <= 30) {
            Information = "Nguoi co diem thap o yeu to nay thuong de bo cuoc, kha nang chiu ap luc, tuan thu ky luat cua to chuc kem.";
        }
        else {
            Information = "Khong xac dinh";
        }
    }
    void DisplayInformation() override {
        cout << Personality << " " << Score << " " << Information << endl;
    }
};

class Extraversion : public OCEAN {
public:
    Extraversion() : OCEAN() {
        Personality = "E";
        if (Score >= 70) {
            Information = "Nguoi co diem cao o yeu to nay thuong la nguoi nhiet tinh, nang dong, giao tiep tot, thich the hien ban than.";
        }
        else if (Score <= 30) {
            Information = "Nguoi co diem thap o yeu to nay thuong ngai giao tiep, khong thich su noi bat, thich duoc lam viec doc lap.";
        }
        else {
            Information = "Khong xac dinh";
        }
    }
    void DisplayInformation() override {
        cout << Personality << " " << Score << " " << Information << endl;
    }
};

class Agreeableness : public OCEAN {
public:
    Agreeableness() : OCEAN() {
        Personality = "A";
        if (Score >= 70) {
            Information = "Nguoi co diem cao o yeu to nay thuong than thien, coi mo, dong cam voi moi nguoi nhung nhieu khi thieu chinh kien.";
        }
        else if (Score <= 30) {
            Information = "Nguoi co diem thap thuong dat loi ich cua ban than len tren, it dong cam, chia se voi dong nghiep, co tinh canh tranh cao.";
        }
        else {
            Information = "Khong xac dinh";
        }
    }
    void DisplayInformation() override {
        cout << Personality << " " << Score << " " << Information << endl;
    }
};

class Neuroticism : public OCEAN {
public:
    Neuroticism() : OCEAN() {
        Personality = "N";
        if (Score >= 70) {
            Information = "Nguoi co diem cao o yeu to nay thuong co cac cam xuc tieu cuc nhu: lo lang, buc boi, tu ti, yeu duoi va kha nang chiu ap luc kem.";
        }
        else if (Score <= 30) {
            Information = "Nguoi co diem thap o yeu to nay thuong kiem soat duoc cam xuc, ung pho voi cang thang tot, it bi ben ngoai anh huong den tam trang cua ban than.";
        }
        else {
            Information = "Khong xac dinh";
        }
    }
    void DisplayInformation() override {
        cout << Personality << " " << Score << " " << Information << endl;
    }
};

void ExtractScore(string input, OCEAN*& temp, int position) {
    string scoreStr = "";
    for (size_t i = position; i < input.size(); i++) {
        if (isdigit(input[i])) {
            scoreStr += input[i];
        }
        else {
            break;
        }
    }
    temp->SetScore(stoi(scoreStr));
}

class Person {
private:
    vector<OCEAN*> Personalities;
public:
    void InputInformation() {
        string temporary;
        getline(cin, temporary);
        OCEAN* temp = nullptr;
        for (int i = 1; i <= 17; i += 4) {
            if (i == 1) {
                temp = new Openness();
                ExtractScore(temporary, temp, i);
            }
            else if (i == 5) {
                temp = new Conscientiousness();
                ExtractScore(temporary, temp, i);
            }
            else if (i == 9) {
                temp = new Extraversion();
                ExtractScore(temporary, temp, i);
            }
            else if (i == 13) {
                temp = new Agreeableness();
                ExtractScore(temporary, temp, i);
            }
            else if (i == 17) {
                temp = new Neuroticism();
                ExtractScore(temporary, temp, i);
            }
            else {
                break;
            }
            Personalities.push_back(temp);
        }
    }
    void DisplayInformation() {
        for (OCEAN* index : Personalities) {
            index->DisplayInformation();
        }
    }
    bool CheckStability() {
        bool unstable = false;
        for (OCEAN* temp : Personalities) {
            if (dynamic_cast<Conscientiousness*>(temp) && static_cast<Conscientiousness*>(temp)->GetScore() <= 30) {
                unstable = true;
            }
            if (dynamic_cast<Neuroticism*>(temp) && static_cast<Neuroticism*>(temp)->GetScore() >= 70) {
                unstable = true;
            }
        }
        return unstable;
    }
    ~Person(){
        for(OCEAN* x : Personalities){
            delete x;
        }
    }
};

int main() {
    cout << "Nhap vao thong tin ket qua danh gia tam ly cua mot nguoi.\n";
    Person person;
    person.InputInformation();
    person.DisplayInformation();
    cout << "Nhap vao ket qua danh gia tam ly cua n nguoi trong danh sach.\n";
    int quantity;
    cin >> quantity;
    cin.ignore();
    vector<Person> persons;
    for (int i = 0; i < quantity; i++) {
        Person temp;
        temp.InputInformation();
        persons.push_back(temp);
    }
    cout << "Chon mot nguoi trong danh sach va cho biet cac thong tin ve tinh cach cua nguoi do." << "0 - " << quantity - 1 << endl;
    int index;
    cin >> index;
    cin.ignore();
    persons[index].DisplayInformation();
    cout << "Nhung nguoi nguy co cao ma nha tuyen dung/ to chuc/ doanh nghiep can luu y la:\n";
    for (Person person : persons) {
        if (person.CheckStability()) {
            person.DisplayInformation();
        }
    }
}