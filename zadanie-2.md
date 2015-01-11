#Zadanie 2

##Dane

W tym zadaniu posłużę się danymi z IMDB zawierającymi filmy. Dane zawierają 19831300 jsonówi mają rozmiar około 10.67 GiB.

Przykładowy rekord pliku `getglue_sample.json`:

```json
{"comment": "", "modelName": "movies", "displayName": "", "title": "Shutter", "timestamp": "2008-11-13T18:48:38Z", "image": "http://ia.media-imdb.com/images/M/MV5BMTU1NDAwMDMyNl5BMl5BanBnXkFtZTcwNzU3NTg1MQ@@.jpg", "userId": "droop", "private": "false", "director": "masayuki ochiai", "source": "", "version": "1", "link": "http://www.imdb.com/title/tt0482599/", "lastModified": "2011-12-16T19:39:37Z", "action": "Liked", "lctitle": "shutter", "objectKey": "movies/shutter/masayuki_ochiai"}
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


