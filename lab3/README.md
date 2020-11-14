## Zadania pdf
### zad 1 
#### ls -R 
-R, --recursive
  list subdirectories recursively 
### zad 2 
#### SUID (ang. Set User ID upon execution):
program zawarty w uruchamianym pliku wykonywany jest z uprawnieniami właściciela
indywidualnego pliku, a nie użytkownika uruchamiającego program
##### chmod u[+/-]s [filename/dirname]
#### SGID (ang. Set Group ID upon execution):
– w przypadku plików – program zawarty w uruchamianym pliku
wykonywany jest z uprawnieniami właściciela grupowego pliku,
a nie użytkownika uruchamiającego program,
– w przypadku katalogów – pliki dziedziczą po katalogu, w którym się
znajdują, właściciela grupowego,
##### chmod g[+/-]s [filename/dirname]
####  Sticky bit:
– w przypadku plików wykonywalnych – program pozostaje w pamię-
ci nawet po jego wyłączeniu, co przyspiesza jego ponowne włączenie
(w praktyce rozwiązanie to nie jest już stosowane i przez większość
systemów ustawienie sticky bit na pliku jest ignorowane),
– w przypadku katalogów – pliki znajdujące się w tym katalogu może
usunąć tylko właściciel tych plików (normalnie jest to posiadacz
prawa zapisu do katalogu).
##### chmod o[+/-]t [filename/dirname]

