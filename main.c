#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lista.h"
#include "destino.h"

void carga_archivo(lista_reserva *reservas, FILE *f1) {
    int auxCant_Acomp, auxDia = 0, auxMes = 0, auxAnio = 0,i;
    double auxSenia;
    char auxNombre[40], auxCuil[12], auxc, auxTipoVinc[15], auxTipoSer[15], auxDestino[25];
    double auxcosto;
    reserva auxrese;
    fecha auxfecha;
    //Carga Cuil
    fscanf(f1, "%s", auxCuil);
    fscanf(f1, "%c", &auxc);
    carga_cuil(&auxrese, auxCuil);
    //Fin carga Cuil

    //Carga nommbre
    fflush(stdin);

    fscanf(f1, "%[^\n].s", auxNombre);
    fscanf(f1, "%c", &auxc);
    carga_nombre(&auxrese, auxNombre);
    //Fin carga nombre

    //Carga destino

    fscanf(f1, "%[^\n].s", auxDestino);
    fscanf(f1, "%c", &auxc);
    carga_destino(&auxrese,auxDestino);

    //Fin carga destino
    //Carga cantidad acompa�antes

    fscanf(f1, "%d", &auxCant_Acomp);
    fscanf(f1, "%c", &auxc);
    carga_amcomp(&auxrese, auxCant_Acomp);
    //Fin carga cantidad acompa�antes

    //Carga vinculo

    fscanf(f1, "%s", auxTipoVinc);
    fscanf(f1, "%c", &auxc);
    for(i=0;i<strlen(auxTipoVinc);i++){
        auxTipoVinc[i]=tolower(auxTipoVinc[i]);
    }
    if (strcmp(auxTipoVinc, "amigos") == 0) {
        carga_tipvinc(&auxrese, 1);
    } else if (strcmp(auxTipoVinc, "familia") == 0) {
        carga_tipvinc(&auxrese, 2);
    } else if (strcmp(auxTipoVinc, "companeros") == 0) {
        carga_tipvinc(&auxrese, 3);
    } else if (strcmp(auxTipoVinc, "otro") == 0) {
        carga_tipvinc(&auxrese, 4);
    }
    else{
       carga_tipvinc(&auxrese, 0);
    }

    //Fin carga vinculo

    //Carga se�a

    fscanf(f1, "%lf", &auxSenia);
    fscanf(f1, "%c", &auxc);
    carga_senia(&auxrese, auxSenia);

    //Fin carga se�a
    //Carga Fecha

    fscanf(f1, "%d", &auxDia);
    fscanf(f1, "%c", &auxc);

    fscanf(f1, "%d", &auxMes);
    fscanf(f1, "%c", &auxc);

    fscanf(f1, "%d", &auxAnio);
    fscanf(f1, "%c", &auxc);


    mod_anio(&auxfecha, auxAnio);
    mod_mes(&auxfecha, auxMes);
    mod_dia(&auxfecha, auxDia);
    carga_fecha(&auxrese, auxfecha);

    //Fin carga fecha
    //Carga tipo servicio
    fscanf(f1, "%s", auxTipoSer);
    fscanf(f1, "%c", &auxc);
    for (i=0;i<strlen(auxTipoSer);i++){
        auxTipoSer[i]=tolower(auxTipoSer[i]);
    }
    if (strcmp(auxTipoSer, "pasaje") == 0) {
        carga_tiposer(&auxrese, 1);
    } else if (strcmp(auxTipoSer, "alojamiento") == 0) {
        carga_tiposer(&auxrese, 2);
    } else if (strcmp(auxTipoSer, "allinclusive") == 0) {
        carga_tiposer(&auxrese, 3);
    }
    else {
       carga_tiposer(&auxrese, 0);
    }


    //Fin carga tipo servicio

    //Carga costo

    fscanf(f1, "%lf", &auxcosto);
    fscanf(f1, "%c", &auxc);
    carga_costo(&auxrese,auxcosto);

    //Fin carga costo





    //Insert
    if (isFull()) {
        printf("Error: no hay memoria para insertar la reserva, por favor intentelo de nuevo mas tarde. \n");
    } else {
        Insert(reservas, auxrese);
    }
}

void archivo2(lista_reserva *reserva) {
    FILE *archivo;
    if ((archivo = fopen("precarga.txt", "r")) == NULL) {
        printf("Error: no se pudo abrir el archivo. Intentelo de nuevo mas tarde \n");
    } else {
        while (feof(archivo) == 0) {
            carga_archivo(reserva, archivo);
        }
      printf("Carga realizada con exito.");
    }
    fclose(archivo);
}

