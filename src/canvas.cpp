#include "canvas.h"

#include <iostream>
#include "numericalVectors.hpp"
#include "colors.hpp"

RenderTexture2D* Canvas::CurrentLayer = nullptr;
std::vector<RenderTexture2D> Canvas::LayerTextures;
Vector2 Canvas::Size;
int Canvas::CurrentLayerIndex = -1;
Camera2D Canvas::camera;

void Canvas::RenderPixelGrid()
{
	const float lineThickness = 1.0f;
	const Color color = (Color){88, 88, 88, 128};

	// Draw vertical lines
	for (int i = 0; i <= Size.x; i++)
	{
		float x = i * camera.zoom;
		DrawLineEx({ x, 0 }, { x, Size.y * camera.zoom }, lineThickness, color);
	}

	// Draw horizontal lines
	for (int i = 0; i <= Size.y; i++)
	{
		float y = i * camera.zoom;
		DrawLineEx({ 0, y }, { Size.x * camera.zoom, y }, lineThickness, color);
	}
}

void Canvas::RenderLayerHierarchy()
{
	// Draw the background thing
	float sectionSize = GetScreenWidth() / 8; 
	DrawRectangle(0, 0, sectionSize, GetScreenHeight(), Colors::Panel);
	
	const float padding = sectionSize / 10.0f;
	const float layerSize = sectionSize - (padding * 2);

	// Starting at the bottom, draw a preview of all layers
	for (int i = 0; i < LayerTextures.size(); i++)
	{
		// Calculate the Y height for the current layer
		float y = GetScreenHeight() - ((layerSize + padding) * i) - (layerSize + padding);

		// Add a little background color thing so we
		// can see stuff with a transparent background
		DrawRectangle(
			padding,
			y,
			layerSize,
			layerSize,
			Colors::PanelAlt
		);

		// Draw the layer preview thing
		Texture2D& texture = LayerTextures[i].texture;
		DrawTexturePro(texture,
			{ 0, 0, (float)texture.width, -(float)texture.height },
			{ padding, y, layerSize, layerSize },
			{ 0, 0 },
			0.0f,
			WHITE
		);
	}
}

void Canvas::DrawOnCanvas()
{
	// Check for if the user is clicking
	if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT) == false) return;

	// Check for if we're clicking on the texture
	Vector2 canvasPosition = GetScreenToWorld2D(GetMousePosition(), camera);
	if (CheckCollisionPointRec(canvasPosition, { 0, 0, Size.x, Size.y}) == false) return;

	// Draw a pixel where we clicked
	BeginTextureMode(LayerTextures[CurrentLayerIndex]);
	DrawPixelV(canvasPosition, BLACK);
	EndTextureMode();
}

void Canvas::ManageLayers()
{
	// Check for shortcuts
	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		// If we press ctrl+n make a new layer
		if (IsKeyPressed(KEY_N) || IsKeyPressedRepeat(KEY_N)) CreateEmptyLayer();
	
		// If we press ctrl+d duplicate the current layer
		if (IsKeyPressed(KEY_D) || IsKeyPressedRepeat(KEY_D)) DuplicateCurrentLayer();
	}
}

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
}

void Canvas::DuplicateCurrentLayer()
{
	// Make a new empty layer
	CreateEmptyLayer();

	// Paste the previous layers contents onto
	// the new empty layer that we just made
	BeginTextureMode(LayerTextures[CurrentLayerIndex]);
	Texture2D& texture = LayerTextures[CurrentLayerIndex - 1].texture;
	DrawTexturePro(texture,
		{ 0, 0, (float)texture.width, -(float)texture.height },
		{ 0, 0, (float)texture.width, (float)texture.height },
		{ 0, 0 },
		0.0f,
		WHITE
	);
	EndTextureMode();
}

void Canvas::Update()
{
	ManageLayers();
	DrawOnCanvas();
}

void Canvas::Render()
{
	BeginMode2D(camera);

	// Draw the behind layer at 50% opacity
	if (CurrentLayerIndex > 0)
	{
		const Color halfOpacity = (Color){ 255u, 255u, 255u, 128u };
		Texture2D& texture = LayerTextures[CurrentLayerIndex - 1].texture;
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

	RenderPixelGrid();
	RenderLayerHierarchy();
}
