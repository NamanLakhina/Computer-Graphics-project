#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

// Function to draw a quadratic Bezier curve
void drawBezierCurve(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0; t <= 1.0; t += 0.01) {
        float x = (1 - t) * (1 - t) * x1 + 2 * (1 - t) * t * x2 + t * t * x3;
        float y = (1 - t) * (1 - t) * y1 + 2 * (1 - t) * t * y2 + t * t * y3;
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to draw a curved square
void drawCurvedSquare(float x, float y, float size, float r) {
    // Top-right corner
    drawBezierCurve(x + size - r, y + size, x + size, y + size, x + size, y + size - r);

    // Bottom-right corner
    drawBezierCurve(x + size, y + r, x + size, y, x + size - r, y);

    // Bottom-left corner
    drawBezierCurve(x + r, y, x, y, x, y + r);

    // Top-left corner
    drawBezierCurve(x, y + size - r, x, y + size, x + r, y + size);

    // Connecting lines between corners
    glBegin(GL_LINES);
    glVertex2f(x + r, y);                 // Bottom-left to bottom-right
    glVertex2f(x + size - r, y);

    glVertex2f(x, y + r);                 // Bottom-left to top-left
    glVertex2f(x, y + size - r);

    glVertex2f(x + size, y + r);          // Bottom-right to top-right
    glVertex2f(x + size, y + size - r);

    glVertex2f(x + r, y + size);          // Top-left to top-right
    glVertex2f(x + size - r, y + size);
    glEnd();
}

// Function to draw a raised square with curved vertices
void drawRaisedSquare(float x, float y, float size) {
    float r = size * 0.2f; // Radius for the curved corners

    // Outer square (base)
    glColor3f(0.2f, 0.6f, 0.8f); // Base color
    drawCurvedSquare(x, y, size, r);

    // Inner square (top face)
    float inset = size * 0.1f; // Inset for the inner square
    float xInset = x + inset;
    float yInset = y + inset;
    float innerSize = size - 2 * inset;
    glColor3f(0.4f, 0.8f, 1.0f); // Highlight color
    drawCurvedSquare(xInset, yInset, innerSize, r * 0.8f);

    // Connecting lines to simulate depth
    glColor3f(0.1f, 0.4f, 0.6f); // Shadow color
    glBegin(GL_LINES);
    // Top-left corner
    glVertex2f(x, y + size - r);
    glVertex2f(xInset, yInset + innerSize - r * 0.8f);

    // Top-right corner
    glVertex2f(x + size, y + size - r);
    glVertex2f(xInset + innerSize, yInset + innerSize - r * 0.8f);

    // Bottom-right corner
    glVertex2f(x + size, y + r);
    glVertex2f(xInset + innerSize, yInset + r * 0.8f);

    // Bottom-left corner
    glVertex2f(x, y + r);
    glVertex2f(xInset, yInset + r * 0.8f);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a single raised square with curved vertices
    drawRaisedSquare(-0.5f, -0.5f, 1.0f);

    glFlush();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Raised Curved Square(making a tile)");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