void imprime_reserva_archivo(reserva r, FILE *f1) {
    fprintf(f1, "Datos de la reserva\n");
    fprintf(f1, "CUIL: %s\n", obtener_cuil(r));
    fprintf(f1, "Apellido y nombre: %s\n", obtener_nombre(r));
    fprintf(f1, "Destino: %s\n", obtener_destino(r));
    fprintf(f1, "Cantidad de acompa�antes: %d\n", obtener_acompan(r));
    fprintf(f1, "Vinculo con los acompa�antes: ");
    switch (obtener_vinculo(r)) {
        case 1:
            fprintf(f1, "Amigos\n");
            break;
        case 2:
            fprintf(f1, "Familia\n");
            break;
        case 3:
            fprintf(f1, "Compa�eros\n");
            break;
        case 4:
            fprintf(f1, "Otros\n");
            break;
        default:
            printf("Error: la precarga del archivo fallo.\n");
            break;
    }
    fprintf(f1, "Se�a: %.2lf\n", obtener_senia(r));
    fprintf(f1, "Fecha:\n");
    fprintf(f1, "Dia: %d\n", copy_dia(obtener_fecha(r)));
    fprintf(f1, "Mes: %d\n", copy_mes(obtener_fecha(r)));
    fprintf(f1, "A�o: %d\n", copy_anio(obtener_fecha(r)));
    fprintf(f1, "Tipo de servicio:");
    switch (obtener_tiposer(r)) {
        case 1:
            fprintf(f1, "Pasaje\n");
            break;
        case 2:
            fprintf(f1, "Alojamiento\n");
            break;
        case 3:
            fprintf(f1, "All-inclusive\n");
            break;
    }
    fprintf(f1, "Costo: %.2lf\n\n", obtener_monto(r));
}

int archivo1(lista_reserva *reserva, int auxtip) {
    int i = 0;
    FILE *archivo;
    switch (auxtip) {
        case 1:
            if ((archivo = fopen("amigos.txt", "a+")) == NULL) {
                printf("Error: no se pudo abrir el archivo. Intentelo de nuevo mas tarde");
                return 0;
            } else {
                while (!isOos(*reserva)) {
                    if (obtener_vinculo(copy(*reserva)) == 1) {
                        imprime_reserva_archivo(copy(*reserva), archivo);
                        i++;
                    }
                    forwards(reserva);
                }
            }
            break;
        case 2:
            if ((archivo = fopen("familia.txt", "a+")) == NULL) {
                printf("Error: no se pudo abrir el archivo. Intentelo de nuevo mas tarde");
                return 0;
            } else {
                while (!isOos(*reserva)) {
                    if (obtener_vinculo(copy(*reserva)) == 2) {
                        imprime_reserva_archivo(copy(*reserva), archivo);
                        i++;
                    }
                    forwards(reserva);
                }
            }
            break;
        case 3:
            if ((archivo = fopen("companieros.txt", "a+")) == NULL) {
                printf("Error: no se pudo abrir el archivo. Intentelo de nuevo mas tarde");
                return 0;
            } else {
                while (!isOos(*reserva)) {
                    if (obtener_vinculo(copy(*reserva)) == 3) {
                        imprime_reserva_archivo(copy(*reserva), archivo);
                        i++;
                    }
                    forwards(reserva);
                }
            }
            break;
        case 4:
            if ((archivo = fopen("otros.txt", "a+")) == NULL) {
                printf("Error: no se pudo abrir el archivo. Intentelo de nuevo mas tarde");
                return 0;
            } else {
                while (!isOos(*reserva)) {
                    if (obtener_vinculo(copy(*reserva)) == 4) {
                        imprime_reserva_archivo(copy(*reserva), archivo);
                        i++;
                    }
                    forwards(reserva);
                }
            }
            break;
    }
    fclose(archivo);
    return i;
}

void otra_op(int *oPtr) {
    int aux = 0;
    do {
        printf("\nDesea realizar otra operacion? 1 SI || 2 NO: ");
        scanf("%d", &aux);
    } while (aux != 1 && aux != 2);
    if (aux == 2)
        *oPtr = 13;
    system("cls");
}

void init_destinos(Destino destinos[]) {
    mod_destino(&destinos[0], "Venecia");
    mod_pasaje(&destinos[0], 351751);
    mod_alojamiento(&destinos[0], 447397);
    mod_allinclusive(&destinos[0], 523125);
    mod_destino(&destinos[1], "Sarajevo");
    mod_pasaje(&destinos[1], 331789);
    mod_alojamiento(&destinos[1], 412359);
    mod_allinclusive(&destinos[1], 483549);
    mod_destino(&destinos[2], "Kuala Lumpur");
    mod_pasaje(&destinos[2], 424725);
    mod_alojamiento(&destinos[2], 494421);
    mod_allinclusive(&destinos[2], 571679);
    mod_destino(&destinos[3], "Bali");
    mod_pasaje(&destinos[3], 417929);
    mod_alojamiento(&destinos[3], 488979);
    mod_allinclusive(&destinos[3], 524286);
    mod_destino(&destinos[4], "Zagreb");
    mod_pasaje(&destinos[4], 460937);
    mod_alojamiento(&destinos[4], 525782);
    mod_allinclusive(&destinos[4], 612125);
    mod_destino(&destinos[5], "Corsega");
    mod_pasaje(&destinos[5], 343145);
    mod_alojamiento(&destinos[5], 489046);
    mod_allinclusive(&destinos[5], 602948);
    mod_destino(&destinos[6], "Malta");
    mod_pasaje(&destinos[6], 560605);
    mod_alojamiento(&destinos[6], 665859);
    mod_allinclusive(&destinos[6], 695176);
    mod_destino(&destinos[7], "Ciudad del Cabo");
    mod_pasaje(&destinos[7], 236985);
    mod_alojamiento(&destinos[7], 315314);
    mod_allinclusive(&destinos[7], 412354);
    mod_destino(&destinos[8], "Tokio-Kioto");
    mod_pasaje(&destinos[8], 341375);
    mod_alojamiento(&destinos[8], 398875);
    mod_allinclusive(&destinos[8], 412354);
    mod_destino(&destinos[9], "Edinburgo");
    mod_pasaje(&destinos[9], 468864);
    mod_alojamiento(&destinos[9], 618490);
    mod_allinclusive(&destinos[9], 630531);
    mod_destino(&destinos[10], "Oslo");
    mod_pasaje(&destinos[10], 541508);
    mod_alojamiento(&destinos[10], 647093);
    mod_allinclusive(&destinos[10], 670157);
    mod_destino(&destinos[11], "Atenas");
    mod_pasaje(&destinos[11], 384184);
    mod_alojamiento(&destinos[11], 449029);
    mod_allinclusive(&destinos[11], 500239);
}

