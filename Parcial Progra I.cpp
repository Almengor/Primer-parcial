#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const char *nombre_archivo = "archivo.dat";
struct Empleado{
	int codigo;
	char nombres[50];
	char apellidos[50];
	char puesto[50];
	int sueldo, bonificacion, total;
};
void abrir();
void ingresar();
void buscar_indice();
void modificar();
void buscar_codigo();
void eliminarporid();

main (){
	abrir();
	ingresar();
	buscar_indice();
	modificar();
	buscar_codigo();
	eliminarporid();
}
void abrir(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo,"rb");
	if (!archivo){
		archivo = fopen(nombre_archivo,"w+b");;
	}
	
	Empleado empleado;
	int registro = 0;
	fread(&empleado,sizeof(Empleado),1,archivo);
	cout<<"-------------------------------------------------------------------------------------------------"<<endl;
	cout<<"*                                        Empresa EL AGUILA                                      *"<<endl;
	cout<<"*                                      Registro de Empleados                                    *"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------"<<endl;
	cout<<"_________________________________________________________________________________________________"<<endl;
	cout<<"id"<<"    Codigo"<<"    Nombres     "<<"Apellidos    "<<"Puesto   "<<"Sueldo Base   "<<"Bonificacion      "<<"Salario total  "<<endl;
	do{
		cout<<"_________________________________________________________________________________________________"<<endl;
		cout<<registro<<"     | "<<empleado.codigo<<"     | "<<empleado.nombres<<"     | "<<empleado.apellidos<<"     | "<<empleado.puesto<<"      |"<<empleado.sueldo<<"     |"<<empleado.bonificacion<<"    |"<<empleado.total<<endl;
		fread(&empleado,sizeof(Empleado),1,archivo);
		registro+=1;
	} while (feof(archivo) ==0);
	cout<<endl;

	fclose(archivo);
}

