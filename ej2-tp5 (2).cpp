/*Basándose en su código fuente de su ejercicio 5 del TP4 de archivos, va a trabajar con
listas enlazadas para datos de mediciones.
Puede tener pre-cargada algunos nodos a su lista. La lista debe ser doblemente enlazada.
Debe crear funciones que permitan al usuario:
? añadir un nodo a la lista,
? eliminarlo de la lista,
? guardar la lista completa en un archivo (modo append y binario),
? recuperar/leer esa lista del archivo (al momento de iniciar el programa y cuando el
usuario lo solicite),
? realizar búsquedas de mediciones:
? Por el tipo de sensor
? Por el valor medido. En el caso del valor medido, especificar si se busca
mediciones cuyo valor supere un umbral X (ingresado por teclado) o

mediciones menores a X umbral o mediciones de exactamente el mismo
valor.

? Mostrar el contenido de la lista para visualizar todos sus elementos
? Mostrar la lista ordenada cronológicamente según la fecha de la medición
(dd/mm/aaaa).*/

#include <iostream>
#include <string.h> //<>
#define TAM 20
using namespace std;

struct Sensores{
	char marca[20];
	char tipo[20];
	char unidad[20];
};

struct Medicion{
	int fecha;
	int hora;
	char comentarios[150];
	float valor_medido;
	struct Sensores sensor;
	struct Medicion *sig;
	struct Medicion *prev;
};

struct Medicion *agregarnuevonodo(struct Medicion*);
struct Medicion *eliminarnodo(struct Medicion*);
void cargararchivo(struct Medicion*);
struct Medicion *leerarchivo(struct Medicion*);
void mostrarlista(struct Medicion*);
void realizarbusqueda(struct Medicion*);
void mostrarlistaordenada(struct Medicion*);
void printlista(struct Medicion*);

int main(int argc, char *argv[]) {
	
	struct Medicion *PRIMERO,*ULTIMO;
	PRIMERO=(struct Medicion*)malloc(sizeof(struct Medicion));
	ULTIMO=(struct Medicion*)malloc(sizeof(struct Medicion));
	
	PRIMERO->fecha=20;
	PRIMERO->hora=1331;
	strcpy(PRIMERO->comentarios,"Sin comentarios");
	PRIMERO->valor_medido=23.2;
	strcpy(PRIMERO->sensor.marca,"Fluke");
	strcpy(PRIMERO->sensor.tipo,"Voltimetro");				//precargamos 2 nodos
	strcpy(PRIMERO->sensor.unidad,"Voltio");
	PRIMERO->sig=ULTIMO;
	PRIMERO->prev=NULL;
	
	ULTIMO->fecha=23;
	ULTIMO->hora=2041;
	strcpy(ULTIMO->comentarios,"Sin comentarios");
	ULTIMO->valor_medido=14.2;
	strcpy(ULTIMO->sensor.marca,"Shunt");
	strcpy(ULTIMO->sensor.tipo,"Ohmimetro");
	strcpy(ULTIMO->sensor.unidad,"Ohm");
	ULTIMO->sig=NULL;
	ULTIMO->prev=PRIMERO;
	
	int opcion;
		
		do{
			printf("\n\nMenu de opciones");
			printf("\n1. Agregar nuevo nodo/imagen (AL FINAL)");
			printf("\n2. Eliminar un nodo/imagen (LA PRIMERA)");
			printf("\n3. Cargar lista en un archivo binario");
			printf("\n4. Leer archivo binario");
			printf("\n5. Realizar busqueda por miembro");
			printf("\n6. Mostrar lista completa");
			printf("\n7. Mostrar lista ordenada cronologicamente");
			printf("\n8. Salir\n");
			scanf("%d",&opcion);
			switch(opcion){
				case 1:
					ULTIMO=agregarnuevonodo(ULTIMO);
					break;
				case 2:
					PRIMERO=eliminarnodo(PRIMERO);
					break;
				case 3:
					cargararchivo(PRIMERO);
					break;
				case 4:
					ULTIMO=leerarchivo(ULTIMO);
					break;
				case 5:
					realizarbusqueda(PRIMERO);
					break;
				case 6:
					mostrarlista(PRIMERO);
					break;
				case 7:
					mostrarlistaordenada(PRIMERO);
					break;
				default:
					printf("\nEsa opcion no es correcta");
			
			}
		} while(opcion!=8);
	
	return 0;
}

