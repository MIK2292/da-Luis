#include <iostream>
#include <iomanip>
#include <map>
#include <utility>
#include <string>
#include <algorithm>
using namespace std;

struct verdura{
	string tipo;
	float prezzo_unitario;
};

struct quantita{
	float peso;
	float prezzo_complessivo;
};

struct verdura_comparator{
	bool operator()(verdura V1, verdura V2)
	{
		return V1.tipo < V2.tipo;
	}
};

map<verdura, quantita>::iterator BinarySearch(
	map<verdura, quantita>::iterator it1, 
	map<verdura, quantita>::iterator it2, int size, string verd)
{
	map<verdura, quantita>::iterator mid = next(it1, size/2);
		
	if (mid->first.tipo == verd)
		return mid;
	else if (mid->first.tipo > verd)
		return BinarySearch(it1, mid--, size/2, verd);
	else if (mid->first.tipo < verd)
		return BinarySearch(mid++, it2, size/2 +1, verd);
	else 
		cerr<<"\n\n\tError 404, verdura not found";
}

map<verdura, quantita, verdura_comparator> input(vector<verdura> elenco)
{
	map<verdura, quantita, verdura_comparator> Scontrino;
	for (verdura Verd : elenco)
		Scontrino.insert({Verd, {0,0}});
		
	int counter;
	string verd;
	float peso;
	map<verdura, quantita>::iterator it_verdura = Scontrino.begin();
	
	cout << "Quante verdure vuoi inserire?\n";
	cin >> counter;
	
	for (int i = 0; i < counter; i++)
	{
		cout << "\nInserisci il tipo di verdura: ";
		cin >> verd;
		cout << "\nInserisci il peso: ";
		cin >> peso;
		
		it_verdura = BinarySearch(Scontrino.begin(), Scontrino.end(), 
								  Scontrino.size(), verd);
		
		it_verdura->second.peso += peso;
		it_verdura->second.prezzo_complessivo += 
			it_verdura->first.prezzo_unitario * peso;
			
		it_verdura++;
	}
	return Scontrino;
}

void stampa_scontrino(map<verdura, quantita, verdura_comparator> Scontrino)
{
	float tot;
	
	cout << "\n\n\t" << "Verdura" 
		 << ":\t" << "Peso" 
		 << "\t" << "Costo\n";
	
	for (pair<verdura, quantita> x : Scontrino)
	{
		if (x.second.prezzo_complessivo != 0)
		{
			
		if(x.first.tipo.size() < 7)
		{
			cout << "\n\n\t" << x.first.tipo 
			 << ":\t\t" << x.second.peso 
			 << " kg\t" << x.second.prezzo_complessivo << char(36);
		}
		else
		{
			cout << "\n\n\t" << x.first.tipo 
			 << ":\t" << x.second.peso 
			 << " kg\t" << x.second.prezzo_complessivo << char(36);
		}
		tot += x.second.prezzo_complessivo;
		
		}
	}
	
	cout << "\n\n\n\tTot:\t\t\t" << tot;
}

int main()
{
	vector<verdura> prezzario = {{"pomodori", 0.85}, {"melanzane", 1.20}, 
			{"peperoni", 0.70}, {"carote", 1.25}, {"zucchine", 2.20}, 
			{"simone", 0.20}, {"fragole", 2.50}, {"castagne", 8576}};
			
	map<verdura, quantita, verdura_comparator> Scontrino = input(prezzario);
	stampa_scontrino(Scontrino);
}




