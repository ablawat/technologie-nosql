#Zadanie 1a

Importowanie danych z pliku `Train.csv` do systemów baz danych:

* MongoDB
* PostgreSQL

##Modyfikacja danych

Przed importem do bazy danych musimy upewnić się, że na każdy obiekt z danymi przypada dokładnie jedna linia, bez dodatkowych znaków nowej linii wewnątrz pól. Nieporządane znaki nowej linii można usunąć poleceniem:

```sh
cat Train.csv | tr "\n" " " | tr "\r" "\n" > train-tmp.csv
```

Po przekształceniu pliku z danymi pozostała jeszcze ostatnia linia, która jest pusta. Można ją usunąć poprzez sprawdzenie aktualnej ilości linii w pliku poleceniem:

```sh
wc -l train-tmp.csv
6034196 train-tmp.csv
```

Następnie tworzymy plik zawierający o jedną linię mniej poleceniem:

```sh
head -n 6034195 train-tmp.csv > train-modified.csv
```

Po tej operacji plik `train-modified.csv` jest w odpowiednim formacie dla operacji importowania do obu systemów baz danych.

##Importowanie danych do MongoDB

Aby wykonać import danych do bazy MongoDB należy użyć polecenia `mongoimport` z odpowiednimi opcjami. Dodatkowo polecenie importu zostało poprzedzone poleceniem `time` mierzącym czas wykonania importu.

###Import

Plik `train-modified.csv` importujemy do bazy danych poleceniem:

```sh
user@host:~$ time mongoimport -d train -c train --type csv --headerline --file train-modified.csv
connected to: 127.0.0.1
Sun Nov  9 21:15:45.035         Progress: 25525519/7253916754   0%
Sun Nov  9 21:15:45.035             21100   7033/second
Sun Nov  9 21:15:48.000         Progress: 74346367/7253916754   1%
Sun Nov  9 21:15:48.000             61800   10300/second
...
Sun Nov  9 21:27:31.000         Progress: 7189920626/7253916754 99%
Sun Nov  9 21:27:31.000             5980900 8435/second
Sun Nov  9 21:27:34.001         Progress: 7232691044/7253916754 99%
Sun Nov  9 21:27:34.001             6016600 8450/second
Sun Nov  9 21:27:35.473 check 9 6034195
Sun Nov  9 21:27:35.509 imported 6034194 objects
```

###Czas wykonania

```sh
real    11m54.168s
user    1m32.571s
sys     0m12.549s
```

Całkowity czas trwania importu do bazy trwał około 11 minut i 54 sekund.

##Importowanie danych do PostgreSQL

Aby wykonać import danych do bazy PostgreSQL należy napisać skrypt SQL zawierający zapytanie tworzące odpowiednią tabelę oraz komendę COPY.

###Skrypt SQL

```
CREATE TABLE train
(
    id    integer,
    title text,
    body  text,
    tags  text
);

COPY train
FROM '/home/user/train-modified.csv'
WITH DELIMITER ','
CSV HEADER;
```

###Import

Aby wykonać powyższy skrypt na bazie danych należy użyć polecenia `psql` odpowiednio przekazując w parametrach plik SQL. Plik `train-modified.csv` importujemy do bazy danych poleceniem:

```sh
user@host:~$ time psql -f skrypt.sql train
CREATE TABLE
COPY 6034194
```

###Czas wykonania

```sh
real    15m47.877s
user    0m0.042s
sys     0m0.009s
```

Całkowity czas trwania importu do bazy trwał około 15 minut i 47 sekund.

#Zadanie 1b

###Test

```sh
user@host:~$ psql
psql (9.3.5)
Type "help" for help.

postgres=# \c train
You are now connected to database "train" as user "postgres".
train=# SELECT COUNT(*) FROM train;
  count  
---------
 6034194
(1 row)
```
###Test

```sh
user@host:~$ mongo
MongoDB shell version: 2.4.9
connecting to: test
> use train
switched to db train
> db.train.count()
6034194
```

#Zadanie 1c

Zamienić string zawierający tagi na tablicę napisów z tagami następnie zliczyć wszystkie tagi i wszystkie różne tagi.

##Zamiana formatu danych w MongoDB

W celu zamiany formatu danych w bazie MongoDB napisałem program w języku C, który wykorzystuje sterownik `C MongoDB Driver`. Aby sterownik mógł działać prawidłowo wymaga on dodatkowo biblioteki `Libbson`, natomiast operacje na dokumentach json pobranych z bazy wykonuję za pomocą `Libjson`.

* `libmongoc wersja 1.0.2`
* `libbson wersja 1.0.0`
* `libjson wersja 0.10`

Kod programu znajduje się: [tutaj](./zadanie-1c-mongodb).

#Zadanie 1d

Wyszukać w sieci dane zawierające obiekty GeoJSON. Następnie dane zapisać w bazie MongoDB. Dla zapisanych danych przygotować co najmniej 6 różnych geospatial queries (w tym, co najmniej po jednym, dla obiektów Point, LineString i Polygon).

##Dane

W sieci znalazłem wykaz wszystkich stacji RTV zawierający współżędne i opis wszystkich nadajników znajdujących się na terenie polski. Dane zostały udostępnione na stronie http://radiopolska.pl w postaci pliku csv i są dostępne pod adresem http://old.radiopolska.pl/wykaz/lokal2csv.php.

##Modyfikacja danych

Przed dokonaniem importu do bazy danych, musimy przekształcić plik z formatu `csv` na format `json`. Aby to zrobić napisałem w tym celu program w języku C, który konwertuje kolejne linie pliku `radiopolska_obiekty.csv` na odpowiadające mi obiekty `json`, które następnie zapisuje do pliku `stations.json`.

Kod programu znajduje się: [tutaj](./zadanie-1d-json-parser).

##Importowanie danych do MongoDB

W celu wykonania importu danych do bazy MongoDB należy użyć polecenia `mongoimport` z odpowiednimi opcjami. Dodatkowo polecenie importu zostało poprzedzone poleceniem `time` mierzącym czas wykonania importu.

###Import

Plik `stations.json` importujemy do bazy danych poleceniem:

```sh
user@host:~$ time mongoimport -d train -c train --type csv --headerline --file train-modified.csv
connected to: 127.0.0.1
Sun Nov  9 21:15:45.035         Progress: 25525519/7253916754   0%
Sun Nov  9 21:15:45.035             21100   7033/second
Sun Nov  9 21:15:48.000         Progress: 74346367/7253916754   1%
Sun Nov  9 21:15:48.000             61800   10300/second
...
Sun Nov  9 21:27:31.000         Progress: 7189920626/7253916754 99%
Sun Nov  9 21:27:31.000             5980900 8435/second
Sun Nov  9 21:27:34.001         Progress: 7232691044/7253916754 99%
Sun Nov  9 21:27:34.001             6016600 8450/second
Sun Nov  9 21:27:35.473 check 9 6034195
Sun Nov  9 21:27:35.509 imported 6034194 objects
```

###Czas wykonania

```sh
real    11m54.168s
user    1m32.571s
sys     0m12.549s
```

Całkowity czas trwania importu do bazy trwał około 11 minut i 54 sekund.

##Zapytanie 1
