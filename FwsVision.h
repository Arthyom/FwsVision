#ifndef FWSVISION_H
#define FWSVISION_H

    /**************************************************************************************/
    /*********                                                                  ***********/
    /*********          conjunto de utilidades para vision computacional        ***********/
    /*********                                                                  ***********/
    /**************************************************************************************/

    # include <stdio.h>
    # include <stdlib.h>
    # include <stdarg.h>
    # include <string.h>
    # include <math.h>
    # include <time.h>

    # define RUTA_DIR "C:/Users/frodo/Documents/herramientas/Utilidades/FWSvision/FWSvision/"

        /******************************************/
        /******** contenedor imagen BmP   *********/
        /******************************************/
        typedef struct {

            /****** cabecera de la imagen ********/

            char *      nombreRuta;     // ruta o nombre de la imagen
            char *      nombreImagen;   //
            char *      nombreCompleto; // ruta + nombre de la imagen
            int         vectorDims;     // dimenciones para un vector de imagenes BMP
            char        nmbrRtSv;       // ruta o nombre de guardado

            char        imagenTipo [2]; // tipo de imagen BMP, JPEG etc
            int         imagenDims;     // tamanio de la imagen en bytes
            int         imagenResrv;
            int         imagenOffst;    // despalazamiento hasta los datos
            int         imagenDmsMt;    // dimenciones en bytes de los metadatos

            int         imagenAlto;
            int         imagenAncho;

            short int   imagenNmPlns;   // numero de planos
            short int   imagenPrfClr;   // profundidad de color

            int         imagenTpCmp;    // tipo de comprencion
            int         imagenDEstr;    // dimenciones en bytes de la estructura imagen
            int         imagenPxMH;     // pixeles por metro horizontal
            int         imagenPxMV;     // pixeles por metro vertical
            int         imagenClrUs;    // cantidad de colores usados
            int         imagenClrImp;   // cantidad de colores importantes

            unsigned char **     imagenMtrzPxlR;  // matriz de pixeles para la imagen
            unsigned char **     imagenMtrzPxlG;  // matriz de pixeles para la imagen
            unsigned char **     imagenMtrzPxlB;  // matriz de pixeles para la imagen

        }contenedorBmp;


        /**********************************************************/
        /**************** prototips y declaracion *****************/
        /**********************************************************/





