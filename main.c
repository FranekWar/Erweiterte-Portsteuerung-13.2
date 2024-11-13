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
13.11.2024: 
Matrix Tastur Funkiton wurde hinzugefügt, und es wurde die Globale Variable hinzugefügt.
Rechner rechnet die Zahl entweder hoch bzw. runter ist jetzt funktionstüchtig
	

*****************************************************************************/
/******************* Text im Quelltext einbinden *********************/
#include "REG517A.h"

/*************************** Konstanten ******************************/


/*********************** globale Variablen ***************************/
int ZAHL[4] = {0,0,0,9}; 

/************************** Prototypen *******************************/
void erstEingabe();
//setzt einen Zahlenwert über die Tastaturmatrix

char ziffer(int zifferwert);
//nimmt eine Ziffer auf 0-9 und konventriert diese in die HEXA zahl
//welche die jeweilige Ziffer auf der Siebensegmentanzeige anzeigt 
void delay(int ms);
// macht eine pause 
void zaehler(int wert, int zaehler);
// bringt die ziffer auf das jeweilige Segment der Siebensegmentanzeige
int isMatrixtaste_gedrueckt(int bitnr); //0: alle 16-> 
// 1= Bit1 (A1), 2= Bit2 (A2) u.s.w. bis D4
// liefert bei einzel Bit Abfrage (Code für Taster s.u.) 
// eine 0 falls nicht gedrückt und eine 1 falls gedrückt
// wenn alle Bits angefordert werde (0) dann enthält jedes Bit des Rückgabewertes 
// den entsprechenden Tastendruck:
//A1: 0x0008,A2: 0x0004, A3: 0x0002,A4: 0x0001
//B1: 0x0080,B2: 0x0040, B3: 0x0020,B4: 0x0010
//C1: 0x0800,C2: 0x0400, C3: 0x0200,C4: 0x0100
//D1: 0x8000,D2: 0x4000, D3: 0x2000,D4: 0x1000
void rechner(int plusOderMinus); //zählt die zahl ("ZAHL" globale Variable)
//entweder bei plusOderMinus = 0 hoch (+1)
//oder bei plusOderMinus = 1 runter (-1)


//Abfrage des Tasters am P5.0 bei Rückgabe: 0 = nicht gedrückt / 1 = ist gedrückt
/************************ Hauptprogramm ******************************/

