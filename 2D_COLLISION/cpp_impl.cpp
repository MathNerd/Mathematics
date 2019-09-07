
namespace Geometry
{
	class Circle;
	class Rectangle;
	class InversedRectangle;
}

enum class MODE { FIXED , DRAG };

class World
{
	private:
		std::vector<Geometry::Rectangle*> m_rectangles;
		std::vector<Geometry::Circle*> m_circles;
		std::vector<Geometry::InversedRectangle*> m_inversed_rectangles;

	public:
		World();
		~World();
		
		void CreateRectangle(Vector2D<float> position, Vector2D<float> size, Vector2D<float> velocity, MODE mode);
		void CreateCircle(Vector2D<float> position, float radius, Vector2D<float> velocity, MODE mode);
		void CreateInversedRectangle(Vector2D<float> position, Vector2D<float> size, Vector2D<float> velocity, MODE mode);
		
		void RemoveRectangle();
		void RemoveCircle();
		void RemoveInversedRectangle();
};
