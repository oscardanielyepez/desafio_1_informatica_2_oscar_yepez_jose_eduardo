#ifndef TRANSFORMACIONES_H
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

#endif // TRANSFORMACIONES_H