struct Medicion *agregarnuevonodo(struct Medicion *actual){
	
	struct Medicion *nuevo;
	nuevo=(struct Medicion*)malloc(sizeof(struct Medicion));		//reservamos memoria para el nodo nuevo
	actual->sig=nuevo;	//lo mismo pero al revez
	nuevo->prev=actual;
	nuevo->sig=NULL;	//le asignamos NULL al sig del ultimo nodo
	
	printf("\nIngrese la fecha de la nueva medicion: (AA/MM/DD)");
	scanf("%d",&nuevo->fecha);
	printf("\nIngrese la hora de la nueva medicion: (HH:MM)");
	scanf("%d", &nuevo->hora);
	printf("\nIngrese comentarios sobre la nueva medicion: ");
	scanf("%s", nuevo->comentarios);
	printf("\nIngrese el valor medido de la nueva medicion: ");
	scanf("%f", &nuevo->valor_medido);
	printf("\nIngrese la marca del sensor: ");
	scanf("%s", nuevo->sensor.marca);
	printf("\nIngrese el tipo de sensor: ");
	scanf("%s", nuevo->sensor.tipo);
	printf("\nIngrese la unidad de medida del sensor");
	scanf("%s", nuevo->sensor.unidad);

	printf("\nMedicion/nodo cargado al final con éxito");
	
return nuevo;
}
	
struct Medicion *eliminarnodo(struct Medicion *PRIMERO){
	
	PRIMERO=PRIMERO->sig;
	PRIMERO->prev=NULL;
	printf("\nPrimer imagen/nodo eliminado con éxito");

return PRIMERO;
}
	
void cargararchivo(struct Medicion *PRIMERO){
	FILE *fp;
	fp=fopen("Listas.bin","ab");
	struct Medicion *actual;
	actual=PRIMERO;
	if(fp!=NULL){
		printf("\nLa apertura del archivo fue exitosa");  
		
		while(actual!=NULL){
		fwrite(actual, sizeof(struct Medicion), 1, fp);
		//printlista(actual);
		actual=actual->sig;
		}
		if(actual==NULL){
			printf("\nSe realizó con exito la escritura del archivo");
		}
		
	}
	else{
		printf("\nFalló la apertura del archivo");
	}
	fclose(fp);
	
}
	
struct Medicion* leerarchivo(struct Medicion* ULTIMO) {
		FILE *archivolectura;		
		archivolectura = fopen("Listas.bin", "rb");
		
		if (archivolectura != NULL) {
			
			struct Medicion *temp;
			temp = (struct Medicion*)malloc(sizeof(struct Medicion));
			ULTIMO->sig = temp;
			temp->prev = ULTIMO;
			
			while (fread(temp, sizeof(struct Medicion), 1, archivolectura) == 1){
				
				struct Medicion *nuevo;
				nuevo = (struct Medicion*)malloc(sizeof(struct Medicion));				
				temp->sig = nuevo;		
				nuevo->prev = temp;
				temp = nuevo;
				
			};
			printf("\nLeida exitosa");
			fclose(archivolectura);
		} else {
			printf("Falló la apertura del archivo.\n");
		}
	return ULTIMO;
	}
void mostrarlista(struct Medicion *actual){
	
	int cont=1;
	while(actual!=NULL){
		
		printf("\n\n\nLista numero %d\n",cont);
		printlista(actual);
		cont++;
		actual=actual->sig;
		
	}
}

