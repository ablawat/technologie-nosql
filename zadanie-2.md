#Zadanie 2

Wyszukać w sieci dane zawierające co najmniej 1000000 rekordów/jsonów, dane zapisać w bazie MongoDB. Przygotować i zaprogramować co najmniej cztery agregacje korzystające z Aggregation Pipeline.

##Dane

W tym zadaniu posłużę się danymi z IMDB zawierającymi filmy. Dane zawierają 19831300 jsonów i mają rozmiar około 10.67 GiB.

Przykładowy rekord pliku `getglue_sample.json`:

```json
{
    "comment": "",
    "modelName": "movies",
    "displayName": "",
    "title": "Shutter",
    "timestamp": "2008-11-13T18:48:38Z",
    "image": "http://ia.media-imdb.com/images/M/MV5BMTU1NDAwMDMyNl5BMl5BanBnXkFtZTcwNzU3NTg1MQ@@.jpg",
    "userId": "droop",
    "private": "false",
    "director": "masayuki ochiai",
    "source": "",
    "version": "1",
    "link": "http://www.imdb.com/title/tt0482599/",
    "lastModified": "2011-12-16T19:39:37Z",
    "action": "Liked",
    "lctitle": "shutter",
    "objectKey": "movies/shutter/masayuki_ochiai"
}
```

##Importowanie danych do MongoDB

Po pobraniu danych należy je rozpakować poleceniem:

```sh
tar -xf getglue_sample.tar.gz
```

Po rozpakowaniu archiwum, plik `getglue_sample.json` należy impotrować do bazy danych.

W celu wykonania importu danych do bazy MongoDB należy użyć polecenia `mongoimport` z odpowiednimi opcjami. Dodatkowo polecenie importu zostało poprzedzone poleceniem `time` mierzącym czas wykonania importu.

###Import

Plik `getglue_sample.json` importujemy do bazy danych poleceniem:

```sh
user@host:~$ time mongoimport -c imdb < getglue_sample.json
connected to: 127.0.0.1
...
2015-01-11T16:34:32.337+0100 check 9 19831300
2015-01-11T16:34:32.337+0100 imported 19831300 objects
```

###Czas wykonania

```sh
real    40m23.734s
user    18m9.197s
sys     3m44.504s
```

Całkowity czas trwania importu do bazy trwał około 40 minut i 24 sekund.

##Agregacje

###Agregacja 1

Polega na pogrupowaniu wszystkich wpisów w bazie względem id użytkownika, zsumowaniu ilości wpisów w każdej grupie, posortowaniu w kolejności malejącej i ograniczeniu wyniku do 20 pozycji.

####Zapytanie

```json
{ $group: { _id: "$userId", count: { $sum: 1 } } }
{ $sort : { count: -1 } }
{ $limit: 20 }
```

####Wynik

```json
{ "_id" : "LukeWilliamss", "count" : 696782 }
{ "_id" : "demi_konti", "count" : 68137 }
{ "_id" : "bangwid", "count" : 59261 }
{ "_id" : "zenofmac", "count" : 56233 }
{ "_id" : "agentdunham", "count" : 55740 }
{ "_id" : "cillax", "count" : 43161 }
{ "_id" : "tamtomo", "count" : 42378 }
{ "_id" : "hblackwood", "count" : 32832 }
{ "_id" : "ellen_turner", "count" : 32239 }
{ "_id" : "husainholic", "count" : 32135 }
{ "_id" : "dollyrasyad", "count" : 31314 }
{ "_id" : "DeniseChinita", "count" : 31263 }
{ "_id" : "Putu_Nitovic", "count" : 29895 }
{ "_id" : "SusantiBharuna", "count" : 28706 }
{ "_id" : "zbj", "count" : 28601 }
{ "_id" : "xtrachrisp", "count" : 28282 }
{ "_id" : "carla_moraglia", "count" : 27621 }
{ "_id" : "shady2brandals", "count" : 27038 }
{ "_id" : "tedi31", "count" : 25403 }
{ "_id" : "johnnym2001", "count" : 25249 }
```

###Agregacja 2

Polega na znalezieniu wpisów odnoszących się do filmów, pogrupowaniu względem tytułu, zsumowaniu ilości wpisów w każdej grupie, posortowaniu w kolejności malejącej i ograniczeniu wyniku do 10 pozycji.

####Zapytanie

```json
{ $match: { "modelName": "movies" } }
{ $group: { _id: "$title", count: { $sum: 1 } } }
{ $sort : { count: -1 } }
{ $limit: 10 }
```

####Wynik

```json
{ "_id" : "The Twilight Saga: Breaking Dawn Part 1", "count" : 87521 }
{ "_id" : "The Hunger Games", "count" : 79340 }
{ "_id" : "Marvel's The Avengers", "count" : 64356 }
{ "_id" : "Harry Potter and the Deathly Hallows: Part II", "count" : 33680 }
{ "_id" : "The Muppets", "count" : 29002 }
{ "_id" : "Captain America: The First Avenger", "count" : 28406 }
{ "_id" : "Avatar", "count" : 23238 }
{ "_id" : "Thor", "count" : 23207 }
{ "_id" : "The Hangover", "count" : 22709 }
{ "_id" : "Titanic", "count" : 20791 }
```
