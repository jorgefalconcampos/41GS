//FALCÓN CAMPOS JORGE ANTONIO, 2019. IPN.

#include<iostream>
#include<ctime>
#include<stdlib.h>
#include <Windows.h>
#define max 10

using namespace std;

int personasEnEspera=0; int datos=0;
void MostrarOpc();
void DatosCliente(int a); int WaitingTime();
void MostrarCola_Clientes(); void actualizar(string nompersona,int b,int c,int d);
void Stats_RealTime(); void condicion();


struct nodo //le damos los atributos de nombre, hora, min, seg, atencion y lleno a nuestro nodo.
{
	string nombre; int hora, min, seg, atencion; bool lleno;
}clientes[max],futuro[max]; //después creamos un arreglo llamado cliente de 9 elementos, cada elemento "hereda" los  6 atrib. del nodo, lo mismo pasa con max.



int main() { MostrarOpc(); }



void MostrarOpc()
{ 
	int opc=0;
	do
	{ 
		system("cls"); 	
		cout << "\n Men\243 de opciones: \n"; 
		cout << "\n 1 - A\244adir clientes";
		cout << "\n 2 - Mostrar cola";
		cout << "\n 3 - Mostrar estadistica";
		cout << "\n 4 - Salir \n\n";
		cout << " Seleccione una opci\242n: "; cin >> opc;	
		switch(opc)
		{
			case 1: system("cls");
				cout << "\n ----- Has elegido la opci\242n 1 - A\244adir cliente ----- \n\n Cuantos clientes desea agregar? ";
				int num; cin >> num; cout << "\n"; 
				DatosCliente(num); 				
			break;
			
			case 2: system("cls");
		         cout << "\n ----- Has elegido la la opci\242n 2 - Mostrar cola ----- \n\n";
		         MostrarCola_Clientes();
		   	break;
		   	
		   	case 3: system("cls");
				Stats_RealTime();
		   	break;
			
			case 4:
				system("cls");
		        cout << "\n ----- Has salido del programa. ----- \n\n"; 
				system("pause");
				exit(0);
			break;
			
			default:
				cout << "\n Opci\242n inv\240lida, int\202ntelo de nuevo. ";
				system("pause");
		}
	} while(opc<1 || opc>4);	
}


void EncolarCliente(string nombre) //encolarrr, push
{
	int posClnt=(personasEnEspera+datos)%max;  //esta será la posicion del Cliente en el arreglo "cliente[max]" y por tanto en la cola. La posición la obtendremos unas lineas más abajo.
	//Obtenemos la posición del cliente en la cola circular haciendo lo siguiente: Con la operación módulo, obtenemos el sobrante de la división de (personasEnEspera+datos)/max y max=10
	//accedemos a la posición del arreglo "Clientes" con la posición obtenida de la linea anterior. Una vez en esa posición del arreglo, le asignamos valores a sus atributos.
	
	time_t now = time(0);
	tm* hora_actual = localtime(&now);
	 
	clientes[posClnt].nombre = nombre; 
	clientes[posClnt].hora = hora_actual->tm_hour;
	clientes[posClnt].min = hora_actual->tm_min;
	clientes[posClnt].seg = hora_actual->tm_sec;
	clientes[posClnt].atencion = WaitingTime();
	clientes[posClnt].lleno=true;
	
	actualizar(nombre, hora_actual->tm_hour, hora_actual->tm_min, hora_actual->tm_sec);
	
	datos++;
	
	cout << clientes[posClnt].hora<<":"<<clientes[posClnt].min<<":"<<clientes[posClnt].seg << "\n" <<endl; //Cliente agregado correctamente a las...
}


int WaitingTime() //Obtenemos un num. aleat. del 20 al 40
{
	int tiempoAtenc;
	srand(time(NULL));	
	tiempoAtenc = 20 + rand() % (41 - 20); //Lim_Inf + rand() % (Lim_Sup - L)
	return tiempoAtenc;
}


//datos del usuario a un futuro segun atencion 
void actualizar(string nompersona, int hrs ,int mins,int segs) //tentativamente, este se acutalizaria cada segundo
{
	int posClnt=(personasEnEspera+datos)%max;  //esta será la posicion del Cliente en el arreglo "cliente[max]" y por tanto en la cola. La posición la obtendremos unas lineas más abajo.
	//Obtenemos la posición del cliente en la cola circular haciendo lo siguiente: Con la operación módulo, obtenemos el sobrante de la división de (personasEnEspera+datos)/max y max=10
	//accedemos a la posición del arreglo "Clientes" con la posición obtenida de la linea anterior. Una vez en esa posición del arreglo, le asignamos valores a sus atributos.
	
	int tiempo;
	
	futuro[posClnt].nombre = nompersona;
	futuro[posClnt].hora = hrs;
	futuro[posClnt].min = mins;
	futuro[posClnt].seg = segs;
	futuro[posClnt].atencion = WaitingTime();
	futuro[posClnt].lleno=true;
	
	tiempo = clientes[posClnt].seg+clientes[posClnt].atencion;
	
	if(tiempo>59) //tentativamente lo que está dentro de este if se iría alv
	{
		if((clientes[posClnt].min+1)>59)
		{
			futuro[posClnt].hora++;
			futuro[posClnt].min=0;
		}
		else
		{ futuro[posClnt].min++; }
		
		futuro[posClnt].seg=tiempo-60;
	}
	else
	{
		futuro[posClnt].seg=tiempo;
	}
}


