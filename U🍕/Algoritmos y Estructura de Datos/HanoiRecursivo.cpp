//FALCÓN CAMPOS JORGE ANTONIO, 2019. IPN.

#include <iostream> 
#include <math.h>

using namespace std; 

void Hanoi(int numDiscos, int T1, int T2, int T3);

int discos, movs, paso=1;

int main()
{	
	cout << "\n\n Ingrese el numero de discos: "; 
	cin >> discos;
	movs = (pow(2, discos)-1);
	cout << "\n El juego se solucionar\240 en " << movs << " paso(s).\n\n\n";
	Hanoi(discos, 1, 2, 3);
}

void Hanoi(int numDiscos, int T1, int T2, int T3) 
{
	if(numDiscos==1) { cout<< " - Paso " << paso++ << ": Mover disco #" << T1 << " de la torre " << T1 << " a la torre " << T3 << ".\n"; }
	else
	{
		Hanoi(numDiscos-1, T1, T3, T2);
		cout<< " - Paso " << paso++ << ": Mover disco #" << numDiscos <<  " de la torre " << T1 << " a la torre " << T3 << ".\n"; 
		Hanoi(numDiscos-1, T2, T1, T3);
	}
}
