#include <stdint.h>
#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include <memory.h>
#include <ctime>
#include "glut\glut.h"

#include "SearchNode.h"
#include "SearchLevel.h"
#include "OpenList.h"
#include "ClosedList.h"

namespace
{
	OpenList openList;
	ClosedList closedList;

	SearchNode startNode;
	SearchNode endNode;
	SearchNode* currentNode = &startNode;

	bool completed = false;
	bool initialized = false;

	time_t startTime;
	time_t endTime;

	std::vector<Position> adjacentNodes;

	void doPathFinding(const uint8_t* inputData, int width, int height, uint8_t* outputData, int startX, int startY, int endX, int endY, char input)
	{
		// The seeker is used to find information about the level
		SearchLevel seeker(inputData, width, height);

		if (initialized == false)
		{
			startNode.pos = Position(startX, startY);
			endNode.pos = Position(endX, endY);

			startNode.H = seeker.calculateH(Position(startX, startY), Position(endX, endY));
			endNode.H = 0.0f;

			startNode.G = 0.0f;
			endNode.G = seeker.calculateG(&startNode, &endNode);

			startNode.prevNode = nullptr;
			endNode.prevNode = nullptr;

			startNode.resetPrev(nullptr, 0.0f);

			time(&startTime);
			initialized = true;
		}

		if (completed == false && input == 'a')
		{
			/************************************************************************/
			/// DJIKSTRA'S SHORTEST PATH ALGORITHM

			//Add start node and adjacent to OpenNodes
			adjacentNodes = seeker.getAdjacentNodes(currentNode->pos.first, currentNode->pos.second);

			float deltaG;
			for (unsigned int i = 0; i < adjacentNodes.size(); i++)
			{
				if (adjacentNodes[i].first == currentNode->pos.first || adjacentNodes[i].second == currentNode->pos.second)
				{
					deltaG = 1.0f;
				}
				else
				{
					deltaG = 1.41f;
				}

				if (closedList.isInClosedList(adjacentNodes[i]) == false && openList.findFromOpenList(adjacentNodes[i]) == nullptr)
				{
					openList.insertToOpenList(new SearchNode(adjacentNodes[i], 0.0f, deltaG, currentNode));
				}
			}

			closedList.addToClosedList(currentNode);

			// Find the node with shortest distance to start (first one after sorting)
			currentNode = openList.removeSmallestF();

			printf("DJIKSTRA'S SHORTEST PATH ALGORITHM\n");
			printf("Open list size: %d\n", openList.getSize());
			printf("Closed list size: %d\n", closedList.getSize());
			printf("Current G distance: %.2f\n", currentNode->G);
			printf("Current node X: %d, Y: %d\n", currentNode->pos.first, currentNode->pos.second);
		}
			
		else if (completed == false && input == 'b')
		{
			/************************************************************************/
			/// A* ALGORITHM

			// Add start node and adjacent to OpenNodes
			adjacentNodes = seeker.getAdjacentNodes(currentNode->pos.first, currentNode->pos.second);

			float deltaG;
			for (unsigned int i = 0; i < adjacentNodes.size(); i++)
			{
				if (adjacentNodes[i].first == currentNode->pos.first || adjacentNodes[i].second == currentNode->pos.second)
				{
					deltaG = 1.0f;
				}
				else
				{
					deltaG = 1.41f;
				}

				if (closedList.isInClosedList(adjacentNodes[i]) == false && openList.findFromOpenList(adjacentNodes[i]) == nullptr)
				{
					openList.insertToOpenList(new SearchNode(adjacentNodes[i], seeker.calculateH(adjacentNodes[i], endNode.pos), deltaG, currentNode));
				}
			}

			closedList.addToClosedList(currentNode);

			// Find the node with shortest distance to start (first one after sorting)
			currentNode = openList.removeSmallestF();

			printf("A* SEARCH ALGORITHM\n");
			printf("Open list size: %d\n", openList.getSize());
			printf("Closed list size: %d\n", closedList.getSize());
			printf("Current G distance: %.2f\n", currentNode->G);
			printf("Current node X: %d, Y: %d\n", currentNode->pos.first, currentNode->pos.second);

			/************************************************************************/
		}

			// Coloring the searched area blue
			outputData[3 * (currentNode->pos.second * width + currentNode->pos.first)] = currentNode->G * 2.55;
			outputData[3 * (currentNode->pos.second * width + currentNode->pos.first) + 1] = 0;
			outputData[3 * (currentNode->pos.second * width + currentNode->pos.first) + 2] = (255 - currentNode->G * 2.55);

			// If we have found our end point, stop the search and color the best path yellow
			if (currentNode->pos.first == endX && currentNode->pos.second == endY)
			{
				printf("Search complete!\n");
				
				time(&endTime);
				printf("Operation took %.f seconds.\n", difftime(endTime, startTime));
				
				SearchNode* pathNode;

				do 
				{
					pathNode = currentNode->prevNode;

					outputData[3 * (pathNode->pos.second * width + pathNode->pos.first)] = 0;
					outputData[3 * (pathNode->pos.second * width + pathNode->pos.first) + 1] = 255;
					outputData[3 * (pathNode->pos.second * width + pathNode->pos.first) + 2] = 255;

					currentNode = pathNode;

				} while (currentNode->prevNode != nullptr);	// The path ends back at the start point

				completed = true;
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
	// input for algorithm selection.
	char input;
	char mapInput;

	// Initialization
	bool init()
	{
		printf("Select algorithm:\n");
		printf("a) Djikstra's shortest path algorithm\n");
		printf("b) A* search algorithm\n");

		input = getchar();
		while ((getchar()) != '\n');
		
		printf("Select map:\n");
		printf("a) Empty level\n");
		printf("b) Original map\n");
		printf("c) Maze\n");

		mapInput = getchar();
		while ((getchar()) != '\n');

		glMatrixMode(GL_PROJECTION);
		glOrtho(0, 512 + 4, 256 + 2, 0, -1, 1);

		// Load input file

		if (mapInput == 'a')
		{
			inputTexture = loadBMPTexture("input_empty.bmp", &width, &height, &inputData);
		}
		else if (mapInput == 'b')
		{
			inputTexture = loadBMPTexture("input.bmp", &width, &height, &inputData);
		}
		else if (mapInput == 'c')
		{
			inputTexture = loadBMPTexture("input_maze.bmp", &width, &height, &inputData);
		}

		if (0 == inputTexture)
		{
			printf("Error! Cannot open input file!\n");
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
		doPathFinding(inputData, width, height, outputData, startX, startY, endX, endY, input);

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
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(2*(512+4), 2*(256+2));

	glutCreateWindow("Pathfinding Demo");
	glutDisplayFunc(draw);

	if (!init()) { return -1; };

	glutMainLoop();

	delete inputData;
	delete outputData;

	return 0;
}