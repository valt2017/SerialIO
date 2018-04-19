// ModemCommands Constants.h : Header-Datei
//

#if !defined(MODEM_COMMANDS_CONSTANTS_H_INCLUDED)
#define MODEM_COMMANDS_CONSTANTS_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////////

//Makros:
#if !defined(Void)
#define Void void
#endif //!defined(Void)

//Konstanten:
//Die Übertragungsgeschwindigkeit:
const DWORD DEFAULT_COM_SPEED  = CBR_9600;
const BYTE  DEFAULT_COM_PARITY = NOPARITY;
const BYTE  DEFAULT_COM_STOPB  = ONESTOPBIT;
const BYTE  DEFAULT_COM_DATAB  = 8;

//in ms; Die Zeit, nach der sich das Modem resetiert (Break-Signal):
const DWORD MODEM_RESET_TIME = 150;
//in ms; Wartezeit nach dem Modem-Reset:
#define MODEM_PAUSE_AFTER_RESET	"25000"

//Schlüsselworte für die Befehle:
//Spezielle Zeichen sind in <> einzugeben:
//<pin>, <telnr>, <cr>, <lf>, < >, <<>, <>>, <125>, <0xb1>
//Maximale Länge von speziellen Zeichen-Sequenz:
const int MAX_SPECIAL_SEQUENCE_LEN = 6;
//Befehl:
#define KEYWORD_COMMAND			"COMMAND:"
//Mögliche Werte für COMMAND:
//AT-Befehl:
#define KEYWORD_COMMAND_AT_COMMAND	"AT_COMMAND"
//Reset des Modems:
#define KEYWORD_COMMAND_MODEM_RESET	"MODEM_RESET"
//z.B.: "COMMAND: AT_COMMAND"

//Textausgabe vor dem Ausführen des Befehls:
#define KEYWORD_BEGIN_OUTTEXT	"BEGIN_OUTTEXT:" //z.B.: "BEGIN_OUTTEXT: Suche das Modem..."
//Zyklus für den AT-Befehl, maximal bis den Wert in ms:
#define KEYWORD_LOOP			"LOOP:" //z.B.: "LOOP: 10000"
//Der AT-Befehl:
#define KEYWORD_AT_COMMAND		"AT_COMMAND:" //z.B.: "AT_COMMAND: AT&D2<cr>"
//Maximale Wartezeit auf die Modem-Antwort in ms (ohne Zeit, die notwendig ist, um "echo" zu empfangen):
#define KEYWORD_WAIT_FOR_ANSWER	"WAIT_FOR_ANSWER:" //z.B.: "WAIT_FOR_ANSWER: 500"
//OK-Antwort auf den AT-Befehl. Dürfen mehrere davon definiert sein:
#define KEYWORD_OK				"OK_" //z.B.: "OK_1: <cr><lf>OK<cr><lf>"
//Fehler-Antwort auf den AT-Befehl. Dürfen mehrere davon sein:
#define KEYWORD_ERROR			"ERROR_" //z.B.: "ERROR_1: <cr><lf>ERR: 5<cr><lf>"
//Fehlertext, der beim Fehlerantwort ausgegeben werden soll:
#define KEYWORD_ERROR_TEXT		"ERROR_TEXT_" //z.B.: "ERROR_TEXT_1: Das Modem antwortet nicht."
//Textausgabe nach dem Ausführen des Befehls:
#define KEYWORD_END_OUTTEXT		"END_OUTTEXT:" //z.B.: "END_OUTTEXT: Das Modem wurde gefunden."
//Pause nach erfolgreichem Ausführen des Befehls (Wert in ms):
#define KEYWORD_PAUSE			"PAUSE:" //z.B. "PAUSE: 1000"

//Neue Zeile:
#define CR		"\r"
#define LF		"\n"
#define CRLF	"\r\n"
//Tabulator
#define TAB		"\t"

#endif // !defined(MODEM_COMMANDS_CONSTANTS_H_INCLUDED)
