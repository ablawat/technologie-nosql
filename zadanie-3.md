#Zadanie 3

Przygotować funkcje map i reduce, które:

* wyszukają wszystkie anagramy w pliku `word_list.txt`
* wyszukają najczęściej występujące słowa z `Wikipedia data PL`

##Anagramy

Zadanie polega na znalezieniu wszystkich anagramów do poszczególnych słów z pliku `word_list.txt`. Anagramy są to słowa tej samej długości, złożone z takich samych znaków ale ułożonych w innej kolejności.

###Dane

Dane dla tego zadania znajdują się w pliku [word_list.txt](http://wbzyl.inf.ug.edu.pl/nosql/doc/data/word_list.txt). Plik zawiera słowa o długości sześciu znaków, każde w osobnej linii. Taki format pliku pozwala potraktować go jako prosty przypadek pliku w formacie `csv`, w którym występuje tylko jedno pole. Dzięki temu możemy w prosty sposób zaimportować taki plik do bazy MongoDB.

###Import

Plik `word_list.txt` importujemy do bazy danych poleceniem:

```sh
user@host:~$ time mongoimport -c words --type csv -f word --file word_list.txt
connected to: 127.0.0.1
2015-01-24T15:58:37.876+0100 check 9 8199
2015-01-24T15:58:38.057+0100 imported 8199 objects
```

###Czas wykonania

```sh
real    0m1.413s
user    0m0.022s
sys     0m0.039s
```

Całkowity czas trwania importu do bazy trwał około 1 sekundy i 413 tysięcznych.

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

db.words.mapReduce(map, reduce, { query: {}, out: "anagrams" })
```

####Zapytanie

Po zapisaniu powyższego kodu do pliku `zadanie-3-1.js`, wykonujemy zapytanie na bazie danych za pomocą polecenia:

```sh
user@host:~$ time mongo test zadanie-3-1.js
MongoDB shell version: 2.6.6
connecting to: test

real    0m0.577s
user    0m0.041s
sys     0m0.008s
```

Czas trwania zapytania wyniósł około pół sekundy.

####Wynik

Wynik możemy obejrzeć wyświetlając zawartość kolekcji `anagrams`.

```json
{ "_id" : "aaabcl", "value" : "cabala" }
{ "_id" : "aaabcn", "value" : "cabana" }
{ "_id" : "aaabcs", "value" : "casaba" }
{ "_id" : "aaabnn", "value" : "banana" }
{ "_id" : "aaabrz", "value" : "bazaar" }
{ "_id" : "aaacci", "value" : "acacia" }
{ "_id" : "aaaclp", "value" : "alpaca" }
{ "_id" : "aaacmr", "value" : "maraca" }
{ "_id" : "aaadmr", "value" : "armada" }
{ "_id" : "aaaelz", "value" : "azalea" }
{ "_id" : "aaaitx", "value" : "ataxia" }
{ "_id" : "aaajmp", "value" : "pajama" }
{ "_id" : "aaalms", "value" : "salaam" }
{ "_id" : "aaamnn", "value" : "manana" }
{ "_id" : "aaamnp", "value" : "panama" }
{ "_id" : "aaappy", "value" : "papaya" }
{ "_id" : "aaartv", "value" : "avatar" }
{ "_id" : "aabbbo", "value" : "baobab" }
{ "_id" : "aabblo", "value" : "balboa" }
{ "_id" : "aabcls", "value" : "cabals" }
{ "_id" : "aabcrs", "value" : "scarab" }
{ "_id" : "aabcsu", "value" : "abacus" }
{ "_id" : "aabder", "value" : "abrade" }
{ "_id" : "aabdes", "value" : "abased" }
{ "_id" : "aabdet", "value" : "abated" }
{ "_id" : "aabdll", "value" : "ballad" }
{ "_id" : "aabdlm", "value" : "lambda" }
{ "_id" : "aabdmn", "value" : "badman" }
{ "_id" : "aabdor", "value" : "abroad,aboard" }
{ "_id" : "aabegt", "value" : "teabag" }
{ "_id" : "aabelr", "value" : "arable" }
{ "_id" : "aabelt", "value" : "ablate" }
{ "_id" : "aabelz", "value" : "ablaze" }
{ "_id" : "aabemo", "value" : "amoeba" }
{ "_id" : "aabess", "value" : "abases" }
{ "_id" : "aabest", "value" : "abates" }
{ "_id" : "aabggr", "value" : "ragbag" }
{ "_id" : "aabggs", "value" : "gasbag" }
{ "_id" : "aabgin", "value" : "baaing" }
{ "_id" : "aabgir", "value" : "airbag" }
```

##Wikipedia

###Dane
