#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::init(float x, float y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}
	
	/*float vertexData[12];

	vertextData[0] = x + width;
	vertextData[1] = y + height;
	vertextData[2] = x;
	vertextData[3] = y + height;
	vertextData[4] = x;
	vertextData[5] = y;
	vertextData[6] = x;
	vertextData[7] = y;
	vertextData[8] = x + width;
	vertextData[9] = y;
	vertextData[10] = x + width;
	vertextData[11] = y + height;*/

	Vertex vertexData[6];

	vertexData[0].setPosicion(x + width, y + height);
	vertexData[1].setPosicion(x, y + height);
	vertexData[2].setPosicion(x, y);
	vertexData[3].setPosicion(x, y);
	vertexData[4].setPosicion(x + width, y);
	vertexData[5].setPosicion(x + width, y + height);

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 0, 0, 255);
	}

	vertexData[1].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID); 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
