#Zadanie 1a

Importowanie danych z pliku `Train.csv` do systemów baz danych:

* MongoDB
* PostgreSQL

##Modyfikacja danych

Przed importem do bazy danych musimy upewnić się, że na każdy obiekt z danymi przypada dokładnie jedna linia, bez dodatkowych znaków nowej linii wewnątrz pól. Nieporządane znaki nowej linii można usunąć takim poleceniem:

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
