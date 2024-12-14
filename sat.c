#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <GL/glut.h>
#include "agbinary.h"
#include "parameters.h"

// Store fitness for each generation
int fit[GEN_MAX][POP_MAX];
int bestFit[GEN_MAX];
float avgFit[GEN_MAX];
int currentGen = 0;
bool solutionFound = false;

bool fitnessPop(bool **pop);
int calcularFunc(bool *vet);
bool funcao_cls(bool *b, int n);

void initOpenGL(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int width, int height);
void idle(void);

bool **population;  // Global population to access in display function

int main(int argc, char **argv){
    // Initialize OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Genetic Algorithm Fitness Visualization");

    // Register GLUT callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    // Initialize OpenGL settings
    initOpenGL();

    srand(time(NULL)); // Set random seed
    population = createPop(POP_MAX, NUM_VAR); // Generate population

    // // Initialize fit array with -1 to indicate uncomputed generations
    // for(int i = 0; i < GEN_MAX; i++) {
    //     avgFit[i] = -1;
    //     bestFit[i] = -1;
    //     for(int j = 0; j < POP_MAX; j++) {
    //         fit[i][j] = -1;
    //     }
    // }

    // Start the GLUT event processing loop
    glutMainLoop();

    return 0;
}

bool fitnessPop(bool **pop){
    int bestindex = 0;
    float totalFit = 0;

    // printf("%d° Geração\n", currentGen); Debug
    // printf("Fit: "); Debug
    
    for(int i = 0; i < POP_MAX; i++){
        fit[currentGen][i] = calcularFunc(pop[i]);
        // printf("%d ", fit[currentGen][i]); Debug

        // Compute total fitness and average
        totalFit += fit[currentGen][i];
        avgFit[currentGen] = totalFit / POP_MAX;

        if(fit[currentGen][i] == NUM_CLS){
            bestFit[currentGen] = fit[currentGen][i];

            for(int j = 0; j < NUM_VAR; j++)
                printf("x%d = %d\n", j + 1, pop[i][j]);
                
            return true;
        }

        if(fit[currentGen][i] >= bestFit[currentGen]){
            bestFit[currentGen] = fit[currentGen][i];
            bestindex = i;
        }
    }

    if(currentGen > 3 && avgFit[currentGen] < avgFit[currentGen - 3] - 5){
            genocide(pop, bestindex);
    }

    // printf("\nMelhor indivíduo: %d\n", bestFit[currentGen]); Debug
    // printf("Fitness médio: %.2f\n", avgFit[currentGen]); Debug

    // Elitism
    for(int i = 0; i < POP_MAX; i++){
        if(i == bestindex)
            continue;

        singlePoint_crossover(pop[bestindex], pop[i]);
        // twoPoint_crossover(pop[bestindex], pop[i]);
        multiple_mutation(pop[i], 0.1);
    }

    return false;
}

int calcularFunc(bool *vet){
    int fit = 0, k = 0;
    bool b[TERM_MAX] = {false};

    // O loop lê as strings no formato "x1 0 x2 1 x3 0"
    for(int i = 0; i < NUM_CLS; i++){ // Lê todas as cláusulas
        char tempStr[strlen(operacoes_t[i]) + 1];
        strcpy(tempStr, operacoes_t[i]);
        char *token = strtok(tempStr, " "); // Separa a string em tokens por " "

        while (token != NULL){
            int indice = atoi(token + 1) - 1;
            token = strtok(NULL, " "); // Recupera o valor booleano (0/1);

            if(token[0] == '0')
                b[k] = !vet[indice];
            else
                b[k] = vet[indice];

            k++;

            token = strtok(NULL, " "); // Pega o próximo x
        }

        if(funcao_cls(b, k)) fit++;
        k = 0;
    }

    return fit;
}

// Function to test clause function
bool funcao_cls(bool *b, int n){
    bool res = 0;
    for(int i = 0; i < n; i++){
        res = res || b[i];
    }
    return res;
}

void initOpenGL(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GEN_MAX - 1, 0.0, NUM_CLS);  // Set coordinate system
}

void renderBitmapString(float x, float y, void *font, char *string) {
    glRasterPos2f(x, y);
    for (char *c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void drawGridLines() {
    glLineStipple(1, 0x5555);  // Dashed lines
    glEnable(GL_LINE_STIPPLE);

    // Horizontal grid lines
    for (float i = 0; i <= NUM_CLS; i += (NUM_CLS > 5) ? NUM_CLS / 5 : 1) {
        glColor3f(0.3, 0.3, 0.3);
        glBegin(GL_LINES);
        glVertex2f(0, i);
        glVertex2f(GEN_MAX, i);
        glEnd();

        char line[20];
        snprintf(line, sizeof(line), "%.2f", i);
        glColor3f(1.0, 1.0, 1.0);
        renderBitmapString(0.01, i + 0.01, GLUT_BITMAP_HELVETICA_12, line);
    }

    glDisable(GL_LINE_STIPPLE);
}

void drawAxes() {
    glColor3f(1.0, 1.0, 1.0);  // Cor branca para eixos
    
    // Eixo X
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(GEN_MAX, 0);
    glEnd();

    // Eixo Y
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, NUM_CLS);
    glEnd();
}

void displayStatistics() {
    char statsText[200];
    glColor3f(1.0, 1.0, 1.0);  // Texto branco

    // Texto de estatísticas no canto superior direito
    sprintf(statsText, "Generation: %d", currentGen);
    renderBitmapString(GEN_MAX * 0.8, NUM_CLS * 0.2, GLUT_BITMAP_HELVETICA_12, statsText);

    sprintf(statsText, "Best Fitness: %d", bestFit[currentGen - 1]);
    renderBitmapString(GEN_MAX * 0.8, NUM_CLS * 0.15, GLUT_BITMAP_HELVETICA_12, statsText);

    sprintf(statsText, "Average Fitness: %.2f", avgFit[currentGen - 1]);
    renderBitmapString(GEN_MAX * 0.8, NUM_CLS * 0.1, GLUT_BITMAP_HELVETICA_12, statsText);
}

void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GEN_MAX - 1, 0.0, NUM_CLS);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Left side: Best Fitness Graph
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GEN_MAX - 1, 0.0, NUM_CLS);

    drawGridLines();
    drawAxes();

    // Draw best fitness graph
    glColor3f(0.0, 1.0, 0.0);  // Green color for best fitness
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < currentGen; i++) 
        glVertex2f(i, bestFit[i]);

    glEnd();

    // Right side: Average Fitness Graph
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GEN_MAX - 1, 0.0, NUM_CLS);

    // Draw average fitness graph
    glColor3f(1.0, 0.0, 0.0);  // Red color for average fitness
    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < currentGen; i++) 
        glVertex2f(i, avgFit[i]);
    glEnd();

    displayStatistics();

    if (solutionFound) {
        glColor3f(1.0, 1.0, 1.0);  // Texto branco
        renderBitmapString(GEN_MAX / 2.0, NUM_CLS / 2.0, GLUT_BITMAP_HELVETICA_18, "Solution Found!");
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 13:  // Enter key
            if(currentGen < GEN_MAX){
                if(!solutionFound){
                    solutionFound = fitnessPop(population);
                }
                glutPostRedisplay();  // Request a redraw
                if(!solutionFound)
                    currentGen++;
            }
            break;
        case 27:  // Escape key
            exit(0);
            break;
    }
}

void idle(void){
    if(currentGen < GEN_MAX){
        if(!solutionFound){
            solutionFound = fitnessPop(population);
        }
        glutPostRedisplay();
        if(!solutionFound)
            currentGen++;
    }
}