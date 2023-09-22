#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Métodos constructores -----------------------------------

// Métodos públicos ----------------------------------------

/**
 * Método para pintar los ejes coordenados llamando a funciones de OpenGL
 */
void igvEscena3D::pintar_ejes() {
    GLfloat rojo[] = {1, 0, 0, 1.0};
    GLfloat verde[] = {0, 1, 0, 1.0};
    GLfloat azul[] = {0, 0, 1, 1.0};

    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
    glVertex3f(1000, 0, 0);
    glVertex3f(-1000, 0, 0);

    glMaterialfv(GL_FRONT, GL_EMISSION, verde);
    glVertex3f(0, 1000, 0);
    glVertex3f(0, -1000, 0);

    glMaterialfv(GL_FRONT, GL_EMISSION, azul);
    glVertex3f(0, 0, 1000);
    glVertex3f(0, 0, -1000);
    glEnd();
}

/**
 * Método con las llamadas OpenGL para visualizar la escena
 * @param escena Identificador del tipo de escena a dibujar
 * @pre Se asume que el valor del parámetro es correcto
 */
void igvEscena3D::visualizar(int escena) {  // borra la ventana y el Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Luces
    GLfloat light0[] = {10, 8, 9, 1}; // point light source
    glLightfv(GL_LIGHT0, GL_POSITION, light0);
    glEnable(GL_LIGHT0);

    glPushMatrix(); // guarda la matriz de modelado

    // se pintan los ejes
    if (ejes) {
        pintar_ejes();
    }

    // Escena seleccionada a través del menú (clic botón derecho)
    if (escena == EscenaA) {
        renderEscenaA();
    } else {
        if (escena == EscenaB) {
            renderEscenaB(3);
        } else {
            if (escena == EscenaC) {
                renderEscenaC();
            }
        }
    }

    glPopMatrix(); // restaura la matriz de modelado
    glutSwapBuffers(); // se utiliza, en vez de glFlush(), para evitar el parpadeo
}

/**
 * Pinta la escena A llamando a las funciones de OpenGL
 */

void igvEscena3D::renderEscenaA() {

    GLfloat color_caja[] = {0, 0.25, 0};

    glMaterialfv(GL_FRONT, GL_EMISSION, color_caja);

    glPushMatrix();
    glScalef(1.0, 1.0, 2.0);  // Escala el cubo en el eje Z para que tenga el doble de profundidad.
    glutSolidCube(1);
    glPopMatrix();

    GLfloat color_tapa[] = {0, 0.30, 0};

    glMaterialfv(GL_FRONT, GL_EMISSION, color_tapa);

    glPushMatrix();
    glScalef(1.15, 0.25, 2.15);  // Escala la tapa para que sea un poco mas grande pero de menor altura
    glTranslatef(0, 2, 0);       // Traslada la tapa hacia arriba
    glutSolidCube(1);
    glPopMatrix();
}

/**
 * Pinta la escena B llamando a las funciones de OpenGL
 */
void igvEscena3D::renderEscenaB(int num) {

    setNumInstancias(num);
    int altura_caja = 1;

    for (int i = 0; i < numInstancias; i++) {
        glPushMatrix();
        // Traslada la caja en el eje Y según la instancia actual
        glTranslatef(0, i * altura_caja, 0);
        renderEscenaA(); // Dibuja una instancia de la escena A
        glPopMatrix();
    }
}

/**
 * Pinta la escena C llamando a las funciones de OpenGL
 */
void igvEscena3D::renderEscenaC() {

    for (int i = 0; i < numInstanciasX; i++) {
        for (int j = 0; j < numInstanciasZ; j++) {
            for (int k = 0; k < numInstanciasY; k++) {
                glPushMatrix();
                glTranslatef(i * 1.5, k * 1.1, j * 2.5);
                renderEscenaA();
                glPopMatrix();
            }
        }
    }
}


/**
 * Método para consultar si hay que dibujar los ejes o no
 * @retval true Si hay que dibujar los ejes
 * @retval false Si no hay que dibujar los ejes
 */
bool igvEscena3D::get_ejes() {
    return ejes;
}

/**
 * Método para activar o desactivar el dibujado de los ejes
 * @param _ejes Indica si hay que dibujar los ejes (true) o no (false)
 * @post El estado del objeto cambia en lo que respecta al dibujado de ejes,
 *       de acuerdo al valor pasado como parámetro
 */
void igvEscena3D::set_ejes(bool _ejes) {
    ejes = _ejes;
}