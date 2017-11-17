/*
 * zachowajta mój email i róbta co chceta.
 */

/*
 * File:   csv.cpp
 * Author: fajnysoft@gmail.com
 *
 * Created on 22 kwietnia 2017, 19:27
 */

#include "csv.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>

using namespace std;

CSV::CSV() {
}

CSV::CSV(string fName) {
    fileName = fName;
    CSV::file.open(fName.c_str(),ios_base::app);
}

CSV::~CSV() {
    CSV::file.close();
}

void CSV::addToRecord(float fPomiar){
    char sPomiar[32];
    setlocale(LC_ALL, "Polish");
    sprintf(sPomiar, "%f", fPomiar);
    CSV::record += sPomiar;
    CSV::record += ";";
    setlocale(LC_ALL, "USA");
    //cout<<csv::record<<endl;
}

void CSV::storeRecord(){
    CSV::record = CSV::record.substr(0, CSV::record.size()-1);
    CSV::record += "\n";
    CSV::file.write(CSV::record.c_str(), CSV::record.size());
    CSV::record = "";
}