#endif // FWSVISION_H

        //*************> FUNCIONES MISELANEAS

        // lista
        contenedorBmp *     FwsVcrearContenedor           ( ){

            // crear un nuevo contnedor
            contenedorBmp * nuevoContenedor = ( contenedorBmp * ) malloc ( sizeof(contenedorBmp));

            // iniciar propiedades a valores conocidos
            nuevoContenedor->nombreRuta = ' ';
            nuevoContenedor->vectorDims = 0;

            return nuevoContenedor;
        }

        // limpia
        char **             FwsVcrearMatriz               ( int dimsX, int dimsY ){

            // reservar una nueva matriz
            char ** matriz = (char**) malloc(sizeof(char*) * dimsX);
            int i,j;
            for ( i = 0 ; i < dimsX ; i ++ )
                matriz[i] = (char*) malloc (sizeof(char) * dimsY);

            // iniciar la matriz a algo conocido
            for ( i = 0 ; i < dimsX ; i ++ )
                for ( j = 0 ; j < dimsY ; j ++ )
                    matriz[i][j] = '0';

            return matriz;
        }

        // lista
        void                FwsVmostrarImagenes           ( char identificador, contenedorBmp * contenedorEntrada, contenedorBmp * contenedorSalida, char *nombreDestino ){

            /******** la funcion toma un html como plantilla donde buscara el caracter #
                   sera cambiado por el nombre de las imagenes bmp de entrada y salida
                   el html del archivo plantilla sera pasado a un segundo archivo
                   con el nombre destino que se le proporcione a la funcion los caracteres #
                   son intercambiado por el nobre de la imagen ********/

            FILE * plantillaHtml  = fopen("C:/Users/frodo/Documents/herramientas/Utilidades/FWSvision/FWSvision/plantillaHtml.html","r");
            FILE * archivoDestino = fopen(nombreDestino,"w");

            int imagenDestino= 1;

            // mover caracteres de plantilla a destino y cambiar # por nombres de imagenes
            while ( !feof(plantillaHtml) ){
                char caracterExtraido = fgetc(plantillaHtml);
                if (caracterExtraido != identificador)
                    fputc(caracterExtraido,archivoDestino);
                else
                {
                    switch (imagenDestino){
                        case 1:
                            fprintf(archivoDestino," \" %s \" ",contenedorEntrada->nombreImagen);
                            imagenDestino++;
                        break;

                        case 2:
                            fprintf(archivoDestino," \" %s \" ",contenedorSalida->nombreImagen);
                            imagenDestino++;
                        break;

                    }
                }
            }

            // cerrar plantilla y mostrar archivo destino
            fclose(plantillaHtml);
            fclose(archivoDestino);
            system(nombreDestino);
        }

        // lista
        void                FwsVimprmrRutas               ( contenedorBmp * vectorContenedorBmp, int dims ){

            // recorrer cada uno de los elementos del vecotor
            int i;
            for ( i = 0 ; i < dims ; i ++ )
                printf("%s \n", &vectorContenedorBmp[i].nombreImagen);
        }

        // lista
        void                FwsVmostrarImagen             ( contenedorBmp * contenedorEntrada, char identificador, char *nombreDestino ){

            FILE * plantillaHtml  = fopen("C:/Users/frodo/Documents/herramientas/Utilidades/FWSvision/FWSvision/plantillaHtml.html","r");
            FILE * archivoDestino = fopen(nombreDestino,"w");

            while ( !feof(plantillaHtml) ){
                char caracterExtraido = fgetc(plantillaHtml);
                if (caracterExtraido != identificador)
                    fputc(caracterExtraido,archivoDestino);
                else
                    fprintf(archivoDestino," \" %s \" ",archivoDestino);
            }

            fclose(plantillaHtml);
            fclose(archivoDestino);
            system(nombreDestino);

        }

        contenedorBmp *     FwsVcopiarImagenColor         ( contenedorBmp * contenedorEntrada){

            // crear nuevo contendor
            contenedorBmp * contenedorCopia = FwsVcrearContenedor();

            // copiar propiedades
            contenedorCopia->imagenAlto  = contenedorEntrada->imagenAlto;
            contenedorCopia->imagenAncho = contenedorEntrada->imagenAncho;
            contenedorCopia->imagenClrImp = contenedorEntrada->imagenClrImp;

            contenedorCopia->imagenClrUs = contenedorEntrada->imagenClrUs;
            contenedorCopia->imagenDEstr = contenedorEntrada->imagenDEstr;
            contenedorCopia->imagenDims = contenedorEntrada->imagenDims;

            contenedorCopia->imagenDmsMt = contenedorEntrada->imagenDmsMt;
            contenedorCopia->imagenMtrzPxlB = contenedorEntrada->imagenMtrzPxlB;
            contenedorCopia->imagenMtrzPxlG = contenedorEntrada->imagenMtrzPxlG;
            contenedorCopia->imagenMtrzPxlR = contenedorEntrada->imagenMtrzPxlR;

            contenedorCopia->imagenNmPlns = contenedorEntrada->imagenNmPlns;
            contenedorCopia->imagenPrfClr = contenedorEntrada->imagenPrfClr;
            contenedorCopia->imagenPxMH = contenedorEntrada->imagenPxMH;
            contenedorCopia->imagenPxMV = contenedorEntrada->imagenPxMV;
            contenedorCopia->imagenResrv = contenedorEntrada->imagenResrv;

            strcpy(contenedorCopia->imagenTipo,contenedorEntrada->imagenTipo);
            contenedorCopia->imagenTpCmp = contenedorEntrada->imagenTpCmp;
            strcpy(contenedorCopia->nmbrRtSv, contenedorEntrada->nmbrRtSv);
            strcpy(contenedorCopia->nombreCompleto, contenedorEntrada->nombreCompleto);
            strcpy(contenedorCopia->nombreImagen,contenedorEntrada->nombreImagen);

            strcpy(contenedorCopia->nombreRuta, contenedorEntrada->nombreRuta);
            return contenedorCopia;

        }

        void                FwsVinConctName                 ( contenedorBmp * contenedorEntrada){

            // concatenar el nombre de imagen con la ruta de la imagen para obtener el nombre completo
            char * nombreCompleto = (char*) malloc( sizeof(char) *( strlength(contenedorEntrada->nombreRuta) + strlength(contenedorEntrada->nombreImagen) ) );
            strcpy(nombreCompleto,contenedorEntrada->nombreRuta);

            // concatenar la cadena
            strcat(nombreCompleto,contenedorEntrada->nombreImagen);
            strcpy(contenedorEntrada->nombreCompleto, contenedorEntrada->nombreCompleto);

        }

        /************ peligo **********/
        contenedorBmp *     FwsVguardarImagenBmpColor         ( contenedorBmp * bmpEntrada, char * nombreSalida, char *nombreImagens ){

            // crear el nuevo archivo
            FILE * nuevaImagenSalida = fopen( nombreSalida, "wb+");

            // verificar si se ha podifo salvar la imagen
            if ( nuevaImagenSalida ){

                // crear contenedor para la imagen de salida
                contenedorBmp * nuevoContenedorSalida = FwsVcrearContenedor();
                nuevoContenedorSalida->nombreRuta   = nombreSalida;
                nuevoContenedorSalida->nombreImagen = nombreImagens;

                // leer la imagen indicada
                fseek(nuevaImagenSalida,0,SEEK_SET);
                fwrite(&bmpEntrada->imagenTipo,sizeof(char),2,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenDims,sizeof(int),1,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenResrv,sizeof(int),1,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenOffst,sizeof(int),1,nuevaImagenSalida);

                fwrite(&bmpEntrada->imagenDmsMt ,sizeof(int),1,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenAlto,sizeof(int),1,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenAncho,sizeof(int),1,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenNmPlns,sizeof(short int),1,nuevaImagenSalida);

                fwrite(&bmpEntrada->imagenPrfClr,sizeof(short int),1,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenTpCmp,sizeof(int),1,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenDEstr,sizeof(int),1,nuevaImagenSalida);

                fwrite(&bmpEntrada->imagenPxMH,sizeof(int),1,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenPxMV,sizeof(int),1,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenClrUs,sizeof(int),1,nuevaImagenSalida);
                fwrite(&bmpEntrada->imagenClrImp,sizeof(int),1,nuevaImagenSalida);

                // mover la matriz del contenedor de entrada al contenedor de salida
                int i, j ;



                for ( i = 0 ; i < bmpEntrada->imagenAlto ; i ++ )
                {
                    for ( j = 0 ; j < bmpEntrada->imagenAncho ; j ++ )
                    {
                        fwrite(&bmpEntrada->imagenMtrzPxlR[i][j],sizeof(char),1,nuevaImagenSalida);
                        fwrite(&bmpEntrada->imagenMtrzPxlG[i][j],sizeof(char),1,nuevaImagenSalida);
                        fwrite(&bmpEntrada->imagenMtrzPxlB[i][j],sizeof(char),1,nuevaImagenSalida);

                    }
                }

                // cerrar el archivo y regresar estado
                fclose(nuevaImagenSalida);
                return nuevoContenedorSalida;
            }
            else
                return NULL;
        }


        //*************> FUNCIONES DE CARGAR Y CREACION DE IMAGENES BMP

        // lista

        contenedorBmp *     FwsVcargarImagenBmpColor          ( char * nombreRutaImagen, char * nombreImagen ){

            // intentar cargar ruta especificada
            FILE * nuevaImagenBmp = fopen( nombreRutaImagen, "rb+");
            if (  nuevaImagenBmp ){

                // crear contenedor para la nueva imagen
                contenedorBmp * nuevoContenedor = FwsVcrearContenedor();

                // leer datos extra
                nuevoContenedor->nombreRuta = nombreRutaImagen;
                nuevoContenedor->nombreImagen = nombreImagen;

                //////////nuevoContenedor->nombreCompleto = strcat(nuevoContenedor->nombreRuta,nuevoContenedor->nombreImagen);


                // leer imagen BMP
                fseek(nuevaImagenBmp,0,SEEK_SET);
                fread(&nuevoContenedor->imagenTipo, sizeof(char),2,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenDims, sizeof(int),1,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenResrv, sizeof(int),1,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenOffst, sizeof(int),1,nuevaImagenBmp);

                fread(&nuevoContenedor->imagenDmsMt, sizeof(int),1,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenAlto, sizeof(int),1,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenAncho, sizeof(int),1,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenNmPlns, sizeof(short int),1,nuevaImagenBmp);

                fread(&nuevoContenedor->imagenPrfClr, sizeof(short int),1,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenTpCmp, sizeof(int),1,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenDEstr, sizeof(int),1,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenPxMH, sizeof(int),1,nuevaImagenBmp);

                fread(&nuevoContenedor->imagenPxMV, sizeof(int),1,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenClrUs, sizeof(int),1,nuevaImagenBmp);
                fread(&nuevoContenedor->imagenClrImp, sizeof(int),1,nuevaImagenBmp);

                //if(nuevoContenedor->imagenPrfClr != 24 )
                  //  exit(1);

                // pasar de la imagen a la matriz del contenedor
                int i,j;

                // crear las 3 metrices R,G,B
                nuevoContenedor->imagenMtrzPxlR = FwsVcrearMatriz( nuevoContenedor->imagenAlto, nuevoContenedor->imagenAncho);
                nuevoContenedor->imagenMtrzPxlG = FwsVcrearMatriz( nuevoContenedor->imagenAlto, nuevoContenedor->imagenAncho);
                nuevoContenedor->imagenMtrzPxlB = FwsVcrearMatriz( nuevoContenedor->imagenAlto, nuevoContenedor->imagenAncho);


                // recolectar datos de la imagen para las matricez
                char r,g,b;
                for ( i = 0 ; i < nuevoContenedor->imagenAlto ; i ++ )
                {
                    for ( j = 0 ; j < nuevoContenedor->imagenAncho ; j ++ )
                    {
                        fread(&r,sizeof(char),1,nuevaImagenBmp);
                        fread(&g,sizeof(char),1,nuevaImagenBmp);
                        fread(&b,sizeof(char),1,nuevaImagenBmp);


                        nuevoContenedor->imagenMtrzPxlR[i][j] = r;
                        nuevoContenedor->imagenMtrzPxlG[i][j] = g;
                        nuevoContenedor->imagenMtrzPxlB[i][j] = b;
                    }
                }

                // cerrar el archivo y regresar la imagen ya cargada
                fclose(nuevaImagenBmp);
                return nuevoContenedor;
            }
            else
                return NULL;
        }


        contenedorBmp **    FwsVcargarImagenesBmpColor        ( int dims, char *nombreRuta, ... ){

            // crear un vector de contenedores vacios
            contenedorBmp * vectorContendores = (contenedorBmp*) malloc( sizeof(contenedorBmp) *dims );
            int i  ;



            // mover parametros a cada contenedor del vector
            va_list listaDatos;
            va_start(listaDatos,nombreRuta);
            char *var = va_arg(listaDatos,char*);

            for ( i= 0; i < dims; i++ ){

                strcpy(&vectorContendores[i].nombreImagen,var);
                var = va_arg(listaDatos,char*);
            }
            va_end(listaDatos);

            return vectorContendores;
        }

        contenedorBmp *     FwsVcrearImagenBmpColor           ( char * nombreImagen, char * nombreRutaImagen, int alto, int ancho ){

            // crear un nuevo contenedor
            FILE * archivoImagen = fopen(nombreRutaImagen, "w");
            contenedorBmp * nuevoContenedor = FwsVcrearContenedor();

            // asignar valores
            nuevoContenedor->imagenAlto = alto;
            nuevoContenedor->imagenAncho = ancho;
            nuevoContenedor->imagenDims = alto * ancho;

            nuevoContenedor->nombreImagen = nombreImagen;
            nuevoContenedor->nombreRuta = nombreRutaImagen;
            strcpy(nuevoContenedor->imagenTipo,"BM");

            // iniciar las matrices de color
            nuevoContenedor->imagenMtrzPxlB = FwsVcrearMatriz(alto,ancho);
            nuevoContenedor->imagenMtrzPxlG = FwsVcrearMatriz(alto,ancho);
            nuevoContenedor->imagenMtrzPxlR = FwsVcrearMatriz(alto,ancho);

            // escribir la imagen de salida
            contenedorBmp * imagenSalida = FwsVguardarImagenBmpColor(nuevoContenedor,nombreImagen,nombreRutaImagen);

            return imagenSalida;

        }

        contenedorBmp *     FwsVcrearImagenForAt              ( contenedorBmp * imagenEntrada, char * nombreRuta, char * nombreImagen ){

            // crear un nuevo contenedor vacio
            contenedorBmp * imagenNueva = FwsVcrearContenedor();

            // mover metadatos de la imagen de entrada a la imagen vacia
            imagenNueva->imagenAlto         = imagenEntrada->imagenAlto;
            imagenNueva->imagenAncho        = imagenEntrada->imagenAncho;
            imagenNueva->imagenClrImp       = imagenEntrada->imagenClrImp;
            imagenNueva->imagenClrUs        = imagenEntrada->imagenClrUs;

            imagenNueva->imagenDEstr        = imagenEntrada->imagenDEstr;
            imagenNueva->imagenDmsMt        = imagenEntrada->imagenDmsMt;
            imagenNueva->imagenNmPlns       = imagenEntrada->imagenNmPlns;
            imagenNueva->imagenOffst        = imagenEntrada->imagenOffst;

            imagenNueva->imagenPrfClr       = imagenEntrada->imagenPrfClr;
            imagenNueva->imagenPxMH         = imagenEntrada->imagenPxMH;
            imagenNueva->imagenPxMV         = imagenEntrada->imagenPxMV;
            imagenNueva->imagenResrv        = imagenEntrada->imagenResrv;

            imagenNueva->imagenTipo         = imagenEntrada->imagenTipo;
            imagenNueva->imagenTpCmp        = imagenEntrada->imagenTpCmp;
            imagenNueva->nombreRuta         = imagenEntrada->nombreRuta;
            imagenNueva->nombreImagen       = imagenEntrada->nombreImagen;




            // conectar una matriz negra con la imagen de entrada
            imagenNueva->imagenMtrzPxlR = FwsVcrearMatriz( imagenEntrada->imagenAlto, imagenEntrada->imagenAncho );
            imagenNueva->imagenMtrzPxlG = FwsVcrearMatriz( imagenEntrada->imagenAlto, imagenEntrada->imagenAncho );
            imagenNueva->imagenMtrzPxlB = FwsVcrearMatriz( imagenEntrada->imagenAlto, imagenEntrada->imagenAncho );

            return imagenNueva;

        }

        // FUNIONES DE ESCITURA DE IMAGENES BMP
