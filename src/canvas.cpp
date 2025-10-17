#include "canvas.h"

#include <iostream>
#include "numericalVectors.hpp"

RenderTexture2D* Canvas::CurrentLayer = nullptr;
std::vector<RenderTexture2D> Canvas::LayerTextures;
Vector2 Canvas::Size;
int Canvas::CurrentLayerIndex = -1;
Camera2D Canvas::camera;

void Canvas::Init(Vector2 size)
{
	// Set the dimensions of the layers
	Size = size;

	// Set the cameras default zoom
	camera.zoom = 25.0f;
	HideCursor();

	// Make an intial base layer
	CreateEmptyLayer();
}

void Canvas::CreateEmptyLayer()
{
	// Make and add the actual layer
	RenderTexture newLayer = LoadRenderTexture(Size.x, Size.y);
	LayerTextures.insert(LayerTextures.begin() + (CurrentLayerIndex + 1), newLayer);

	// Select the layer
	CurrentLayerIndex++;

	//! debug give it a background color
	BeginTextureMode(LayerTextures[CurrentLayerIndex]);
	ClearBackground(WHITE);
	EndTextureMode();
}

void Canvas::DuplicatePreviousLayer()
{
	
}

void Canvas::Update()
{
	// Check for if the user is clicking
	if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT) == false) return;

	// Check for if we're clicking on the texture
	Vector2 canvasPosition = GetScreenToWorld2D(GetMousePosition(), camera);

	// Draw a pixel where we clicked
	BeginTextureMode(LayerTextures[CurrentLayerIndex]);
	DrawPixelV(canvasPosition, BLACK);
	EndTextureMode();
}

void Canvas::Draw()
{
	BeginMode2D(camera);

	// Draw the behind layer at 50% opacity
	if (CurrentLayerIndex - 1 > 0)
	{
		const Color halfOpacity = (Color){ 255u, 255u, 255u, 128u };
		Texture2D& texture = LayerTextures[CurrentLayerIndex].texture;
		DrawTexturePro(texture,
			{ 0, 0, (float)texture.width, -(float)texture.height },
			{ 0, 0, (float)texture.width, (float)texture.height },
			{ 0, 0 },
			0.0f,
			halfOpacity
		);
	}

	// Draw the current layer
	Texture2D& texture = LayerTextures[CurrentLayerIndex].texture;
	DrawTexturePro(texture,
		{ 0, 0, (float)texture.width, -(float)texture.height },
		{ 0, 0, (float)texture.width, (float)texture.height },
		{ 0, 0 },
		0.0f,
		WHITE
	);

	EndMode2D();

	// Draw a cursor thing over the users mouse
	// TODO: Snap to the pixels
	Vector2 actualPixelSize = { camera.zoom, camera.zoom };
	DrawRectangleLines(
		GetMousePosition().x,
		GetMousePosition().y,
		actualPixelSize.x,
		actualPixelSize.y,
		BLACK
	);
}
