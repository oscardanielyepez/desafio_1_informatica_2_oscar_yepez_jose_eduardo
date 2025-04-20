#define TRANSFORMACIONES_H

// Operaciones a nivel de bits
void aplicarXOR(unsigned char* imagen1, unsigned char* imagen2, unsigned char* resultado, int totalPixeles);
void rotarBitsDerecha(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits);
void rotarBitsIzquierda(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits);
void desplazarBitsDerecha(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits);
void desplazarBitsIzquierda(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits);

//Enmascaramiento
bool verificarEnmascaramiento(unsigned char* imagenTransformada, unsigned char* mascara,
                              unsigned int* datosEnmascaramiento, int semilla,
                              int anchoImagen, int altoImagen, int anchoMascara, int altoMascara);
void aplicarEnmascaramiento(unsigned char* imagen, unsigned char* mascara,
                             unsigned int* resultado, int semilla,
                             int anchoImagen, int altoImagen, int anchoMascara, int altoMascara);

#ifndef FUNCIONES_H
#define FUNCIONES_H

// Operaciones a nivel de bits
void aplicarXOR(unsigned char* pixelData, unsigned char* mascara, unsigned char* resultado, int &numPixeles);
void rotarBitsDerecha(unsigned char* pixelData, unsigned char* resultado, int &numPixeles, int parametrosTransformaciones);
void rotarBitsIzquierda(unsigned char* pixelData, unsigned char* resultado, int &numPixeles, int parametrosTransformaciones);
void desplazarBitsDerecha(unsigned char* pixelData, unsigned char* resultado, int &numPixeles, int parametrosTransformaciones);
void desplazarBitsIzquierda(unsigned char* pixelData, unsigned char* resultado, int &numPixeles, int parametrosTransformaciones);

//Enmascaramiento
bool verificarEnmascaramiento(unsigned char* imagenTransformada, unsigned char* mascara,
                              unsigned int* maskingData, int seed,
                              int width, int height, int widthM, int heightM);
void aplicarEnmascaramiento(unsigned char* pixelData, unsigned char* mascara,
                            unsigned int* resultado, int seed,
                            int width, int height, int widthM, int heightM);

//Identificacion de transformaciones
bool identificarTransformaciones(
    unsigned char* imagenTransformada,
    unsigned char* imagenDistorsion,
    unsigned char* mascara,
    unsigned int** maskingData,
    int* seed,
    int numArchivos,
    int width, int height,
    int widthM, int heightM,
    int* tiposTransformaciones,
    int* parametrosTransformaciones);

//Reconstrucción de la imagen original
void reconstruirImagenOriginal(
    unsigned char* imagenTransformada,
    unsigned char* imagenDistorsion,
    unsigned char* archivoEntrada,
    int* tiposTransformaciones,
    int* parametrosTransformaciones,
    int numTransformaciones,
    int totalPixeles);

#endif // FUNCIONES_H
