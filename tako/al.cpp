#include <iostream>
#include <cstdio>
#include <cstdlib> // dla malloc i free
#include <cstring> // dla operacji na stringach

using namespace std;

struct Autobus {
    char rejestracja[31];
    char marka[31];
    int dystans;
    int max_pasazerow;
    double zuzycie_paliwa;
};

int main() {
    char nazwa_pliku[50];

    // wczytaj nazwę pliku z danymi od użytkownika
    cout << "Podaj nazwe pliku z danymi: ";
    cin >> nazwa_pliku;

    FILE* plik_we = fopen(nazwa_pliku, "r"); // otwórz plik do odczytu
    if (plik_we == NULL) { // sprawdź, czy plik istnieje
        cout << "blad" << endl;
        return 1;
    }

    int n;
    fscanf(plik_we, "%d", &n); // wczytaj liczbę autobusów
    
    // dynamiczna alokacja pamięci dla tablicy autobusów, - n structów Autobus
    Autobus* autobusy = (Autobus*)malloc(n * sizeof(Autobus));
    // wczytaj dane każdego autobusu z pliku
    for (int i = 0; i < n; i++) {
        
        fscanf(plik_we, "%s %s %d %d %lf", autobusy[i].rejestracja, autobusy[i].marka, // zeby odczytac double zawsze %lf
               &autobusy[i].dystans, &autobusy[i].max_pasazerow, &autobusy[i].zuzycie_paliwa);
    }
    fclose(plik_we); // zamknij plik wejściowy
    
    // otwórz plik "duze.txt" do zapisu
    FILE* plik_duze = fopen("duze.txt", "w");
    for (int i = 0; i < n; ++i) {
        // jeśli autobus ma przynajmniej 40 miejsc, zapisz jego dane
        if (autobusy[i].max_pasazerow >= 40) {
            // 48 to 0 w ASCII, a 57 to 9 w ASCII
            int s3 = int(autobusy[i].rejestracja[2]); // 3ci znak w rejestracji w ASCII
            int s2 = int(autobusy[i].rejestracja[1]); // 2gi znak w rejestracji w ASCII
            if(s2 > 47 && s2 < 58){ 
                fprintf(plik_duze, "%s %d %lf %.1s\n", autobusy[i].marka, autobusy[i].max_pasazerow, // jezeli 2gi znak rejestracji to cyfra, wypisz 1wszy znak
                        autobusy[i].zuzycie_paliwa, autobusy[i].rejestracja);
            }
            else{
                if(s3 > 47 && s3 < 58){
                    fprintf(plik_duze, "%s %d %lf %.2s\n", autobusy[i].marka, autobusy[i].max_pasazerow, // jezeli 3ci znak rejestracji to cyfra, wypisz 2 pierwsze znaki
                        autobusy[i].zuzycie_paliwa, autobusy[i].rejestracja);
                }
                else{
                    fprintf(plik_duze, "%s %d %lf %.3s\n", autobusy[i].marka, autobusy[i].max_pasazerow, // jezeli 3ci symbol rejestracji nie jest cyfra, wypisz 3 pierwsze symbole
                        autobusy[i].zuzycie_paliwa, autobusy[i].rejestracja);
                }
            }
        }
    }
    fclose(plik_duze); // zamknij plik "duze.txt"

    // otwórz plik "zuzyte.txt" do zapisu
    FILE* plik_zuzyte = fopen("zuzyte.txt", "w");
    for (int i = 0; i < n; ++i) {
        // jeśli autobus przejechał ponad milion km i zużywa więcej niż 20 litrów paliwa
        if (autobusy[i].dystans > 1000000 && autobusy[i].zuzycie_paliwa > 20) {
            fprintf(plik_zuzyte, "%s %f %d\n", autobusy[i].rejestracja, autobusy[i].zuzycie_paliwa, autobusy[i].dystans);
        }
    }
    fclose(plik_zuzyte); // zamknij plik "zuzyte.txt"

    free(autobusy); // zwolnij pamięć zajmowana przez tablice autobusów
    return 0;
}
