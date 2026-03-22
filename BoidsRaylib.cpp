// BoidsRaylib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "raylib/src/raylib.h"
#include "rlImGui/rlImGui.h"
#include "imgui/imgui.h"
#include "Boids.h"
#include <iostream>

constexpr float BoidLength = 12.f;
constexpr float BoidWidth = 8.f;

void DrawBoid(const Vector2& Center, float AngleRotation, Color BoidColor)
{
	float SinAngle = std::sinf(AngleRotation);
	float CosAngle = std::cosf(AngleRotation);
	Vector2 Direction = { CosAngle, SinAngle };
	Vector2 PerpDir = { -SinAngle, CosAngle };

	Vector2 PointA = Center + Direction * BoidLength * 0.75f;
	Vector2 PointB = Center + Direction * BoidLength * -0.25f + PerpDir * BoidWidth * -0.5f;
	Vector2 PointC = Center + Direction * BoidLength * -0.25f + PerpDir * BoidWidth * 0.5f;

	DrawTriangle(PointA, PointB, PointC, BoidColor);
}

int main()
{
	// Initialization
	 //--------------------------------------------------------------------------------------
	const int screenWidth = 1280;
	const int screenHeight = 720;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Boids");
	SetTargetFPS(144);
	rlImGuiSetup(true);

	//--------------------------------------------------------------------------------------

	BoidsSystem* BoidSystem = BoidsSystem::GetSystem();
	BoidSystem->InitializeBoids(50, screenWidth, screenHeight);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		// GUI
		{
			// start ImGui content
			rlImGuiBegin();

			// show ImGui Content
			bool open = true;
			ImGui::ShowDemoWindow(&open);
			open = true;
			if (ImGui::Begin("Test Window", &open))
			{
				ImGui::TextUnformatted(ICON_FA_JEDI);
			}
			ImGui::End();

			// end ImGui Content
			rlImGuiEnd();
		}

		// Simulate boids
		float DeltaTime = GetFrameTime();
		BoidSystem->SimulateBoids(DeltaTime);

		// Render
		BoidSystem->RenderAdditionalData();
		size_t NumBoids = BoidSystem->GetNumBoids();
		for (size_t Index = 0; Index < NumBoids; ++Index)
		{
			const BoidData& Boid = BoidSystem->GetBoidData(Index);
			DrawBoid(Boid.Center, Boid.Angle, { 255, 64, 64, 255 });
		}

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
