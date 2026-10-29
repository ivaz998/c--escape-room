#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

struct Soba {
    int broj;
    string opis;
};

struct Zagonetka{
    int broj;
    string pitanje;
    string A;
    string B;
    string C;
    string D;
    char tocno;
};
int main()
{  Soba sobe[10];
    Zagonetka zagonetke[10];

    ifstream datSobe("sobe.txt");
    ifstream datZagonetke("zagonetke.txt");

    if(!datSobe){
        cout<<"Ne mogu otvoriti sobe.txt"<<endl;
        return 1;
    }
    if (!datZagonetke){
        cout << "Ne mogu otvoriti zagonetke.txt" << endl;
        return 1;
    }
    string red;

    for (int i=0; i<10;i++) {
        getline(datSobe,red);
        sobe[i].broj=stoi(red);

        getline(datSobe,sobe[i].opis);
    }

    for (int i=0;i<10;i++) {

        getline(datZagonetke,red);
    zagonetke[i].broj=stoi(red);

    getline(datZagonetke,zagonetke[i].pitanje,';');
    getline(datZagonetke,zagonetke[i].A,';');
    getline(datZagonetke,zagonetke[i].B,';');
    getline(datZagonetke,zagonetke[i].C,';');
    getline(datZagonetke,zagonetke[i].D,';');

    getline(datZagonetke,red,';');
    zagonetke[i].tocno=red[0];

    getline(datZagonetke,red);
    }

    datSobe.close();
    datZagonetke.close();

    string ime;

    cout<<"TENIS ESCAPE ROOM"<<endl;
    cout << "Unesite svoje ime: ";
    getline(cin,ime);

    int tocni=0;
    int pokusaji=0;

    bool odustao=false;

    auto pocetakVrijeme=chrono::steady_clock::now();

    for (int i=0;i<10;i++) {

        cout<<endl;
        cout<<"----------------------------------"<<endl;
        cout<<"SOBA "<<sobe[i].broj<<endl;
        cout<<sobe[i].opis<<endl;

        cout<<endl;

        cout<<zagonetke[i].pitanje<<endl;
        cout<<zagonetke[i].A<<endl;
        cout<<zagonetke[i].B<<endl;
        cout<<zagonetke[i].C<<endl;
        cout<<zagonetke[i].D<<endl;

        char odgovor;
        bool tocnoOdgovoreno=false;

        while(!tocnoOdgovoreno) {
            cout<<"Odgovor (A/B/C/D) ili O za odustajanje: ";
            cin>>odgovor;

            odgovor=toupper(odgovor);

            if(odgovor=='O'){
                odustao=true;
                break;
            }

            pokusaji++;

            if(odgovor==zagonetke[i].tocno){
                cout<<"Tocno! Idete dalje."<<endl;

                tocni++;
                tocnoOdgovoreno=true;
            }
            else{
                cout<<"Netocno! Pokusajte ponovno."<<endl;
            }
        }
        if(odustao){
            break;
        }
    }

    auto krajVrijeme = chrono::steady_clock::now();
    int trajanje=
        chrono::duration_cast<chrono::seconds>
        (krajVrijeme-pocetakVrijeme).count();

    int minute=trajanje/60;
    int sekunde=trajanje%60;

    string status;

    cout<<endl;
    cout<<"----------------------------------"<<endl;

    if(odustao){
        status="Igra prekinuta";
        cout<<"Odustali ste od igre."<<endl;
    }
    else{
        status="Pobjeda";
        cout << "Cestitam! Pobjegli ste iz escape rooma!" << endl;
    }

    cout<<"Tocni odgovori: "<<tocni<<"/10"<<endl;
    cout<<"Broj pokusaja: "<<pokusaji<<endl;
    cout<<"Trajanje: "
         <<minute<<" min "
         <<sekunde<<" s"<<endl;

    ofstream rezultati("rezultati.txt",ios::app);

    if(!rezultati){

        cout<<"Ne mogu otvoriti rezultati.txt"<<endl;
        return 1;
    }

    rezultati<<ime<<"; "
               <<tocni<<"/10 tocnih; "
               <<status<< "; "
               <<"Trajanje: "
               <<minute<< " min "
               <<sekunde<< " s; "
               <<"Pokusaji: "
               <<pokusaji
               <<endl;

    rezultati.close();

    cout<<"Rezultat spremljen u rezultati.txt"<<endl;

    return 0;
}
