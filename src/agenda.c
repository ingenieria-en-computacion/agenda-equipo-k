#include "agenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Esta función se encarga de iniciar el número de contactos a cero
 */
void iniciar_agenda(Agenda *agenda){
    agenda->num_contactos=0;

}



// Varible que lleva la cuenta de cuantos contactos hay en la agenda
int num_contactos;

/**
 * Esta función sirve para agregar un contacto nuevo en la agenda
 */
void agregar_contacto(Agenda *agenda, Contacto c){
    if (num_contactos < MAX_CONTACTOS){
        agenda->contactos[agenda->num_contactos] = c;
        agenda->num_contactos++;
    }else{
        printf("ERROR! La agenda esta llena, no se pueden agregar más contactos");
    }

}


/**
 * Esta función sirve para buscar un contacto por nombre en la agenda y retorna la posición del contacto si exisite
 * En caso contrario retorna -1
 */
int buscar_contacto(Agenda *agenda, char *nombre){
    for (int i = 0; i < agenda->num_contactos; i++){
        if (strcmp(agenda->contactos[i].nombre, nombre) == 0){
            return i;
        }
    }
    return -1;
}


/**
 * Esta función  sirve para buscar un contacto por su número de telefono en la agenda
 */
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]){ //Maestra, porque char telefono y no int y ya T_T
    
    for(int i = 0; i < agenda->num_contactos; i++){
        if(strcmp(agenda->contactos[i].numero, telefono) == 0){
            return i;
        }
    }
    return -1;

}


/*
  Esta función sirve para ordenar los contactos por nombres de forma ascendente
*/
void ordenar_contactos(Agenda *agenda){
    int i, j;
    Contacto temp;
    for(i = 0; i < agenda->num_contactos; i++){
        for(j = 0; j < agenda->num_contactos-i-1; j++){
            if(strcmp(agenda->contactos[j].nombre, agenda->contactos[j+1].nombre)>0){
                temp = agenda->contactos[j];
                agenda->contactos[j] = agenda->contactos[j+1];
                agenda->contactos[j+1] = temp;
            }
        }
    }
}

/**
 * Esta función sirve para ordenar los contactos por nombres de forma descendente
 */

void ordenar_contactos_inv(Agenda *agenda) {
    int i, j;
    Contacto temp;

    for (i = 0; i < agenda->num_contactos; i++) {
        for (j = 0; j < agenda->num_contactos - i - 1; j++) {
            if (strcmp(agenda->contactos[j].nombre, agenda->contactos[j + 1].nombre) < 0){
                temp = agenda->contactos[j];
                agenda->contactos[j] = agenda->contactos[j + 1];
                agenda->contactos[j + 1] = temp;
            }
        }
    }
}



/**
 * Función auxiliar para imprimir un contacto
 */
void mostrar_contacto(Contacto c){
    printf("Nombre: %s\n", c.nombre);
    printf("Apellido: %s\n", c.apellido);
    printf("Mes de nacimiento: %s\n", c.mes);
    printf("Dia de nacimiento: %d\n", c.nacimiento);
    printf("Tipo de contacto: %s\n", c.tipo_contacto);
    printf("Numero telefonico: %s\n", c.numero);
    printf("Tipo de numero: %s\n", c.tipo_numero);
    printf("----------------------------------\n");
}


/**
 * Función auxiliar para leer un contacto
 */
void leer_contacto(Contacto *c){
    printf("Nombre: ");
    scanf("%s", c->nombre); 
    
    printf("Apellido: ");
    scanf("%s", c->apellido);
    
    printf("Mes de nacimiento (ej. ENERO): ");
    scanf("%s", c->mes);

    printf("Dia de nacimiento: ");
    scanf("%d", &c->nacimiento); 

    printf("Tipo de contacto (ej. FAMILIA): ");
    scanf("%s", c->tipo_contacto);

    printf("Numero de telefono: ");
    scanf("%s", c->numero); 

    printf("Tipo de numero (CASA, MOVIL, OFICINA u OTRO): ");
    scanf("%s", c->tipo_numero);

}

/**
 * Función que imprime todos los contactos de la agenda en pantalla
 */
void imprimir_agenda(Agenda agenda){
    if (agenda.num_contactos == 0){
        printf("La agenda esta vacia");
        return;
    }

    printf("Agenda completa:\n");
    printf("=============================\n");

    for (int i = 0; i < agenda.num_contactos; i++){
        printf("Contacto #%d:\n", i + 1);
        mostrar_contacto(agenda.contactos[i]);
    }

}

/**
 * Función que sirve para cargar contactos escritos en un archivo a la agenda
 */
void cargar_contactos(char *filename, Agenda *agenda){ 
    FILE *archivo;

    archivo = fopen(filename, "r");
    
    if (archivo == NULL) {
        printf("Archivo '%s' no encontrado", filename);
        iniciar_agenda(agenda);
        return;
    }

    iniciar_agenda(agenda);

    while (agenda->num_contactos < MAX_CONTACTOS && 
           fscanf(archivo, "%s %s %s %d %s %s %s", 
                  agenda->contactos[agenda->num_contactos].nombre,
                  agenda->contactos[agenda->num_contactos].apellido, 
                  agenda->contactos[agenda->num_contactos].mes,
                  &agenda->contactos[agenda->num_contactos].nacimiento, 
                  agenda->contactos[agenda->num_contactos].tipo_contacto,
                  &agenda->contactos[agenda->num_contactos].numero,
                  agenda->contactos[agenda->num_contactos].tipo_numero 
                 ) == 7) {
        agenda->num_contactos++;
    }
    
    fclose(archivo);
    printf("Se completo la carga en  %s. Total de contactos cargados: %d\n", filename, agenda->num_contactos);

}


/**
 * Función que sirve para guardar todos los contactos de la agenda en un archivo
 */
void guardar_contactos(char *filename, Agenda *agenda){
    FILE *archivo;
    archivo = fopen(filename, "w");
    if (archivo == NULL){
        printf("Error al abrir el archivo '%s' para guardar.\n", filename);
        return;
    }

    for(int i = 0; i < agenda->num_contactos; i++){
        fprintf(archivo, "%s %s %s %d %s %s %s\n",
        agenda->contactos[i].nombre,
        agenda->contactos[i].apellido,
        agenda->contactos[i].mes,
        agenda->contactos[i].nacimiento,
        agenda->contactos[i].tipo_contacto,
        agenda->contactos[i].numero,
        agenda->contactos[i].tipo_numero);
    }

    fclose(archivo);
    printf("Agenda guardada correctamente en '%s'. Total de contactos: %d\n", filename, agenda->num_contactos);

}