void realizarbusqueda(struct Medicion *actual){
	
	int opcion=0;
	
	struct Medicion *NodoPatron;

	NodoPatron=actual;
	
	do{
	printf("\n\n\nElija el parametro a realizar la busqueda:");
	printf("\n1. Fecha");
	printf("\n2. Hora");
	printf("\n3. Valor medido");
	printf("\n4. Marca de sensor");
	printf("\n5. Tipo de sensor");
	printf("\n6. Unidad de medida del sensor");
	printf("\n7. Salir\n");
	scanf("%d",&opcion);
		
		switch(opcion){
			
			case 1:
				int fechaP;
				printf("\nIngrese la fecha a buscar: ");
				scanf("%i",&fechaP);
				
				actual=NodoPatron;
				
				while(actual!=NULL){
					if(actual->fecha==fechaP){
						printf("\nSe encontró una coincidencia\n\n");
						printlista(actual);
					}
					actual=actual->sig;
				}
				break;
			
			case 2:
				int horaP;
				printf("\nIngrese la hora a buscar: ");
				scanf("%i",&horaP);
			
				actual=NodoPatron;
			
				while(actual!=NULL){
					if(actual->hora==horaP){
						printf("\nSe encontró una coincidencia\n\n");
						printlista(actual);
					}
					actual=actual->sig;
				}
				break;
			
			case 3:
				int buscar;
				do{
				printf("\n\n\n1.Buscar por valor exacto");
				printf("\n2.Buscar por rango menor a: ");
				printf("\n3.Buscar por rango mayor a: ");
				printf("\n4.Salir\n");
				scanf("%d",&buscar);
				
				switch(buscar){
					
					case 1:
						actual=NodoPatron;
						float valor_medidoP;
						printf("\nIngrese el valor medido a buscar: ");
						scanf("%f",&valor_medidoP);
						
						actual=NodoPatron;
						
						while(actual!=NULL){
							if(actual->valor_medido==valor_medidoP){
								printf("\nSe encontró una coincidencia\n\n");
								printlista(actual);
							}
							actual=actual->sig;
						}
					break;
					
					case 2:
						actual=NodoPatron;
						float valor_medidoPP;
						printf("\nBuscar por rango menor a: ");
						scanf("%f",&valor_medidoPP);
						
						actual=NodoPatron;
						
						while(actual!=NULL){
							if(actual->valor_medido<=valor_medidoPP){
								printf("\nSe encontró una coincidencia\n\n");
								printlista(actual);
							}
							actual=actual->sig;
						}
					break;
					
					case 3:
						actual=NodoPatron;
						float valor_medidoPPP;
						printf("\nBuscar por rango mayor a: ");
						scanf("%f",&valor_medidoPPP);
						
						actual=NodoPatron;
						
						while(actual!=NULL){
							if(actual->valor_medido>=valor_medidoPPP){
								printf("\nSe encontró una coincidencia\n\n");
								printlista(actual);
							}
							actual=actual->sig;
						}
					break;
						
					case 4:
						break;
						
					default:
						printf("\nOpcion no valida");
					break;
				}
				
				}while(buscar!=4);
				break;
			
			case 4:
				char marcaP[TAM];
				printf("\nIngrese la marca a buscar: ");
				scanf("%s",marcaP);
				
				actual=NodoPatron;
				
				while(actual!=NULL){
					if(strcmp(marcaP,actual->sensor.marca)==0){
						printf("\nSe encontró una coincidencia\n\n");
						printlista(actual);
					}
					actual=actual->sig;
				}
				break;
			
			case 5:
				char tipoP[TAM];
				printf("\nIngrese el tipo de sensor a buscar: ");
				scanf("%s",tipoP);
			
				actual=NodoPatron;
				
				while(actual!=NULL){
					if(strcmp(tipoP,actual->sensor.tipo)==0){
						printf("\nSe encontró una coincidencia\n\n");
						printlista(actual);
					}	
						 actual=actual->sig;
				}
				break;
				
			case 6:
				char unidadP[TAM];
				printf("\nIngrese la unidad de medida a buscar: ");
				scanf("%s",unidadP);
				
				actual=NodoPatron;
				
				while(actual!=NULL){
					if(strcmp(unidadP,actual->sensor.unidad)==0){
						printf("\nSe encontró una coincidencia\n\n");
						printlista(actual);
					}	
					actual=actual->sig;
				}	
				break;
			
			case 7:
				break;
				
			default:
				printf("\nOpcion invalida");
		}
	}while(opcion!=7);
}

