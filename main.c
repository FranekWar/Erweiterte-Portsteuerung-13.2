/*****************************************************************************
h e i n r i c h -h e r t z -b e r u f s k o l l e g  d e r  s t a d t  b o n n
Autor:			Warsitz, Franek
Klasse:			IAH221
Datum:			30.10.2024
Datei:			Erwiterte Portsteuerung
Einsatz:		Zähler mit möglcihkeiten einen Startwert zu setzen 
Beschreibung:	Zähler kann auf einen Anfangswert gesetzt werden und bei Überlauf, beginnt dieser von vorne 
Funktionen:		
******************************************************************************
Aenderungen:

*****************************************************************************/
/******************* Text im Quelltext einbinden *********************/
#include "REG517A.h"

/*************************** Konstanten ******************************/


/*********************** globale Variablen ***************************/


/************************** Prototypen *******************************/
char ziffer(int zifferwert);
void delay(int ms);
void zaehler(int wert, int zaehler);

/************************ Hauptprogramm ******************************/

void main()
{
	
	int zahl[4] = {0,3,0,5};
	int zaehler1 = 0;
	
	//hauptschleife
	while(1)
	{
		zaehler1 = 0;
		for(zaehler1 = 0;zaehler1 < 3;zaehler1 = zaehler1 + 1)
		{
			zaehler(zahl[zaehler1], zaehler1);
		}
		
	}

}

char ziffer(int zifferwert)
{
	char rueckgabewert;
	
	if(zifferwert == 0)
	{
		rueckgabewert = 0xBB;
	}
	else if(zifferwert == 1)
	{
		rueckgabewert = 0x82;
	}
	else if(zifferwert == 2)
	{
		rueckgabewert = 0x1F;
	}
	else if(zifferwert == 3)
	{
		rueckgabewert = 0x8F;
	}
	else if(zifferwert == 4)
	{
		rueckgabewert = 0xA6;
	}
	else if(zifferwert == 5)
	{
		rueckgabewert = 0xAD;
	}
	else if(zifferwert == 6)
	{
		rueckgabewert = 0xBD;
	}
	else if(zifferwert == 7)
	{
		rueckgabewert = 0xA3;
	}
	else if(zifferwert == 8)
	{
		rueckgabewert = 0xBF;
	}
	else if(zifferwert == 9)
	{
		rueckgabewert = 0xAF;
	}
	else
	{
	
	}
	
	return rueckgabewert;
}

void delay(int ms)
{	
	int zaehler1 = 0;
	int geschwindigkeit = 0;
	unsigned int zaehler2 = 0;
	for(zaehler1 = 0;zaehler1 < 3;zaehler1 = zaehler1 + 1)
	{
		for(zaehler2 = 0;zaehler2 < (11 * (ms + geschwindigkeit));zaehler2 = zaehler2 + 1)
		{
	
		}
	}
}

void zaehler(int wert, int zaehler)
{
	char Port =  0;
	char maske = 0xF0;
	
	Port = P6;
	Port = Port | maske;
	
	if(zaehler == 0)
	{
		maske = 0x7F;
		Port = Port & maske;
		P6 = Port;
		P4 = ziffer(wert);
		
	}
	else if(zaehler == 1)
	{
		maske = 0xBF;
		Port = Port & maske;
		P6 = Port;
		P4 = ziffer(wert);

	}
	else if(zaehler == 2)
	{
		maske = 0xDF;
		Port = Port & maske;
		P6 = Port;
		P4 = ziffer(wert);
		
	}
	else if(zaehler == 3)
	{
		maske = 0xEF;
		Port = Port & maske;
		P6 = Port;
		P4 = ziffer(wert);
	}
	else
	{
	}
}