void mod_reserva(reserva *rese, reserva r) {
    carga_cuil(rese, obtener_cuil(r));
    carga_tiposer(rese, obtener_tiposer(r));
    carga_nombre(rese, obtener_nombre(r));
    carga_costo(rese, obtener_monto(r));
    carga_senia(rese, obtener_senia(r));
    carga_amcomp(rese, obtener_acompan(r));
    carga_tipvinc(rese, obtener_vinculo(r));
    carga_destino(rese, obtener_destino(r));
    carga_fecha(rese, obtener_fecha(r));
}

void imprime_reserva(reserva r) {
    printf("Datos de la reserva\n");
    printf("CUIL: %s\n", obtener_cuil(r));
    printf("Apellido y nombre: %s\n", obtener_nombre(r));
    printf("Destino: %s\n", obtener_destino(r));
    printf("Cantidad de acompa%cantes: %d\n", 164, obtener_acompan(r));
    printf("Vinculo con los acompa%cantes: ", 164);
    switch (obtener_vinculo(r)) {
        case 1:
            printf("Amigos\n");
            break;
        case 2:
            printf("Familia\n");
            break;
        case 3:
            printf("Compa%ceros\n", 164);
            break;
        case 4:
            printf("Otros\n");
            break;
        default:
            printf("Error: la precarga del archivo fallo.\n");
            break;
    }
    printf("Se%ca: %.2lf\n", 164, obtener_senia(r));
    printf("Fecha:\n");
    printf("Dia: %d\n", copy_dia(obtener_fecha(r)));
    printf("Mes: %d\n", copy_mes(obtener_fecha(r)));
    printf("A%co: %d\n", 164, copy_anio(obtener_fecha(r)));
    printf("Tipo de servicio:");
    switch (obtener_tiposer(r)) {
        case 1:
            printf("Pasaje\n");
            break;
        case 2:
            printf("Alojamiento\n");
            break;
        case 3:
            printf("All-inclusive\n");
            break;
        default:
            printf("Error: la precarga del archivo fallo.\n");
            break;
    }
    printf("Costo: %.2lf\n\n", obtener_monto(r));
}

