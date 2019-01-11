#include "GraphicsDevice.h"
#include "v2.h"
#include "v3.h"
#include "mat4.h"
#include "maths.h"
#include "Model.h"
#include "texture.h"
#include "ObjLoader.h"
#include "BitmapLoader.h"

enum kViewMode
{
	kViewModeWireFrame = 0,
	kViewModeFlat = 1,
	kViewModeTextured = 2,
	kViewModeMAX
};

int main(int argc, char* argv[])
{
	SDLWindow window(1024, 768);
	window.init();

	GraphicsDevice renderer(window);

	texture skin1;
	BitmapLoader bmpLoader;
	bmpLoader.load("sample.bmp", &skin1);

	Model model;
	model.matrix = maths::rotate(model.matrix, v3(0.0f, 45.0f, 0.0f));

	ObjLoader obj;
	obj.load("sample.obj", &model.meshData);

	v2 offset(500.5f, 400.0f);
	v3 angle(0.0f, 0.0f, 0.0f);
	v3 lightAngle(0.0f, -PI /2, PI);

	float scalef = 3.f;

	v3 lightColour(1.0f, 1.0f, 1.0f);
	v3 lightDir(0.0f, 0.0f, -1.0f);

	int lastMouseState[2];
	SDL_GetGlobalMouseState(&lastMouseState[0], &lastMouseState[1]);

	unsigned int viewMode = kViewModeTextured;
	bool viewModeToggle = false;

	double dt = 0.0f;

	while (window.running())
	{
		dt = window.getFrameTime();

		const Uint8* keyState = SDL_GetKeyboardState(NULL);
		SDL_Scancode e = SDL_GetScancodeFromName("E");
		SDL_Scancode q = SDL_GetScancodeFromName("Q");
		SDL_Scancode keyM = SDL_GetScancodeFromName("M");
		SDL_Scancode keyN = SDL_GetScancodeFromName("N");
		SDL_Scancode keyB = SDL_GetScancodeFromName("B");

		int currentMouseState[2];
		Uint32 mouseButtonState = SDL_GetGlobalMouseState(&currentMouseState[0], &currentMouseState[1]);

		int mouseDelta[2];
		mouseDelta[0] = lastMouseState[0] - currentMouseState[0];
		mouseDelta[1] = lastMouseState[1] - currentMouseState[1];

		lastMouseState[0] = currentMouseState[0];
		lastMouseState[1] = currentMouseState[1];

		
		if (keyState[keyB])
		{
			angle.y -= 100 * dt;
			lightAngle.x = (angle.y - 45) * PI / 180;
		}

		if (mouseButtonState & SDL_BUTTON_LMASK)
		{
			angle.x += (float)mouseDelta[1] * 30 * dt;
			angle.y += (float)mouseDelta[0] * 30 * dt;
		}

		if (mouseButtonState & SDL_BUTTON_MMASK)
		{
			lightAngle.x -= (float)mouseDelta[0] * dt;
			lightAngle.y -= (float)mouseDelta[1] * dt;
		}

		if (mouseButtonState & SDL_BUTTON_RMASK)
		{
			offset.y -= (float)mouseDelta[1] * 30 * dt;
			offset.x -= (float)mouseDelta[0] * 30 * dt;
		}

		if (keyState[keyM] && !viewModeToggle)
		{
			viewModeToggle = true;
			viewMode++;
			viewMode %= kViewModeMAX;
		}
		else if (!keyState[keyM] && viewModeToggle)
		{
			viewModeToggle = false;
		}
		
		scalef += (keyState[q] - keyState[e])*.1f;

		model.matrix.identity();
		model.matrix = maths::rotate(model.matrix, angle);
		model.matrix = maths::scale(model.matrix, v3(scalef, scalef, scalef));
		model.matrix = maths::translate(model.matrix, v3(offset.x, offset.y, 0.0f));
		
		lightDir.x = cosf(lightAngle.x) * sinf(lightAngle.y);
		lightDir.y = cosf(lightAngle.y);
		lightDir.z = sinf(lightAngle.x) * sinf(lightAngle.y);

		renderer.clear();

		if (keyState[keyN])
		{
			renderer.blitTexture(skin1, v2(10.f, 10.f));
			for (int i = 0; i < model.meshData.faces.size(); i++)
			{
				v2 texcoord1 = model.meshData.texCoords[model.meshData.faces[i].texcoord[0]];
				v2 texcoord2 = model.meshData.texCoords[model.meshData.faces[i].texcoord[1]];
				v2 texcoord3 = model.meshData.texCoords[model.meshData.faces[i].texcoord[2]];

				texcoord1.x *= skin1.width;
				texcoord1.y *= skin1.height;

				texcoord2.x *= skin1.width;
				texcoord2.y *= skin1.height;

				texcoord3.x *= skin1.width;
				texcoord3.y *= skin1.height;

				renderer.drawTriangle(texcoord1, texcoord2, texcoord3, v4(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		if (viewMode == kViewModeWireFrame)
		{
			for (int i = 0; i < model.meshData.faces.size(); i++)
			{
				v4 p1(model.meshData.vertices[model.meshData.faces[i].vertex[0]], 1);
				v4 p2(model.meshData.vertices[model.meshData.faces[i].vertex[1]], 1);
				v4 p3(model.meshData.vertices[model.meshData.faces[i].vertex[2]], 1);

				p1 = model.matrix * p1;
				p2 = model.matrix * p2;
				p3 = model.matrix * p3;

				renderer.drawTriangle(v2(p1.x, p1.y), v2(p2.x, p2.y), v2(p3.x, p3.y), v4(0, 0, 0, 1));
			}
		}
		else if (viewMode == kViewModeFlat)
		{
			for (int i = 0; i < model.meshData.faces.size(); i++)
			{
				v4 p1(model.meshData.vertices[model.meshData.faces[i].vertex[0]], 1);
				v4 p2(model.meshData.vertices[model.meshData.faces[i].vertex[1]], 1);
				v4 p3(model.meshData.vertices[model.meshData.faces[i].vertex[2]], 1);

				v4 triLine1 = p3 - p1;
				v4 triLine2 = p2 - p1;

				p1 = model.matrix * p1;
				p2 = model.matrix * p2;
				p3 = model.matrix * p3;

				v3 norm = maths::cross(v3(triLine1.x, triLine1.y, triLine1.z), v3(triLine2.x, triLine2.y, triLine2.z));
				norm.normalize();

				float lightFactor = norm.dot(lightDir);
				lightFactor = (lightFactor < 0.4f) ? 0.4f : lightFactor;

				v4 colr(lightFactor, lightFactor, lightFactor, 1);
				v2 tx;

				renderer.drawFillTriangle(
					v3(p1.x, p1.y, p1.z), v3(p2.x, p2.y, p2.z), v3(p3.x, p3.y, p3.z),
					colr, colr, colr, tx, tx, tx);
			}
		}
		else if (viewMode == kViewModeTextured)
		{

			for (int i = 0; i < model.meshData.faces.size(); i++)
			{
				v3 vert1 = model.meshData.vertices[model.meshData.faces[i].vertex[0]];
				v3 vert2 = model.meshData.vertices[model.meshData.faces[i].vertex[1]];
				v3 vert3 = model.meshData.vertices[model.meshData.faces[i].vertex[2]];

				v3 norm1 = model.meshData.normals[model.meshData.faces[i].normal[0]];
				v3 norm2 = model.meshData.normals[model.meshData.faces[i].normal[1]];
				v3 norm3 = model.meshData.normals[model.meshData.faces[i].normal[2]];

				v2 texcoord1 = model.meshData.texCoords[model.meshData.faces[i].texcoord[0]];
				v2 texcoord2 = model.meshData.texCoords[model.meshData.faces[i].texcoord[1]];
				v2 texcoord3 = model.meshData.texCoords[model.meshData.faces[i].texcoord[2]];

				v4 p1(vert1, 1.0f);
				v4 p2(vert2, 1.0f);
				v4 p3(vert3, 1.0f);

				p1 = model.matrix * p1;
				p2 = model.matrix * p2;
				p3 = model.matrix * p3;

				float v1fac = norm1.dot(lightDir);
				v1fac = (v1fac < 0.4f) ? 0.4f : v1fac;

				float v2fac = norm2.dot(lightDir);
				v2fac = (v2fac < 0.4f) ? 0.4f : v2fac;

				float v3fac = norm3.dot(lightDir);
				v3fac = (v3fac < 0.4f) ? 0.4f : v3fac;

				v3 colr = v3(1.0f, 1.0f, 1.0f) * v1fac;
				v3 colg = v3(1.0f, 1.0f, 1.0f) * v2fac;
				v3 colb = v3(1.0f, 1.0f, 1.0f) * v3fac;

				renderer.drawFillTriangle(
					v3(p1.x, p1.y, p1.z), v3(p2.x, p2.y, p2.z), v3(p3.x, p3.y, p3.z),
					v4(colr.x, colr.y, colr.z, 1.0f), v4(colg.x, colg.y, colg.z, 1.0f), v4(colb.x, colb.y, colb.z, 1.0f), texcoord1, texcoord2, texcoord3, &skin1);
			}
		}
		
		renderer.present();
		window.update();

	}

	return 0;
}