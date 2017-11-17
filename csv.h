/*
 * zachowajta mój email i róbta co chceta.
 */

/*
 * File:   csv.h
 * Author: fajnysoft@gmail.com
 *
 * Created on 22 kwietnia 2017, 19:27
 */

#ifndef CSV_H
#define CSV_H

#include <fstream>

using namespace std;



class CSV {
public:
    string fileName;
    fstream file;
    string record;
    CSV();
    /**\<html><h3>tworzy plik o nazwie fName</h2><p></p></html>
     * \param fName
     * \return void
     */
    CSV(string);
    /**\<html><h2>funkcja dopisująca do rekordu kolejne pomiary</h2><p>tworzy linię w pliku csv kolejne wartości rozdzielone znakiem';' Znak dziesiętny to ','</p></html>
     * \param fPomiar float
     * \return void
     */
    void addToRecord(float);
    /**\<html><h2>zapisuje do pliku kolejny rekord </h2><p></p></html>
     * \return void
     */
    void storeRecord();
    virtual ~CSV();
private:

};

#endif /* CSV_H */

