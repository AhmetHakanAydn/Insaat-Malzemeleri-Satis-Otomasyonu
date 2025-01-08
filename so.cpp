#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Malzeme {
private:
    int id;
    string ad;
    double fiyat;
    int stok;

public:
    Malzeme(int _id, const string& _ad, double _fiyat, int _stok)
        : id(_id), ad(_ad), fiyat(_fiyat), stok(_stok) {}

    int getId() const { return id; }
    string getAd() const { return ad; }
    double getFiyat() const { return fiyat; }
    int getStok() const { return stok; }

    void setAd(const string& _ad) { ad = _ad; }
    void setFiyat(double _fiyat) { fiyat = _fiyat; }
    void setStok(int _stok) { stok = _stok; }
};

class Otomasyon {
private:
    vector<Malzeme> malzemeler;
    int sonId;

public:
    Otomasyon() : sonId(0) {}

    void malzemeEkle() {
        string ad;
        double fiyat;
        int stok;

        cout << "Malzeme Adi: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        getline(cin, ad);

        cout << "Fiyat: ";
        cin >> fiyat;

        cout << "Stok: ";
        cin >> stok;

        sonId++;
        Malzeme yeniMalzeme(sonId, ad, fiyat, stok);
        malzemeler.push_back(yeniMalzeme);

        cout << "Malzeme eklendi! (ID = " << sonId << ")" << endl;
    }

    void malzemeleriListele() {
        if (malzemeler.empty()) {
            cout << "Liste bos." << endl;
            return;
        }

        cout << "\n--- Mevcut Malzemeler ---\n";

        for (size_t i = 0; i < malzemeler.size(); i++) {
            cout << "ID: " << malzemeler[i].getId() 
                 << " | Ad: " << malzemeler[i].getAd()
                 << " | Fiyat: " << malzemeler[i].getFiyat() 
                 << " | Stok: " << malzemeler[i].getStok() 
                 << endl;
        }
        cout << "--------------------------\n" << endl;
    }

    void malzemeGuncelle() {
        int arananId;
        cout << "Guncellenecek malzemenin ID'si: ";
        cin >> arananId;

        bool bulundu = false;
        for (size_t i = 0; i < malzemeler.size(); i++) {
            if (malzemeler[i].getId() == arananId) {
                bulundu = true;
                cout << "Malzeme Adi (Guncellemek istemiyorsaniz ayni degeri girin): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string yeniAd;
                getline(cin, yeniAd);
                if (!yeniAd.empty()) {
                    malzemeler[i].setAd(yeniAd);
                }

                cout << "Yeni Fiyat (0 girerseniz degismez): ";
                double yeniFiyat;
                cin >> yeniFiyat;
                if (yeniFiyat != 0) {
                    malzemeler[i].setFiyat(yeniFiyat);
                }

                cout << "Yeni Stok (0 girerseniz degismez): ";
                int yeniStok;
                cin >> yeniStok;
                if (yeniStok != 0) {
                    malzemeler[i].setStok(yeniStok);
                }

                cout << "Malzeme güncellendi!\n";
                break;
            }
        }
        if (!bulundu) {
            cout << "Aranan ID (" << arananId << ") bulunamadi!\n";
        }
    }

    void malzemeSil() {
        int arananId;
        cout << "Silinecek malzemenin ID'si: ";
        cin >> arananId;

        for (size_t i = 0; i < malzemeler.size(); i++) {
            if (malzemeler[i].getId() == arananId) {
                malzemeler.erase(malzemeler.begin() + i);
                cout << "Malzeme silindi.\n";
                return;
            }
        }
        cout << "Aranan ID (" << arananId << ") bulunamadi!\n";
    }

    void satisYap() {
        int arananId;
        cout << "Satilacak malzemenin ID'si: ";
        cin >> arananId;

        int adet;
        cout << "Satilacak miktar: ";
        cin >> adet;

        for (size_t i = 0; i < malzemeler.size(); i++) {
            if (malzemeler[i].getId() == arananId) {
                if (malzemeler[i].getStok() >= adet) {
                    double toplamFiyat = malzemeler[i].getFiyat() * adet;
                    malzemeler[i].setStok(malzemeler[i].getStok() - adet);

                    cout << "Satis basarili!\n";
                    cout << "Toplam Fiyat: " << toplamFiyat << endl;
                    cout << "Kalan Stok: " << malzemeler[i].getStok() << endl;
                } else {
                    cout << "Yeterli stok yok! Mevcut stok: " 
                         << malzemeler[i].getStok() << endl;
                }
                return;
            }
        }
        cout << "Aranan ID (" << arananId << ") bulunamadi!\n";
    }
};

int main() {
    Otomasyon otomasyon;
    int secim;

    while (true) {
        cout << "\n--- Insaat Malzemeleri Satis Otomasyonu ---\n";
        cout << "1. Malzeme Ekle\n";
        cout << "2. Malzemeleri Listele\n";
        cout << "3. Malzeme Guncelle\n";
        cout << "4. Malzeme Sil\n";
        cout << "5. Satis Yap\n";
        cout << "6. Cikis\n";
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
        case 1:
            otomasyon.malzemeEkle();
            break;
        case 2:
            otomasyon.malzemeleriListele();
            break;
        case 3:
            otomasyon.malzemeGuncelle();
            break;
        case 4:
            otomasyon.malzemeSil();
            break;
        case 5:
            otomasyon.satisYap();
            break;
        case 6:
            cout << "Programdan cikiliyor...\n";
            return 0;
        default:
            cout << "Gecersiz secim! Yeniden deneyin.\n";
            break;
        }
    }
    return 0;
}

