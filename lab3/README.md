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

### zad 3 
Utworzenie pliku:
##### man ls > ~/c2/text  
Sprawdzenie praw dostępu:
##### ls -l  ~/c2/text  
Prawa dostępu może zmienić właściciel pliku lub root, za pomocą komendy chmod (właściciela możemy zmienić przez chown, z poziomu administratora

### zad 4 
Ograniczenie wykonywania i zapisywania:
##### chmod 744 ~/c2/text  
Uniemożliwienie usunięcia przez rm:
##### chmod a-w  ~/c2 

### zad 5 
Kopiowanie:
##### sudo cp ~/c2/text ~/c2/text2  
##### sudo chown [user] ~/c2/text2
Do odczytu tylko przez właściciela i grupę:
##### chmod o-r text2

### zad 6
Predefiniowana inicjacyjna wartość dla uprawnień to 666 (rw-rw-rw) dla plików i 777 (rwxrwxrwx) dla katalogów. Jeżeli umask będzie ustawiony na 000 to nowe pliki będą dostawać uprawnienia 666. Domyślna wartośc umask to 002, zatem domyślnie pliki będą miały uprawnienia 664 a foldery 775. Aby to zmienić stosujemy polecenie:
#### umask [wartość odejmowana od domyślnych uprawnień]

### zad 7
Największy plik w katalogu domowym:
#### find ~ -type f -printf "%s\t%p\n" | sort -n | tail -1
Największy plik w ~ i bezpośrednich potomkach:
#### find ~ -maxdepth 2 -type f -printf "%s\t%p\n" | sort -n | tail -1


### zad 8
Plik o największej ilości bloków w katalogu domowym:
#### find ~  -printf '%b\t%p\n' | sort -nr | head -1

### zad 9
Pliki zaczynjące sie od 'c' w postaci długiej w katalogu /usr/include i podkatalogach:
#### find /usr/include -type f -name "c*" -ls


### zad 10
Pliki modyfikowane w ciągu ostatnich 2 dni:
z uwzględnieniem podkatalogów:
#### find ~ -mtime -2  -ls
bez uwzględniania podkatalogów:
#### find ~ -maxdepth 1 -mtime -2  -ls

### zad 11
#### Find . -maxdepth 1 -type f -size -12k | grep ‘./m.*h’ | wc -l 6 elementów

### zad 12
#### tar -cvf c2.tar c2 – utworzenie archiwum gzip c2.tar - kompresja rm c2 – usunięcie katalogu pierwotnego tar -cvf c2.tar c2 – odtworzenie katalogu pierwotnego

### zad 13

### zad 14
#### df -T 
– kolumna Use% zużycie w odniesieniu do liczby bloków df -h – jw. w odniesieniu do liczby struktur inode

### zad 15
#### mount -l
– listuje punkty montowania, oraz typy używanych systemów plików lsblk – a -kolumna MAJ:MIN – numer seryjny dysku

### zad 16
#### du -a * | sort -nr
– wyświetlenie wszystkich katalogów oraz podkatalogów, oraz posortowanie ich w kolejności malejącej względem zużycia przestrzeni

### zad 17
#### ln -s moj_ls symbol 
– utworzenie dowiązania symbolicznego 
#### ln ls.txt twarde
– utworzenie dowiązania twardego 
#### ls -R -i -sh
– wylistowanie zawartości katalogu c2 (rekurencyjnie, wraz z numerami inode i rozmiarami) W przypadku dowiązania twardego zarówno numer inode jak i rozmiar pozostaje taki sam (jak w powiązanym pliku). Natomiast w przypadku dowiązania symbolicznego rozmiar dowiązania wynosi 0 i nadawany jest nowy numer inode.

Po wykonaniu komend: 
#### rm ls.txt
#### rm moj_ls.txt

Dowiązanie twarde nadal istnieje (można odczytać z niego dane zawarte wcześniej w pliku). Natomiast dowiązanie symboliczne jest widoczne, ale z powodu braku pliku źródłowego nie można go odczytać.


## Zadania sprawdzające

### zad 1
#### find -type f -printf ‘%T+ %p\n’ | sort |head -1

### zad 2 
#### ls -al /usr/include | grep ‘^d’ | wc -l

### zad 3
#### ls -al /usr/include | grep ‘^-’ | awk ‘{print $9}’ | grep ‘^m.{6}h$ | wc -l

### zad 4
Liczba plików większych niż 12000 bajtów:
#### find /usr/include -maxdepth 2 -type f -size +12000c | wc -l

### zad 5
Liczba plików w usr/bin mniejszych niż 2 MB:
#### find /usr/bin -maxdepth 1 -type f -size -2M | wc -l
