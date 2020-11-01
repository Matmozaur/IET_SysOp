## zad 1

Używanie programu:
-kompilacja:
  gcc -o raising_list raising_list.c
-uruchomienie (wielkość listy podane w bajtach):
  ./raising_list n
 (problem - nie zajmuje dokładnie tyle pamięci ile powinno - zazwyczaj do około 3% mniej)

Spraawdzanie za pomocą htop:
-włączyć program
-htop
-f4 i wpisujemy ./raising_list


Spraawdzanie za pomocą free:
-free -b | grep ^Mem | tr -s ' ' | cut -d ' ' -f 3
-zapamiętać/zapisac wynik
-włączyć program
-free -b | grep ^Mem | tr -s ' ' | cut -d ' ' -f 3
-odjąć poprzedni  wynik

## zad 2
-ulimit -v - wyświetli maksymalną ilość pamięci wirtualnej do wykorzystania przez uzytkownika (default - unlimited)
-aby zmienić:
  ulimit -v limit (w kilobajtach)
 jeśli teraz puścimy program zajmujący większą ilośc pamięci otrzymamy komunikat: Segmentation fault (core dumped)
 
  
