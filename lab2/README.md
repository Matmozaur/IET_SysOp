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

Spraawdzanie za pomocą folderu /proc/:<br>
-włączyć program<br>
-sprawdzić nr. pid procesu (np w htop)
-cat /proc/[pid]/status | grep "^VmSize"<br>
<br>
## zad 2
-ulimit -v - wyświetli maksymalną ilość pamięci wirtualnej do wykorzystania przez uzytkownika (default - unlimited)<br>
-aby zmienić:<br>
  ulimit -v limit (w kilobajtach)<br>
 jeśli teraz puścimy program zajmujący większą ilośc pamięci otrzymamy komunikat: Segmentation fault (core dumped)<br>
 
  
## zad 3
strace pozwala nam podglądać w jahi sposób program komunikuje się z systemem, może służyć do debuggowania i monitorowania działania programów, zwłaszcza w sytuacjach gdynie mamy dostepu do kodu źródłowego.<br>
strace date może wypisać przykładowo: <br>  <br>  <br>
execve("/bin/date", ["date"], 0x7fff27463b40 /* 57 vars */) = 0
brk(NULL)                               = 0x55f3e68ff000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=91245, ...}) = 0
mmap(NULL, 91245, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f9552d3b000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9552d39000
mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f955273a000
mprotect(0x7f9552921000, 2097152, PROT_NONE) = 0
mmap(0x7f9552b21000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7f9552b21000
mmap(0x7f9552b27000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9552b27000
close(3)                                = 0
arch_prctl(ARCH_SET_FS, 0x7f9552d3a540) = 0
mprotect(0x7f9552b21000, 16384, PROT_READ) = 0
mprotect(0x55f3e56b1000, 8192, PROT_READ) = 0
mprotect(0x7f9552d52000, 4096, PROT_READ) = 0
munmap(0x7f9552d3b000, 91245)           = 0
brk(NULL)                               = 0x55f3e68ff000
brk(0x55f3e6920000)                     = 0x55f3e6920000
openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=4252880, ...}) = 0
mmap(NULL, 4252880, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f955232b000
close(3)                                = 0
openat(AT_FDCWD, "/etc/localtime", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=2705, ...}) = 0
fstat(3, {st_mode=S_IFREG|0644, st_size=2705, ...}) = 0
read(3, "TZif2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\v\0\0\0\v\0\0\0\0"..., 4096) = 2705
lseek(3, -1707, SEEK_CUR)               = 998
read(3, "TZif2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\v\0\0\0\v\0\0\0\0"..., 4096) = 1707
close(3)                                = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
write(1, "Sun Nov  1 16:18:59 CET 2020\n", 29Sun Nov  1 16:18:59 CET 2020
) = 29
close(1)                                = 0
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
<br>  <br>  <br>
widzimy tutaj między innymi sytuacje gdzie chcieliśmy dostać się do zasobu systemu, ale nie mogliśmy ich zlokalizować  (np. access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory))
 <br>
 Możemy też prześledzieć wywołanie naszego programu typu hello world: <br>  <br>  <br>
 execve("./hello_world", ["./hello_world"], 0x7fff471b2300 /* 57 vars */) = 0
brk(NULL)                               = 0x55da50619000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=91245, ...}) = 0
mmap(NULL, 91245, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fc98bf05000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fc98bf03000
mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fc98b904000
mprotect(0x7fc98baeb000, 2097152, PROT_NONE) = 0
mmap(0x7fc98bceb000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fc98bceb000
mmap(0x7fc98bcf1000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fc98bcf1000
close(3)                                = 0
arch_prctl(ARCH_SET_FS, 0x7fc98bf044c0) = 0
mprotect(0x7fc98bceb000, 16384, PROT_READ) = 0
mprotect(0x55da4f22b000, 4096, PROT_READ) = 0
mprotect(0x7fc98bf1c000, 4096, PROT_READ) = 0
munmap(0x7fc98bf05000, 91245)           = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
brk(NULL)                               = 0x55da50619000
brk(0x55da5063a000)                     = 0x55da5063a000
write(1, "Hello world!!!", 14Hello world!!!)          = 14
exit_group(0)                           = ?
+++ exited with 0 +++
<br>  <br>  <br>
Zwróćmy tu uwagę na linijkę: write(1, "Hello world!!!", 14Hello world!!!)          = 14, informującą o tym że zostało wypisanych 14 znaków (Hello world!!!)
