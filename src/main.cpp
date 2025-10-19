#include <raylib.h>
#include "canvas.h"

int main()
{
	SetTraceLogLevel(LOG_WARNING);
	SetConfigFlags(ConfigFlags::FLAG_WINDOW_RESIZABLE);
	InitWindow(480, 480, "z is for new zealand");

	Canvas::Init({ 16, 16 });

	while (!WindowShouldClose())
	{
		Canvas::Update();

		BeginDrawing();
		ClearBackground(MAGENTA);
		Canvas::Render();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}