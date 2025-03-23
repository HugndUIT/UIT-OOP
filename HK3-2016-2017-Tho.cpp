#include <bits/stdc++.h>
using namespace std;

class Poem {
    protected:
        vector<string> PoemLines; int LineCount;
    public:
        int GetLineCount(){
            return this->LineCount;
        }
        virtual bool CheckSyllableCount() = 0;
        virtual void EnterInfo() = 0;
        virtual void DisplayInfo() = 0;
        virtual ~Poem(){}
};

class LucBatPoem : public Poem {
    public:
        bool CheckSyllableCount() override {
            vector<int> SyllablesPerLine;
            if(LineCount % 2 != 0){
                return false; 
            }
            for(string Line : PoemLines){
                stringstream ss(Line);
                string Word;
                int SyllableCount = 0;
                while(ss >> Word){
                    SyllableCount++;
                }
                SyllablesPerLine.push_back(SyllableCount);
            }
            for(size_t i = 0; i < SyllablesPerLine.size(); i += 2){
                if(!(SyllablesPerLine[i] == 6 && SyllablesPerLine[i + 1] == 8)){
                    return false; 
                }
            }
            return true;
        }

        void EnterInfo() override {
            cout << "Nhap bai tho luc bat (go STOP de dung):\n";
            LineCount = 0; 
            while (true) {
                string Temporary;
                getline(cin, Temporary);
                if (Temporary == "STOP") break;
                PoemLines.push_back(Temporary);
                LineCount++; 
            }
        }

        void DisplayInfo() override {
            cout << "\n---- Bai tho Luc Bat ----\n";
            for(string Temporary : PoemLines){
                cout << Temporary << endl;
            }
        }
};

class SongThatLucBatPoem : public Poem {
    public:
        bool CheckSyllableCount() override {
            if(LineCount % 4 != 0){
                return false; 
            }
            vector<int> SyllablesPerLine;
            for(string Line : PoemLines){
                stringstream ss(Line);
                string Word;
                int SyllableCount = 0;
                while(ss >> Word){
                    SyllableCount++;
                }
                SyllablesPerLine.push_back(SyllableCount);
            }
            for(size_t i = 0; i < SyllablesPerLine.size(); i += 4){
                if(!(SyllablesPerLine[i] == 7 && 
                     SyllablesPerLine[i + 1] == 7 && 
                     SyllablesPerLine[i + 2] == 6 && 
                     SyllablesPerLine[i + 3] == 8)){
                    return false; 
                }
            }
            return true;
        }

        void EnterInfo() override {
            cout << "Nhap bai tho song that luc bat (go STOP de dung):\n";
            LineCount = 0; 
            while (true) {
                string Temporary;
                getline(cin, Temporary);
                if (Temporary == "STOP") break;
                PoemLines.push_back(Temporary);
                LineCount++; 
            }
        }

        void DisplayInfo() override {
            cout << "\n---- Bai tho Song That Luc Bat ----\n";
            for(string Temporary : PoemLines){
                cout << Temporary << endl;
            }
        }
};

class DuongLuatThatNgonBatCuPoem : public Poem {
    public:
        bool CheckSyllableCount() override {
            if(LineCount != 8){
                return false; 
            }
            vector<int> SyllablesPerLine;
            for(string Line : PoemLines){
                stringstream ss(Line);
                string Word;
                int SyllableCount = 0;
                while(ss >> Word){
                    SyllableCount++;
                }
                SyllablesPerLine.push_back(SyllableCount);
            }
            for(size_t i = 0; i < SyllablesPerLine.size(); i++){
                if(!(SyllablesPerLine[i] == 7)){
                    return false; 
                }
            }
            return true;
        }

        void EnterInfo() override {
            cout << "Nhap bai tho Duong Luat That Ngon Bat Cu (go STOP de dung):\n";
            LineCount = 0; 
            while (true) {
                string Temporary;
                getline(cin, Temporary);
                if (Temporary == "STOP") break;
                PoemLines.push_back(Temporary);
                LineCount++; 
            }
        } 

        void DisplayInfo() override {
            cout << "\n---- Bai tho Duong Luat That Ngon Bat Cu ----\n";
            for(string Temporary : PoemLines){
                cout << Temporary << endl;
            }
        }
};

int main(){
    vector<Poem*> Poems;
    int Quantity;
    cout << "Nhap so luong bai tho: ";
    cin >> Quantity;
    cin.ignore();
    for(int i = 0; i<Quantity; i++){
        int Type;
        Poem* Temporary = nullptr;
        cout << "1 - Luc Bat\n"; 
        cout << "2 - Song That Luc Bat\n";
        cout << "3 - Duong Luat That Ngon Bat Cu\n";
        cout << "Chon the loai tho: ";
        cin >> Type;
        cin.ignore();
        if(Type == 1){
            Temporary = new LucBatPoem();
        }
        else if(Type == 2){
            Temporary = new SongThatLucBatPoem();
        }
        else if(Type == 3){
            Temporary = new DuongLuatThatNgonBatCuPoem();
        }
        else{
            cout << "The loai khong hop le!\n";
            break;
        }
        Temporary->EnterInfo();
        Poems.push_back(Temporary);
    }
    int MaxLines = 0;
    cout << "\n================== Cac bai tho ==================\n";
    for(Poem* Temporary : Poems){
        if(Temporary->GetLineCount() > MaxLines){
            MaxLines = Temporary->GetLineCount();
        }
        Temporary->DisplayInfo();
    }
    cout << "\nBai tho nhieu dong nhat: " << MaxLines << " dong\n";
    cout << "\n=============== Kiem tra bai tho ===============\n";
    for(Poem* Temporary : Poems){
        bool IsValid = Temporary->CheckSyllableCount();
        cout << (IsValid ? "Bai tho hop le\n" : "Bai tho khong hop le\n");
    }
    for (Poem* TempPoem : Poems){
        delete TempPoem;
    }
}