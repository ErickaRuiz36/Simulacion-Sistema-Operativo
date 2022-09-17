/*
PRACTICA 02 SIMULACION DE LA EJECUCION DE PROCESOS EN EL SISTEMA OPERATIVO

DESCRIPCIÓN: Simula la ejecución de los procesos gestionados por el sistema operativo en un equipo monoprocesador sin manejo de 
             prioridades.


OBSERVACIONES: Maneja únicamente el cambio de la cola de listos a ejecución y una vez terminado el proceso este se envía a la 
                cola de terminados.
                NO  hay cola de prioridades

INSTRUCCION DE COMPILACION: gcc OperatingSystem.c TADColaDin.c presentacionWin.c -o OperatingSystem
EJECUCIÓN: OperatingSystem.exe 

AUTORES:  

Ericka Ruiz López              (C) Marzo 2021

*/
#include<stdio.h>
#include "presentacion.h"
#include "TADColaDin.h"
//#include <time.h>
#include <stdlib.h>
#include <windows.h>
#define TIEMPO_BASE	1000		//Tiempo base en ms

void llenafunciones(aplicaciones *aplicacion,int n);
void imprimeEstructuras(aplicaciones *aplicacion, int posicion);
void dibujarCuadro(int x1,int y1,int x2,int y2);
void llenafuncionesManual(aplicaciones *aplicacion);

//Funcion principal
void main()
{   
    //DECLARACION DE LAS VARAIBLES E INICIALIZACION DE LAS COLAS 
    elemento e, aux;
    cola listos;
    cola finalizados;
    aplicaciones  aplicacion;
  
    Initialize(&listos);
    Initialize(&finalizados);
    int tiempo,i,caso, tiempoc=0, num_aplicaciones, opcion=0;
    boolean vueltas=FALSE;
    int tam = Size(&listos);

    while(opcion>2 || opcion<1){
        printf("\n1. Simular con aplicaciones predeterminadas. \n");
        printf("2. Agregar aplicaciones. \n");
        printf("\nIngrese la opcion: \n");
        scanf("%d", &opcion);
    }

    if(opcion==1){
        for(i=0;i<3;i++)
        {
            llenafunciones(&aplicacion, i+1);
            e.s=aplicacion;
            Queue(&listos,e);
        }
    }

    if(opcion==2){
        do{
            llenafuncionesManual(&aplicacion);
            e.s = aplicacion;
            Queue(&listos, e);
            printf("\nOtro? (1: si, 2: no): ");
            scanf("%d", &opcion);
        }while(opcion != 2);
    }

    //Modificacion de la consola y creacion del marco
    system("mode con: cols=100 lines=38");
    system("COLOR 0B");
    
    //dibujarCuadro(37,2,58,4);

    dibujarCuadro(22,0,67,27);
         
    MoverCursor(38,1);
    printf("COLA DE PROCESOS");
    while(!Empty(&listos))
	{
        Sleep(TIEMPO_BASE);		//Esperar el tiempo base
        if (!Empty(&listos))
        {
            //anterior
            if(vueltas == TRUE)
            {   
                dibujarCuadro(24,3,65,10);
                MoverCursor(25,4);
                printf("Anterior:");
                imprimeEstructuras(&aux.s,1);
            }
            
            
            e = Dequeue(&listos);
            e.s.tiempo--;
            e.s.tiempoTotal++;
           
            aux = e;
         	tiempoc++;
            
            //actual
            dibujarCuadro(24,11,65,18);
            MoverCursor(25,12);
            printf("Actual:");
            imprimeEstructuras(&e.s,2);

            if(e.s.tiempo > 0)
            {
                Queue(&listos, e);
            }
            else
            {
                e.s.tiempoTotal=tiempoc;
                Queue(&finalizados, e);
            }
            
            //siguiente
            if(!Empty(&listos))
            {
                e = Element(&listos, 1);
                dibujarCuadro(24,19,65,26);
                MoverCursor(25,20); 
                printf("Siguiente:");
                imprimeEstructuras(&e.s,3);
            }
            vueltas = TRUE;       
        }
	}
    MoverCursor(25,4);
    printf("         ");
    MoverCursor(25,12);
    printf("         ");
    MoverCursor(25,20); 
    printf("          ");
    i=1;
    printf("\n\n\n\n\n");
    while(!Empty(&finalizados))
    {
    	e=Dequeue(&finalizados);
        imprimeEstructuras(&e.s,i);
        i++;
    }
   
       
    
    for(i=0;i<3;i++)
    {
        printf("\n");
    }

}

