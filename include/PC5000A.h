#ifndef PC5000A_H
#define PC5000A_H

class PC5000A
{
    public:

        int comport_number;
        int baudrate;
        const char *mode; //serial port mode
        static const char modePC5000A[4];

        PC5000A();
        PC5000A(int);
        virtual ~PC5000A();
        float getMultimetr(int*);


    protected:

    private:
};

#endif // PC5000A_H
