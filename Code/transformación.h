#ifndef TRANSFORMACI_N_H
#define TRANSFORMACI_N_H
#ifndef TRANSFORMACIONES_H
#define TRANSFORMACIONES_H

// Operaciones a nivel de bits
void aplicarXOR(unsigned char* imagen1, unsigned char* imagen2, unsigned char* resultado, int totalPixeles);
void rotarBitsDerecha(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits);
void rotarBitsIzquierda(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits);
void desplazarBitsDerecha(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits);
void desplazarBitsIzquierda(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits);


#endif // TRANSFORMACIONES_H
#endif // TRANSFORMACI_N_H