void ingresar(){
	char continuar;
	FILE* archivo = fopen(nombre_archivo,"ab");
	Empleado empleado;
	string nombre,apellido,puesto,sueldo,bonificacion;
	do{
		fflush(stdin);
		cout<<"Ingrese el Codigo del empleado:";
		cin>>empleado.codigo;
		cin.ignore();
		cout<<"Ingrese Los Nombres:";
		getline(cin,nombre);
		strcpy(empleado.nombres,nombre.c_str());
		cout<<"Ingrese Los Apellidos:";
		getline(cin,apellido);
		strcpy(empleado.apellidos,apellido.c_str());
		cout<<"Ingrese El Puesto:";
		getline(cin,puesto);
		strcpy(empleado.puesto,puesto.c_str());
		cout<<"Ingrese El Sueldo Base:";
		cin>>empleado.sueldo;
		cout<<"Ingrese La Bonificacion:";
		cin>>empleado.bonificacion;
		cout<<"El Salario total es: "<<empleado.total<<endl;
		empleado.total=empleado.sueldo+empleado.bonificacion;
		fwrite(&empleado,sizeof(Empleado),1,archivo);
		cout<<"Desea Agregar Otro Nombre (s/n):";
		cin>>continuar;
	} while(continuar=='s'||continuar=='S');
	fclose(archivo);
	abrir();
}
void buscar_indice(){
	FILE* archivo = fopen(nombre_archivo,"rb");	
	int pos = 0;
	cout<<"Que registro desea visualizar (id): ";
	cin>>pos;
	fseek(archivo,pos * sizeof(Empleado),SEEK_SET);

	Empleado empleado;
	fread(&empleado,sizeof(Empleado),1,archivo);
	cout<<"Codigo: "<<empleado.codigo<<endl;
	cout<<"Nombres: "<<empleado.nombres<<endl;
	cout<<"Apellidos: "<<empleado.apellidos<<endl;
	cout<<"Puesto: "<<empleado.puesto<<endl;
	cout<<"Sueldo Base: "<<empleado.sueldo<<endl;
	cout<<"Bonificacion: "<<empleado.bonificacion<<endl;
	cout<<"Salario total: "<<empleado.total<<endl;
	fclose(archivo);
}
void modificar(){

	FILE* archivo = fopen(nombre_archivo,"r+b");
	string nombre,apellido;
	Empleado empleado;
	int id = 0;
	cout<<"Que registro desea modificar (id): ";
	cin>>id;
	fseek(archivo,id * sizeof(Empleado),SEEK_SET);
	cout<<"Ingres Nuevo Codigo: ";
	cin>>empleado.codigo;
	cin.ignore();
	cout<<"Ingrese Nuevo Nombre: ";
	getline(cin,nombre);
	strcpy(empleado.nombres,nombre.c_str());
	cout<<"Ingrese Nuevo Apellido: ";
	getline(cin,apellido);
	strcpy(empleado.apellidos,apellido.c_str());
	cout<<"Ingrese Nuevo Puesto: ";
	cin>>empleado.puesto;
	cout<<"Ingrese Nuevo Sueldo: ";
	cin>>empleado.sueldo;
	cout<<"Ingrese Nueva Bonificacion: ";
	cin>>empleado.bonificacion;
	cout<<"El Salario total es: "<<empleado.total<<endl;
	empleado.total=empleado.sueldo+empleado.bonificacion;
	fwrite(&empleado,sizeof(Empleado),1,archivo);
	fclose(archivo);
	abrir();
}
void buscar_codigo(){
	FILE* archivo = fopen(nombre_archivo,"rb");	
	int	 indice=0,pos=0,cod= 0;
	cout<<"Buscar Codigo:";
	cin>>cod;
	Empleado empleado;
	fread(&empleado,sizeof(Empleado),1,archivo);
	do{
		if (empleado.codigo ==cod){
			pos = indice;
		}
		fread(&empleado,sizeof(Empleado),1,archivo);
		indice+=1;
	} while (feof(archivo)==0);

	cout<<"_____________"<<pos<<"__________________"<<endl;
	fseek(archivo,pos * sizeof(Empleado),SEEK_SET);
	fread(&empleado,sizeof(Empleado),1,archivo);
	cout<<"Codigo: "<<empleado.codigo<<endl;
	cout<<"Nombres: "<<empleado.nombres<<endl;
	cout<<"Apellidos: "<<empleado.apellidos<<endl;
	cout<<"Puesto: "<<empleado.puesto<<endl;
	cout<<"Sueldo Base: "<<empleado.sueldo<<endl;
	cout<<"Bonificacion: "<<empleado.bonificacion<<endl;
	cout<<"Salario total: "<<empleado.total<<endl;
	fclose(archivo);	
}
void eliminarporid()
{
	FILE* archivo = fopen(nombre_archivo,"rb");
	FILE * auxiliar=fopen("auxiliar.dat","wb");
	string nombre,apellido;
	Empleado empleado;
	int id = 0;
	cout<<"Que registro desea eliminar (id): ";cin>>id;
	fread(&empleado,sizeof(Empleado),1,archivo);
	int des= fseek(archivo,id* sizeof(Empleado), SEEK_SET);
	while(!feof(archivo)==0)
{
	fseek(archivo,id * sizeof(Empleado),SEEK_SET);
	fread(&empleado,sizeof(Empleado),1,archivo);
	cout<<"Codigo: "<<empleado.codigo<<endl;
	cout<<"Nombres: "<<empleado.nombres<<endl;
	cout<<"Apellidos: "<<empleado.apellidos<<endl;
	cout<<"Puesto: "<<empleado.puesto<<endl;
	cout<<"Sueldo Base: "<<empleado.sueldo<<endl;
	cout<<"Bonificacion: "<<empleado.bonificacion<<endl;
	cout<<"Salario total: "<<empleado.total<<endl;
	fclose(archivo);	
		fwrite(&empleado,sizeof(Empleado),1,auxiliar);
		if(des==id)
		{
			int pos=ftell(auxiliar)-sizeof(Empleado);
			fseek(auxiliar,pos,SEEK_SET);
		}
		fread(&empleado,sizeof(Empleado),1,archivo);
}
	cout<<"Producto eliminado"<<endl;
	fclose(archivo);
	fclose(auxiliar);
	remove("archivo.dat");
	rename("auxiliar.dat","archivo.dat");
}
