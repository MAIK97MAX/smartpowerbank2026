/*-------------------------------------------------------------------------*\
| Datei:        molibdisplay.h
| Version:      1.0
| Projekt:      Display-Bibliothek fuer die MEGACARD V5.5
| Beschreibung: Font-Information
| Schaltung:    MEGACARD V5.5
| Autor:        D.I. Leopold Moosbrugger
| Erstellung:   3.3.2022
|
| Aenderung:
\*-------------------------------------------------------------------------*/

// Defines für den Zeichensatz--------------------------------------------
#ifndef FONTDATA_H_
#define FONTDATA_H_

// Struktur fuer die Zeichensatzdaten
typedef struct
{
	uint8_t char_first;
	uint8_t char_last;
	uint8_t width;
	uint8_t height;
	uint8_t spacing;
} FontParam_t;

extern FontParam_t fontParam;
extern const uint8_t fontData[];
#endif /* FONTDATA_H_ */
// Defines für den Zeichensatz--------------------------------------------


// Defines für den I2C Zugriff--------------------------------------------
#ifndef TWI_SOFT_PORT_DEF_H_
#define TWI_SOFT_PORT_DEF_H_

// TWI_S_STD  100kHz
// TWI_S_FAST 400kHz
#define TWI_S_FAST

// TWI Pins festlegen (Port und Pin)
// beliebige Pins, aber auf dem gleichen Port
#define DDR_TWI_S DDRC
#define PRT_TWI_S PORTC
#define PIN_TWI_S PINC

#define PSCL_TWI_S 5
#define PSDA_TWI_S 4

#endif /* TWI_SOFT_PORT_DEF_H_ */

#ifndef TWI_SOFT_H_
#define TWI_SOFT_H_

#define  ACK 1
#define NACK 0

// Definition der Datentransfer-Richtung (lesen vom I2C Baustein)
#define I2C_READ    1

// Definition der Datentransfer-Richtung (schreiben in den I2C Baustein)
#define I2C_WRITE   0

/*-------------------------------------------------------------------------*\
| Initialisierung der beiden Pins
\*-------------------------------------------------------------------------*/
void twi_s_init(void);

/*-------------------------------------------------------------------------*\
| Legt eine  Start-Bedingung auf den Bus
| (wird auch fuer twi_s_repstart verwendet)
\*-------------------------------------------------------------------------*/
uint8_t twi_s_start(uint8_t address);
uint8_t twi_s_rep_start(uint8_t address);

/*-------------------------------------------------------------------------*\
| Legt eine  Stop-Bedingung auf den Bus
\*-------------------------------------------------------------------------*/
void twi_s_stop(void);

/*-------------------------------------------------------------------------*\
| Uebertraegt ein Byte an den Slave
\*-------------------------------------------------------------------------*/
uint8_t twi_s_write(uint8_t data);

/*-------------------------------------------------------------------------*\
| Liest ein Byte vom Slave
\*-------------------------------------------------------------------------*/
uint8_t twi_s_read(uint8_t ack);

#endif /* TWI_SOFT_H_ */
// Defines für den I2C Zugriff--------------------------------------------




#ifndef DISPLAY_H_
#define DISPLAY_H_

// Konfigurieren des Displays und der Leitungen
void display_init(void);

// Informationen zur Anzeige
// Anzahl der Zeilen
uint8_t display_lines (void);

// Anzahl der Zeichen pro Zeile (zeichensatzabhaengig)
uint8_t display_chars (void);

// erstes gueltige Zeichen im Zeichensatz
uint8_t display_char_first (void);

// letztes gueltige Zeichen im Zeichensatz
uint8_t display_char_last (void);

// Die Anzeige loeschen und den Cursor an die Position (0, 0) setzen
void display_clear();

// Verschiebt den Bildschirminhalt eine Zeile nach oben
// letzte Zeile ist leer
void display_scroll_up (void);

// Verschiebt den Bildschirminhalt eine Zeile nach unten
// erste Zeile ist leer
void display_scroll_down (void);

// Den Cursor an eine beliebige Position im Display setzen
// Bei Ueberschreiten der Limite bleibt der Cursor unveraendert
// X-Position von links nach rechts, y-Position von oben nach unten
// Zaehler beginnt bei 0
void display_pos(uint8_t posx, uint8_t posy);

// Ein Zeichen an der aktuellen Cursor-Position ausgeben und
// den Cursor um eine Stelle weiterrücken.
void display_char(uint8_t c);

// Schreibt eine Zeichenkette an die aktuelle Position
void display_string (char *line);

// Schreibt eine Zeichenkette an die Position posx, posy
void display_string_pos (uint8_t posx, uint8_t posy, char *line);

// Schreibt die formatierte Zeichenkette an die aktuelle Position
int8_t  display_printf(const char *fmt, ...);

// Schreibt die formatierte Zeichenkette an die Position posx, posy
int8_t  display_printf_pos(uint8_t posx, uint8_t posy, const char *fmt, ...);

// Schreibt ein Byte in den Grafikspeicher (Position: pcol, prow)
void display_pixel_byte (uint8_t pcol, uint8_t prow, uint8_t pbyte);

#endif /* DISPLAY_H_ */