void mostrarlistaordenada(struct Medicion *actual){
	
	struct Medicion *sig;
	struct Medicion *copia;
	copia=actual;
	sig=actual->sig;
	
	
	do{
		/*printf("\n\nEntro al do while");							//funca o no funca
		printf("\nactual->fecha es: %d",actual->fecha);
		printf("\nsig->fecha es: %d",sig->fecha);*/
		
		if(actual->fecha<sig->fecha){			//que este if se cumpla quiere decir que el actual es posterior al sig, debe cambiarse
			
			//printf("\n\nEntro al if");
			
			
			struct Medicion *temp;
			temp=(struct Medicion*)malloc(sizeof(struct Medicion));
			
			/*printf("\n\nAntes del cambio\n");
			printf("\nlista actual es:");
			printlista(actual);
			printf("\n\nlista sig es:");
			printlista(sig);*/
			
			temp->fecha=sig->fecha;
			temp->hora=sig->hora;
			strcpy(temp->comentarios,sig->comentarios);
			temp->valor_medido=sig->valor_medido;			//hacemos un respaldo de sig para no perder su ubicacion
			strcpy(temp->sensor.marca,sig->sensor.marca);  
			strcpy(temp->sensor.tipo,sig->sensor.tipo);
			strcpy(temp->sensor.unidad,sig->sensor.unidad);
			
			sig->fecha=actual->fecha;
			sig->hora=actual->hora;
			strcpy(sig->comentarios,actual->comentarios);
			sig->valor_medido=actual->valor_medido;			//cambiamos a sig por actual
			strcpy(sig->sensor.marca,actual->sensor.marca);  
			strcpy(sig->sensor.tipo,actual->sensor.tipo);
			strcpy(sig->sensor.unidad,actual->sensor.unidad);
			
			
			actual->fecha=temp->fecha;
			actual->hora=temp->hora;
			strcpy(actual->comentarios,temp->comentarios);
			actual->valor_medido=temp->valor_medido;			//cambiamos a actual por sig
			strcpy(actual->sensor.marca,temp->sensor.marca);  
			strcpy(actual->sensor.tipo,temp->sensor.tipo);
			strcpy(actual->sensor.unidad,temp->sensor.unidad);
			
			/*printf("\n\nDespues del cambio\n");
			printf("\nlista actual es:");				//funca o no funca
			printlista(actual);
			printf("\n\nlista sig es:");
			printlista(sig);*/
			
			actual=actual->sig;
			sig=sig->sig;
			free(temp);
			
		}else{
			actual=actual->sig;
			sig=sig->sig;
		}
		
		
	}while(sig!=NULL);
	
	actual=copia;
	
	printf("\n\nLista ordenada");
	
	mostrarlista(actual);
}
	
void printlista(struct Medicion* actual){
	printf("\nFecha: %d",actual->fecha);
	printf("\nHora: %d",actual->hora);
	printf("\nComentarios: %s",actual->comentarios);
	printf("\nValor medido: %.2f",actual->valor_medido);
	printf("\nMarca sensor: %s",actual->sensor.marca);
	printf("\nTipo sensor %s",actual->sensor.tipo);
	printf("\nUnidad de medida del sensor: %s",actual->sensor.unidad);
}
