#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

int main() {
    Agenda miAgendaPrueba;
    iniciar_agenda(&miAgendaPrueba);

    int opcion, nom, tel;
    char nombre[30], telefono[15];
    Contacto c;

    do
    {
        
        printf("\n===== MENU DE AGENDA =====\n");
        printf("1. Agregar contacto\n");
        printf("2. Mostrar agenda\n");
        printf("3. Buscar contacto por nombre\n");
        printf("4. Buscar contacto por telefono\n");
        printf("5. Ordenar contactos (de forma ascendente)\n");
        printf("6. Ordenar contactos (de forma descendente)\n");
        printf("7. Guardar agenda en archivo\n");
        printf("8. Cargar agenda desde archivo\n");
        printf("9. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1: //Caso para agregar contacto -Yamil
            leer_contacto(&c);
            agregar_contacto(&miAgendaPrueba, c);
            break;
        
        case 2: //Caso para mostrar agenda -Yamil
            imprimir_agenda(miAgendaPrueba);
            break;
        
        case 3: //Cas para buscar contacto por nombre -Yamil
            printf("ingrese el nombre que quiere buscar: ");
            scanf("%s", nombre);
            
            nom = buscar_contacto(&miAgendaPrueba, nombre);
            
            if(nom != -1){
                printf("\nContacto encontrado:\n\n");
                mostrar_contacto(miAgendaPrueba.contactos[nom]);

            }else{
                printf("El contacto no se encontro.\n");
            }
            break;
        
        case 4: //Caso para buscar contacto por telefono -Yamil
            printf("Escribe el telefono de la persona que quiere buscar: ");
            scanf("%s", telefono);

            tel = buscar_contacto_x_telefono(&miAgendaPrueba, telefono);

            if(tel != -1){
                printf("\nContacto encontrado:\n\n");
                mostrar_contacto(miAgendaPrueba.contactos[tel]);

            } else {
                printf("El contacto no se encontro.\n");

            }
            break;

        case 5: //Caso para ordenar contactos de forma ascendente -Yamil 
            ordenar_contactos(&miAgendaPrueba);
            printf("Agenda ordenada en forma ascendente.\n");
            break;

        case 6: //caso para ordentar contactos de forma descendente -Yamil
            ordenar_contactos_inv(&miAgendaPrueba);
            printf("Agenda ordenada en forma descendente.\n");
            break;

        case 7: //Caso para guardar contactos en el archivo -Yamil
            guardar_contactos("agenda.txt", &miAgendaPrueba);
            printf("Datos de la agenda guardados con exito en el archivo");
            break;

        case 8: //Caso para cargar los contactos del archivo a la RAM -Yamil
            cargar_contactos("agenda.txt", &miAgendaPrueba);
            printf("Datos del archivo cargados con exito en la agenda");
            break;

        case 9: //Caso para salir del programa -Ivan
            printf("Saliendo de la agenda\n\n");
            break;

        default:
            printf("Opción invalida, intente de nuevo.\n");
        }

    } while (opcion != 9); //Funcion para siempre tener el menu o una opcion en marcha -Yamil
    
    return 0;

}