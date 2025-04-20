#include <iostream>
#include <funciones.h>

using namespace std;

// Verifica si los datos de enmascaramiento coinciden con el resultado de aplicar la máscara a la imagen
bool verificarEnmascaramiento(unsigned char* imagenTransformada, unsigned char* mascara,
                              unsigned int* maskingData, int seed,
                              int width, int height, int widthM, int heightM) {

    // Número total de píxeles en la máscara
    int totalPixelesMascara = widthM * heightM;

    // Para cada píxel en la máscara, verificar si la suma coincide
    for (int i = 0; i < totalPixelesMascara; i++) {
        // Calcular posición lineal en la imagen considerando los 3 canales RGB
        int posMascara = i * 3;
        int posImagen = (seed + i) * 3;

        // Comprobar que la posición en la imagen es válida
        if (posImagen + 2 < width * height * 3) {
            // Verificar cada canal RGB
            for (int c = 0; c < 3; c++) {
                int suma = imagenTransformada[posImagen + c] + mascara[posMascara + c];

                // Si la suma calculada no coincide con los datos del archivo
                if (suma != maskingData[posMascara + c]) {
                    return false;  // Encontramos una discrepancia
                }
            }
        } else {
            return false;  // Fuera de límites de la imagen
        }
    }

    return true;  // Todas las sumas coinciden
}

// Aplica el enmascaramiento y almacena los resultados
void aplicarEnmascaramiento(unsigned char* pixelData, unsigned char* mascara,
                            unsigned int* resultado, int seed,
                            int width, int height, int widthM, int heightM) {

    // Número total de píxeles en la máscara
    int totalPixelesMascara = widthM * heightM;

    // Para cada píxel en la máscara, calcular la suma
    for (int i = 0; i < totalPixelesMascara; i++) {
        int posMascara = i * 3;
        int posImagen = (seed + i) * 3;

        // Verificar que la posición en la imagen es válida
        if (posImagen + 2 < width * height * 3) {
            // Calcular la suma para cada canal RGB
            for (int c = 0; c < 3; c++) {
                resultado[posMascara + c] = pixelData[posImagen + c] + mascara[posMascara + c];
            }
        }
    }
}