void carga(lista_reserva *reservas, Destino destinos[]) {
    int i, cant, auxCant_Acomp, auxTipoVinc, auxTipoSer, ifaux, auxDia = 0, auxMes = 0, auxAnio = 0;
    double auxSenia;
    char auxNombre[40], auxCuil[12];
    int auxDestino;
    double auxcosto;
    reserva auxrese;
    fecha auxfecha;
    printf("Ingrese la cantidad de reservas que desea ingresar: \n");
    scanf("%d", &cant);
    fflush(stdin);
    for (i = 1; i <= cant; i++) {
        auxSenia = 0;
        //Carga Cuil
        printf("Ingrese su CUIL (sin guiones por favor): \n");
        scanf("%s", auxCuil);
        while ((strncmp(auxCuil, "20", 2) != 0) && (strncmp(auxCuil, "25", 2) != 0) &&
               (strncmp(auxCuil, "27", 2) != 0)) {
            printf("Ingrese un CUIl valido: \n");
            scanf("%s", auxCuil);
        }
        carga_cuil(&auxrese, auxCuil);
        //Fin carga Cuil

        //Carga nommbre
        fflush(stdin);
        printf("Ingrese su nombre completo como figura en su DNI: \n");
        scanf("%[^\n].s", auxNombre);
        carga_nombre(&auxrese, auxNombre);
        //Fin carga nombre

        //Carga cantidad acompa�antes
        printf("Ingrese la cantidad de personas con las que viaja (sin contarse a usted): \n");
        scanf("%d", &auxCant_Acomp);
        carga_amcomp(&auxrese, auxCant_Acomp);
        while(auxCant_Acomp<1){
            printf("Ingrese una cantidad valida\n");
            scanf("%d",&auxCant_Acomp);
        }
        //Fin carga cantidad acompa�antes

        //Carga vinculo
        printf("Ingrese el vinculo con sus acompa%cantes (1 <- Amigo | 2 <- Familia | 3 <- Compa%cero | 4 <- Otro): \n",164,164);
        scanf("%d", &auxTipoVinc);
        while (auxTipoVinc > 4 || auxTipoVinc < 0) {
            printf("Ingrese un numero correcto por favor. (1 <- Amigo | 2 <- Familia | 3 <- Compa%cero | 4 <- Otro): \n",164);
            scanf("%d", &auxTipoVinc);
        }
        carga_tipvinc(&auxrese, auxTipoVinc);
        //Fin carga vinculo

        //Carga destino
        printf("Ingrese el destino al cual desea viajar: \n");
        printf(" <1> Venecia \n <2> Sarajevo \n <3> Kuala Lumpur \n <4> Bali \n <5> Zagreb \n <6> Corsega \n <7> Malta \n <8> Ciudad del cabo \n <9> Tokio-Kioto \n <10> Edimburgo \n <11> Oslo \n <12> Atenas\n");
        scanf("%d", &auxDestino);
        while (auxDestino < 0 || auxDestino > 12) {
            printf("Valor ingresado invalido. Ingrese un destino valido\n");
            scanf("%d", &auxDestino);
        }
        carga_destino(&auxrese, destinos[auxDestino - 1].destino);
        //Fin carga destino

        //Carga tipo servicio
        printf("Ingrese el tipo de servicio: 1 Pasaje,  2 Alojamiento, 3 All-inclusive\n");
        scanf("%d", &auxTipoSer);
        while (auxTipoSer < 0 || auxTipoSer > 3) {
            printf("Valor invalido. Ingrese un tipo de servicio valido\n");
            scanf("%d", &auxTipoSer);
        }
        carga_tiposer(&auxrese, auxTipoSer);
        //Fin carga tipo servicio

        //Carga costo
        switch (auxTipoSer) {
            case 1:
                carga_costo(&auxrese, obtener_pasaje(destinos[auxDestino - 1]) * (auxCant_Acomp + 1));
                auxcosto = obtener_pasaje(destinos[auxDestino - 1]) * (auxCant_Acomp + 1);
                break;
            case 2:
                carga_costo(&auxrese, obtener_alojamiento(destinos[auxDestino - 1]) * (auxCant_Acomp + 1));
                auxcosto = obtener_alojamiento(destinos[auxDestino - 1]) * (auxCant_Acomp + 1);
                break;
            case 3:
                carga_costo(&auxrese, obtener_allinclusive(destinos[auxDestino - 1]) * (auxCant_Acomp + 1));
                auxcosto = obtener_allinclusive(destinos[auxDestino - 1]) * (auxCant_Acomp + 1);
                break;
        }
        printf("El costo total de su reserva es: %lf\n", obtener_monto(auxrese));
        //Fin carga costo

        //Carga se�a
        printf("Desea abonar la se%ca ahora? Recuerde que el valor minimo para el primer se%cado es de el 30 porciento del costo. 1 <- SI | 2 <- NO\n",
               164, 164);
        scanf("%d", &ifaux);
        while (ifaux < 1 || ifaux > 2) {
            printf("Ingrese una opcion valida\n");
            scanf("%d", &ifaux);
        }
        if (ifaux == 1) {
            printf("El monto minimo a abonar es: %.2lf\n", auxcosto * 0.3);
            printf("Ingrese el monto a abonar en la se%ca:\n", 164);
            scanf("%lf", &auxSenia);
            while (auxSenia < obtener_monto(auxrese) * 0.3 || auxSenia > obtener_monto(auxrese)) {
                printf("Ingrese un monto valido, recuerde que el primer pago de la se%ca debe ser mayor o igual al 30 porciento del costo y no puede superar el costo\n", 164);
                scanf("%lf", &auxSenia);
            }
            carga_senia(&auxrese, auxSenia);
        } else {
            carga_senia(&auxrese, 0);
        }
        //Fin carga se�a

        //Carga Fecha
        printf("Ingrese la fecha en la que desea viajar (fechas disponibles entre diciembre de 2021 y febrero de 2022)\n");
        printf("Dia: \n");
        scanf("%d", &auxDia);
        printf("Mes: \n");
        scanf("%d", &auxMes);
        printf("A%co: \n", 164);
        scanf("%d", &auxAnio);


        while (auxAnio < 2021 || auxAnio > 2022) {
            printf("Ingrese un a%co valido (fechas validas: de diciembre de 2021 a febero de 2022):  \n", 164);
            scanf("%d", &auxAnio);
        }
        while ((auxAnio == 2021 && auxMes != 12) || (auxAnio == 2022 && (auxMes != 1 && auxMes != 2))) {
            printf("Ingrese un mes valido (fechas validas: de diciembre de 2021 a febero de 2022): \n");
            scanf("%d", &auxMes);
        }
        while (((auxMes == 12 || auxMes == 1) && (auxDia < 1 || auxDia > 31)) ||
               (auxMes == 2 && (auxDia < 1 || auxDia > 28))) {
            printf("Ingrese un dia valido (fechas validas: de diciembre de 2021 a febero de 2022): \n");
            scanf("%d", &auxDia);
        }
        mod_anio(&auxfecha, auxAnio);
        mod_mes(&auxfecha, auxMes);
        mod_dia(&auxfecha, auxDia);
        carga_fecha(&auxrese, auxfecha);
        //Fin carga fecha

        //Insert
        if (isFull()) {
            printf("Error: no hay memoria para insertar la reserva, por favor intentelo de nuevo mas tarde. \n");
        } else {
            Insert(reservas, auxrese);
            printf("Carga realizada exitosamente.\n");
        }
    }
}

