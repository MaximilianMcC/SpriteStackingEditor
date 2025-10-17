#include <raylib.h>
#include <cmath>

int main()
{
	InitWindow(480, 480, "z is for new zealand");

	// Load the texture
	Texture texture = LoadTexture("./assets/milky.png");
	const float textureSize = 16.0f;
	int layers = texture.width / textureSize;
	float layerDistance = 6.0f;

	Vector2 position = { 480 * 0.5f, 480 * 0.5f };
	float rotation = 0.0f;
	float drawScale = 8;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(MAGENTA);

		if (IsKeyPressed(KeyboardKey::KEY_UP)) layerDistance++;
		if (IsKeyPressed(KeyboardKey::KEY_DOWN)) layerDistance--;
		
		if (IsKeyDown(KeyboardKey::KEY_LEFT)) rotation += 100 * GetFrameTime();
		if (IsKeyDown(KeyboardKey::KEY_RIGHT)) rotation -= 100 * GetFrameTime();

		// Loop over each layer and draw it
		for (int i = 0; i < layers; i++)
		{
			DrawTexturePro(
				texture,
				{ textureSize * i, 0, textureSize, textureSize },
				{ position.x, position.y - (layerDistance * i), textureSize * drawScale, textureSize * drawScale },
				{ (textureSize * drawScale) / 2, (textureSize * drawScale) / 2 },
				rotation,
				WHITE
			);
		}


		EndDrawing();
	}

	CloseWindow();

	return 0;
}