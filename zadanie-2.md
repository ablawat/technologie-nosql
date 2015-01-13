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

W celu wykonania na bazie danych agregacji, napisałem program w języku C, który automatycznie wysyła odpowiednie zapytania do bazy MongoDB i zwraca ich wynik. Program wykorzystuje sterownik `C MongoDB Driver oraz bibliotekę `Libbison`.

Kod programu znajduje się: [tutaj](./zadanie-2-aggregations)

###Agregacja 1

Polega na pogrupowaniu wszystkich wpisów w bazie względem akcji, zsumowaniu ilości wpisów w każdej grupie i posortowaniu w kolejności malejącej.

####Zapytanie

```json
{ $group: { _id: "$action", count: { $sum: 1 } } }
{ $sort : { count: -1 } }
```

####Wynik

```json
{ "_id" : "Checkin", "count" : 10958039 }
{ "_id" : "Liked", "count" : 7664733 }
{ "_id" : "Disliked", "count" : 469093 }
{ "_id" : "Favorited", "count" : 288096 }
{ "_id" : "Unwanted", "count" : 270330 }
{ "_id" : "Saved", "count" : 101944 }
{ "_id" : "Said", "count" : 73887 }
{ "_id" : "Looked", "count" : 2972 }
{ "_id" : "Comment", "count" : 2150 }
{ "_id" : null, "count" : 40 }
{ "_id" : "Reply", "count" : 15 }
{ "_id" : "LikedComment", "count" : 1 }
```

####Tabelka

| Akcja        | Ilość    |
|:------------:|:--------:|
| Checkin      | 10958039 |
| Liked        | 7664733  |
| Disliked     | 469093   |
| Favorited    | 288096   |
| Unwanted     | 270330   |
| Saved        | 101944   |
| Said         | 73887    |
| Looked       | 2972     |
| Comment      | 2150     |
| null         | 40       |
| Reply        | 15       |
| LikedComment | 1        |

###Agregacja 2

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

####Tabelka

| Użytkownik     | Ilość  |
|:--------------:|:------:|
| LukeWilliamss  | 696782 |
| demi_konti     | 68137  |
| bangwid        | 59261  |
| zenofmac       | 56233  |
| agentdunham    | 55740  |
| cillax         | 43161  |
| tamtomo        | 42378  |
| hblackwood     | 32832  |
| ellen_turner   | 32239  |
| husainholic    | 32135  |
| dollyrasyad    | 31314  |
| DeniseChinita  | 31263  |
| Putu_Nitovic   | 29895  |
| SusantiBharuna | 28706  |
| zbj            | 28601  |
| xtrachrisp     | 28282  |
| carla_moraglia | 27621  |
| shady2brandals | 27038  |
| tedi31         | 25403  |
| johnnym2001    | 25249  |

###Agregacja 3

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

####Tabelka

| Tytuł                                         | Ilość |
|:---------------------------------------------:|:-----:|
| The Twilight Saga: Breaking Dawn Part 1       | 87521 |
| The Hunger Games                              | 79340 |
| Marvel's The Avengers                         | 64356 |
| Harry Potter and the Deathly Hallows: Part II | 33680 |
| The Muppets                                   | 29002 |
| Captain America: The First Avenger            | 28406 |
| Avatar                                        | 23238 |
| Thor                                          | 23207 |
| The Hangover                                  | 22709 |
| Titanic                                       | 20791 |

###Agregacja 4

Polega na znalezieniu wpisów odnoszących się do filmów, odfiltrowaniu tych mających pozytywną opinię, pogrupowaniu względem tytułu, zsumowaniu ilości wpisów w każdej grupie, posortowaniu w kolejności malejącej i ograniczeniu wyniku do 15 pozycji.

####Zapytanie

```json
{ $match: { "modelName": "movies" } }
{ $match: { "action": "Liked" } }
{ $group: { _id: "$title", count: { $sum: 1 } } }
{ $sort : { count: -1 } }
{ $limit: 15 }
```

####Wynik

```json
{ "_id" : "The Hangover", "count" : 18631 }
{ "_id" : "Avatar", "count" : 16311 }
{ "_id" : "Monsters, Inc.", "count" : 16256 }
{ "_id" : "Iron Man", "count" : 14859 }
{ "_id" : "Toy Story", "count" : 14439 }
{ "_id" : "Titanic", "count" : 14337 }
{ "_id" : "Forrest Gump", "count" : 14273 }
{ "_id" : "Up", "count" : 13604 }
{ "_id" : "Ratatouille", "count" : 12990 }
{ "_id" : "Fight Club", "count" : 12669 }
{ "_id" : "The Incredibles", "count" : 12518 }
{ "_id" : "Back to the Future", "count" : 12499 }
{ "_id" : "Pirates of the Caribbean: The Curse of the Black Pearl", "count" : 12364 }
{ "_id" : "Lord of the Rings: The Return of the King", "count" : 12354 }
{ "_id" : "The Matrix", "count" : 12325 }
```

####Tabelka

| Tytuł                                                  | Ilość |
|:------------------------------------------------------:|:-----:|
| The Hangover                                           | 18631 |
| Avatar                                                 | 16311 |
| Monsters, Inc.                                         | 16256 |
| Iron Man                                               | 14859 |
| Toy Story                                              | 14439 |
| Titanic                                                | 14337 |
| Forrest Gump                                           | 14273 |
| Up                                                     | 13604 |
| Ratatouille                                            | 12990 |
| Fight Club                                             | 12669 |
| The Incredibles                                        | 12518 |
| Back to the Future                                     | 12499 |
| Pirates of the Caribbean: The Curse of the Black Pearl | 12364 |
| Lord of the Rings: The Return of the King              | 12354 |
| The Matrix                                             | 12325 |
