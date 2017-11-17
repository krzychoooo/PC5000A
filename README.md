# PC5000A
PC5000A C++ CONTROL


W katalogu bin/Release/ jest gotowy program do obsługi przystawki IMUSB0403.

Program należy uruchomić w konsoli wiersza poleceń z parametrami

-p - numer portu COM
-n - 
<table>
<tr><td>Opcja</td><td>Wartość</td><td>Opis</td></tr>
<tr><td>-p</td><td>nrCOM</td><td>numer portu COM</td></tr>
<tr><td>-n</td><td>nr samples</td><td>liczba próbek</td></tr>
<tr><td>-t</td><td>sample time [ms]</td><td>czas pomiędzy pomiarami w ms. Minimalna wartość to 2000ms</td></tr>
<tr><td>-f</td><td>file</td><td>plik do którego będzie zapis pomiarów</td></tr>
<tr><td>-i</td><td></td><td>dodaje znaczniki szasu do pomiarów</td></tr>
</table>

Przykład:

sanwa.exe -p 8 -n 100 -t 2500 -f log.csv -i