void llenafunciones(aplicaciones *aplicacion,int n){
    //char cadena[] = aplicacion->nombre + n;
    if(n==1)
    {
        strcpy(aplicacion->nombre,"aplicacion word" );
        strcpy(aplicacion->actividad,"procesador de textos");
        strcpy(aplicacion->id,"word24" );
        aplicacion->tiempo=4;
        aplicacion->tiempoTotal = 0;
    }
    if(n==2)
    {
        strcpy(aplicacion->nombre,"aplicacion excel" );
        strcpy(aplicacion->actividad,"Procesar hojas de calculo");
        strcpy(aplicacion->id,"exc84" );
        aplicacion->tiempo=6;
        aplicacion->tiempoTotal = 0;
    }
    if(n==3)
    {
        strcpy(aplicacion->nombre,"aplicacion power point" );
        strcpy(aplicacion->actividad,"Procesar presentaciones");
        strcpy(aplicacion->id,"powerpup89" );
        aplicacion->tiempo=9;
        aplicacion->tiempoTotal = 0;
    }
    
}

void llenafuncionesManual(aplicaciones *aplicacion){
    fflush(stdin);
    printf("\nIntroduzca el nombre de  la aplicacion: ");
    scanf("%[^\n]",aplicacion->nombre);
    fflush(stdin);

    printf("\nIntroduzca la actividad de la aplicacion: ");
    scanf("%[^\n]",aplicacion->actividad);
    fflush(stdin);

    printf("\nIntroduzca el id de la aplicacion: ");
    scanf("%[^\n]",aplicacion->id);
    fflush(stdin);

    printf("\nIntroduzca el tiempo de la aplicacion: ");
    scanf("%d",&aplicacion->tiempo);
    fflush(stdin);

    aplicacion->tiempoTotal = 0;
}

void imprimeEstructuras(aplicaciones *aplicacion, int posicion){
    switch (posicion)
    {
        case 1:
            MoverCursor(25,5);
            printf("                                     ");
            MoverCursor(25,5);
            printf("Nombre: %s",aplicacion->nombre );

            MoverCursor(25,6);
            printf("                                     ");
            MoverCursor(25,6);
            printf("Actividad: %s",aplicacion->actividad );

            MoverCursor(25,7);
            printf("                                     ");
            MoverCursor(25,7);
            printf("Id: %s",aplicacion->id );

            MoverCursor(25,8);
            printf("                                     ");
            MoverCursor(25,8);
            printf("Tiempo:%d",aplicacion->tiempo );

            MoverCursor(25,9);
            printf("                                     ");
            MoverCursor(25,9);
            printf("Tiempo Total:%d",aplicacion->tiempoTotal);
            
        break;
        case 2:
            MoverCursor(25,13);
            printf("                                     ");
            MoverCursor(25,13);
            printf("Nombre: %s",aplicacion->nombre );
            
            MoverCursor(25,14);
            printf("                                     ");
            MoverCursor(25,14);
            printf("Actividad: %s",aplicacion->actividad );

            MoverCursor(25,15);
            printf("                                     ");
            MoverCursor(25,15);
            printf("Id: %s",aplicacion->id );

            MoverCursor(25,16);
            printf("                                     ");
            MoverCursor(25,16);
            printf("Tiempo:%d",aplicacion->tiempo );

            MoverCursor(25,17);
            printf("                                     ");
            MoverCursor(25,17);
            printf("Tiempo Total:%d",aplicacion->tiempoTotal);
            
        break;
        case 3:
            MoverCursor(25,21);
            printf("                                     ");
            MoverCursor(25,21);
            printf("Nombre: %s",aplicacion->nombre );

            MoverCursor(25,22);
            printf("                                     ");
            MoverCursor(25,22);
            printf("Actividad: %s",aplicacion->actividad );

            MoverCursor(25,23);
            printf("                                     ");
             MoverCursor(25,23);
            printf("Id: %s",aplicacion->id );

            MoverCursor(25,24);
            printf("                                     ");
             MoverCursor(25,24);
            printf("Tiempo:%d",aplicacion->tiempo );

            MoverCursor(25,25);
            printf("                                     ");
            MoverCursor(25,25);

            printf("Tiempo Total:%d",aplicacion->tiempoTotal);
        break;

        default:
        	Sleep(TIEMPO_BASE * 6);
        		printf("\n\nContinuara...\n");

	        	printf("--------------------------------------\n");
	            printf("\nNombre: %s",aplicacion->nombre );

	            
	            printf("\nActividad: %s",aplicacion->actividad );

	            
	            printf("\nId: %s",aplicacion->id );

	            printf("\nTiempo:%d",aplicacion->tiempo );

	            

	            printf("\nTiempo Total:%d",aplicacion->tiempoTotal); 
        	
        break;
    }
	
}

void dibujarCuadro(int x1,int y1,int x2,int y2){
    int i;

    for (i=x1;i<x2;i++){
        MoverCursor(i,y1); 
        printf("\304"); //linea horizontal superior
        MoverCursor(i,y2); 
        printf("\304"); //linea horizontal inferior
    }

    for (i=y1;i<y2;i++){
        MoverCursor(x1,i); 
        printf("\263"); //linea vertical izquierda
        MoverCursor(x2,i); 
        printf("\263"); //linea vertical derecha
    }

    MoverCursor(x1,y1); 
    printf("\332");
    MoverCursor(x1,y2); 
    printf("\300");
    MoverCursor(x2,y1); 
    printf("\277");
    MoverCursor(x2,y2); 
    printf("\331");
}


