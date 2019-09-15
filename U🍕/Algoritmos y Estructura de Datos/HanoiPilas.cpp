//FALCÓN CAMPOS JORGE ANTONIO, 2019. IPN.

#include <iostream> 
#include <math.h>

using namespace std; 

void Hanoi();

int discos, tope, varAux, paso=1;
bool band = false;
//pilas: N, O, D y AUX son arreglos de tam. n, n=num max de discos
int pilaN[10]; //pila que representa los datos de N
int pilaO[10]; //pila para la torre de origen
int pilaD[10]; //pila para la torre destino
int pilaAUX[10]; //pila para la torre aux
int numDiscos, origen=1, aux=2, destino=3;


int main()
{	
	cout << "\n\n Ingrese el numero de discos: "; cin >> discos;
	int movs = (pow(2, discos)-1); numDiscos = discos;
	cout << "\n El juego se solucionar\240 en " << movs << " paso(s).\n\n\n"; // pasos=(2^n)-1, n=numDiscos
	Hanoi();
}

void Hanoi() //Usando pilas
{
	tope = 0; band = false;
	while((numDiscos>0) && (band == false))
	{
		while(numDiscos>1)
		{
			tope = tope+1;
			pilaN[tope] = numDiscos;
			pilaO[tope] = origen;
			pilaD[tope] = destino;
			pilaAUX[tope] = aux;
	
			numDiscos = numDiscos-1;
			varAux = destino;
			destino = aux;
			aux = varAux;
		}
			
		cout << " - Paso " << paso++ << ": Mover disco "<< numDiscos <<" de la torre " << origen << " a la torre " << destino << ".\n";
		band = true;
	
		if(tope>0) //o sea si las listas no están vacias, se extraen los elementos del tope de las pilas
		{
			numDiscos = pilaN[tope];
			origen = pilaO[tope];
			destino = pilaD[tope];
			aux = pilaAUX[tope]; 
			tope = tope-1;
			
			cout << " - Paso " << paso++ << ": Mover disco " << numDiscos << " de la torre " << origen << " a la torre " << destino << ".\n";
			
			numDiscos = numDiscos-1;
			varAux = origen;
			origen = aux;
			aux = varAux; 
			band = false;	
		}	
	}
}



