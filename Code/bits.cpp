#include <iostream>

using namespace std;

// Operaciones a nivel de bits (XOR)
void aplicarXOR(unsigned char* pixelData, unsigned char* mascara, unsigned char* resultado, int &numPixeles) {
    for (int i = 0; i < numPixeles * 3; i++) {
        resultado[i] = pixelData[i] ^ mascara[i];
    }
}

// Rotación de bits a la derecha
void rotarBitsDerecha(unsigned char* pixelData, unsigned char* resultado, int &numPixeles, int parametrosTransformaciones) {
    for (int i = 0; i < numPixeles * 3; i++) {
        resultado[i] = (pixelData[i] >> parametrosTransformaciones) | (pixelData[i] << (8 - parametrosTransformaciones));
    }
}

// Rotación de bits a la izquierda
void rotarBitsIzquierda(unsigned char* pixelData, unsigned char* resultado, int &numPixeles, int parametrosTransformaciones) {
    for (int i = 0; i < numPixeles * 3; i++) {
        resultado[i] = (pixelData[i] << parametrosTransformaciones) | (pixelData[i] >> (8 - parametrosTransformaciones));
    }
}

// Desplazamiento de bits a la derecha
void desplazarBitsDerecha(unsigned char* pixelData, unsigned char* resultado, int &numPixeles, int parametrosTransformaciones) {
    for (int i = 0; i < numPixeles * 3; i++) {
        resultado[i] = pixelData[i] >> parametrosTransformaciones;
    }
}

// Desplazamiento de bits a la izquierda
void desplazarBitsIzquierda(unsigned char* pixelData, unsigned char* resultado, int &numPixeles, int parametrosTransformaciones) {
    for (int i = 0; i < numPixeles * 3; i++) {
        resultado[i] = pixelData[i] << parametrosTransformaciones;
    }
}
