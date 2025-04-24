#include <iostream>
#include <QImage>

using namespace std;

void SumarMascara() {
    // Operaciones para sumar la mascara.
}

void AplicandoDesplazamiento(unsigned char *pixelDataIMG, float tipoDesplazamiento) {

    if (tipoDesplazamiento == true)
    {
        // operaciones a nivel bit a pixelDataIMG, a la derecha.
    }
    else if(tipoDesplazamiento == false)
    {
        // operaciones a nivel bit a pixelDataIMG, a la izquierda.
    }
    else {
        // Si entramos aca debe haber un error al momento de analizar con los txt, que tipo de rotación se efectuo.
    }

    //resultado_operaciones = SumarMascara()
}

void AplicandoRotacion() {
    // Opereaciones de rotación.
    // resultado_operaciones = SumarMascara()
}

void AplicandoXOR() {
    // Operaciones del XOR.
    // resultado_operaciones = SumarMascara()
}


// Definimos funciones que nos ayuden a encontrar las transformaciones realizadas sobre los respectivos, archivos .txt, 

// Esta función intenta descubrir qué operación lógica fue usada para transformar un valor 'original'
// (que resulta de imagenTransformada + máscara) al valor enmascarado del archivo .txt.
// Prueba combinaciones XOR, rotaciones y desplazamientos.
// Si encuentra una coincidencia, devuelve el tipo de operación y el parámetro asociado.
int identificarTransformacionPixel(unsigned int original, unsigned int enmascarado, int &parametroOut)
{
    // Prueba XOR con todos los valores posibles
    for (int k = 0; k < 256; ++k)
    {
        if ((original ^ k) == enmascarado)
        {
            parametroOut = k;
            return 1; // Operación XOR detectada
        }
    }
    // Prueba rotaciones a la derecha de 1 a 7 bits
    for (int b = 1; b < 8; ++b)
    {
        unsigned int rot = (original >> b) | (original << (8 - b));
        if ((rot & 0xFF) == (enmascarado & 0xFF))
        {
            parametroOut = b;
            return 2; // Rotación a la derecha detectada
        }
    }
    // Prueba rotaciones a la izquierda de 1 a 7 bits
    for (int b = 1; b < 8; ++b)
    {
        unsigned int rot = (original << b) | (original >> (8 - b));
        if ((rot & 0xFF) == (enmascarado & 0xFF))
        {
            parametroOut = b;
            return 3; // Rotación a la izquierda detectada
        }
    }
    // Prueba desplazamientos lógicos a la derecha
    for (int b = 1; b < 8; ++b)
    {
        if (((original >> b) & 0xFF) == (enmascarado & 0xFF))
        {
            parametroOut = b;
            return 4; // Desplazamiento a la derecha detectado
        }
    }
    // Prueba desplazamientos lógicos a la izquierda
    for (int b = 1; b < 8; ++b)
    {
        if (((original << b) & 0xFF) == (enmascarado & 0xFF))
        {
            parametroOut = b;
            return 5; // Desplazamiento a la izquierda detectado
        }
    }
    return 0; // No se encontró coincidencia
}

// Esta función compara los datos enmascarados (provenientes de archivos Mx.txt) con la imagen transformada
// y la máscara. Evalúa para cada píxel si hay una transformación lógica que convierte
// imagenTransformada[pos + seed] + mascara[pos] → maskingData[pos].
// Si identifica el patrón correcto, lo guarda en los arreglos de tipo y parámetro.
bool identificarTransformaciones(
    unsigned char *imagenTransformada,
    unsigned char *imagenDistorsionada, // no se usa directamente aquí
    unsigned char *mascara,
    unsigned int **maskingData,
    int *seed,
    int numArchivos,
    int width, int height,
    int widthM, int heightM,
    int *tiposTransformaciones,
    int *parametrosTransformaciones)
{
    for (int idx = 0; idx < numArchivos; ++idx)
    {
        int offset = seed[idx];
        int numPixeles = widthM * heightM;
        int coincidencias[6] = {0}; // contador de coincidencias por cada tipo de transformación (1-5)
        int parametros[6] = {0};    // último parámetro válido encontrado por tipo

        // Recorremos todos los píxeles definidos en la máscara y el archivo Mx.txt
        for (int i = 0; i < numPixeles; ++i)
        {
            int pos = offset + i; // posición desplazada por la semilla

            // Validación para evitar desbordamientos de memoria
            if (pos * 3 + 2 >= width * height * 3)
                continue;

            // Para cada canal R, G, B
            for (int c = 0; c < 3; ++c)
            {
                // Suma: imagen transformada + máscara
                unsigned int original = imagenTransformada[pos * 3 + c] + mascara[i * 3 + c];
                unsigned int enmascarado = maskingData[idx][i * 3 + c];

                int param = 0;
                // Identifica la transformación que genera el valor enmascarado
                int tipo = identificarTransformacionPixel(original & 0xFF, enmascarado & 0xFF, param);
                if (tipo > 0)
                {
                    coincidencias[tipo]++;
                    parametros[tipo] = param;
                }
            }
        }

        // Seleccionamos la transformación con mayor número de coincidencias
        int mejorTipo = 0;
        int maxCoinc = 0;
        for (int t = 1; t <= 5; ++t)
        {
            if (coincidencias[t] > maxCoinc)
            {
                maxCoinc = coincidencias[t];
                mejorTipo = t;
            }
        }

        // Si no se detectó una transformación clara, se retorna false
        if (mejorTipo == 0)
            return false;

        // Guardamos el tipo y el parámetro correspondiente a esta transformación
        tiposTransformaciones[idx] = mejorTipo;
        parametrosTransformaciones[idx] = parametros[mejorTipo];
    }

    return true; // Transformaciones identificadas correctamente
}
