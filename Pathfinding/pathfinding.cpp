#include <stdint.h>
#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include "glut\glut.h"
#include <memory.h>



namespace
{
	// STUDENT_TODO: Make implementation for doPathFinding function, which writes found path to outputData
	void doPathFinding(const uint8_t* inputData, int width, int height, uint8_t* outputData, int startX, int startY, int endX, int endY)
	{
		printf("STUDENT_TODO: Do path finding from <%d,%d> to <%d,%d>\n", startX, startY, endX, endY);
		// Make noise for now
		for (size_t i = 0; i < static_cast<unsigned int>(3 * width * height); i+=3)
		{
			int val = rand();
			outputData[i+0] = val;
			outputData[i+1] = val;
			outputData[i+2] = val;

		}
	}
}


namespace
{
	// Quick and dirty function for reading bmp-files to opengl textures.
	GLuint loadBMPTexture(const char *fileName, int* w, int* h, uint8_t** data)
	{
		assert(w != 0);
		assert(h != 0);
		assert(data != 0);
		FILE *file;

		errno_t err;

		if ((err = fopen_s(&file, fileName, "rb")) != NULL)
			return 0;
		fseek(file, 18, SEEK_SET);

		int width = 0;
		fread(&width, 2, 1, file);
		fseek(file, 2, SEEK_CUR);
		int height = 0;
		fread(&height, 2, 1, file);
		printf("Image \"%s\" (%dx%d)\n", fileName, width, height);

		*data = new uint8_t[3 * width * height];
		assert(data != 0);
		fseek(file, 30, SEEK_CUR);
		fread(*data, 3, width * height, file);
		fclose(file);

		GLuint  texId;
		glGenTextures(1, &texId);
		glBindTexture(GL_TEXTURE_2D, texId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, *data);
		glBindTexture(GL_TEXTURE_2D, 0);
		if (w) *w = width;
		if (h) *h = height;
		return texId;
	}

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	// Global variables

	// OpenGL texture ids for rendering.
	GLuint  inputTexture = 0;
	GLuint  outputTexture = 0;
	// Input and output data in pixels. outputData is updated to outputTexture each frame
	uint8_t* inputData = 0;
	uint8_t* outputData = 0;
	// width and height of the input and output datas
	int width = 0;
	int height = 0;
	// start and end position for path finding. These are found automatically from input file.
	int startX = -1;
	int startY = -1;
	int endX = -1;
	int endY = -1;

	// Initialization
	bool init()
	{
		glMatrixMode(GL_PROJECTION);
		glOrtho(0, 512 + 4, 256 + 2, 0, -1, 1);

		// Load input file
		inputTexture = loadBMPTexture("input.bmp", &width, &height, &inputData);
		if (0 == inputTexture)
		{
			printf("Error! Cannot open file: \"input.bmp\"\n");
			return false;
		}

		// Make outputTexture
		glGenTextures(1, &outputTexture);
		glBindTexture(GL_TEXTURE_2D, outputTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Copy inputData also to outputData
		outputData = new uint8_t[3 * width*height];
		memcpy(outputData, inputData, 3 * width*height);

		// find start and end
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				uint8_t* pix = &inputData[3 * (y*width + x)]; // get pixel
				uint8_t r = pix[0];
				uint8_t g = pix[1];
				uint8_t b = pix[2];
				if (255 == r && g == 0 && b == 0) // Red?
				{
					// Start
					startX = x;
					startY = y;
					printf("Start position: <%d,%d>\n", x, y);
				}
				if (255 == b && r == 0 && g == 0) // Blue?
				{
					// End
					endX = x;
					endY = y;
					printf("End position: <%d,%d>\n", x, y);
				}
			}
		}

		if (startX < 0 || startY < 0)
		{
			printf("Error! Start position not found\n");
			return false;
		}

		if (endX < 0 || endY < 0)
		{
			printf("Error! End position not found\n");
			return false;
		}

		return true;
	}

	// Draw/Render
	void draw() 
	{
		doPathFinding(inputData, width, height, outputData, startX, startY, endX, endY);

		// Copy outputData to outputTexture
		glBindTexture(GL_TEXTURE_2D, outputTexture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, outputData);
		glBindTexture(GL_TEXTURE_2D, 0);

		glClear(GL_COLOR_BUFFER_BIT);

		// Draw input texture to left half of the screen
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, inputTexture);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1); glVertex2d(1, 1);
		glTexCoord2d(0, 0); glVertex2d(1, 1 + 256);
		glTexCoord2d(1, 0); glVertex2d(1 + 256, 1 + 256);
		glTexCoord2d(1, 1); glVertex2d(1 + 256, 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		// Draw output texture to right half of the screen
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, outputTexture);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1); glVertex2d(2 + 256, 1);
		glTexCoord2d(0, 0); glVertex2d(2 + 256, 1 + 256);
		glTexCoord2d(1, 0); glVertex2d(2 + 512, 1 + 256);
		glTexCoord2d(1, 1); glVertex2d(2 + 512, 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glutSwapBuffers();
		glutPostRedisplay();
	}
} // end - anonymous namespace


// Main
int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(2*(512+4), 2*(256+2));
	glutCreateWindow("Pathfinding Demo");
	glutDisplayFunc(draw);
	if (!init()) return -1;
	glutMainLoop();
	delete inputData;
	delete outputData;
	return 0;
}