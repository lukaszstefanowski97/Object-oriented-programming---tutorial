#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
// hermetyzacja - public, private, protected
// private - tylko w obrębie klasy
// protected - pola i metody w obrębie klasy oraz klas pochodnych (wtedy stają się private w klasie pochodnej)
// virtual - trzeba zdefiniować metodę w klasie pochodnej
// przeciążenie - dopisanie czegoś do istniejącej metody
// sterta - operator new double; - alokuje na stercie miejsce na liczbe typu double
// stos = [a()| ]
// void a()
//{
//    b();
//
//}
//
//void b()
//{
//    int zmienna;
//    int *zmienna2 = new int;
//}


//Filar I - Hermetyzacja
// dzielenie pól alokowanych dynamicznie i kontrola ich zwalniania za pomocą pól statycznych.

using namespace std;
class Figura{
public:
    static bool isAnyCreated;
    virtual double pole() = 0;
    virtual double obwod() = 0;
    virtual void wyswietlTyp() = 0;
protected:
private:
};


bool Figura::isAnyCreated = false;

class Prostokat: public Figura{
public:

    //zabezpieczenie na wypadek jakby nie podano parametrów
    Prostokat() {

    }// = delete;

    Prostokat(double a, double b) {
        isAnyCreated = true;
        this->a = new double(a);
        this->b = new double(b);
        cout << "Obiekt prostokat zostal utworzony" << endl;
    }
    Prostokat(string a, string b){
        isAnyCreated = true;
        this->a = new double;
        this->b = new double;
//stos
        stringstream ss;
        ss << a << b;
        ss >> *(this->a) >> *(this->b);
        cout << "Obiekt prostokat (string) zostal utworzony" << endl;
    }

    // konstruktor kopiujący
    Prostokat(const Prostokat & copy){
        this->a = new double;
        this->b = new double;
        *(this->a) = *(copy.a);
        *(this->b) = *(copy.b);

    }

    ~Prostokat(){
        delete a;
        delete b;
        cout << "Obiekt prostokat zostal usuniety" << endl;
    }
    double pole() {
        return *a * *b;
    }
    double obwod(){
      return *a*2+*b*2;
    }

    double getA(){
        return *a;
    }

    static void printType(){
        cout << "Jestem metoda statyczna" << endl;
    }

    void wyswietlTyp(){
        cout << "Jestem prostokatem" << endl;
    }


    void setA(double a){
        //przypisuję a do boku prostokąta
        *(this->a) = a;
    }

    double getB(){
        return *b;
    }

    void setB(double b){
        *(this->b) = b;
    }

    virtual void rysuj()
    {
        cout << "Rysuje prostokat" << endl;
    }
protected:
    double *a, *b;
private:
};

class Kwadrat: public Prostokat{
    public:

        Kwadrat(double a){
            this->a = new double(a);
            this->b = new double(a);
        }

        ~Kwadrat()
        {
            delete a;
            delete b;
        }

        void rysuj()
        {
            cout << "Rysuje kwadrat"  << endl;
        }

        void wyrownajBoki(){
            *b=*a;
        }

        void wyswietlTyp(){
        cout << "Jestem kwadratem" << endl;
        }
    protected:

    private:
};

class Kolo: public Figura{
public:
    Kolo() = delete;

    Kolo(double r) {
        this->r = new double(r);

    }
    Kolo(string r){
        this->r = new double;

        stringstream ss;
        ss << r;
        ss >> *(this->r);
    }
    //destruktor
    ~Kolo(){
        delete r;
        cout << "Obiekt kolo zostal usuniety" << endl;
    }
    double pole(){
        return pi**r**r;
    };
    double obwod(){
        return 2*pi**r;
    };
    void wyswietlTyp(){
        cout << "Jestem kolem" << endl;
    }
protected:
private:
    double *r;
    double pi=3.14;
};

class Trojkat: public Figura{
public:
    Trojkat() = delete;

    Trojkat(double a, double  b, double  c) {
        this->a = new double(a);
        this->b = new double(b);
        this->c = new double(c);

    }
    Trojkat(string a, string b, string c){
        this->a = new double;
        this->b = new double;
        this->c = new double;

        stringstream ss;
        ss << a << b << c;
        ss >> *(this->a) >> *(this->b) >> *(this->c);
    }
    //destruktor
    ~Trojkat(){
        delete a;
        delete b;
        delete c;
        cout << "Obiekt trojkat zostal usuniety" << endl;
    }
    //zmienić wzór pola na nie wymagający wysokości
    double pole() {
        return sqrt(((*a+*b+*c)/2)*(((*a+*b+*c)/2)-*a)*(((*a+*b+*c)/2)-*b)*(((*a+*b+*c)/2)-*c));
    }
    double obwod(){
        vector<double>boki;
        boki.push_back(*a);
        boki.push_back(*b);
        boki.push_back(*c);
        sort(boki.begin(), boki.end());
        if ((boki[0]+boki[1]) < boki[2]){
            throw string("Trojkjat nie istnieje");
        }
        return *a+*b+*c;
    }

    void wyswietlTyp(){
        cout << "Jestem trojkatem" << endl;
    }

protected:
private:
    double *a, *b, *c;
};



int main() {
    cout << "isAnyCreated? = " << Prostokat::isAnyCreated << endl;
    Prostokat::printType();


//    Figura *p2 = new Kwadrat(1);
//    p2->rysuj();
//
//    delete p2;
//    p2 = new Trojkat(1,2,3);
//    p2->rysuj();

    //dynamiczna tablica, automatycznie się dostosowuje ilość elementów
    vector <Figura *> figury;
    try {
        figury.push_back(new Prostokat(2,4));
        figury.push_back(new Kwadrat(3));
        figury.push_back(new Trojkat(1,2,12));
        figury.push_back(new Kolo(3));
        cout << "Wesolych swiat!" << endl;
    }
    catch (bad_alloc &ob)
    {
        cout << "Blad: " << ob.what() << endl;
    }



    for (int i=0; i<figury.size(); i++) {
            try {

                    figury[i]->wyswietlTyp();
                    cout << "Pole: " << figury[i]->pole() << endl;
                    cout << "Obwod: " << figury[i]->obwod() << endl;
                    cout << "isAnyCreated? = " << Figura::isAnyCreated << endl;
                }
            catch(string &s)
                {
                    cout << "Blad: " << s << endl;
                }
        }


    Prostokat p(2, 4);
    cout << "Pole prostokata: " << p.pole() << endl;
    cout << "Obwod prostokata: " << p.obwod() << endl;


    Prostokat p2(p);
    cout << "Pole skopiowanego prostokata: " << p2.pole() << endl;
    cout << "Obwod skopiowanego prostokata: " << p2.obwod() << endl;
    p2.setA(3);
    p2.setB(6);
    cout << "Pole skopiowanego i zmienionego prostokata: " << p2.getA()*p2.getB() << endl;
    cout << "Obwod skopiowanego i zmienionego prostokata: " << 2*p2.getA() + 2*p2.getB() << endl;



    return 0;
}