#include <iostream> 
#include <string>
#include <time.h>
#include <random>
#include <algorithm>
using namespace std; 


struct tavolo
{
	int max_persone;
	float altezza;
	float lunghezza;
	float larghezza;
	int num_persone;
};
struct Locanda
{
	int tot_persone;
	int persone_att;
	vector <tavolo> tavoli;
	
};

void sleep(int secondi = 2)
{
	int then = time(NULL) + secondi;
	
	while(time(NULL) != then){}
	
	return;
}

tavolo tavoli()
{
	float altezza, lunghezza, larghezza;
	int max_persone=0;
	cout<<"Inserisci le dimensioni del tavolo"<<endl<<"Altezza: ";
	cin>>altezza;
	while(altezza<0.5 || altezza>1.5)
	{
		cout<<"Inserisci un'altezza adeguata, compresa tra 0,5 e 1,5 metri: ";
		cin>>altezza;
	}
	cout<<"Lunghezza: ";//>1.00 metri
	cin>>lunghezza;
		while(lunghezza<1 || lunghezza>4)
	{
		cout<<"Inserisci una lunghezza adeguata, compresa tra 1 e 4 metri: ";
		cin>>lunghezza;
	}
	cout<<"Larghezza: ";//>1.00 metri
	cin>>larghezza;
		while(larghezza<1 || larghezza>4)
	{
		cout<<"Inserisci una larghezza adeguata, compresa tra 1 e 4 metri: ";
		cin>>larghezza;
	}
	int g=lunghezza*larghezza;
	if (g>=1 && g<=6)
	{
		max_persone=6;	
	}
	else if(g>=6 && g<=8)
	{
		max_persone=8;
	}
	else if(g>=8 && g<=12)
	{
		max_persone=12;
	}
	else if(g>=12 && g<=16)
	{
		max_persone=16;
	}
	else
	{
		cerr << "errore\n";
	}

	return {max_persone, altezza, lunghezza, larghezza};	
}

tavolo new_tavolo(float altezza, float lunghezza, float larghezza)
{
	int max_persone=0;
	int g=lunghezza*larghezza;
	if (g>=1 && g<=6)
	{
		max_persone=6;	
	}
	else if(g>=6 && g<=8)
	{
		max_persone=8;
	}
	else if(g>=8 && g<=12)
	{
		max_persone=12;
	}
	else if(g>=12 && g<=16)
	{
		max_persone=16;
	}
	else
	{
		cerr << "errore\n";
	}

	return {max_persone, altezza, lunghezza, larghezza};	
}


bool comparatore(tavolo t1, tavolo t2)
{
	return(t1.max_persone<t2.max_persone);
}

void stampa(Locanda&L1)
{ 	
	cout<<endl<<"La locanda:"<<endl<<endl<<"Tot_persone: "<<L1.tot_persone<<endl;
	cout<<"Le persone attualmente nella locanda sono: "<<L1.persone_att<<endl;
	cout<<"Tutti i tavoli della locanda: "<<endl<<endl;
	for(auto culo:L1.tavoli)
	{
		cout<<"Max persone: "<<culo.max_persone<<endl;
		cout<<"Altezza: "<<culo.altezza<<endl;
		cout<<"Lunghezza: "<<culo.lunghezza<<endl;
		cout<<"Larghezza: "<<culo.larghezza<<endl;
		cout<<"Num_persone: "<<culo.num_persone<<endl<<endl<<endl;
	}
}

void inserimento_tavoli(vector<tavolo> &tav, int &tot_persone)
{
	int t = 0;
	while(t<4)
	{
		tav.push_back(tavoli());
		tot_persone=tav[t].max_persone+tot_persone;
		cout<<tav[t].max_persone<<endl;
		t++;
	}
}

