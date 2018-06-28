#include <iostream>
#include "PC5000A.h"
#include "csv.h"
#include <windows.h>
#include <unistd.h>
#include <time.h>
#include <winuser.h>

#define STRICT 1

using namespace std;

int getopt(int argc, char * const argv[], const char *optstring);
extern int optind;       /* wartoœæ pocz¹tkowa 1 */
extern char *optarg;
extern int optopt;
extern int opterr;           /* wartoœæ pocz¹tkowa 1 */

void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime);

int error;
float value1;
PC5000A *miernik;
bool indexInsert=false;
CSV *plik;
int sampleCounter;
UINT TimerId;


int main(int argc, char *argv[])
{

    int nSamples=10;
    int timeSamples=2000;
    int nrPort=1;

    std::string csvFile;

    int opcja;
    int kod_powrotu=0;
    char optstring[] = ":p:n:t:f:i";  /* przetwarzane opcje */
    while ( (opcja = getopt(argc,argv,optstring)) != -1 )
        switch ( opcja )
        {
        case 'n' :
            nSamples = strtol(optarg, NULL, 10);
            //fprintf(stderr,"nSamples=%d\n",nSamples);
            break;
        case 't' :
            timeSamples = strtol(optarg, NULL, 10);
            //fprintf(stderr,"timeSamples =%d\n",timeSamples);
            break;
        case 'f' :
            csvFile = optarg;
            //printf("%d->file=%s\n",optind ,csvFile.c_str());
            break;
        case 'p' :
            nrPort = strtol(optarg, NULL, 10);
            break;
        case 'i' :
            indexInsert = true;
            //printf("INDEX ON\n");
            break;
        case ':' :  /* brakuje argumentu w opcji */
            fprintf(stderr,"opcja -%c wymaga argumentu\n",optopt);
            kod_powrotu = 1; /* Wystapil blad */
            break;
        case '?' :
        default  :
            fprintf(stderr, "opcja -%c nie znana – ignoruje\n", optopt);
            kod_powrotu = 1; /* Wystapil blad */
            break;
        }

    if(timeSamples<200)
    {
        cout<<"Czas musi być >=2000mS"<<endl;
        kod_powrotu = 2;
    }
    if(nSamples<1)
    {
        cout<<"Liczba sampli mniejsza od 1"<<endl;
        kod_powrotu = 3;
    }
    if(kod_powrotu != 0)
    {
        return kod_powrotu;
    }

    miernik = new PC5000A(nrPort);
    if(!miernik->isOpen)
    {
        cout<<"Problem z portem"<<endl;
        return 4;
    }
    plik = new CSV("log.csv");
    //plik = CSV(csvFile);

    cout<<"liczba sampli="<<nSamples<<" co "<<timeSamples<<" milisekund"<<endl;


    TimerId = SetTimer(NULL, 1, timeSamples, &TimerProc);

    HWND hwndTimer;   // handle to window for timer messages
    MSG msg;          // message structure
    sampleCounter = 0;

    time_t startTime = 0;
    while (GetMessage(&msg, // message structure
                      NULL,           // handle to window to receive the message
                      0,           // lowest message to examine
                      0))          // highest message to examine
    {

        // Post WM_TIMER messages to the hwndTimer procedure.

//************************************  T I M E R   ***************************************
        value1 = miernik->getMultimetr(&error);
        cout<<sampleCounter<<"->"<<value1<<endl;
        if(startTime == 0)startTime = clock();
        if(indexInsert)plik->addToRecord((float)(clock()-startTime));
        plik->addToRecord(value1);
        plik->storeRecord();
        if(sampleCounter++ == nSamples)
        {
            plik->~CSV();
            KillTimer(NULL, TimerId);
            Beep(523,500);Beep(1523,500);Beep(523,500);
            return kod_powrotu;
        }
//****************** END TIMER
        if (msg.message == WM_TIMER)
        {
            msg.hwnd = hwndTimer;
        }


        TranslateMessage(&msg); // translates virtual-key codes
        DispatchMessage(&msg);  // dispatches message to window
    }

    /*
        for(int i=1; i!=nSamples; i++)
        {
            value1 = miernik.getMultimetr(&error);
            cout<<"->"<<value1<<endl;
            if(indexInsert)plik.addToRecord((float)i);
            plik.addToRecord(value1);
            plik.storeRecord();
            Sleep(timeSamples);
        }*/
    return kod_powrotu;
}



void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{

}

