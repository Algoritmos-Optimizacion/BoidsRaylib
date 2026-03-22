
#include "Boids.h"
#include "time.h"
#include <Vector>
#include "imgui/imgui.h"


constexpr float DriverSpeed = 0.65f;
// How speed of boids are dragged. The lower the value, the more drag is applied. % of the speed preserved for the frame
constexpr float DragBoidSpeed = 0.1f;
// Boid's speed is clamped to MaxBoidSpeed
constexpr float MaxBoidSpeed = 200.f;
// Radius of neighborhood
constexpr float NeighborhoodRadius = 50.f;


struct Boid : public BoidData
{
	Vector2 Force{ 0.f, 0.f };
	Vector2 Velocity{ 0.f, 0.f };
};

class BoidsSystemImplementation : public BoidsSystem
{
public:
	static BoidsSystem* GetSystem() { return &System; }

protected:
	virtual void InitializeBoids(int NumBoids, int InScreenWidth, int InScreenHeight)  override;
	virtual void ShowGui() override;
	virtual void RenderAdditionalData() override;
	virtual void SimulateBoids(float DeltaTime)  override;
	virtual size_t GetNumBoids() const override { return Boids.size(); }
	virtual const BoidData& GetBoidData(size_t Index) const override { return Boids[Index]; }

private:
	void SimulateBoid(Boid& Boid, float DeltaTime);

	void FollowDriver(Boid& Boid);
	void Separation(Boid& Boid);
	void Alignment(Boid& Boid);
	void Cohesion(Boid& Boid);

	static BoidsSystemImplementation System;

	int ScreenWidth = 0;
	int ScreenHeight = 0;

	Vector2 Driver;
	float DriverCircleRadiusX = 0.f;
	float DriverCircleRadiusY = 0.f;
	float DriverTime = 0.f;

	std::vector<Boid> Boids;

};

BoidsSystemImplementation BoidsSystemImplementation::System;

BoidsSystem* BoidsSystem::GetSystem()
{
	return BoidsSystemImplementation::GetSystem();
}

void BoidsSystemImplementation::InitializeBoids(int NumBoids, int InScreenWidth, int InScreenHeight)
{
	ScreenWidth = InScreenWidth;
	ScreenHeight = InScreenHeight;
	DriverCircleRadiusX = InScreenWidth * 0.27f;
	DriverCircleRadiusY = InScreenHeight * 0.27f;
	DriverTime = 0.f;

	Boids = std::vector<Boid>(NumBoids);
	srand(time(nullptr));
	for (size_t Index = 0; Index < NumBoids; ++Index)
	{
		float x = ScreenWidth * (float)rand() / RAND_MAX;
		float y = ScreenHeight * (float)rand() / RAND_MAX;
		Boids[Index].Center = { x, y };
	}
}

void BoidsSystemImplementation::ShowGui()
{

}

void BoidsSystemImplementation::RenderAdditionalData()
{
	DrawCircle(Driver.x, Driver.y, 5, {0, 0, 255, 255});
}

void BoidsSystemImplementation::SimulateBoids(float DeltaTime)
{
	// Move Driver
	DriverTime += (DeltaTime * DriverSpeed);
	const float SinTime = sinf(DriverTime);
	const float CosTime = cosf(DriverTime);
	Driver.x = ScreenWidth * 0.5f + DriverCircleRadiusX * CosTime + DriverCircleRadiusX * SinTime;
	Driver.y = ScreenHeight * 0.5f - DriverCircleRadiusY * SinTime + DriverCircleRadiusY * CosTime;

	// Boids
	for (size_t Index = 0; Index < Boids.size(); ++Index)
	{
		SimulateBoid(Boids[Index], DeltaTime);
	}
}

void BoidsSystemImplementation::SimulateBoid(Boid& Boid, float DeltaTime)
{
	// Drag
	Boid.Velocity *= DragBoidSpeed;

	// Compute new forces
	FollowDriver(Boid);
	Separation(Boid);
	Alignment(Boid);
	Cohesion(Boid);

	// Add force to velocity
	Boid.Velocity = ClampSize(Boid.Velocity + Boid.Force * DeltaTime, MaxBoidSpeed);
	// Compute new position of Boid
	Boid.Center = Boid.Center + Boid.Velocity * DeltaTime;
	// Reset force
	Boid.Force = {0, 0};
	// Compute direction of Boid using its velocity vector
	Boid.Angle = atan2f(Boid.Velocity.y, Boid.Velocity.x);
}

void BoidsSystemImplementation::FollowDriver(Boid& Boid)
{
	// Add force to follow the driver
	constexpr float MaxForce = 500.f;
	Vector2 ForceToDriver = ClampSize(Driver - Boid.Center, MaxForce);
	Boid.Force = ForceToDriver;
}

void BoidsSystemImplementation::Separation(Boid& Boid)
{
	// TODO
}

void BoidsSystemImplementation::Alignment(Boid& Boid)
{
	// TODO
}

void BoidsSystemImplementation::Cohesion(Boid& Boid)
{
	// TODO
}
