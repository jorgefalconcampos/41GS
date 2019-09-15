//FALCÓN CAMPOS JORGE ANTONIO, 2019. IPN.

#include <iostream>
#include <conio.h>
			
short int FilasMatrizA = 0, ColumnasMatrizA = 0;
short int FilasMatrizB = 0, ColumnasMatrizB = 0; 
int f,c;
	
void InsertarDatosMatriz(short int Af, short int Ac, short int Bf, short int Bc)
{
	short int MatrizA[Af][Ac], MatrizB[Bf][Bc];

	printf("\n -> MATRIZ A, de orden %hd x %hd <-\n", Af, Ac); 
	
	for(f=1; f<=FilasMatrizA; f++) //Recorre la matriz A por filas, elemento x elemento en esa fila y les asinga un valor
	{
		printf("\n"); 
		for(c=1; c<=ColumnasMatrizA; c++)
		{ 
			printf("   A(%hd,%hd): ",f, c); //se imprime el siguiente formato -> B(f,c): 
			scanf("%hd", &MatrizA[f][c]); //aqui se asigna el valor dado por el usuario
		}
	}
	
	printf("\n Inserte ahora los datos de la matriz B\n\n"); system("pause"); system("cls");
	
	printf("\n -> MATRIZ B, de orden %hd x %hd <-\n", Bf, Bc);
	for(f=1; f<=FilasMatrizB; f++) //Recorre la matriz B por filas, elemento x elemento en esa fila y les asinga un valor
	{
		printf("\n"); 
		for(c=1; c<=ColumnasMatrizB; c++)
		{ 
			printf("   B(%hd,%hd): ",f, c); //se imprime el siguiente formato -> B(f,c): 
			scanf("%hd", &MatrizB[f][c]); //aqui se asigna el valor dado por el usuario
		}
	}
	
	system("cls");
	
	printf("\n Matriz resultante C, de orden %hd x %hd\n\n", FilasMatrizA, ColumnasMatrizB);
	
	short int MatrizC[FilasMatrizA][ColumnasMatrizB]; //Declaramos la matriz resultante con orden Af x Bc
	
	//MULTIPLICACIÓN DE A*B
	for(f=1; f<=FilasMatrizA; f++) //fila
	{	
		for(c=1; c<=ColumnasMatrizB; c++) //columna
		{
			MatrizC[f][c]=0;
			for(int k=1; k<=ColumnasMatrizA; k++)
			{
				MatrizC[f][c] = MatrizC[f][c]+MatrizA[f][k]*MatrizB[k][c];
			}	
		}
	}
	
	//IMPRESIÓN DE LA MATRIZ C
	for(f=1; f<=FilasMatrizA; f++) 
	{
		printf("\n");
		for(c=1; c<=ColumnasMatrizB; c++)
		{
			printf(" | %hd",MatrizC[f][c]);
			if(c==ColumnasMatrizB) { printf(" | "); }
		}
	}
}

int main()
{
	printf("\n Este programa le ayudar\240 a hacer una multiplicaci\242n de matrices nxn \n\n\n "); system("pause");
	DefinirMatrices:
	system("cls");
	printf("\n -> Ingrese los datos correspondientes al orden de la matriz A \n");
	printf("       N\243mero de FILAS de la matriz A: "); 
	scanf("%hd", &FilasMatrizA);
	printf("       N\243mero de COLUMNAS de la matriz A: "); 
	scanf("%hd", &ColumnasMatrizA);
	printf("    La matriz A es una matriz de orden %hd filas x %hd columnas \n", FilasMatrizA, ColumnasMatrizA);
	
	
	printf("\n -> Ingrese los datos correspondientes al orden de la matriz B \n");
	printf("       N\243mero de FILAS de la matriz B: ");
	scanf("%hd", &FilasMatrizB);
	printf("       N\243mero COLUMNAS de la matriz B: "); 
	scanf("%hd", &ColumnasMatrizB);
	printf("    La matriz B es una matriz de orden %hd filas x %hd columnas", FilasMatrizB, ColumnasMatrizB);
 	
	system("cls");
	if(ColumnasMatrizA != FilasMatrizB) //Verificamos si se puede efectuar el prod. de matrices
	{
		printf("\n El num. de FILAS de la matriz A difieren con el num. de COLUMNAS de la matriz B \n No se puede realizar el producto, intente de nuevo con una matriz v\240lida. \n\n\n\n\n");
		system("pause"); goto DefinirMatrices;
	}
	else 
	{ 
		InsertarDatosMatriz(FilasMatrizA, ColumnasMatrizA, FilasMatrizB, ColumnasMatrizB); //enviamos al método el número entero de las filas y columnas de las matrices A y B, respectivamente
	}
}
