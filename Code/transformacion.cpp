#include <iostream>
#include <funciones.h>

using namespace std;

// Función para identificar las transformaciones aplicadas a la imagen
bool identificarTransformaciones(
    unsigned char* imagenTransformada,
    unsigned char* imagenDistorsion,
    unsigned char* mascara,
    unsigned int** maskingData,  // Array de punteros a datos de enmascaramiento
    int* seed,                        // Array de semillas
    int numArchivos,                      // Número de archivos de enmascaramiento
    int width, int height,
    int widthM, int heightM,
    int* tiposTransformaciones,           // Array donde se guardarán los tipos de transformación identificados
    int* parametrosTransformaciones)      // Array donde se guardarán los parámetros (ej: cantidad de bits)
{
    // Crear buffer temporal para almacenar resultados intermedios
    int numPixeles = width * height;
    unsigned char* imagenTemporal = new unsigned char[numPixeles * 3];
    unsigned char* resultado = new unsigned char[numPixeles * 3];

    // Intentar identificar cada transformación en orden inverso
    for (int paso = numArchivos - 1; paso >= 0; paso--) {
        bool transformacionIdentificada = false;

        // Probar XOR con la imagen de distorsión
        aplicarXOR(imagenTransformada, imagenDistorsion, resultado, numPixeles);
        if (verificarEnmascaramiento(resultado, mascara, maskingData[paso],
                                     seed[paso], width, height, widthM, heightM)) {
            // Encontramos la transformación correcta
            tiposTransformaciones[paso] = 1; // 1 = XOR
            parametrosTransformaciones[paso] = 0;
            transformacionIdentificada = true;
        }

        // Probar rotaciones de bits - Con esta evitamos una confusion.
        // Probar desplazamiento de bits
        if (!transformacionIdentificada) {
            for (int bits = 1; bits <= 7; bits++) {
                // Probar rotación a la izquierda
                rotarBitsIzquierda(imagenTransformada, resultado, numPixeles, bits);
                if (verificarEnmascaramiento(resultado, mascara, maskingData[paso],
                                             seed[paso], width, height, widthM, heightM)) {
                    tiposTransformaciones[paso] = 2; // 2 = Rotación izquierda
                    parametrosTransformaciones[paso] = bits;
                    transformacionIdentificada = true;
                    break;
                }
                // Probar rotación a la derecha
                rotarBitsDerecha(imagenTransformada, resultado, numPixeles, bits);
                if (verificarEnmascaramiento(resultado, mascara, maskingData[paso],
                                             seed[paso], width, height, widthM, heightM)) {
                    tiposTransformaciones[paso] = 3; // 3 = Rotación derecha
                    parametrosTransformaciones[paso] = bits;
                    transformacionIdentificada = true;
                    break;
                }
            }
        }

        // Si no fue XOR, probar rotación de bits (varios valores)
        if (!transformacionIdentificada) {
            for (int bits = 1; bits <= 7; bits++) {
                // Probar desplazamiento a la derecha
                desplazarBitsDerecha(imagenTransformada, resultado, numPixeles, bits);
                if (verificarEnmascaramiento(resultado, mascara, maskingData[paso],
                                             seed[paso], width, height, widthM, heightM)) {
                    tiposTransformaciones[paso] = 4; // 4 = Desplazamiento derecha
                    parametrosTransformaciones[paso] = bits;
                    transformacionIdentificada = true;
                    break;
                }

                // Probar desplazamiento a la izquierda
                desplazarBitsIzquierda(imagenTransformada, resultado, numPixeles, bits);
                if (verificarEnmascaramiento(resultado, mascara, maskingData[paso],
                                             seed[paso], width, height, widthM, heightM)) {
                    tiposTransformaciones[paso] = 5; // 5 = Desplazamiento izquierda
                    parametrosTransformaciones[paso] = bits;
                    transformacionIdentificada = true;
                    break;
                }
            }
        }

        // Si no se identificó ninguna transformación, fallar
        if (!transformacionIdentificada) {
            delete[] imagenTemporal;
            delete[] resultado;
            return false;
        }

        // Actualizar la imagen transformada para el siguiente paso (considerando que vamos en orden inverso)
        if (paso > 0) {
            // Guarda el resultado de esta transformación
            memcpy(imagenTemporal, resultado, numPixeles * 3);
            // Usa este resultado como entrada para identificar la siguiente transformación
            memcpy(imagenTransformada, imagenTemporal, numPixeles * 3);
        }
    }

    delete[] imagenTemporal;
    delete[] resultado;
    return true;
}

// Función para reconstruir la imagen original aplicando las transformaciones inversas
void reconstruirImagenOriginal(
    unsigned char* imagenTransformada,
    unsigned char* imagenDistorsion,
    unsigned char* imagenOriginal,
    int* tiposTransformaciones,
    int* parametrosTransformaciones,
    int numTransformaciones,
    int numPixeles)
{
    // Buffer temporal para resultados intermedios
    unsigned char* imagenTemporal = new unsigned char[numPixeles * 3];

    // Copiar la imagen transformada al inicio
    memcpy(imagenTemporal, imagenTransformada, numPixeles * 3);

    // Aplicar las transformaciones inversas en orden inverso
    for (int i = numTransformaciones - 1; i >= 0; i--) {
        switch (tiposTransformaciones[i]) {
        case 1: // XOR (su inverso es XOR con la misma imagen)
            aplicarXOR(imagenTemporal, imagenDistorsion, imagenTemporal, numPixeles);
            break;

        case 2: // Rotación derecha (su inverso es rotación izquierda)
            rotarBitsIzquierda(imagenTemporal, imagenTemporal, numPixeles, parametrosTransformaciones[i]);
            break;

        case 3: // Rotación izquierda (su inverso es rotación derecha)
            rotarBitsDerecha(imagenTemporal, imagenTemporal, numPixeles, parametrosTransformaciones[i]);
            break;

        case 4: // Desplazamiento derecha
            desplazarBitsIzquierda(imagenTemporal, imagenTemporal, numPixeles, parametrosTransformaciones[i]);
            break;

        case 5: // Desplazamiento izquierda
            desplazarBitsDerecha(imagenTemporal, imagenTemporal, numPixeles, parametrosTransformaciones[i]);
            break;
        }
    }

    // Copiar el resultado final a la imagen original
    memcpy(imagenOriginal, imagenTemporal, numPixeles * 3);

    // Liberar memoria
    delete[] imagenTemporal;
}
