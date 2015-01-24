#Zadanie 3

Przygotować funkcje map i reduce, które:

* wyszukają wszystkie anagramy w pliku `word_list.txt`
* wyszukają najczęściej występujące słowa z `Wikipedia data PL` aktualny plik z artykułami, ok. 1.3 GB

##Anagramy

Zadanie polega na znalezieniu wszystkich anagramów do poszczególnych słów z pliku `word_list.txt`. Anagramy są to słowa tej samej długości, złożone z takich samych znaków ale ułożonych w innej kolejności.

###Dane

Dane dla tego zadania znajdują się w pliku [word_list.txt](http://wbzyl.inf.ug.edu.pl/nosql/doc/data/word_list.txt). Plik zawiera słowa o długości sześciu znaków, każde w osobnej linii. Taki format pliku pozwala potraktować go jako prosty przypadek pliku w formacie `csv`, w którym występuje tylko jedno pole. Dzięki temu możemy w prosty sposób zaimportować taki plik do bazy MongoDB.

###Import

Plik `word_list.txt` importujemy do bazy danych poleceniem:

```sh
user@host:~$ time mongoimport -c words --type csv -f word --file word_list.txt
connected to: 127.0.0.1
x
```

###Czas wykonania

```sh
real    x
user    x
sys     x
```

Całkowity czas trwania importu do bazy trwał około x.

###Map i Reduce

####Kod

```js
var map = function()
{
    emit(Array.sum(this.word.split("").sort()), this.word);
};

var reduce = function(key, values)
{
    return values.toString();
};

db.words.mapReduce(map, reduce, { query: {}, out: "anagramy" })
```

####Wynik

```json
x
```

##Wikipedia

###Dane
