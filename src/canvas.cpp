#include "canvas.h"

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

	// Make the camera so we can zoom and whatnot
	camera.target = size / 2;
	camera.offset = { 0.0f, 0.0f };
	camera.rotation = 0.0f;
	camera.zoom = 20.0f;

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
	if (CheckCollisionPointRec(canvasPosition, { 0, 0, Size.x, Size.y }) == false) return;

	// Draw a pixel where we clicked
	const Color color = BLACK;
	BeginTextureMode(LayerTextures[CurrentLayerIndex]);
	DrawPixelV(canvasPosition, color);
	EndTextureMode();
}

void Canvas::Draw()
{
	BeginMode2D(camera);

	// Draw the behind layer at 50% opacity
	if (CurrentLayerIndex - 1 > 0)
	{
		const Color halfOpacity = (Color){ 255u, 255u, 255u, 128u };
		DrawTexture(LayerTextures[CurrentLayerIndex - 1].texture, 0, 0, halfOpacity);
	}

	// Draw the current layer
	DrawTexture(LayerTextures[CurrentLayerIndex].texture, 0, 0, WHITE);

	EndMode2D();
}