void main()
{
	
	int zaehler1 = 0;
	int zaehler2 = 0;
	int geschwindigkeit = 100;
	

	erstEingabe();
	//start Knopf 

	
	//hauptschleife
	while(1)
	{
		
		rechner(1);
		for(zaehler2 =0;  zaehler2 < geschwindigkeit; zaehler2 = zaehler2 +1)
		{
			
			for(zaehler1 = 0;zaehler1 < 4;zaehler1 = zaehler1 + 1)
			{
			
				
				zaehler(ZAHL[zaehler1], zaehler1);		
				delay(1);
			}
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

void rechner(int plusOderMinus) 
{
	if( plusOderMinus == 0)
	{
		if(ZAHL[3] < 9)
		{
			ZAHL[3] = ZAHL[3] + 1;
		}
		else
		{
			ZAHL[3] = 0;
			if (ZAHL[2] < 9)
			{
				ZAHL[2] = ZAHL[2] + 1;
			}
			else
			{
				ZAHL[2] = 0;
				if (ZAHL[1] < 9)
				{
					ZAHL[1] = ZAHL[1] + 1;
				}
				else
				{
					ZAHL[1] = 0;
					if (ZAHL[0] < 9)
					{
						ZAHL[0] = ZAHL[0] + 1;
					}
					else
					{
						ZAHL[0] = 0;
					}
				}
			}
		}
	}
	else if (plusOderMinus == 1)
	{
		if(ZAHL[3] > 0)
		{
			ZAHL[3] = ZAHL[3] - 1;
		}
		else
		{
			ZAHL[3] = 9;
			if (ZAHL[2] > 0)
			{
				ZAHL[2] = ZAHL[2] - 1;
			}
			else
			{
				ZAHL[2] = 9;
				if (ZAHL[1] > 0)
				{
					ZAHL[1] = ZAHL[1] - 1;
				}
				else
				{
					ZAHL[1] = 9;
					if (ZAHL[0] > 0)
					{
						ZAHL[0] = ZAHL[0] - 1;
					}
					else
					{
						ZAHL[0] = 9;
					}
				}
			}
		}
	}
	else //nichts
	{
	
	}
}

//Abfrage der Matrixtastatur Übergabe: 0: alle 16 Tasten abfragen und Ergebnis zurückgeben 1= Bit1 (A1), 2= Bit2 (A2) u.s.w. bis D4
//liefert bei einzel Bit Abfrage (Code für Taster s.u.) eine 0 falls nicht gedrückt und eine 1 falls gedrückt
//wenn alle Bits angefordert werde (0) dann enthält jedes Bit des Rückgabewertes den entsprechenden Tastendruck:
//A1: 0x0008,A2: 0x0004, A3: 0x0002,A4: 0x0001
//B1: 0x0080,B2: 0x0040, B3: 0x0020,B4: 0x0010
//C1: 0x0800,C2: 0x0400, C3: 0x0200,C4: 0x0100
//D1: 0x8000,D2: 0x4000, D3: 0x2000,D4: 0x1000
int isMatrixtaste_gedrueckt(int bitnr)
{
	int status = 0;
	char P8M = 0;
	char P6M = 0;
	int zeile = 0;
	int spalte = 0;
  char spaltenmaske = 0xF0;
	
	if(bitnr == 0x0000)
	{
	 for(spalte = 1;spalte <= 8;spalte = spalte * 2)//4 Spalten abfragen
	 {
		spaltenmaske = 0xF0 - 0x10*spalte;
		//Spalte maskieren
		P6 = P6 & 0x0F;//oberes Nibble alle auf Null
		
		P6 = P6 | (spaltenmaske);//oberes Nibble eine Spalte auswählen
		
		//Zeilen abfragen
		P8M = P8 & 0x0F; //-> 0x0E Zeile A, 0x0D Zeile B,0x0B Zeile C, 0x07 Zeile D
		
		//Auswerten

    if(P8M == 0x0E)			
		{
			//A1-4, Je nach Spalte Bit in status setzen
			switch(spalte)
			{
				case 1:
					status = status | 0x01;
					break;
				case 2:
					status = status | 0x02;
					break;
				case 4:
					status = status | 0x04;
					break;
				case 8:
					status = status | 0x08;
					break;
			}
		}
		else if(P8M == 0x0D)
		{
			//B1-4
			switch(spalte)
			{
				case 1:
					status = status | 0x0010;
					break;
				case 2:
					status = status | 0x0020;
					break;
				case 4:
					status = status | 0x0040;
					break;
				case 8:
					status = status | 0x0080;
					break;
			}
		}	
		else if(P8M == 0x0C) //Reihe A und B gleichzeitig
		{
			switch(spalte)
			{
				case 1: //A4/B4
					status = status | 0x0011;
					break;
				case 2: //A3/B3
					status = status | 0x0022;
					break;
				case 4: //A2/B2
					status = status | 0x0044;
					break; //A1/B1
				case 8:
					status = status | 0x0088;
					break;
			}
		}		
		else if(P8M == 0x0B)
		{
			//C1-4
			switch(spalte)
			{
				case 1:
					status = status | 0x0100;
					break;
				case 2:
					status = status | 0x0200;
					break;
				case 4:
					status = status | 0x0400;
					break;
				case 8:
					status = status | 0x0800;
					break;
			}
		}	
		else if(P8M == 0x0A) //Reihe A und C gleichzeitig
		{
			switch(spalte)
			{
				case 1:
					status = status | 0x0101;
					break;
				case 2:
					status = status | 0x0202;
					break;
				case 4:
					status = status | 0x0404;
					break;
				case 8:
					status = status | 0x0808;
					break;
			}
		}		
		else if(P8M == 0x09) //Reihe B und C gleichzeitig
		{
			switch(spalte)
			{
				case 1:
					status = status | 0x0110;
					break;
				case 2:
					status = status | 0x0220;
					break;
				case 4:
					status = status | 0x0440;
					break;
				case 8:
					status = status | 0x0880;
					break;
			}
		}					
		else if(P8M == 0x07)
		{
			//D1-4
						switch(spalte)
			{
				case 1:
					status = status | 0x1000;
					break;
				case 2:
					status = status | 0x2000;
					break;
				case 4:
					status = status | 0x4000;
					break;
				case 8:
					status = status | 0x8000;
					break;
			}
		}	
		else if(P8M == 0x06) //Reihe A und D gleichzeitig
		{
			switch(spalte)
			{
				case 1:
					status = status | 0x1001;
					break;
				case 2:
					status = status | 0x2002;
					break;
				case 4:
					status = status | 0x4004;
					break;
				case 8:
					status = status | 0x8008;
					break;
			}
		}		
		else if(P8M == 0x05) //Reihe B und D gleichzeitig
		{
			switch(spalte)
			{
				case 1:
					status = status | 0x1010;
					break;
				case 2:
					status = status | 0x2020;
					break;
				case 4:
					status = status | 0x4040;
					break;
				case 8:
					status = status | 0x8080;
					break;
			}
		}		
		else if(P8M == 0x03) //Reihe C und D gleichzeitig
		{
			switch(spalte)
			{
				case 1:
					status = status | 0x1100;
					break;
				case 2:
					status = status | 0x2200;
					break;
				case 4:
					status = status | 0x4400;
					break;
				case 8:
					status = status | 0x8800;
					break;
			}
		}					
		else
		{}
	 }
  }
	else
	{
		//einzelne Taste abfragen		
		if(bitnr == 0x0001)//A4
		{
			spaltenmaske = 0xF0 - 0x10*1;
			//Spalte maskieren
			P6 = P6 & 0x0F;//oberes Nibble alle auf Null
		
			P6 = P6 | (spaltenmaske);//oberes Nibble eine Spalte auswählen
			
			//Zeilen abfragen
			P8M = P8 & 0x0F; //-> 0x0E Zeile A, 0x0D Zeile B,0x0B Zeile C, 0x07 Zeile D
			if(P8M == 0x0E)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if(bitnr == 0x0002)//A3
		{
			spaltenmaske = 0xF0 - 0x10*2;
			//Spalte maskieren
			P6 = P6 & 0x0F;//oberes Nibble alle auf Null
		
			P6 = P6 | (spaltenmaske);//oberes Nibble eine Spalte auswählen
			
			//Zeilen abfragen
			P8M = P8 & 0x0F; //-> 0x0E Zeile A, 0x0D Zeile B,0x0B Zeile C, 0x07 Zeile D
			if(P8M == 0x0E)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if(bitnr == 0x0004)//A2
		{
			spaltenmaske = 0xF0 - 0x10*4;
			//Spalte maskieren
			P6 = P6 & 0x0F;//oberes Nibble alle auf Null
		
			P6 = P6 | (spaltenmaske);//oberes Nibble eine Spalte auswählen
			
			//Zeilen abfragen
			P8M = P8 & 0x0F; //-> 0x0E Zeile A, 0x0D Zeile B,0x0B Zeile C, 0x07 Zeile D
			if(P8M == 0x0E)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if(bitnr == 0x0008)//A1
		{
			spaltenmaske = 0xF0 - 0x10*8;
			//Spalte maskieren
			P6 = P6 & 0x0F;//oberes Nibble alle auf Null
		
			P6 = P6 | (spaltenmaske);//oberes Nibble eine Spalte auswählen
			
			//Zeilen abfragen
			P8M = P8 & 0x0F; //-> 0x0E Zeile A, 0x0D Zeile B,0x0B Zeile C, 0x07 Zeile D
			if(P8M == 0x0E)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else if(bitnr == 0x0010)//B4
		{		
		}
		else if(bitnr == 0x0020)//B3
		{
		}
		else if(bitnr == 0x0040)//B2
		{
		}
		else if(bitnr == 0x0080)//B1
		{
		}
		else if(bitnr == 0x0100)//C4
		{
		}
		else if(bitnr == 0x0200)//C3
		{
		}
		else if(bitnr == 0x0400)//C2
		{
		}
		else if(bitnr == 0x0800)//C1
		{
		}
		else if(bitnr == 0x1000)//D4
		{
		}
		else if(bitnr == 0x2000)//D3
		{
		}
		else if(bitnr == 0x4000)//D2
		{
		}
		else if(bitnr == 0x8000)//D1
		{
		}
		else
		{}
	}
	return status;
}


void erstEingabe()
{
	int index1 = 0;
	for(index1 = 0; index1 < 4; index1 = index1 + 1)
	{
		
		switch(isMatrixtaste_gedrueckt(0))
		{
			case 0x0008:
				ZAHL[index1] = 1;
				break;
			case 0x0004:
				ZAHL[index1] = 2;
				break;
			case 0x0002:
				ZAHL[index1] = 3;
				break;
			case 0x0001:
				ZAHL[index1] = 4;
				break;
		}
			
	}
}
//Abfrage des Tasters am P5.0 bei 
//Rückgabe: 0 = nicht gedrückt / 1 = ist gedrückt
