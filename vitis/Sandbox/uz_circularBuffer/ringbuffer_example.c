#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struktur fuer die Daten
typedef struct 
{
    //Schluesselwert
    int key;
    //Name
    char name[20];
} userdata_t;

//Struktur fuer einen Ringbuffer-Handler
//wird benoetigt, um mehrere Listen zu verwalten
typedef struct
{
    //Index zum Lesen
    int readIndex;
    //Index zum Schreiben
    int writeIndex;
    //Platz fuer Speicherelemente, eigentlicher Buffer
    userdata_t *fifo;
    //Groesse des Buffers, d.h. Anzahl der Elemente
    int size;
} ringbuffer_handler_t;

/*-------------------------------------------------------------------------*/

//eine Funktion, um einen Ringbuffer anzulegen
//Parameter size: Groesse des Buffers (Anzahl der Elemente)
//Rückgabewert: Zeiger auf Ringbuffer-Handler
ringbuffer_handler_t *createFIFO(int size)
{
    //Zeiger auf Ringbuffer-Handler deklarieren und genuegend Speicher
    //reservieren
    ringbuffer_handler_t *buffer = 
	(ringbuffer_handler_t *)malloc(sizeof(ringbuffer_handler_t));
    
    //Werte des Handler belegen
    //readIndex und WriteIndex zu Anfang 0
    //fuer fifo muss genuegend Speicher reserviert werden, 
    //um size Datenelemente aufnehmen zu koennen
    //size gibt Anzahl der Elemente im Ringbuffer an (aus Parameter)
    buffer->readIndex=0;
    buffer->writeIndex=0;
    buffer->fifo = (userdata_t *)malloc(sizeof(userdata_t) * (size + 1));
    buffer->size = size;

    //Zeiger auf Ringbuffer-Handler zurueckgeben
    return buffer;
}

/*-------------------------------------------------------------------------*/

//eine Funktion, um Elemente anzuhaengen, d.h. in den Buffer zu schreiben
//Parameter data: Daten, die in den Buffer geschrieben werden sollen
//Parameter *buffer: Zeiger auf Ringbuffer-Handler
//kein Rueckgabewert 
void appendFIFO(userdata_t data, ringbuffer_handler_t *buffer)
{
    //Ringbuffer-Handler muss gueltig sein
    if(buffer)
    {
	//Daten in den entsprechenden Platz im Buffer schreiben
	//dafuer ist writeIndex da
	buffer->fifo[buffer->writeIndex] = data;
	//writeIndex wird fuer das naechste Schreiben auf den neuen Wert
	//gesetzt
	//Achtung: wenn der Buffer voll ist, wird wieder vorne hineinge-
	//schrieben (deshalb RINGbuffer), Daten koennen verloren gehen,
	//wenn nicht zwischendurch gelesen wird
	buffer->writeIndex = buffer->writeIndex++ % (buffer->size+1);
	//an dieser Stelle ist es deshalb sinnvoll, den readIndex auf den
	//letzen wahren Wert zu setzen, wenn NICHT zwischendurch gelesen
	//wurde
	if(buffer->readIndex == buffer->writeIndex)
	    buffer->readIndex = buffer->readIndex ++ % (buffer->size+1);
    }
}

int readFIFO(userdata_t *data, ringbuffer_handler_t *buffer)
{
    //Ringbuffer-Handler muss gueltig sein
    if(buffer)
    {
	//der writeIndex zeigt immer auf das naechste zu beschreibende Element,
	//d.h. dieses Element ist noch nicht beschrieben worden und enthaelt
	//deshalb keine gueltigen Daten
	//wenn readIndex also gleich writeIndex, darf nicht gelesen werden
	if(buffer->readIndex != buffer->writeIndex)
	{
	    //Daten kopieren
	    *data = buffer->fifo[buffer->readIndex];
	    //readIndex fuer das naechste Lesen hochsetzen
	    buffer->readIndex = buffer->readIndex++ % (buffer->size+1);
	    //Rueckgabewert 1, da gelesen wurde
	    return 1;
	}
	else
	    //es konnten keine Daten gelesen werden, da keine gueltigen Daten
	    //Rueckgabewert also -1
	    return -1;
    }
    //es konnte nicht gelesen werden, da Buffer-Handler nicht gueltig, 
    //Ruckegabewert also -1
    else return -1;
}

/*-------------------------------------------------------------------------*/

int main()
{
    //eine Variable fuer die Daten
    userdata_t data;
    //ein Ringbuffer-Handler
    ringbuffer_handler_t *buffer;
    //eine Variable, um Ergebnisse von readFIFO() abzufragen
    int ergebnis;

    //einen Ringbuffer-Handler und damit auch einen Ringbuffer anlegen
    buffer = createFIFO(2);

    //Daten anlegen und in den Buffer schreiben
    data.key=10;
    strcpy(data.name, "hans");
    appendFIFO(data, buffer);
    
    //nochmal Daten anlegen und in den Buffer schreiben
    data.key=11;
    strcpy(data.name,"franz");
    appendFIFO(data, buffer);

    //Daten aus Buffer holen, wenn erfolgreich, dann ausgeben
    ergebnis = readFIFO(&data, buffer);
    if(ergebnis == 1)
    {
	printf("%d %s\n", data.key, data.name);
    }

    //Daten aus Buffer holen, wenn erfolgreich, dann ausgeben
    ergebnis = readFIFO(&data, buffer);
    if(ergebnis == 1)
    {
	printf("%d %s\n", data.key, data.name);
    }

    //nochmal Daten anlegen und in den Buffer schreiben
    data.key=12;
    strcpy(data.name,"egon");
    appendFIFO(data, buffer);

    //Daten aus Buffer holen, wenn erfolgreich, dann ausgeben
    ergebnis = readFIFO(&data, buffer);
    if(ergebnis == 1)
    {
	printf("%d %s\n", data.key, data.name);
    }

    //jetzt einmal soviele Daten anlegen, dass Daten ueberschrieben werden
    data.key=13;
    strcpy(data.name, "walter");
    appendFIFO(data, buffer);
    data.key=14;
    strcpy(data.name, "werner");
    appendFIFO(data, buffer);
    data.key=15;
    strcpy(data.name, "wolfgang");
    appendFIFO(data, buffer);
    data.key=16;
    strcpy(data.name, "felix");

    //Daten aus Buffer holen, wenn erfolgreich, dann ausgeben
    //Der Datensatz (13, walter) ist verlorengegangen!), weil
    //nicht oft genug gelesen wurde
    ergebnis = readFIFO(&data, buffer);
    if(ergebnis == 1)
    {
	printf("%d %s\n", data.key, data.name);
    }
}

   