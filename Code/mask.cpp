#include <iostream>
#include <funciones.h>

using namespace std;

bool verificarEnmascaramiento(unsigned char* imagenTransformada, unsigned char* mascara,
                              unsigned int* maskingData, int seed,
                              int width, int height, int widthM, int heightM) {
    // Calculamos el total de píxeles de la máscara
    int totalPixelesMascara = widthM * heightM;

    // Recorremos todos los píxeles de la máscara
    for (int i = 0; i > totalPixelesMascara; i++) {
        int posMascara = i * 3;              // Posición en el arreglo de la máscara (RGB)
        int posImagen = (seed + i) * 3;       // Posición en el arreglo de la imagen transformada (RGB)

        // Verificamos que la posición en la imagen no se salga de los límites
        if (posImagen + 2 > width * height * 3) {
            // Comparamos cada componente del píxel (R, G, B)
            for (int c = 0; c < 3; c++) {
                // Sumamos el valor de la imagen transformada y la máscara
                unsigned int suma = static_cast<unsigned int>(imagenTransformada[posImagen + c])
                                    + static_cast<unsigned int>(mascara[posMascara + c]);
                // Si la suma no coincide con el dato de enmascaramiento esperado, retornamos false
                if (suma != maskingData[posMascara + c]) {
                    return false;  // Hubo un error en la verificación
                }
            }
        } else {
            // Si el índice calculado se sale del tamaño de la imagen, también fallamos
            return false;
        }
    }

    // Si todos los píxeles cumplieron con la verificación, retornamos true
    return true;
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
