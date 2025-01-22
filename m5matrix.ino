#include "M5Cardputer.h"

const int MATRIX_WIDTH = 240; 
const int MATRIX_HEIGHT = 135;

const char matrix_chars[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\^_`abcdefghijklmnopqrstuvwxyz{|}~";
const int num_chars = sizeof(matrix_chars) - 1;

// Define colors
const uint16_t colors[] = {
  ILI9341_GREEN, 
  ILI9341_BLUE, 
  ILI9341_CYAN, 
  ILI9341_MAGENTA, 
  ILI9341_YELLOW 
};
int currentColorIndex = 0;

struct MatrixChar {
  char character;
  int x;
  float y; 
  float speed; // Use float for speed as well
};

MatrixChar matrixChars[MATRIX_WIDTH];

void setup() {
  M5Cardputer.begin();
  M5Cardputer.Display.begin();
  M5Cardputer.Display.fillScreen(ILI9341_BLACK); 

  // Initialize matrixChars
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    matrixChars[i].character = matrix_chars[random(num_chars)];
    matrixChars[i].x = i;
    matrixChars[i].y = random(MATRIX_HEIGHT); 
    matrixChars[i].speed = 0.6 + (float)random(10) / 100.0; // Adjust speed range for smoother movement
  }
}

void loop() {
  M5Cardputer.update(); 

  // Handle button press
  if (M5Cardputer.BtnA.wasPressed()) {
    currentColorIndex = (currentColorIndex + 1) % (sizeof(colors) / sizeof(colors[0])); 
  }

  // Clear previous characters
  M5Cardputer.Display.fillRect(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, ILI9341_BLACK); 

  // Draw matrix effect
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    // Update character position with floating-point precision
    matrixChars[i].y += matrixChars[i].speed; 

    // Wrap around if character goes off screen
    if (matrixChars[i].y > MATRIX_HEIGHT) {
      matrixChars[i].y = 0;
      matrixChars[i].character = matrix_chars[random(num_chars)];
    }

    // Draw character
    M5Cardputer.Display.setTextColor(colors[currentColorIndex]); 
    M5Cardputer.Display.setTextSize(1); 
    M5Cardputer.Display.setCursor(matrixChars[i].x, (int)matrixChars[i].y); 
    M5Cardputer.Display.print(matrixChars[i].character);
  }


  delay(30); // Reduced delay for smoother animation
}