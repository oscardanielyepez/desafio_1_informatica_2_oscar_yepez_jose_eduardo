// Operaciones a nivel de bits (XOR)
void aplicarXOR(unsigned char* imagen1, unsigned char* imagen2, unsigned char* resultado, int totalPixeles) {
    for (int i = 0; i < totalPixeles * 3; i++) {
        resultado[i] = imagen1[i] ^ imagen2[i];
    }
}

// Rotación de bits a la derecha
void rotarBitsDerecha(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits) {
    for (int i = 0; i < totalPixeles * 3; i++) {
        resultado[i] = (imagen[i] >> cantidadBits) | (imagen[i] << (8 - cantidadBits));
    }
}

// Rotación de bits a la izquierda
void rotarBitsIzquierda(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits) {
    for (int i = 0; i < totalPixeles * 3; i++) {
        resultado[i] = (imagen[i] << cantidadBits) | (imagen[i] >> (8 - cantidadBits));
    }
}

// Desplazamiento de bits a la derecha
void desplazarBitsDerecha(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits) {
    for (int i = 0; i < totalPixeles * 3; i++) {
        resultado[i] = imagen[i] >> cantidadBits;
    }
}

// Desplazamiento de bits a la izquierda
void desplazarBitsIzquierda(unsigned char* imagen, unsigned char* resultado, int totalPixeles, int cantidadBits) {
    for (int i = 0; i < totalPixeles * 3; i++) {
        resultado[i] = imagen[i] << cantidadBits;
    }
}
