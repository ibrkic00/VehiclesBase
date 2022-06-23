#include <iostream>
#include "baza.h"


double vozilo::budzet = 1000000;
std::vector<vozilo*> vozilo::vozila;

int main(void) {

    std::cout << "Stvaranje helikoptera s parametrom, aviona bez parametra i poziv funkcije brojAktivnihVozila:" << std::endl << std::endl;
    helikopter* a = new helikopter(1000, 1143000, 3, "vozA", 10, "Motor1", "Model helikoptera 1", 1000, 10);
    avion* b = new avion();
    std::cout << vozilo::brojAktivnihVozila() << std::endl << std::endl;

    std::cout << "Pozivanje destruktora, stvaranje još 2 helikoptera i jednog aviona te poziv funkcija brojAktivnihVozila i brojPredOtpisom:" << std::endl << std::endl;
    delete b;
    helikopter* c = new helikopter();
    avion* d = new avion(9500, 8799000, 3, "vozB", 10, "Motor2", "Model aviona 1", 1000);


    helikopter* e = new helikopter(1000, 0, 0, "xx", 10, "Motor1", "Model helikoptera 1", 1000, 10);
    std::cout << vozilo::brojAktivnihVozila() << std::endl;
    std::cout << "Broj pred otpisom: " << vozilo::brojPredOtpisom() << std::endl << std::endl;



    std::cout << "Stvaranje novog helikoptera te testiranje funkcija trosakPuta, zarada i novcanoStanje" << std::endl << std::endl;
    helikopter* f = new helikopter(1000, 0, 0, "vozC", 0, "Motor1", "Model helikoptera 2", 1000, 5);
    std::cout << f->trosakPuta(100000, 6, 500) << std::endl; //broj osoba > max
    std::cout << f->trosakPuta(10, 5, 1001) << std::endl; //teret veci > max
    double tr = f->trosakPuta(200, 5, 1000);
    std::cout << "Trosak puta: " << tr << std::endl;
    std::cout << "Budzet: " << f->budzet << std::endl;
    std::cout << "Novcano stanje: " << f->novcanoStanje() << std::endl << std::endl;
    long double z = 0.0;
    if (tr) {
        z = f->zarada(200, 1000);
        std::cout << "Zarada od puta: " << z << std::endl;

        std::cout << "Budzet-zarada: " << a->budzet - z << std::endl;
        std::cout << "Novcano stanje: " << vozilo::novcanoStanje() << std::endl;
        std::cout << "Budzet: " << vozilo::budzet << std::endl << std::endl;//dobro jer se poslije troska mora prizbrojit zarada
    }



    std::cout << "Stvaranje novog aviona i helikoptera koji bi se trebali otpisati, te poziv funkcija otpisi i brojAktivnihVozila" << std::endl << std::endl;
    avion* g = new avion(9500, 8800000, 3, "vozD", 10, "Motor2", "Model aviona 2", 1000);
    helikopter* h = new helikopter(9500, 1144000, 3, "vozE", 10, "Motor2", "Model aviona 2", 1000, 3);
    std::cout << vozilo::brojAktivnihVozila() << std::endl;
    avion::otpisi();
    std::cout << vozilo::brojAktivnihVozila() << std::endl;
    avion::otpisi();
    std::cout << vozilo::brojAktivnihVozila() << std::endl << std::endl;


    std::cout << "Testiranje funkcije ispisAktivnih vozila, poziv copy-konstruktora te poziv funkcije usporedi:" << std::endl << std::endl;
    vozilo::ispisAktivnihVozila();


    helikopter* r1 = new helikopter(*c);
    std::cout << vozilo::usporedi(*r1) << std::endl;
    avion* i = new avion();
    avion* r2 = new avion(*i);
    std::cout << vozilo::usporedi(*r2) << std::endl;
    vozilo::ispisAktivnihVozila();
    std::cout << std::endl << std::endl;

    std::cout << "Brisanje svih vozila i poziv funkcije brojAktivnihVozila:" << std::endl << std::endl;
    delete a;
    delete c;
    delete d;
    delete e;
    delete f;
    delete i;
    delete r1;
    delete r2;
    std::cout << vozilo::brojAktivnihVozila() << std::endl << std::endl;


    std::cout << "Testiranje funkcije koja dodjeljuje jedinstvene oznake vozilima:" << std::endl << std::endl;
    helikopter* a2;
    a2 = new helikopter();
    helikopter* b2 = new helikopter(*a2);
    c = new helikopter(9500, 120, 0, "vozA", 0, "R-2800-54", "Sikorsky CH-37 Mojave", 1000, 10);
    helikopter* d1 = new helikopter();
    e = new helikopter(9500, 120, 0, "voz5", 0, "R-2800-54", "Sikorsky CH-37 Mojave", 1000, 10);
    delete b2;
    delete d1;
    helikopter* z2 = new helikopter();
    b2 = new helikopter();
    d1 = new helikopter();
    helikopter* f1 = new helikopter();
    std::cout << std::endl << std::endl;


    std::cout << "Brisanje svih vozila:" << std::endl << std::endl;
    delete a2;
    delete b2;
    delete c;
    delete d1;
    delete e;
    delete f1;
    delete z2;
    std::cout << vozilo::brojAktivnihVozila() << std::endl;
    std::cout << std::endl;
    std::cout << "Testiranje funkcije ispitajPoslove:" << std::endl << std::endl;
    std::vector<int> put = { 10,20,30,40,50 };
    std::vector<int> osobe = { 2,3,4,5,6 };
    std::vector<int> tereti = { 1000,500,500,200,1000 };

    std::vector <int>& duljinePuteva = put;
    std::vector <int>& brojOsoba = osobe;
    std::vector <int>& teret = tereti;



    avion* x = new avion(); //on sigurno ne moze izvrsit jer ne moze prevozit putnike
    helikopter* y = new helikopter(1000, 120, 0, "vozY", 0, "R-2800-54", "Sikorsky CH-37 Mojave", 1000, 3); //max broj putnika je 3, neæe moæ;
    helikopter* t = new helikopter(1000, 120, 0, "vozT", 0, "R-2800-54", "Sikorsky CH-37 Mojave", 1, 10); // max teret je 1, neæe moæ;
    helikopter* q = new helikopter(1000, 120, 0, "vozQ", 0, "R-2800-54", "Sikorsky CH-37 Mojave", 10000, 10); // trebao bi moc;
    std::cout << vozilo::ispitajPoslove(duljinePuteva, brojOsoba, teret) << std::endl << std::endl;
    return 0;

}