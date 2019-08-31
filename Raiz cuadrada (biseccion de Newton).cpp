#include<iostream>
#include<stdlib.h>

using namespace std;

void MostrarOpc();
void Calcular(double y, double a, double b);
double eval(double r, double x);
double f(double a, double b, double x);

double liminf = 0, limsup = 1000, raiz, aprox; 
int cont=0;

int main() { MostrarOpc(); }

void MostrarOpc()
{ 
	double numero;
	cout << "\n ESTEq PROGRAMA TE AYUDARA A SACAR LA RAIZ CUADRADA DE UN NUMERO";
	cout << "\n\n Vamos a evaluar con el metodo de biseccion, usando la funcion (n)^2 - x \n\n  Donde: \n     n = aproximacion calculada \n     x = raiz a buscar"; 
	cout << "\n\n Escribe un numero del 0 al 1,000: "; cin >> numero;
	while( (numero<0 || numero>1000 ) )
	{
		system("cls");
		cout << "\n ERROR. Escribe solo numeros del 0 al 1,000: ";
		cin >> numero;
	}		
	Calcular(numero, liminf, limsup);
}

void Calcular(double y, double a, double b)
{
	double x = y;
	double r = (a+b)/2; 
	cont = cont + 1;

	cout << "\n\n\n\n --- Iteracion numero (" << cont << ") --- ";
	cout << "\n\n r(" << cont << ") = " << r;
	cout << " : Evaluando a r(" << cont << ") = " << r << " ... ";	
	
	do
	{
		cout << " \n   La evaluacion: f(r(" << cont << ")) = (" << r << ")^2 - " << x << " = " << aprox ;
		
		if( (eval(r,x) > -0.001 ) && (eval(r,x) < 0.001) ) 
		{ raiz = r; cout << " \n\n\n ---->  La raiz de " << x << " es: " << raiz << "  <---- \n\n";  }
		
		else
		{ 
			cout << "La evaluacion es =! 0 \n\n Calculando intervalos...";
			if( f(a,r, x) < 0)
			{
				cout << " \n\n La raiz esta entre el intervalo " << a << " y " << r;
				Calcular(x, a, r); 
			}
			
			else
			{		
				cout << " \n\n La raiz NO esta entre el intervalo " << a << " y " << r;
				cout << " \n\n Buscando en el otro intervalo... ";
				cout << "a = " << a << "; b =" << b << "; r =" << r;
				Calcular(x, r, b); 		
			}
		}
	}
	while (eval(r,x) < -0.001 && aprox > 0.001);
}


double f(double a, double b, double x) //evaluacion de las funciones
{
	double eval1 = ((a*a) - x); //evaluamos lim a
	double eval2 = ((b*b) - x); //evaluamos lim b
	double result = eval1*eval2; //multiplicamos la evaluacion. Si es < 0, la raiz está en ese intervalo
	cout << " \n   Evaluando: f(" << a << ") *  f(" << b << ") . . .";
	if (result < 0) { cout << " [ f(" << a << ")* f(" << b << ") = " << result << " ]  < 0 "; }
	else { cout << " [ f(" << a << ")* f(" << b << ") = " << result << " ]  > 0 "; }
	return result;
}

double eval(double r, double x) //evaluacion "directa" de r(n). Para saber la si la suma de los lim del intervalo/2 es la raiz buscada (a+b)/2
{
	double eval = ((r*r) - x);
	aprox = eval;
	return eval;
}








