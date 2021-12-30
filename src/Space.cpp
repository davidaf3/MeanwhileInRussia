#include "Space.h"

Space::Space(float gravity) {
    this->gravity = gravity;
    dynamicActors.clear();
    staticActors.clear();
}

void Space::update() {
    for (auto const& actor : dynamicActors) {
        // máxima velocidad de caída por gravedad
        if (actor->gravity() && actor->vy < 35) {
            actor->vy = actor->vy + gravity;
        }

        // Aun no se han detectado choques
        actor->collisionTop = false;
        actor->collisionDown = false;
        actor->collisionRight = false;
        actor->collisionLeft = false;
        actor->outLeft = true;
        actor->outRight = true;

        // MoverDerecha / izquierda
        if (actor->vx > 0) updateMoveRight(actor, actor->vx, true);
        if (actor->vx < 0) updateMoveLeft(actor, actor->vx, true);

        // Mover Arriba / Abajo
        if (actor->vy > 0) updateMoveDown(actor, actor->vy, true);
        if (actor->vy < 0) updateMoveTop(actor, actor->vy, true);
    }
}

void Space::updateMoveRight(Actor* dynamicAct, float vx, bool restrict) {
    float possibleMovement = vx;
    // El mejor "idealmente" vx partimos de ese

    for (auto const& staticAct : staticActors) {
        if (dynamicAct != staticAct) {
            float rightDynamic = dynamicAct->x + dynamicAct->width / 2;
            float topDynamic = dynamicAct->y - dynamicAct->height / 2;
            float downDynamic = dynamicAct->y + dynamicAct->height / 2;

            float leftStatic = staticAct->x - staticAct->width / 2;
            float topStatic = staticAct->y - staticAct->height / 2;
            float downStatic = staticAct->y + staticAct->height / 2;

            // Alerta!, Elemento estático en la trayectoria.
            if ((rightDynamic + vx) >= leftStatic
                && rightDynamic <= leftStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {

                // Comprobamos si la distancia al estático es menor
                // que nuestro movimientoPosible actual
                if (possibleMovement >= leftStatic - rightDynamic) {
                    dynamicAct->collisionRight = true;
                    // La distancia es MENOR que nuestro movimiento posible
                    // Tenemos que actualizar el movimiento posible a uno menor
                    possibleMovement = leftStatic - rightDynamic;
                }
            }
        }
    }
    // Ya se han comprobado todos los estáticos
    dynamicAct->x = dynamicAct->x + possibleMovement;
    // Restringir la velocidad actual (opcional)
    if (restrict) dynamicAct->vx = possibleMovement;
}

void Space::updateMoveLeft(Actor* dynamicAct, float vx, bool restrict) {
    float possibleMovement = vx;
    // El mejor "idealmente" vx partimos de ese

    for (auto const& staticAct : staticActors) {
        if (dynamicAct != staticAct) {
            float leftDynamic = dynamicAct->x - dynamicAct->width / 2;
            float topDynamic = dynamicAct->y - dynamicAct->height / 2;
            float downDynamic = dynamicAct->y + dynamicAct->height / 2;

            float rightStatic = staticAct->x + staticAct->width / 2;
            float topStatic = staticAct->y - staticAct->height / 2;
            float downStatic = staticAct->y + staticAct->height / 2;

            // Alerta!, Elemento estático en la trayectoria.
            if ((leftDynamic + vx) <= rightStatic
                && leftDynamic >= rightStatic
                && topStatic < downDynamic
                && downStatic > topDynamic) {

                // Comprobamos si la distancia al estático es menor
                // que nuestro movimientoPosible actual
                if (possibleMovement <= rightStatic - leftDynamic) {
                    dynamicAct->collisionLeft = true;
                    // La distancia es MENOR que nuestro movimiento posible
                    // Tenemos que actualizar el movimiento posible a uno menor
                    possibleMovement = rightStatic - leftDynamic;
                }

            }
        }
    }

    // Ya se han comprobado todos los estáticos
    dynamicAct->x = dynamicAct->x + possibleMovement;
    // Restringir la velocidad actual (opcional)
    if (restrict) dynamicAct->vx = possibleMovement;
}

void Space::updateMoveDown(Actor* dynamicAct, float vy, bool restrict) {
    float possibleMovement = vy;
    // El mejor "idealmente" vy partimos de ese

    for (auto const& staticAct : staticActors) {
        if (dynamicAct != staticAct) {
            float topDynamic = dynamicAct->y - dynamicAct->height / 2;
            float downDynamic = dynamicAct->y + dynamicAct->height / 2;
            float rightDynamic = dynamicAct->x + dynamicAct->width / 2;
            float leftDynamic = dynamicAct->x - dynamicAct->width / 2;

            float topStatic = staticAct->y - staticAct->height / 2;
            float downStatic = staticAct->y + staticAct->height / 2;
            float rightStatic = staticAct->x + staticAct->width / 2;
            float leftStatic = staticAct->x - staticAct->width / 2;

            // Alerta!, Elemento estático en la trayectoria.
            if ((downDynamic + vy) >= topStatic
                && topDynamic < downStatic
                && leftDynamic < rightStatic
                && rightDynamic > leftStatic) {

                // Comprobamos si la distancia al estático es menor
                // que nuestro movimientoPosible actual
                if (possibleMovement >= topStatic - downDynamic) {
                    // La distancia es MENOR que nuestro movimiento posible
                    // Tenemos que actualizar el movimiento posible a uno menor
                    possibleMovement = topStatic - downDynamic;

                    dynamicAct->collisionDown = true;

                    if (rightDynamic <= rightStatic) {
                        dynamicAct->outRight = false;
                    }
                    if (leftDynamic >= leftStatic) {
                        dynamicAct->outLeft = false;
                    }
                }
            }
        }
    }

    // Ya se han comprobado todos los estáticos
    dynamicAct->y = dynamicAct->y + possibleMovement;
    // Restringir la velocidad actual (opcional)
    if (restrict) dynamicAct->vy = possibleMovement;
}

void Space::updateMoveTop(Actor* dynamicAct, float vy, bool restrict) {
    float possibleMovement = vy;
    // El mejor "idealmente" vy partimos de ese

    for (auto const& staticAct : staticActors) {
        if (dynamicAct != staticAct) {
            float topDynamic = dynamicAct->y - dynamicAct->height / 2;
            float downDynamic = dynamicAct->y + dynamicAct->height / 2;
            float rightDynamic = dynamicAct->x + dynamicAct->width / 2;
            float leftDynamic = dynamicAct->x - dynamicAct->width / 2;

            float topStatic = staticAct->y - staticAct->height / 2;
            float downStatic = staticAct->y + staticAct->height / 2;
            float rightStatic = staticAct->x + staticAct->width / 2;
            float leftStatic = staticAct->x - staticAct->width / 2;

            // Alerta!, Elemento estático en la trayectoria.
            if ((topDynamic + vy) <= downStatic
                && downDynamic > topStatic
                && leftDynamic < rightStatic
                && rightDynamic > leftStatic) {

                // Comprobamos si la distancia al estático es menor
                // que nuestro movimientoPosible actual
                if (possibleMovement <= downStatic - topDynamic) {
                    dynamicAct->collisionTop = true;
                    // La distancia es MENOR que nuestro movimiento posible
                    // Tenemos que actualizar el movimiento posible a uno menor
                    possibleMovement = downStatic - topDynamic;
                }
            }
        }
    }
    // Ya se han comprobado todos los estáticos
    dynamicAct->y = dynamicAct->y + possibleMovement;
    // Restringir la velocidad actual (opcional)
    if (restrict) dynamicAct->vy = possibleMovement;
}

void Space::addDynamicActor(Actor* actor) {
    dynamicActors.push_back(actor);
}

void Space::addStaticActor(Actor* actor) {
    staticActors.push_back(actor);
}

void Space::removeDynamicActor(Actor* actor) {
    dynamicActors.remove(actor);
}

void Space::removeStaticActor(Actor* actor) {
    staticActors.remove(actor);
}

bool Space::isRectFree(float x, float y, float width, float height) {
    for (auto const& actor : staticActors)
        if (actor->isOverlap(x, y, width, height)) return false;
    return true;
}

// this function gives the maximum
float maxi(float arr[], int n) {
    float m = 0;
    for (int i = 0; i < n; ++i)
        if (m < arr[i])
            m = arr[i];
    return m;
}

// this function gives the minimum
float mini(float arr[], int n) {
    float m = 1;
    for (int i = 0; i < n; ++i)
        if (m > arr[i])
            m = arr[i];
    return m;
}

// Algoritmo de Liang–Barsky
bool segmentIntersectsRect(float x1, float y1, float x2, float y2, float xmin, float ymin, float xmax, float ymax) {
    // defining variables
    float p1 = -(x2 - x1);
    float p2 = -p1;
    float p3 = -(y2 - y1);
    float p4 = -p3;

    float q1 = x1 - xmin;
    float q2 = xmax - x1;
    float q3 = y1 - ymin;
    float q4 = ymax - y1;

    float posarr[5], negarr[5];
    int posind = 1, negind = 1;
    posarr[0] = 1;
    negarr[0] = 0;

    if ((p1 == 0 && q1 < 0) || (p2 == 0 && q2 < 0) || (p3 == 0 && q3 < 0) || (p4 == 0 && q4 < 0))
        return false;

    if (p1 != 0) {
        float r1 = q1 / p1;
        float r2 = q2 / p2;
        if (p1 < 0) {
            negarr[negind++] = r1; // for negative p1, add it to negative array
            posarr[posind++] = r2; // and add p2 to positive array
        }
        else {
            negarr[negind++] = r2;
            posarr[posind++] = r1;
        }
    }

    if (p3 != 0) {
        float r3 = q3 / p3;
        float r4 = q4 / p4;
        if (p3 < 0) {
            negarr[negind++] = r3;
            posarr[posind++] = r4;
        }
        else {
            negarr[negind++] = r4;
            posarr[posind++] = r3;
        }
    }

    float xn1, yn1, xn2, yn2;
    float rn1, rn2;
    rn1 = maxi(negarr, negind); // maximum of negative array
    rn2 = mini(posarr, posind); // minimum of positive array

    if (rn1 > rn2) return false;

    xn1 = x1 + p2 * rn1;
    yn1 = y1 + p4 * rn1; // computing new points

    xn2 = x1 + p2 * rn2;
    yn2 = y1 + p4 * rn2;

    return true;
}

bool Space::isSegmentFree(float x1, float y1, float x2, float y2) {
    for (auto const& actor : staticActors) {
        float xmin = actor->x - actor->width / 2;
        float xmax = actor->x + actor->width / 2;
        float ymin = actor->y - actor->height / 2;
        float ymax = actor->y + actor->height / 2;
        if (segmentIntersectsRect(x1, y1, x2, y2, xmin, ymin, xmax, ymax)) return false;
    }
    return true;
}
