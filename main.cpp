/*
DIPARTIMENTO DI INGEGNERIA DELL'INFORMAZIONE - UNIVPM
Corso di Laurea in Ingegneria Informatica e dell'Automazione
Progetto del Corso di "Algoritmi e strutture dati" - Prof.ssa Giuseppa Ribighini

Giugno 2015 - Nicola Fioranelli

Il programma consente di calcolare l'integrale di Riemann servendosi dei tre metodi
conosciuti, dando inoltre la possibilità di valutare precisione e iterazioni dei vari
algoritmi presi in considerazione
*/

#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

double rettangoli(double a, double b, int n, double eps, int t, int test);
double trapezi(double a, double b, int n, double eps, int t, int test);
double simpson(double a, double b, int n, double eps, int t, int test);
double funzione(int t, double d);

int main()
{
    double A, B, EPS;
    int T, TEST;
    // la prima parte del main è dedicata all'acquisizione delle variabili globali

    cout << "Benvenuto/a nel programma del calcolo integrale" << endl;
    cout << "Inserisci il primo estremo: ";
    cin >> A;
    cout << "Inserisci il secondo estremo: ";
    cin >> B;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << "Scegli la funzione:" << endl;
    cout << " 1) Integrale di sin(x)" << endl;
    cout << " 2) Integrale di x*e^(-x)*cos(2x)" << endl;
    cout << " 3) Integrale di 1/(1+x^2)" << endl;
    cout << " 4) Integrale di x^5/2" << endl;
    cout << " 5) Integrale di x*sin(x)" << endl;
    cout << " 6) Integrale di e(-x^2)" << endl;
    cout << " 7) Integrale di x^2" << endl;
    cout << " 8) Integrale di e^x" << endl;
    cout << " 9) Integrale di sin(1/x)" << endl;
    cout << "Per uscire dal programma puoi inserire 0 nel numero di sottointervalli..." << endl;
    cout << "-->";

    do {

    cin >> T;

    if (T!=1 && T!=2 && T!=3 && T!=4 && T!=5 && T!=6 && T!=7 && T!=8 && T!=9){
        cout << "! Valore errato, inserisci -->";
        }

    } while(T!=1 && T!=2 && T!=3 && T!=4 && T!=5 && T!=6 && T!=7 && T!=8 && T!=9);

    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;

    /*
    Il test permette di proseguire in due diversi modi:
    - il primo permette di valutare le iterazioni fissata la precisione desiderata;
    - il secondo invece calcola i risultati fissati i sottointervalli di calcolo.
    */

    cout << "Inserisci '1' se vuoi valutare il numero di iterazioni fissata la precisione" << endl;
    cout << "Inserisci '0' se vuoi valutare i risultati fissando di volta in volta il numero di sottointervalli" << endl;
    cin >> TEST;

    if (TEST == 1){
        int N;
        double RET, TRA, SIM;

        cout << "Inserisci la precisione: ";
        cin >> EPS;

        N=1;

        cout << endl << endl << "==NUMERO DI ITERAZIONI==" << endl;

        RET=rettangoli(A,B,N,EPS,T,TEST);
        TRA=trapezi(A,B,N,EPS,T,TEST);
        SIM=simpson(A,B,N,EPS,T,TEST);

        cout << endl << endl << "L'integrale della funzione " << T << " fra " << A << " e " << B << " e':" << endl;
        cout << "METODO DEI RETTANGOLI: " << RET << endl;
        cout << "METODO DEI TRAPEZI: " << TRA << endl;
        cout << "METODO DI SIMPSON: " << SIM << endl;

        return 0;
    }


    else {

        for(;;){

        int N;
        double ERR_RET, ERR_TRA, RET, TRA, SIM;

        cout << "Inserisci il numero di sottointervalli: ";
        cin >> N;

        if (N==0) return 0;

        RET=rettangoli(A,B,N,EPS,T,TEST);
        TRA=trapezi(A,B,N,EPS,T,TEST);
        SIM=simpson(A,B,N,EPS,T,TEST);

        cout << endl << endl << "L'integrale della funzione " << T << " fra " << A << " e " << B << " e':" << endl;
        cout << "METODO DEI RETTANGOLI: " << RET << endl;
        cout << "METODO DEI TRAPEZI: " << TRA << endl;
        cout << "METODO DI SIMPSON: " << SIM << endl;

        ERR_RET=(RET-SIM)/2;
        ERR_TRA=(TRA-SIM)/2;

        cout << endl << "Il metodo dei rettangoli commette un errore di " << ERR_RET << " rispetto a Simpson." << endl;
        cout << "Il metodo dei trapezi commette un errore di " << ERR_TRA << " rispetto a Simpson." << endl;
        cout << "================================================================================" << endl;

        }

        return 0;
    }

}

