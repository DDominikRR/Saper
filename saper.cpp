#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
int koniec(time_t t_start, int wynik)
{
    int x;
    time_t t_stop; //czas zakonczenia gry
    time(&t_stop);
    double diff_t;
    diff_t=difftime(t_stop, t_start); //czas gry
    printf("\n");
    if(wynik==1) printf("Koniec gry, Przegrales!\n");
    if(wynik==2) printf("Koniec gry, WYGRALES!!!\n");
    printf("Gra trwala %.0lf sekundy\n",diff_t);
    printf("Czy chcesz zagrac jeszcze raz?\n");
    printf("1. Tak :D \n");
    printf("0. Nie D: \n");
    printf("Wybor: ");
    scanf("%d",&x);
    return x;
}
struct pole
{
    char czyWidac='0';
    int elem=0;
    char boom=32;
};
int main()
{
    //poztkujacy 8x8 10 // orginalny 16y24x 40 //zaawansowany 30x16 40/ ekspert 30/16 99
    //wlasna
    start:
        system("cls");
    int SZEROKOSC; int WYSOKOSC; int BOMBY;
    int cx,cy;int ilePol;

    printf("Wybierz poziom trudnosci: \n");// X/Y/B
    printf("1. Poczatkujacy \n"); //8/8/10
    printf("2. Oryginalny \n"); //24/16/40
    printf("3. Sredniozaawansowany \n"); //16/16/40
    printf("4. Ekspert \n"); //30/16/99
    printf("5. Wlasna plansza \n"); //X/Y/B
    //printf("6. Losowa plansza \n"); //rX/rY/rB
    printf("Wybor: ");
    int pozTrud;
    scanf("%d",&pozTrud);
    switch(pozTrud)
    {
    case 1:
        {
            SZEROKOSC=8;
            WYSOKOSC=8;
            BOMBY=10;
            break;
        }
    case 2:
        {
            SZEROKOSC=24;
            WYSOKOSC=16;
            BOMBY=40;
            break;
        }
    case 3:
        {
            SZEROKOSC=16;
            WYSOKOSC=16;
            BOMBY=40;
            break;
        }
    case 4:
        {
            SZEROKOSC=30;
            WYSOKOSC=16;
            BOMBY=99;
            break;
        }
    case 5:
        {
            printf("Podaj szerokosc planszy: ");
            do{
                scanf("%d",&SZEROKOSC);
                if(SZEROKOSC<2) {printf("Za mala szerokosc! Podaj wieksza: ");}
                else if(SZEROKOSC>60) {printf("Za duza szerokosc! Podaj mniejsza: ");}
            }while(SZEROKOSC<2 || SZEROKOSC>60);
            printf("Podaj wysokosc planszy: ");
            do{
                scanf("%d",&WYSOKOSC);
                if(WYSOKOSC<2) {printf("Za mala wysokosc! Podaj wieksza: ");}
                else if(WYSOKOSC>60) {printf("Za duza wysokosc! Podaj mniejsza: ");}
            }while(WYSOKOSC<2 || WYSOKOSC>60);
            printf("Podaj ilosc bomb: ");
            int maxb=SZEROKOSC*WYSOKOSC;
            do{
                scanf("%d",&BOMBY);
                if(BOMBY>=maxb) {printf("Za duzo bomb! Podaj mniejsza ilosc: ");}
                else if(BOMBY<1) {printf("Za malo bomb! Podaj wieksza ilosc: ");}
            }while(BOMBY<1 || BOMBY>=maxb);
            break;
        }
    default:
        {
            SZEROKOSC=24;
            WYSOKOSC=16;
            BOMBY=40;
            break;
        }
    }
    int y=WYSOKOSC+2; int x=SZEROKOSC+2; int bomb=BOMBY;
    pole plansza[y][x];
    powtRand:
    for (int i=1;i<=y-1;i++) //zerowanie planszy
    {
        for(int j=1;j<=x-1;j++)
        {
            plansza[i][j].elem=0;
        }
    }
    for(int i=0;i<=x-1;i++) //numeracja os x
    {
        plansza[0][i].elem=(i-1)%10;
        plansza[0][i].czyWidac='1';
    }
    for(int i=0;i<=y-1;i++) //numeracja os y
    {
        plansza[i][0].elem=(i-1)%10;
        plansza[i][0].czyWidac='1';
    }
    for(int i=1;i<=x-1;i++) //bariera os x
    {
        plansza[1][i].elem=11; //11=bariera
        plansza[1][i].czyWidac='1';
    }
    for(int i=1;i<=y-1;i++) //bariera os y
    {
        plansza[i][1].elem=11;
        plansza[i][1].czyWidac='1';
    }
    plansza[0][1].elem=11;
    plansza[1][0].elem=11;
    srand(time(NULL));
    int b1,b2; //losowanie bomb (wspolrzedne)
    for(int i=0;i<=bomb-1;i++) //losowanie planszy
    {
        reroll:
        b1=rand()%(y-3)+2;
        b2=rand()%(x-3)+2;
        if(plansza[b1][b2].elem!=12 && b1>1 && b2>1) //czy bomba znajduje sie na polu gry i nie pokrywa sie z istniejaca bomba
        {
            plansza[b1][b2].elem=12; //12=bomba
        }
        else goto reroll;
    }
    for(int i=2;i<=y-1;i++) //wyliczanie ilosci bomb dookola
    {
        for(int j=2;j<=x-1;j++)
        {
            if(plansza[i][j].elem==12) //czy pole jest bomba (dodaje sie +1 polom dookola)
            {
                for(int o=-1;o<2;o++)
                {
                    for(int p=-1;p<2;p++)
                    {
                        if(o==0 && p==0) {continue;}
                        if(plansza[i+o][j+p].elem==11 || plansza[i+o][j+p].elem==12){continue;} //pomijanie pol bariery i bomb
                        plansza[i+o][j+p].elem+=1; //zwiekszanie pola za kazda sasiednia bombe
                    }
                }
            }
        }
    }
    for(int i=2;i<=y-1;i++) //elementy niestykajace sie z bombami ==13
    {
        for(int j=2;j<=x-1;j++)
        {
            if(plansza[i][j].elem==0) //przypisani polom o wartosci '0' wartosci '13, dla latwosci drukowania
            {
                plansza[i][j].elem=13;
            }
        }
    }
    time_t t_start; //czas w momencie rozpoczecia gry
    time(&t_start); //pobranie czasu poczatkowego
    do
    {
        powtWyb:
        system("cls");
        cx=0;
        cy=0;
        for (int i=0;i<=y-1;i++) //drukowanie planszy
        {
            for(int j=0;j<=x-1;j++)
            {
                if(plansza[i][j].czyWidac=='1')
                {
                    if(plansza[i][j].elem==11) //drukowanie bariery
                    {
                        printf("%c",32);
                    }
                    else if(plansza[i][j].elem==12) //drukowanie bomb
                    {
                        printf("%c ",254);
                    }
                    else if(plansza[i][j].elem==-1 || plansza[i][j].elem==-2) //usuwa rog
                    {
                        printf("%c ",32);
                    }
                    else if(plansza[i][j].elem==13) //pole niestykajace sie z bombami (puste)
                    {
                        printf("%c ",32);
                    }
                    else //drukowanie liczb (pola z bomba obok)
                    {
                        printf("%d ",plansza[i][j].elem);
                    }
                }

                else if(plansza[i][j].czyWidac=='0') //niewidoczna, zakrywanie pola niewidocznego
                {
                    printf("%c ",'#');
                }
                else if(plansza[i][j].czyWidac=='2') // drukowanie: znak zapytania
                {
                    printf("%c ",'?');
                }
                else if(plansza[i][j].czyWidac=='3') //drukowanie: oznaczenie bomby
                {
                    printf("%c ",'X');
                }
            }
            printf("\n");
        }
        for(int i=0;i<=x-1;i++)
        {
            printf("= ");
        }
        printf("\n");
        //WARUNEK WYGRANEJ
        for(int i=2;i<=y-1;i++) //gdy ilosc pol zaslonietych lub oznaczonych rowna sie ilosci bomb na planszy
        {
            for(int j=2;j<=x-1;j++)
            {
                if(plansza[i][j].czyWidac=='0') //niewidoczne (zakryte)
                {
                    ilePol++;
                }
                if(plansza[i][j].czyWidac=='2') //znaki zapytania
                {
                    ilePol++;
                }
                if(plansza[i][j].czyWidac=='3') //oznaczenie bomby 'X'
                {
                    ilePol++;
                }
            }
        }
        if(ilePol==bomb) //warunek wygranej
        {
            int powt;
            powt=koniec(t_start,2); //koniec 2-wygrana
            if(powt==1){goto start;}
            if(powt!=1){goto stop;}
        }
        printf("1. Odslon pole  \n");
        printf("2. Znak zapytania  \n");
        printf("3. Oznacz bombe  \n");
        printf("4. Odznacz pole  \n");
        printf("Wybor: ");
        int sf; //wybor dzialania
        scanf("%d",&sf);
        printf("[X/Y]:\n");
        int ok=1;
        do
        {
            ilePol=0;
            // Wybor pola (strzal)
            scanf("%d",&cx);
            scanf("%d",&cy);
                        //DEV mode//
                        if(cx==211120 && cy==211120) //odslania wszystkie pola
                        {
                            for(int i=2;i<=y-1;i++)
                            {
                                for(int j=2;j<=x-1;j++)
                                {
                                    plansza[i][j].czyWidac='1';
                                }
                            }
                            goto powtWyb;
                        }
                        if(cx==10601 && cy==10601) //zaslania wszystkie pola
                        {
                            for(int i=2;i<=y-1;i++)
                            {
                                for(int j=2;j<=x-1;j++)
                                {
                                    plansza[i][j].czyWidac='0';
                                }
                            }
                            goto powtWyb;
                        }
                        if(cx==10121 && cy==10121) //losuje nowa plansze
                        {
                            goto powtRand;
                        }
            if(cx>x-1 || cy>y-1) //czy poza plansza
            {
                printf("Pole poza plansza!!\n");
                printf("[X/Y]: \n");
            }
            else
            {
                ok=0; //czy wybrane pole jest prawidlowe 0=prawidlowe
                cx+=1; //dopasowanie do numeracji planszy na ekranie
                cy+=1;
                if(sf==1) //odslonienie
                {
                    if(plansza[cy][cx].czyWidac=='2' ||plansza[cy][cx].czyWidac=='3')
                    {
                        printf("Probujesz strzelic w pole, ktore moze byc bomba!\n");
                        Sleep(1500);
                        goto powtWyb;
                    }
                    else if(plansza[cy][cx].czyWidac=='1')
                    {
                        printf("To pole jest juz odsloniete!\n");
                        Sleep(1500);
                        goto powtWyb;
                    }
                    else {plansza[cy][cx].czyWidac='1'; }
                }
                if(sf==2) //postawienie znaku zapytania
                {
                    if(plansza[cy][cx].czyWidac=='1')
                    {
                        printf("To pole jest juz odkryte!\n");
                        Sleep(1500);
                        goto powtWyb;
                    }
                    else {plansza[cy][cx].czyWidac='2'; }
                }
                if(sf==3) //oznaczenie bomby
                {
                        if(plansza[cy][cx].czyWidac=='1')
                    {
                        printf("To pole jest juz odkryte!\n");
                        Sleep(1500);
                        goto powtWyb;
                    }
                    else {plansza[cy][cx].czyWidac='3'; }
                }
                if(sf==4) //odznaczenie pola (wraca do '#'
                {
                    if(plansza[cy][cx].czyWidac=='1')
                    {
                            printf("To pole jest juz odkryte!\n");
                            Sleep(1500);
                            goto powtWyb;
                    }
                    else {plansza[cy][cx].czyWidac='0'; }
                }
            }
        }while(ok!=0);
        //PRZEGRANA GRY//
        if(plansza[cy][cx].elem==12 && sf==1) //jesli odsloniete zostaje pole z bomba
        {
            int kx,ky;
            system("cls");
            for(int i=0;i<=((x-2)*(y-3))/2;i++) //nadaje losoym polom znak 176 z ASCII
            {
                do{
                    kx=rand()%(x);
                    ky=rand()%(y);
                }while(plansza[ky][kx].boom==176);
                plansza[ky][kx].boom=176;
            }
            for(int i=0;i<=y-1;i++) //drukuje efekt przegranej
            {
                for(int j=0;j<=x-1;j++)
                {
                    printf("%c",plansza[i][j].boom);
                }
                Sleep(2);
                printf("\n");
            }
            int powt;
            powt=koniec(t_start,1); //koniec 1-przegrana
            if(powt==1){goto start;}
            if(powt!=1){goto stop;}
        }
        if(plansza[cy][cx].elem==13 && sf==1) //odslania pierwsze 8 pol dookola pola pustego
        {
            for(int i=-1;i<=1;i++)
            {
                for(int j=-1;j<=1;j++)
                {
                    if(plansza[cy-i][cx-j].czyWidac=='0') {plansza[cy-i][cx-j].czyWidac='1';}
                }
            }
        //ODSLANIANIE WSZYSTKICH POL STYKAJACYCH SIE Z POLAMI PUSTYMI (ktore stykaja sie z odslonietym polem pustym)
            int cydl,cydp,cygl,cygp; //odslanianie po cwiartkach, wg punkty cy,cx
            cydl=cy; //wybrane y- dol lewo
            cydp=cy; //wybrane y- dol prawo
            cygl=cy; //wybrane y- gora lewo
            cygp=cy; //wybrane y- gora prawo
            do //W DOL
            {
                for(int i=cx+1;i<=x-1;i++) //W PRAWO
                {
                    if(plansza[cydp][i].czyWidac=='0') {continue;} //jesli zasloniete-pomija
                    if(plansza[cydp][i].czyWidac=='2') {continue;} //jesli znak zapytania- pomija
                    if(plansza[cydp][i].czyWidac=='3') {continue;} //jesli oznaczenie bomby- pomija
                    if(plansza[cydp][i].czyWidac=='1' && plansza[cydp][i].elem==13) //jesli widoczne i pole puste- odslania 8 dookola
                    {
                        for(int k=-1;k<=1;k++)
                        {
                            for(int l=-1;l<=1;l++)
                            {
                                if(plansza[cydp+k][i+l].czyWidac=='0') {plansza[cydp+k][i+l].czyWidac='1';} //odslania 8 pol dookola
                            }
                        }
                    }
                }
                cydp++;
            }while(cydp<y);
            do
            {
                for(int i=cx-1;i>=2;i--) //W LEWO
                {
                    if(plansza[cydl][i].czyWidac=='0') {continue;}
                    if(plansza[cydl][i].czyWidac=='2') {continue;}
                    if(plansza[cydl][i].czyWidac=='3') {continue;}
                    if(plansza[cydl][i].czyWidac=='1' && plansza[cydl][i].elem==13)
                    {
                        for(int k=-1;k<=1;k++)
                        {
                            for(int l=-1;l<=1;l++)
                            {
                                if(plansza[cydl+k][i+l].czyWidac=='0') {plansza[cydl+k][i+l].czyWidac='1';}
                            }
                        }
                    }
                }
                cydl++;
            }while(cydl<y);
            do //W GORE
            {
                for(int i=cx+1;i<=x-1;i++) //W PRAWO
                {
                    if(plansza[cygp][i].czyWidac=='0') {continue;}
                    if(plansza[cygp][i].czyWidac=='2') {continue;}
                    if(plansza[cygp][i].czyWidac=='3') {continue;}
                    if(plansza[cygp][i].czyWidac=='1' && plansza[cygp][i].elem==13)
                    {
                        for(int k=-1;k<=1;k++)
                        {
                            for(int l=-1;l<=1;l++)
                            {
                                if(plansza[cygp+k][i+l].czyWidac=='0') {plansza[cygp+k][i+l].czyWidac='1';}
                            }
                        }
                    }
                }
                cygp--;
            }while(cygp>1);
            do
            {
                for(int i=cx-1;i>=2;i--) //W LEWO
                {
                    if(plansza[cygl][i].czyWidac=='0') {continue;}
                    if(plansza[cygl][i].czyWidac=='2') {continue;}
                    if(plansza[cygl][i].czyWidac=='3') {continue;}
                    if(plansza[cygl][i].czyWidac=='1' && plansza[cygl][i].elem==13)
                    {
                        for(int k=-1;k<=1;k++)
                        {
                            for(int l=-1;l<=1;l++)
                            {
                                if(plansza[cygl+k][i+l].czyWidac=='0') {plansza[cygl+k][i+l].czyWidac='1';}
                            }
                        }
                    }
                }
                cygl--;
            }while(cygl>1);
            int opx=y-1,opy=2,opz=y-1,opq=2;
        //ODSLANIANIE POL PUSTYCH zaczynajac od roznych katow
            do //KAT LEWY GORNY
            {
                for(int i=2;i<x;i++)
                {
                    if(plansza[opy][i].czyWidac=='0') {continue;}
                    if(plansza[opy][i].czyWidac=='2') {continue;}
                    if(plansza[opy][i].czyWidac=='3') {continue;}
                    if(plansza[opy][i].czyWidac=='1' && plansza[opy][i].elem==13)
                    {
                        for(int k=-1;k<=1;k++)
                        {
                            for(int l=-1;l<=1;l++)
                            {
                                if(plansza[opy+k][i+l].czyWidac=='0') {plansza[opy+k][i+l].czyWidac='1';}
                            }
                        }
                    }
                }
                opy++;
            }while(opy<y);
            do //KAT PRAWY DOLNY
            {
                for(int i=x-1;i>=2;i--)
                {
                    if(plansza[opx][i].czyWidac=='0') {continue;}
                    if(plansza[opx][i].czyWidac=='2') {continue;}
                    if(plansza[opx][i].czyWidac=='3') {continue;}
                    if(plansza[opx][i].czyWidac=='1' && plansza[opx][i].elem==13)
                    {
                        for(int k=-1;k<=1;k++)
                        {
                            for(int l=-1;l<=1;l++)
                            {
                                if(plansza[opx+k][i+l].czyWidac=='0') {plansza[opx+k][i+l].czyWidac='1';}
                            }
                        }
                    }
                }
                opx--;
            }while(opx>=2);
            do //KAT LEWY DOLNY
            {
                for(int i=2;i<x;i++)
                {
                    if(plansza[opz][i].czyWidac=='0') {continue;}
                    if(plansza[opz][i].czyWidac=='2') {continue;}
                    if(plansza[opz][i].czyWidac=='3') {continue;}
                    if(plansza[opz][i].czyWidac=='1' && plansza[opz][i].elem==13)
                    {
                        for(int k=-1;k<=1;k++)
                        {
                            for(int l=-1;l<=1;l++)
                            {
                                if(plansza[opz+k][i+l].czyWidac=='0') {plansza[opz+k][i+l].czyWidac='1';}
                            }
                        }
                    }
                }
                opz--;
            }while(opz>=2);
            do //Kat PRAWY GORNY
            {
                for(int i=x-1;i>=2;i--)
                {
                    if(plansza[opq][i].czyWidac=='0') {continue;}
                    if(plansza[opq][i].czyWidac=='2') {continue;}
                    if(plansza[opq][i].czyWidac=='3') {continue;}
                    if(plansza[opq][i].czyWidac=='1' && plansza[opq][i].elem==13)
                    {
                        for(int k=-1;k<=1;k++)
                        {
                            for(int l=-1;l<=1;l++)
                            {
                                if(plansza[opq+k][i+l].czyWidac=='0') {plansza[opq+k][i+l].czyWidac='1';}
                            }
                        }
                    }
                }
                opq++;
            }while(opq<y);
        }
    }while(1);//petla nieskonczona, w niej toczy sie gra
    stop:
    return 0;
}
