# Kalkulator - dokumentacja


## 1. Uruchamianie programu
Program należy uruchomić z argumentami:
```
calc <plik wejsciowy> <plik wyjsciowy>
```

## 2. Plik wejściowy
Plik wejściowy jest plikiem tekstowym, gdzie działanie jest zaprogramowane w następujący sposób:
```
<operator> <podstawa>

<liczba 1>

<liczba 2>
```
Dozwolone działania to:
* dodawanie `+`
* mnożenie `*`
* potęgowanie `^`
* dzielenie całkowite `/`
* dzielenie modulo `%`


Szczególnym przypadkiem jest konwersja liczby na inny system liczbowy. Wówczas składnia wygląda tak:
```
<podstawa> <podstawa docelowa>

<liczba>
```
gdzie podstawą jest liczba całkowita z przedziału [2, 16].
Działania muszą być oddzielone od siebie trzema pustymi liniami.

## 3. Komunikaty
Po każdym prawidłowym działaniu, program wypisze w konsoli komunikat o treści "wykonano dzialanie". Jeśli napotka błąd, to zakończy wykonywania kolejnych kroków i wypisze jeden z komunikatów:


*nie udalo sie wczytac liczby* - program nie był w stanie wczytać liczby do pamięci, przyczyna nieznana


*nieprawidlowa liczba \<c> dla liczby o podstawie \<p>*: dozwolone są cyfry od 0-9 oraz a-f lub A-F


*nie udalo sie zarezerwowac pamieci*: nie udalo sie zarezerowac pamieci dla liczb wejsciowych lub zmiennej pomocniczej


*brak wymaganej pustej linii* - wymagana jest pusta linia pomiędzy operacjami i liczbami, oraz 3 puste linie pomiędzy działaniami


*nieprawidlowa podstawa systemu*: dozwolone są podstawy od 2 do 16 włącznie


*nieprawidlowe dane dzialania* -  linia z informacjami o dzialaniu zawiera błędną składnię lub nie istnieje


*nieprawidlowy typ dzialania* - w miejscu operatora znajduje się znak nieznajdujący się na liście dozwolonych operatorów


*nie udalo sie otworzyc pliku* -  plik nie istnieje lub jest zajęty przez inny proces

*nieprawidlowe argumenty* - program został uruchomiony z nieprawidłową ilością argumentów, wzór znajduje się w punkcie 1.
## 4. Plik wyjściowy
Jeśli plik istnieje, to jego treść zostanie zastąpiona przez program. Jeśli nie istnieje, to zostanie utworzony. Rozwiązania są podane w kolejności, odzielone pustą linią. Jeśli napotkano błąd, zostaną wpisane wyniki działań wykonanych przed wystąpieniem błędu.