/*
La funzione 'rettangoli' restituisce l'integrale calcolato con tale metodo.
*/

double rettangoli(double a, double b, int n, double eps, int t, int test){
    double x=0, i=0, h=0, s=0, area=0, area1=0, diff=0, alfa=0;
    int CONT=0;

    h=(b-a)/n;

    for (i=0; i<n; i++){
        x=a+(i*h);
        s=s+funzione(t,x);
    }

    area=s*h;

    if(test==1){
    do {

        for (i=0; i<n; i++){
            x=a+(h/2)+(i*h);
            s=s+funzione(t,x);
        }

        h=h/2;

        area1=s*h;
        alfa=area1-area;
        diff=fabs(area1-area);
        n=n*2;
        area=area1;
        CONT+=1;

    } while (eps<diff);

    cout << "Rettangoli: " << CONT << " - ";
    }
return area;
}

/*
La funzione 'trapezi' restituisce l'integrale calcolato con tale metodo.
*/

double trapezi(double a, double b, int n, double eps, int t, int test){
    double x=0, i=0, h=0, s=0, area=0, area1=0, diff=0, alfa=0;

    int CONT=0;

    h=(b-a)/n;
    s=(funzione(t,a)+funzione(t,b))/2;
    x=a+h;

    for (i=1; i<n; i++){
        s=s+funzione(t,x);
        x+=h;
    }

    area=s*(h/2);

    if(test==1){
    do {
        x=a+(h/2);

        for (i=0; i<n; i++){
            s=s+funzione(t,x);
            x+=h;
        }

        area1=s*(h/2);
        h=h/2;
        alfa=area1-area;
        diff=fabs(alfa);
        n=n*2;
        area=area1;
        CONT+=1;

    } while (eps<diff);

    cout << "Trapezi: " << CONT << " - ";
    }
return area;
}

/*
La funzione 'simpson' calcola l'integrale utilizzando la somma pari e dispari.
*/

double simpson(double a, double b, int n, double eps, int t, int test){

    double i=0, h=0, SD=0, SP=0, x=0, area=0, area1=0, diff=0, alfa=0;
    int CONT=0;

    if((n/2*2)!=n) ++n;
    h=(b-a)/n;
    x=a;

    for (i=1; i<n-2; i=i+2){
        x=x+h;
        SD+=funzione(t,x);
        x+=h;
        SP+=funzione(t,x);
    }

    x+=h;
    SD+=funzione(t,x);
    area=(h/3)* (funzione(t,a) + 4*SD + 2*SP + funzione(t,b));

    if(test==1){

    do{
        x=a+(h/2);
        SP=SP+SD;
        SD=0;
        for(i=1; i<(n+1); i++){
            SD=SD+funzione(t,x);
            x+=h;
        }

        h=h/2;
        area1=(h/3)* (funzione(t,a) + 4*SD + 2*SP + funzione(t,b));
        alfa=area1-area;
        diff=fabs(alfa);
        n=n*2;
        area=area1;
        CONT+=1;

    } while (eps<diff);

    cout << "Simpson: " << CONT;
    }
return area;
}

/*
Il metodo "funzione" consente di calcolare un risultato numero in base alla funzione matematica
scelta e ritornare tale valore al metodo di calcolo integrale scelto.
*/

double funzione(int t, double d)
{
     switch(t)
       {
        case 1:
            return sin(d);
            break;
        case 2:
            return d*(exp(-d))*(cos(2*d));
            break;
        case 3:
            return 1./(1+pow(d,2));
            break;
        case 4:
            return pow(d, 2.5);
            break;
        case 5:
            return d*sin(d);
            break;
        case 6:
            return exp(-(d*d));
            break;
        case 7:
            return pow(d,2);
            break;
        case 8:
            return exp(d);
            break;
        case 9:
            return sin(1/d);
            break;
    }
}
