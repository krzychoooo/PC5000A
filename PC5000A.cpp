#include<iostream>
#include "PC5000A.h"
#include "rs232.h"

using namespace std;

PC5000A::PC5000A()
{
    //ctor
}


PC5000A::PC5000A(int com)
{
    const char modePC5000A[4] = {'8', 'N', '1', 0};
    comport_number = com-1;
    baudrate = 9600;
    mode = modePC5000A;
    isOpen = 1;
    if (RS232_OpenComport(comport_number,PC5000A::baudrate,PC5000A::mode ))
    {
        printf("Can not open comport\n");
        isOpen = 0;
    }
    /*
    unsigned char command[10]={'*','I','D','N','?'};
    RS232_SendBuf(comport_number, command, 5);
    Sleep(200);
    unsigned char buf[4096];
    int n = RS232_PollComport(comport_number, buf, 4095);

        if (n > 0) {
            buf[n] = 0; // always put a "null" at the end of a string!

            for (int i = 0; i < n; i++) {
                if (buf[i] < 32) // replace unreadable control-codes by dots
                    buf[i] = '.';
                }
            }

            //printf("received %i bytes: %s\n", n, (char *) buf);
        }
    //printf("-com=%d\n\r", PC5000A::comport_number);
    Sleep(200);*/
}

float PC5000A::getMultimetr(int *error)
{
    unsigned char buf[32];
    float value = 0.0;
    char command[] = {'r', 'e', 'a', 'd', '\r'};
    int i,n;

    *error = 0;
    //snprintf(&command1[4], 3, "%d?", ch);
    RS232_flushRX(comport_number);
    unsigned char *wsk = reinterpret_cast<unsigned char*>(command);
    // cout<<comport_number<<endl;
    i=RS232_SendBuf(comport_number, wsk, 5);
    Sleep(200);

    n=0;
    i=0;

    while(n==0 && i++<10){
        Sleep(100);
        n = RS232_PollComport(comport_number, buf, 37);
    }

    if(n>0)
    {
        //printf("received %i bytes: %s\n", n, (char *) buf);
        int j=1;
        float dzielnik=1;
        value = 0;
        value = value + 100000 * (buf[j++]-0x30);
        if(buf[j] == '.')
        {
            j++;
            dzielnik=100000;
        }
        value = value + 10000 * (buf[j++]-0x30);
        if(buf[j] == '.')
        {
            j++;
            dzielnik=10000;
        }
        value = value + 1000 * (buf[j++]-0x30);
        if(buf[j] == '.')
        {
            j++;
            dzielnik=1000;
        }
        value = value + 100 * (buf[j++]-0x30);
        if(buf[j] == '.')
        {
            j++;
            dzielnik=100;
        }
        value = value + 10 * (buf[j++]-0x30);
        value = value + 1 * (buf[j++]-0x30);
        //cout<<"odczyt="<<value<<endl;
        value = value/dzielnik;
        if(buf[0] == '-') value = -value;

        //cout<<"odczyt="<<value<<" dzielnik="<<dzielnik<<endl;
    }
    else{
        *error=1;
    }



    return value;
}

void PC5000A::sendSerial(unsigned char* komenda, int size){
    unsigned char buf[4];
    unsigned char command[64] = {'s', 'e', 'n', 'd'};
    int i,n;

    RS232_flushRX(comport_number);
    for(i=0; i<size; i++) command[i+4] = komenda[i];
    i = RS232_SendBuf(comport_number, command, size+4);

    n=0;
    while(n==0 && i++<10){
        Sleep(100);
        n = RS232_PollComport(comport_number, buf, 2);
    }
    if(n>0){
        //cout<<buf<<endl;
    }
}


PC5000A::~PC5000A()
{
    RS232_CloseComport(PC5000A::comport_number);
}
