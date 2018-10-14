#include "GraphicsDevice.h"
#include "v2.h"
#include "v3.h"
#include "mat4.h"
#include "maths.h"
#include "Model.h"
#include "texture.h"
#include "ObjLoader.h"
#include "BitmapLoader.h"
#include <iostream>
#include <chrono>
#include <cmath>

int main(int argc, char* argv[])
{
	SDLWindow window(1024, 768);
	window.init();

	GraphicsDevice renderer(window);

	float x = .0f;

	v4 somevec(1.0f, 1.0f, 0.5f, 1.0f);

	texture skin1;
	BitmapLoader bmpLoader;
	bmpLoader.load("zero_beat.bmp", &skin1);

	Model model;

	for (auto i = 0; i < 4; i++)
	{
		std::cout << "[";
		for (auto j = 0; j < 4; j++)
		{
			std::cout << " " << model.matrix[i][j] << " ";
		}
		std::cout << "]\n";
	}

	model.matrix = maths::rotate(model.matrix, v3(0.0f, 45.0f, 0.0f));

	for (auto i = 0; i < 4; i++)
	{
		std::cout << "[";
		for (auto j = 0; j < 4; j++)
		{
			std::cout << " " << model.matrix[i][j] << " ";
		}
		std::cout << "]\n";
	}

	std::cout << somevec.x << " " << somevec.y << " " << somevec.z << " " << somevec.w << std::endl;

	ObjLoader obj;
	obj.load("zero_beat.obj", &model.meshData);
//	obj.dump("zero_beat.txt");

	v2 p(400.0f, 500.0f);
	v3 angle(0.0f, 0.0f, 0.0f);
	
	v2 tr1(500.0f, 200.0f);
	v2 tr2(520.0f, 250.0f);
	v2 tr3(450.0f, 280.0f);

	float scalef = -20.f;
	v2 offset(400.0f, 1000.0f);

	std::cout << model.meshData.faces.size() << " " << model.meshData.vertices.size() << std::endl;

	v3 lightColour(1.0f, 1.0f, 1.0f);
	v3 lightDir(0.0f, 0.0f, -1.0f);

	using Time = std::chrono::high_resolution_clock;
	using ms = std::chrono::milliseconds;
	using fsec = std::chrono::duration<float>;
	auto tstart = Time::now();

	float dt = 0.0f;

	while (window.running())
	{
		const Uint8* keyState = SDL_GetKeyboardState(NULL);
		SDL_Scancode w = SDL_GetScancodeFromName("W");
		SDL_Scancode s = SDL_GetScancodeFromName("S");
		SDL_Scancode a = SDL_GetScancodeFromName("A");
		SDL_Scancode d = SDL_GetScancodeFromName("D");
		SDL_Scancode e = SDL_GetScancodeFromName("E");
		SDL_Scancode q = SDL_GetScancodeFromName("Q");
		SDL_Scancode m = SDL_GetScancodeFromName("M");
		SDL_Scancode n = SDL_GetScancodeFromName("N");
		SDL_Scancode kb = SDL_GetScancodeFromName("B");
		SDL_Scancode kv = SDL_GetScancodeFromName("V");
		
		p.y += (keyState[s] - keyState[w]);
		p.x += (keyState[d] - keyState[a]);
		scalef += (keyState[q] - keyState[e])*1.0f;

		model.matrix.identity();

		model.matrix = maths::rotate(model.matrix, angle);
		model.matrix = maths::scale(model.matrix, v3(scalef, scalef, scalef));
		model.matrix = maths::translate(model.matrix, v3(p.x, p.y, 0.0f));
		
		
		
		
		fsec fs = Time::now() - tstart;
		dt = std::chrono::duration_cast<ms>(fs).count();
		angle.y += ((keyState[kv] - keyState[kb])) * 1.0f;
		angle.z += ((keyState[m] - keyState[n])) * 1.0f;
		lightDir.x = cosf(dt/1000);
		lightDir.z = sinf(dt/1000);

		renderer.clear();

//		renderer.blitTexture(skin1, v2(10.f, 10.f));

		for (int i = 0; i < model.meshData.faces.size(); i++)
		{

			v3 vert1 = model.meshData.vertices[model.meshData.faces[i].vertex[0]];
			v3 vert2 = model.meshData.vertices[model.meshData.faces[i].vertex[1]];
			v3 vert3 = model.meshData.vertices[model.meshData.faces[i].vertex[2]];

			v2 texcoord1 = model.meshData.texCoords[model.meshData.faces[i].texcoord[0]];
			v2 texcoord2 = model.meshData.texCoords[model.meshData.faces[i].texcoord[1]];
			v2 texcoord3 = model.meshData.texCoords[model.meshData.faces[i].texcoord[2]];

			


			v4 p1(vert1, 1.0f);
			v4 p2(vert2, 1.0f);
			v4 p3(vert3, 1.0f);

			p1 = model.matrix * p1;
			p2 = model.matrix * p2;
			p3 = model.matrix * p3;

			//flat shading
		/*	v3 triLine1 = vert2 - vert1;
			v3 triLine2 = vert3 - vert1;

			v3 norm = maths::cross(triLine1, triLine2);
			norm.normalize();
			
			float lightFactor = maths::dot(norm, lightDir);

			lightFactor = (lightFactor < 0.0f) ? 0.0f : lightFactor;*/


			float v1fac = model.meshData.normals[model.meshData.faces[i].normal[0]].dot(lightDir);
			v1fac = (v1fac < 0.0f) ? 0.0f : v1fac;
			float v2fac = model.meshData.normals[model.meshData.faces[i].normal[1]].dot(lightDir);
			v2fac = (v2fac < 0.0f) ? 0.0f : v2fac;
			float v3fac = model.meshData.normals[model.meshData.faces[i].normal[2]].dot(lightDir);
			v3fac = (v3fac < 0.0f) ? 0.0f : v3fac;

			v3 colr = v3(1.0f, 1.0f, 1.0f) * v1fac;
			v3 colg = v3(1.0f, 1.0f, 1.0f) * v2fac;
			v3 colb = v3(1.0f, 1.0f, 1.0f) * v3fac;
			renderer.drawFillTriangle(
				v3(p1.x, p1.y, p1.z), v3(p2.x, p2.y, p2.z), v3(p3.x, p3.y, p3.z),
				v4(colr.x, colr.y, colr.z, 1.0f), v4(colg.x, colg.y, colg.z, 1.0f), v4(colb.x, colb.y, colb.z, 1.0f), skin1, texcoord1, texcoord2, texcoord3);
				
			texcoord1.x *= skin1.width;
			texcoord1.y *= skin1.height;

			texcoord2.x *= skin1.width;
			texcoord2.y *= skin1.height;

			texcoord3.x *= skin1.width;
			texcoord3.y *= skin1.height;

		//	renderer.drawTriangle(texcoord1, texcoord2, texcoord3, v4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	/*	for (auto i : model.meshData.vertices)
		{
			v4 pos(i.x, i.y, i.z, 1.0f);
			pos = model.matrix * pos;

			renderer.drawPoint(v2(pos.x, pos.y), v4(0.0f, 1.0f, 0.0f, 1.0f));

		} */

		

	//	renderer.drawLine(v2(10.0f, 10.0f), v2(10.0f, 50.0f), v4(.0f,1.f,1.f, 1.f));
		
	//	renderer.drawFillTriangle(tr1, tr2, tr3, v4(0.0f, 1.0f, 0.0f, 1.0f));
	//	renderer.drawFillTriangle(tr1+tr3, tr2, tr3+tr2, v4(1.0f, 0.0f, 0.0f, 1.0f));
	//	renderer.drawTriangle(tr1, tr2, tr3, v4(0.0f, 0.0f, 1.0f, 1.0f));
	//	renderer.drawFillCircle(v2(500.0f, 200.0f), 5.0f, v4(1.0f, 0.0f, 0.0f, 1.0f));
	//	renderer.drawFillCircle(v2(700.0f, 500.0f), 5.0f, v4(1.0f, 0.0f, 0.0f, 1.0f));
	//	renderer.drawFillCircle(v2(300.0f, 400.0f), 5.0f, v4(1.0f, 0.0f, 0.0f, 1.0f));
		
	//	if (maths::pointInTriangle(p, tr1, tr2, tr3))
	//		renderer.drawFillCircle(p, 5.0f, v4(1.0f, 1.0f, 0.0f, 1.0f));
	//	else
	//		renderer.drawFillCircle(p, 5.0f, v4(1.0f, 1.0f, 1.0f, 1.0f));
		
		renderer.present();
	
		window.update();
	}

	return 0;
}