reserva busca_cuil(lista_reserva *reservas, char auxcuil[]) {
    reserva auxrese;
    carga_cuil(&auxrese, "0");
    while (isOos(*reservas) == 0) {
        if (strcmp(obtener_cuil(copy(*reservas)), auxcuil) == 0) {
            auxrese = copy(*reservas);
            return auxrese;
        } else {
            forwards(reservas);
        }
    }
    return auxrese;
}

void imprime_datos_cuil(lista_reserva *reservas, char auxcuil[]) {
    reserva auxrese;
    int i=0;
    reset(reservas);
    carga_cuil(&auxrese, "0");

    while (!isOos(*reservas)) {
        auxrese = busca_cuil(reservas, auxcuil);
        if (strcmp(obtener_cuil(auxrese), "0") != 0) {
            imprime_reserva(auxrese);
            forwards(reservas);
            i=1;
        }
    }
    if(i == 0){
        printf("No se encontro ninguna reserva con ese CUIL. \n");
    }
}

void imprime_todas_listas(lista_reserva reservas) {
    reserva aux;
    reset(&reservas);
    while (!isOos(reservas)) {
        aux = copy(reservas);
        imprime_reserva(aux);
        forwards(&reservas);
    }
}

void modif_senia(lista_reserva *reservas, double auxmonto) {
    double modificacion = 0;
    reserva auxrese;
    if (obtener_senia(copy(*reservas)) == 0) {
        printf("Su se%ca inicial minima debe ser de %.2lf o mas. Ingrese el monto a pagar la se%ca:\n",164, auxmonto * 0.3, 164);
        scanf("%lf", &modificacion);
        while (modificacion < (auxmonto * 0.3) || modificacion > auxmonto) {
            printf("Ingrese un monto valido. Recuerde que no debe ser menor al 30 porciento ni tampoco exceder el monto total: \n");
            scanf("%lf", &modificacion);
        }
        mod_reserva(&auxrese, copy(*reservas));
        modifica_senia(&auxrese, modificacion);
        supress(reservas);
        Insert(reservas, auxrese);
    } else {
        printf("Ingrese el monto que desea agregarle a la se%ca: (recuerde que no debe pasar el total) \n", 164);
        scanf("%lf", &modificacion);
        while (modificacion + obtener_senia(copy(*reservas)) > auxmonto) {
            printf("El valor ha excedido el precio total. Ingrese nuevamente: \n");
            scanf("%lf", &modificacion);
        }
        mod_reserva(&auxrese, copy(*reservas));
        modifica_senia(&auxrese, modificacion);
        supress(reservas);
        Insert(reservas, auxrese);
    }
}

void modificar_ser(lista_reserva *reservas, Destino destino[]) {
    int choise, i;
    reserva auxrese;
    switch (obtener_tiposer(copy(*reservas))) {
        case 1:
            printf("Su tipo de servicio es: Pasaje \n");
            break;
        case 2:
            printf("Su tipo de servicio es: Alojamiento \n");
            break;
        case 3:
            printf("Su tipo de servicio es: All-inclusive\n");
            break;
    }
    printf("A que tipo de servicio desea cambiarse? \n");
    printf("1 <- Pasaje | 2 <- Alojamiento | 3 <- All-inclusive \n");
    scanf("%d", &choise);
    while (obtener_tiposer(copy(*reservas)) == choise) {
        printf("No puede cambiarse al mismo tipo que habia seleccionado antes. Ingrese nuevamente: \n");
        scanf("%d", &choise);
    }
    switch (choise) {
        case 1:
            mod_reserva(&auxrese, copy(*reservas));
            modifica_tipser(&auxrese, choise);
            supress(reservas);
            Insert(reservas, auxrese);
            for (i = 0; i < 12; i++) {
                if (strcmp(obtener_destino(copy(*reservas)), destino[i].destino) == 0) {
                    mod_reserva(&auxrese, copy(*reservas));
                    modifica_costo(&auxrese, obtener_pasaje(destino[i]) * (obtener_acompan(copy(*reservas)) + 1));
                    supress(reservas);
                    Insert(reservas, auxrese);
                }
            }
            break;
        case 2:
            mod_reserva(&auxrese, copy(*reservas));
            modifica_tipser(&auxrese, choise);
            supress(reservas);
            Insert(reservas, auxrese);
            for (i = 0; i < 12; i++) {
                if (strcmp(obtener_destino(copy(*reservas)), destino[i].destino) == 0) {
                    mod_reserva(&auxrese, copy(*reservas));
                    modifica_costo(&auxrese, obtener_alojamiento(destino[i]) * (obtener_acompan(copy(*reservas)) + 1));
                    supress(reservas);
                    Insert(reservas, auxrese);
                }
            }
            break;
        case 3:
            mod_reserva(&auxrese, copy(*reservas));
            modifica_tipser(&auxrese, choise);
            supress(reservas);
            Insert(reservas, auxrese);
            for (i = 0; i < 12; i++) {
                if (strcmp(obtener_destino(copy(*reservas)), destino[i].destino) == 0) {
                    mod_reserva(&auxrese, copy(*reservas));
                    modifica_costo(&auxrese, obtener_allinclusive(destino[i]) * (obtener_acompan(copy(*reservas)) + 1));
                    supress(reservas);
                    Insert(reservas, auxrese);
                }
            }
            break;
    }
}

