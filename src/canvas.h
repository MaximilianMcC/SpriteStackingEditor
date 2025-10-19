#pragma once

#include <raylib.h>
#include <vector>

class Canvas
{
private:
	static Camera2D camera;
	static void RenderPixelGrid();
	static void RenderLayerHierarchy();
	static void DrawOnCanvas();
	static void ManageLayers();

public:
	static RenderTexture2D* CurrentLayer;
	static std::vector<RenderTexture2D> LayerTextures;
	static Vector2 Size;
	static int CurrentLayerIndex;

	static void Init(Vector2 size);
	static void CreateEmptyLayer();
	static void DuplicatePreviousLayer();

	static void Update();	
	static void Render();
};