void Gente_che_entra(Locanda &da_Luis, int sleep_time)
{
	int n_persone = rand()%100 +1;
	if (n_persone <= 20) //20% 1p
	{
		n_persone = 1;
	}
	else if (n_persone <= 35+20) //35% 2p
	{
		n_persone = 2;
	}
	else if (n_persone <= 15+35+20) //15% 3p
	{
		n_persone = 3;
	}
	else if (n_persone <= 12+15+35+20) //12% 4p
	{
		n_persone = 4;
	}
	else if (n_persone <= 12+12+15+35+20) //12% 5p
	{
		n_persone = 5;
	}
	else if (n_persone <= 6+12+12+15+35+20) //6% 6p
	{
		n_persone = 6;
	}
	//cout << "Sono arrivate " << n_persone << " persone\n";
	
	bool HannoTrovatoPosto = 0;
	for (int i = 0; i < da_Luis.tavoli.size(); i++)
	{
		if (da_Luis.tavoli[i].max_persone - da_Luis.tavoli[i].num_persone >= n_persone)
		{ 
			da_Luis.persone_att += n_persone;
			da_Luis.tavoli[i].num_persone += n_persone;
			cout << "- Si sono aggiunte " << n_persone 
				 << " persone al tavolo n." << i+1 << endl
				 << "    Ora questo tavolo ha " << da_Luis.tavoli[i].num_persone 
				 << " posti occupati su " << da_Luis.tavoli[i].max_persone 
				 << endl << endl;
			HannoTrovatoPosto = 1;
			break;
		}
	}
	
	if (HannoTrovatoPosto == 0)
	{
		cout << "- " << n_persone << " persone non hanno trovato posto\n\n";
	}
	
	sleep(sleep_time);
}

void Gente_che_esce(Locanda &da_Luis, int sleep_time)
{
	int n_tavolo = rand()%da_Luis.tavoli.size(); //da quale tavolo se ne vanno le persone
		
		if (da_Luis.tavoli[n_tavolo].num_persone > 0)
		{
			int n_persone = rand()%da_Luis.tavoli[n_tavolo].num_persone +1;
			//quante persone se ne vanno da quel tavolo
		
			da_Luis.persone_att -= n_persone;
			da_Luis.tavoli[n_tavolo].num_persone -= n_persone;
			cout << "- " << n_persone << " persone hanno lasciato il tavolo n." 
				 << n_tavolo+1 << endl
				 << "    Ora questo tavolo ha " << da_Luis.tavoli[n_tavolo].num_persone 
				 << " posti occupati su " << da_Luis.tavoli[n_tavolo].max_persone 
				 << endl << endl;
			
			sleep(sleep_time);
		}
}

void stampa_tavoli(const vector<tavolo> tavoli)
{
	for(int i = 0; i < tavoli.size(); i++)
	{
		cout << "Tavolo n." << i+1 << endl
			<<"\tPosti occupati: " << tavoli[i].num_persone << endl
			<<"\tPosti totali:   " << tavoli[i].max_persone << endl << endl;
	}
	cout << endl;
}



int main()
{
	vector <tavolo> tot_tavoli;
	int tot_persone=0;
	
//	inserimento_tavoli(tot_tavoli, tot_persone);
	
	for(int i = 0; i < 4; i++)
	{
		tot_tavoli.push_back(new_tavolo(1,rand()%4+1,rand()%4+1));
		tot_persone=tot_tavoli[i].max_persone+tot_persone;
	}
				
	sort(tot_tavoli.begin(), tot_tavoli.end(), comparatore);
//	cout<<endl<<tot_persone;

	Locanda da_Luis={tot_persone, 0, tot_tavoli};
	//stampa(da_Luis);

	srand(time(NULL));
	const int sleep_time = 2;
	
//	int cicli;
//	cout << "\n\nInserire il numero di cicli da eseguire:\n";
//	cin >> cicli;
	
	int counter1 = 0;
	int counter2 = 0;
	while( true /*counter < cicli*/)
	{
		counter2 = 0;
		while(counter2 < 5)
		{
		// i primi cicli la ggente tende a riempire la locanda
		// gli ultimi cicli servono per svuotare la locanda
		
		counter1 =0;
		
		while(counter1<2)
		{
			
			if (counter2 < 3)
			{
				for (int i = 0; i < 3; i++)
					Gente_che_entra(da_Luis, sleep_time);
					//persone che arrivano
				
				for (int i = 0; i < 1; i++)
					Gente_che_esce(da_Luis, sleep_time);
					//persone che se ne vanno
			}
			else
			{
				for (int i = 0; i < 1; i++)
					Gente_che_entra(da_Luis, sleep_time);
					//persone che arrivano
				
				for (int i = 0; i < 3; i++)
					Gente_che_esce(da_Luis, sleep_time);
					//persone che se ne vanno
			}
			counter1++;
		
		}//end while
		
		cout << "\n\nLa locanda 'da Luis' ha attualmente " << da_Luis.persone_att 
			 << " clienti su " << da_Luis.tot_persone << " posti disponibili.\n\n";
		stampa_tavoli(da_Luis.tavoli);
			 
		sleep(sleep_time);
		
		counter2++;
		
		}//end while
		
	}//end while
	
	return 0;
}







