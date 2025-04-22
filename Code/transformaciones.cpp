#include <iostream>

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
