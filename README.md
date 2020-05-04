
# Ubungsblatt 1 - Programmieren
Für alle Aufgaben gilt:

- die Verwendung von dynamischem Speicher (new/malloc) ist verboten. Placement-new
    ist erlaubt.
- keine Verwendung von zusätzlichen Bibliotheken.
- Verzicht auf Teile der Standardbibliothek die Exceptions generieren können.
- Alle Projekte werden mit-Wallund-Werror compiliert.
- Verwenden Sie das bereitgestellte unver ̈anderte Makefile.
- main() gehört in main.cpp.
- Main.cpp !=main.cpp
- Keine leeren oder sinnlosen Dateien (CPP mit lediglich einem Include ohne Code).
- Direkte Ausgabe beispielsweise mit printf ist nicht erlaubt.
- Dateinamen (.hpp != .h)
- Einordnen der Dateien:
    - Definitionen nach include
    - Implementierung nach src

Verwenden Sie Unittests um Ihren Code zu testen. Als Framework ist catch zu verwenden:
https://github.com/catchorg/Catch
Beimake startwird automatisch einen Ordnerunittestangelegt und die zu verwendente
catch-Version von github geladen. Tests können Sie mit make unittests compilieren. Alle Tests
sind in der Dateiunittest/tests.cpp zu implementieren.
Die Datei unittest/main.cpp sieht wie folgt aus:

```
1 #define CATCH_CONFIG_MAIN
2 #include "catch.hpp"
```

## Aufgabe 1: Kommandozeilenparser

Dateinamen:OptParser.h,OptParser.cpp
Schreiben Sie einen generischen Kommandozeilenparser der Optionen in folgender Form parsen
kann:

- -x (Bool, wenn gesetzt wahr, sonst falsch. info ist in diesem Fall nullptr.)
- -xwert (Integer oder Zeichenkette)
- -x wert (Integer oder Zeichenkette)
- -x=wert (Integer oder Zeichenkette)

Der auf x folgende Wert kann aus einem oder mehreren Zeichen inklusive Nummern bestehen.
Ihr Parser soll die folgende Signatur aufweisen:

```
1 class CmdLineOptParser
2 {
3 public:
4 virtual ~CmdLineOptParser () = default;
5
6 // returns true , if all arguments are successfully parsed.
7 bool Parse(int argc , char* argv []);
8
9 protected:
10 // returns true , if option was successfully parsed.
11 virtual bool Option(const char c, const char* info);
12 };
```
Hinweis: x ist nur ein beispielhafter Buchstabe. Der erste Parameter von argv ist der Name des
Programms.

## Aufgabe 2: Ausgabe

Dateinamen:Printf.h,Printf.cpp
Schreiben Sie eine eigene minimale printf Implementierung. Sie soll folgende Ausgabefunktio-
nen erfüllen:

- %d für signed int
- %u für unsigned int
- %c für ein einzelnes Zeichen
- %s für eine Zeichenkette
- %x für die Ausgabe in Hexadezimalform (0xaf)
- %b für die Ausgabe in Bin ̈ ̈arform (0b10101).
- %% für die Ausgabe des Prozentzeichens ̈
    Für x und b gilt, dass beide keine führenden Nullen darstellen und negative Zahlen nutzen
    das Zweierkomplement.

```
char* Printf(char* dst , const void* end , const char* fmt , ...);
```
Als Rückgabe erfolgt das nächste schreibbare Zeichen in dst. Der String ist an der Stelle dst
null-terminiert. end ist das letzte beschreibbare Zeichen im Buffer.


## Aufgabe 3: Strings

Dateinamen:PreAllocString.h,PreAllocString.cpp
Implementieren Sie eine String-KlassePreAllocString, welche bereits zur Compile-Zeit den
erforderlichen Speicher allokiert. Folgende Funktionen sollen implementiert werden:

```
1 operator const char *() const;
2 operator const void *() const;
3 const char & operator [] (const int idx);
4
5 /* Current number of characters in string */
6 size_t GetLength () const;
7
8 /* Maximum number of characters possible */
9 constexpr size_t SizeOf ();
10
11 /* Empty the string , set length field to zero */
12 void Empty();
13
14 PreAllocString& operator =( char rhs);
15 PreAllocString& operator =( const char * rhs);
16 PreAllocString& operator =( char * const rhs);
17
18 PreAllocString& operator +=( char rhs);
19 PreAllocString& operator +=( char const * rhs);
20
21 void AddFormat ( const char* format , ... );
22 void AddWhiteSpace ();
```
Nutzen Sie für die Ausgabe Ihre Printf-Implementierung aus der vorhergehenden Aufgabe.
Füllen Sie desweiteren, das folgende Macro in PreAllocString.h mit Leben:

```
#define CREATE(varName , size)
```
Es dient dazu, Ihre jeweilge Implementierung zu abstrahieren und ein einfaches Testen zu
erm ̈oglichen. Mit dem Marco soll es m ̈oglich sein, IhrePreAllocString-Klasse mit einer be-
stimmten Größe zu instantiieren.

## Aufgabe 4: 7-Segment Anzeige

Dateinamen:7Segment.h,7Segment.cpp

Schreiben Sie ein Programm welches die Ausgabe einer 7-Segment Anzeige simuliert. Es sollen
Zahlenfolgen von 0 - n ausgegeben werden können. Erstellen Sie hierzu eine Klasse mit dem
Namen MultiDigit.
Fügen Sie der Klasse einen Operator hinzu um die Daten in einem einizgen druckbarenchar-
Array zu erhalten:

```
1 operator const char *() const;
```
Die Ausgabe des Strings von MultiDigit{0, 1, 2, 3, 4, 5, 6, 7, 8, 9} soll wie folgt aus-
sehen:

```
 -       -   -       -   -   -   -   -
| |   |   |   | | | |   |     | | | | |
         -   -   -   -   -       -   -
| |   | |     |   |   | | |   | | |   |
 -       -   -       -   -       -   -
```


Zwei aufeinanderfolgende Ziffen sollen mit einem Leerzeichen getrennt sein.
Deseiteren soll die Implementierungconstexprsein, also zur Compile-Zeit instanziierbar. Der
folgende Code soll mit ihrer Implementierung möglich sein:

```
1 constexpr MultiDigit md0 {0};
2 constexpr MultiDigit md1{0 ,1};
3 constexpr MultiDigit md2{0,1,2};
```
Als Hilfestellung: Machen Sie sich mit constexpr if sowie variadischen Templates vertraut.

## Aufgabe 5: Speicherallokation

Dateinamen:PoolAllocator.h,PoolAllocator.cpp

Schreiben Sie einen Pool-Allokator. Er soll das folgende Interface implementieren:

```
1 class IHeap
2 {
3 public:
4 virtual void* Allocate(size_t sizeInBytes) = 0;
5 virtual void Deallocate(void *) = 0;
6 /* Returns remaining # of available bytes */
7 virtual size_t Available () const = 0;
8 };
```
Der Allokator soll generisch, also für verschiedene Objekttypen anwendar sein. Pro Objekttyp
ist dann eine Instanziierung erforderlich.
Füllen Sie desweiteren, das folgende Macro in PoolAllocator.h mit Leben:

```
#define CREATE(varName , blockCount , blockSize)
```
Es dient dazu, Ihre jeweilge Implementierung zu abstrahieren und ein einfaches Testen zu
ermöglichen. Mit dem Marco soll es möglich sein, Ihren Pool-Allokator für eine bestimmte Block-
größe (blockSize) mit einer Anzahl (blockCount) zu instantiieren.


