## zad 1

Używanie programu:
<br>
-kompilacja:<br>
  gcc -o raising_list raising_list.c<br>
-uruchomienie (wielkość listy podane w bajtach):<br>
  ./raising_list n<br>
 (problem - nie zajmuje dokładnie tyle pamięci ile powinno - zazwyczaj do około 3% mniej)<br>

Spraawdzanie za pomocą htop:<br>
-włączyć program<br>
-htop<br>
-f4 i wpisujemy ./raising_list<br>
<br>

Spraawdzanie za pomocą free:<br>
-free -b | grep ^Mem | tr -s ' ' | cut -d ' ' -f 3<br>
-zapamiętać/zapisac wynik<br>
-włączyć program<br>
-free -b | grep ^Mem | tr -s ' ' | cut -d ' ' -f 3<br>
-odjąć poprzedni  wynik<br>
<br>
## zad 2
-ulimit -v - wyświetli maksymalną ilość pamięci wirtualnej do wykorzystania przez uzytkownika (default - unlimited)<br>
-aby zmienić:<br>
  ulimit -v limit (w kilobajtach)<br>
 jeśli teraz puścimy program zajmujący większą ilośc pamięci otrzymamy komunikat: Segmentation fault (core dumped)<br>
 
  