void borrar_reserv(lista_reserva *reservas, char auxcuil[]) {
    reserva auxrese;
    int choise;
    int i=0;
    while (!isOos(*reservas)) {
        auxrese = busca_cuil(reservas, auxcuil);
        if (strcmp(obtener_cuil(auxrese), "0") != 0) {
            imprime_reserva(auxrese);
            printf("Desea borrar esta reserva? 1 <- SI || 2 <- NO \n");
            scanf("%d", &choise);
            while (choise > 2 || choise < 0) {
                printf("Ingrese un numero valido. 1 <- SI || 2 <- NO\n");
                scanf("%d", &choise);
            }
            if (choise == 1) {
                if (isEmpty(*reservas)) {
                    printf("No hay reservas cargadas. Intentelo mas tarde \n");
                    break;
                } else {
                    supress(reservas);
                }
            }
            forwards(reservas);
            i=1;
        }
    }
    if(i==0){
        printf("No se encontro ninguna reserva con ese CUIl\n");
    }
}

void busca_fecha(lista_reserva *reservas) {
    reset(reservas);
    int i=0;
    int auxanio;
    int auxmes;
    reserva auxrese;
    printf("Ingrese el a%co por el que desea filtrar(2021 o 2022): \n", 164);
    scanf("%d", &auxanio);
    while (auxanio < 2021 || auxanio > 2022) {
        printf("Ingrese un a%co disponible (2021 o 2022): \n", 164);
        scanf("%d", &auxanio);
    }
    printf("Ingrese el mes por el que desea filtar (diciembre 2021- febrero 2022) \n");
    scanf("%d", &auxmes);
    if (auxanio == 2021) {
        while (auxmes != 12) {
            printf("Ingrese un mes disponible (diciembre 2021-febrero 2022) \n");
            scanf("%d", &auxmes);
        }
    } else {
        while (auxmes < 1 || auxmes > 2) {
            printf("Ingrese un mes disponible (diciembre 2021- febrero 2022)");
            scanf("%d", &auxmes);
        }
    }
    while (!isOos(*reservas)) {
        auxrese = copy(*reservas);
        if (copy_mes(obtener_fecha(copy(*reservas))) == auxmes &&
            copy_anio(obtener_fecha(copy(*reservas))) == auxanio) {
            imprime_reserva(auxrese);
            i=1;
        }
        forwards(reservas);
    }
    if (i==0){
        printf("No se han encontrado reservas en ese mes\n");
    }

}

void senia_a_pagar(lista_reserva reservas) {
    int i = 0;
    reset(&reservas);
    printf("Las siguientes son las reservas que no han abonado se%ca: \n", 164);
    while (!isOos(reservas)) {
        if (obtener_senia(copy(reservas)) == 0) {
            imprime_reserva(copy(reservas));
            forwards(&reservas);
            i = 1;
        } else {
            forwards(&reservas);
        }
    }
    if (i == 0) {
        printf("Todas las reservas han pagado su se%ca \n", 164);
    }
}

int cant_dest(lista_reserva *reservas, int auxdest, Destino destino[], int acum) {
    if (isOos(*reservas)) {
        return 0;
    } else {
        if (strcmp(obtener_destino(copy(*reservas)), obtener_dest(destino[auxdest - 1])) == 0) {
            acum = obtener_acompan(copy(*reservas));
            forwards(reservas);
            return acum + 1 + cant_dest(reservas, auxdest, destino, acum);
        } else {
            forwards(reservas);
            return cant_dest(reservas, auxdest, destino, acum);

        }
    }
}

double monto_a_pagar(lista_reserva reservas, int tipo) {
    double auxmonto;
    imprime_reserva(copy(reservas));
    switch (tipo) {
        case 1:
            printf("Su monto a pagar es: %.2lf \n\n", (obtener_monto(copy(reservas)) - obtener_senia(copy(reservas))) * 0.9);
            auxmonto=(obtener_monto(copy(reservas)) - obtener_senia(copy(reservas))) * 0.9;
            return auxmonto;
            break;
        case 2:
            printf("Su monto a pagar es: %.2lf \n\n", (obtener_monto(copy(reservas)) - obtener_senia(copy(reservas))) * 1);
            auxmonto=(obtener_monto(copy(reservas)) - obtener_senia(copy(reservas)));
            return auxmonto;
            break;
        case 3:
            printf("Su monto a pagar es: %.2lf \n\n", (obtener_monto(copy(reservas)) - obtener_senia(copy(reservas))) * 1.1);
            auxmonto=(obtener_monto(copy(reservas)) - obtener_senia(copy(reservas))*1.1);
            return auxmonto;
            break;

    }
        return 0;
}