void mostrar()
{
	for(int i=0; i<max; i++)
	{
		if(clientes[i].lleno)
		{
			cout<<clientes[i].nombre;
			cout<<clientes[i].hora;
			cout<<clientes[i].min;
			cout<<clientes[i].seg<<" ";
			cout<<clientes[i].atencion<<" ";
			
			cout<<futuro[i].nombre;
			cout<<futuro[i].hora;
			cout<<futuro[i].min;
			cout<<futuro[i].seg<<endl;
		}
	}
}


//muestra clientes y hora actual
void MostrarCola_Clientes()
{
	time_t now = time(0);
	tm* hora_actual = localtime(&now);
	
	cout<<"   Hora actual: " << hora_actual->tm_hour<< ":"<< hora_actual->tm_min<< ":"<< hora_actual->tm_sec <<endl;
	cout<<"\n   Cliente(s): "; int i;
	
	for(i=0;i<max;i++)
	{	
		if(clientes[i].lleno)
		{
			cout << clientes[i].nombre;
			if(clientes[i+1].lleno) { cout<<", "; }
			else{ cout<<"\n\n"; }
		}
	}
	 
	if(clientes[0].lleno==FALSE) { cout<<"NO HAY CLIENTES PARA MOSTRAR. \n\nRegresando al men\243... Puede agregar un cliente nuevo desde el men\243 principal.\n\n"; }
	
	system("pause");
	MostrarOpc();
}

void pop()
{
	time_t now = time(0);
	tm* hora_actual = localtime(&now);
	int a[3];
	int b,c;

	a[0]=hora_actual->tm_hour;
	a[1]=hora_actual->tm_min;
	a[2]=hora_actual->tm_sec;

	b=(a[0]*3600)+(a[1]*60)+a[2];								
	c=(futuro[personasEnEspera].hora*3600)+(futuro[personasEnEspera].min*60)+futuro[personasEnEspera].seg; //hora a futuro en segundos

	if(c<b)
	{
		clientes[personasEnEspera].lleno=false;
		futuro[personasEnEspera].lleno=false;
		datos--;
		condicion();
	}
}

void MostrarEstadistica()
{
	int a=personasEnEspera;
	
	for(int i=0;i<datos;i++) { pop(); }
	cout << "\n\n";
//	cout<<"   CLIENTES(S) \tHORA DE ENTRADA \tTIEMPO DE ATENCION \tHORA DE SALIDA \tATENDIENDO"<<endl;
	cout<<"   CLIENTES(S) \tHORA DE ENTRADA \tTIEMPO DE ATENCION "<<endl;
	for(int i=0;i<max;i++)
	{	
		if(clientes[a].lleno)
		{
			cout<< "\n   " << clientes[a].nombre;
			cout<< "\t\t " <<clientes[a].hora<<":";
			cout<<clientes[a].min<<":";
			cout<<clientes[a].seg;
			cout<< "\t\t  " <<clientes[a].atencion;
		}
		if(a==9) { a=0; }
		else { a++; }
	}
}


void DatosCliente(int nClientes)
{
	if(nClientes<1) { cout<<"\n Tiene que ingresar al menos un cliente.";}
	else
	{
		for(int i=1; i<=nClientes; i++)
		{
			string nomCliente; 
			cout<< "\n  - Nombre del cliente (" << i << "): ";
			cin >> nomCliente;	
			cout << "   Cliente " << nomCliente << " agregado a la cola correctamente a las ";
			EncolarCliente(nomCliente);
		}
		system("pause"); MostrarOpc();	
	}
	system("pause"); MostrarOpc();
}


void Stats_RealTime() 
{
	time_t hora_actual;
	struct tm * time_info;
	char hrString[9];	
	while(true)
	{
		cout << "\n ----- Has elegido la la opci\242n 3 - Mostrar estadistica ----- \n\n ";
		cout << "\n * Presione la tecla ESC para regresar al men\243 principal";
		time(&hora_actual);
		time_info = localtime(&hora_actual); 	
		cout << "\n   Mostrando la hora actual: ";
		strftime(hrString, sizeof(hrString), "%H:%M:%S", time_info);
   		puts(hrString);	MostrarEstadistica();
		_sleep(1000); system("cls"); 
		if(GetAsyncKeyState(VK_ESCAPE)) { system("cls"); MostrarOpc(); }		
	}	
}


void condicion()
{
	if(personasEnEspera!=9)	{ personasEnEspera++; }
	else { personasEnEspera=0; }
}