int main() {
    lista_reserva reservas;
    reserva auxrese;
    double auxmonto;
    int auxp, choise = 0, auxdestino, auxchoice, auxtip, i;
    char auxcuil[12];
    strcpy(auxcuil, "0");
    Destino destinos[12];
    init_destinos(destinos);
    init(&reservas);
    while (choise != 13) {
        printf("\t\tBienvenido Bifrost viajes!!\n\n\n");
        printf("\t\tPor favor elija una opcion\n\n\n");
        printf("\t\t<1> Cargar Reservas\n\n");
        printf("\t\t<2> Mostrar reservas por CUIL\n\n");
        printf("\t\t<3> Mostrar reservas en un mes y a%co\n\n", 164);
        printf("\t\t<4> Mostrar todas las reservas\n\n");
        printf("\t\t<5> Modificar la se%ca\n\n", 164);
        printf("\t\t<6> Modificar tipo de servicio\n\n");
        printf("\t\t<7> Borrar reservas segun el CUIL\n\n");
        printf("\t\t<8> Calcular la cantidad de personas por Destino\n\n");
        printf("\t\t<9> Mostrar monto a pagar\n\n");
        printf("\t\t<10> Mostrar reservas que aun no han abonado la se%ca \n\n", 164);
        printf("\t\t<11> Cargar reservas a un archivo\n\n");
        printf("\t\t<12> Precargar reservas desde un archivo\n\n");
        printf("\t\t<13> Salir\n\n");
        scanf("%d", &choise);
        while (choise > 13 || choise < 1) {
            printf("\t\t La opcion ingresada es invalida, por favor ingrese una opcion valida\n\n");
            scanf("%d", &choise);
        }
        switch (choise) {
            case 1:
                carga(&reservas, destinos);
                otra_op(&choise);
                break;
            case 2:
                if (isEmpty(reservas)) {
                    printf("No se han ingresado reservas. Intentelo de nuevo mas tarde\n");
                } else {
                    printf("Ingrese el CUIl a buscar: ");
                    scanf("%s", auxcuil);
                    while ((strncmp(auxcuil, "20", 2) != 0) && (strncmp(auxcuil, "25", 2) != 0) &&
                           (strncmp(auxcuil, "27", 2) != 0)) {
                        printf("Ingrese un CUIl valido: \n");
                        scanf("%s", auxcuil);
                    }
                    imprime_datos_cuil(&reservas, auxcuil);
                }
                otra_op(&choise);
                break;
            case 3:
                if (isEmpty(reservas)) {
                    printf("No se han ingresado reservas. Intentelo de nuevo mas tarde \n");
                } else
                    busca_fecha(&reservas);
                otra_op(&choise);
                break;
            case 4:
                if (isEmpty(reservas)) {
                    printf("No se han ingresado reservas. Intentelo de nuevo mas tarde\n");
                } else {
                    imprime_todas_listas(reservas);
                }
                otra_op(&choise);
                break;
            case 5:
                i=0;
                reset(&reservas);
                if (isEmpty(reservas)) {
                    printf("No se han ingresado reservas. Intentelo de nuevo mas tarde \n");
                } else {
                    printf("Ingrese el CUIl a buscar: ");
                    scanf("%s", auxcuil);
                    while ((strncmp(auxcuil, "20", 2) != 0) && (strncmp(auxcuil, "25", 2) != 0) &&
                           (strncmp(auxcuil, "27", 2) != 0)) {
                        printf("Ingrese un CUIl valido: \n");
                        scanf("%s", auxcuil);
                    }
                    while (!isOos(reservas)) {
                        auxrese = busca_cuil(&reservas, auxcuil);
                         if (strcmp(obtener_cuil(auxrese), "0") != 0) {
                            imprime_reserva(auxrese);
                            printf("Es esta la reserva que desea Modificar? <1> SI <2> NO\n");
                            scanf("%d", &auxchoice);
                            while (auxchoice < 1 || auxchoice > 2) {
                                printf("Valor invalido. Ingrese un valor valido <1> SI, <2> NO\n");
                                scanf("%d", &auxchoice);
                            }
                            if (auxchoice == 1) {
                                printf("Ingrese el metodo de pago: <1> Efectivo <2> Debito <3> Credito\n");
                                scanf("%d", &auxp);
                                while (auxp < 1 || auxp > 3) {
                                    printf("Valor invalido. Ingrese un metodo de pago: <1> Efectivo <2> Debito <3> Credito\n");
                                    scanf("%d", &auxp);
                                }
                                auxmonto=monto_a_pagar(reservas, auxp);
                                modif_senia(&reservas,auxmonto);
                                printf("Operacion realizada con exito\n");
                            }
                            i=1;
                            forwards(&reservas);
                        }
                    }
                    if(i == 0){
                        printf("No se ha encontrado una reserva con ese CUIL. \n");
                    }
                }
                otra_op(&choise);
                break;
            case 6:
                i = 0;
                if (isEmpty(reservas)) {
                    printf("No se han ingresado reservas. Intentelo de nuevo mas tarde\n");
                } else {
                    reset(&reservas);
                    printf("Ingrese el CUIl a buscar: ");
                    scanf("%s", auxcuil);
                    while ((strncmp(auxcuil, "20", 2) != 0) && (strncmp(auxcuil, "25", 2) != 0) &&
                           (strncmp(auxcuil, "27", 2) != 0)) {
                        printf("Ingrese un CUIl valido: \n");
                        scanf("%s", auxcuil);
                    }
                    while (!isOos(reservas)) {
                        auxrese = busca_cuil(&reservas, auxcuil);
                        if (strcmp(obtener_cuil(auxrese), "0") != 0) {
                            imprime_reserva(copy(reservas));
                            printf("Es esta la reserva que desea Modificar?: <1> SI <2> NO\n");
                            scanf("%d", &auxchoice);
                            while (auxchoice < 1 || auxchoice > 2) {
                                printf("Valor invalido, Ingrese un valor valido <1> SI <2> NO\n ");
                                scanf("%d", &auxchoice);
                            }
                            if (auxchoice == 1) {
                                modificar_ser(&reservas, destinos);
                                printf("Operacion realizada con exito\n");
                            }
                            forwards(&reservas);
                            i=1;
                        }
                    }
                    if(i == 0){
                        printf("No se ha encontrado una reserva con ese CUIL. \n");
                    }
                }
                otra_op(&choise);
                break;
            case 7:
                if (isEmpty(reservas)) {
                    printf("No se han ingresado reservas. Intentelo de nuevo mas tarde \n");
                } else {
                    reset(&reservas);
                    printf("Ingrese el CUIl a buscar: ");
                    scanf("%s", auxcuil);
                    while ((strncmp(auxcuil, "20", 2) != 0) && (strncmp(auxcuil, "25", 2) != 0) &&
                           (strncmp(auxcuil, "27", 2) != 0)) {
                        printf("Ingrese un CUIl valido: ");
                        scanf("%s", auxcuil);
                    }
                    borrar_reserv(&reservas, auxcuil);
                    printf("Operacion realizada con exito\n");
                }
                otra_op(&choise);
                break;
            case 8:
                if (isEmpty(reservas)) {
                    printf("No se han ingresado reservas. Intentelo de nuevo mas tarde\n");
                } else {
                    printf("Ingrese el destino por el cual desea filtrar: \n");
                    printf(" <1> Venecia \n <2> Sarajevo \n <3> Kuala Lumpur \n <4> Bali \n <5> Zagreb \n <6> Corsega \n <7> Malta \n <8> Ciudad del cabo \n <9> Tokio-Kioto \n <10> Edimburgo \n <11> Oslo \n <12> Atenas\n");
                    scanf("%d", &auxdestino);
                    while (auxdestino < 0 || auxdestino > 12) {
                        printf("Valor ingresado invalido. Ingrese un destino valido: \n");
                        scanf("%d", &auxdestino);
                    }
                    reset(&reservas);
                    printf("La cantidad de personas que viajan a %s son %d\n", obtener_dest(destinos[auxdestino - 1]),cant_dest(&reservas, auxdestino, destinos, 0));
                }
                otra_op(&choise);
                break;
            case 9:
                i=0;
                if (isEmpty(reservas)) {
                    printf("No se han ingresado reservas. Intentelo de nuevo mas tarde\n");
                } else {
                    reset(&reservas);
                    printf("Ingrese el CUIl a buscar: ");
                    scanf("%s", auxcuil);
                    while ((strncmp(auxcuil, "20", 2) != 0) && (strncmp(auxcuil, "25", 2) != 0) &&
                           (strncmp(auxcuil, "27", 2) != 0)) {
                        printf("Ingrese un CUIl valido: ");
                        scanf("%s", auxcuil);
                    }
                    printf("Ingrese el metodo de pago: <1> Efectivo <2> Debito <3> Credito \n");
                    scanf("%d", &auxp);
                    while (auxp < 1 || auxp > 3) {
                        printf("Valor invalido. Ingrese un metodo de pago: <1> Efectivo <2> Debito <3> Credito\n");
                        scanf("%d", &auxp);
                    }
                    while (!isOos(reservas)) {
                        auxrese = busca_cuil(&reservas, auxcuil);
                        if (strcmp(obtener_cuil(auxrese), "0") != 0) {
                            monto_a_pagar(reservas, auxp);
                            forwards(&reservas);
                            i=1;
                        }
                    }
                    if (i==0){
                        printf("No se ha encontrado reservas con ese CUIL\n");
                    }
                }
                otra_op(&choise);
                break;
            case 10:
                if (isEmpty(reservas)) {
                    printf("No se han ingresado reservas. Intentelo de nuevo mas tarde \n");
                } else
                    senia_a_pagar(reservas);
                otra_op(&choise);
                break;
            case 11:
                reset(&reservas);
                printf("Por que vinculo desea filtrar? 1 <- Amigos || 2 <- Familia || 3 <- Compa%ceros || 4 <- Otro \n",
                       164);
                scanf("%d", &auxtip);
                while (auxtip < 0 || auxtip > 4) {
                    printf("Valor invalido. Ingrese un valor valido:  1 <- Amigos || 2 <- Familia || 3 <- Compa%ceros || 4 <- Otro \n",
                           164);
                    scanf("%d", &auxtip);
                }
                printf("La cantidad de reservas cargadas al archivo son: %d\n", archivo1(&reservas, auxtip));
                otra_op(&choise);
                break;
            case 12:
                archivo2(&reservas);
                otra_op(&choise);
                break;
            case 13:
                break;
        }
    }
     printf("Gracias por usar nuestro sistema!!");
    return 0;
}
