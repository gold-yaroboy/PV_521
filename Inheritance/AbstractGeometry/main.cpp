#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Orange = 0x0000A5FF,
		White = 0x00FFFFFF
	};

#define SHAPE_TAKE_PARAMETERS	int start_x, int star_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS	start_x, star_y, line_width, color
	class Shape
	{
	protected:
		Color color;
		int line_width;
		int start_x;
		int start_y;
	public:
		static const int min_start_x = 100;
		static const int min_start_y = 100;
		static const int max_start_x = 1000;
		static const int max_start_y = 600;
		static const int min_line_width = 3;
		static const int max_line_width = 16;
		static const int min_size = 32;
		static const int max_size = 768;

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}

		void set_start_x(int start_x)
		{
			this->start_x =
				start_x<min_start_x ? min_start_x :
				start_x>max_start_x ? max_start_x :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y<min_start_y ? min_start_y :
				start_y>max_start_y ? max_start_y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width<min_line_width ? min_line_width :
				line_width>max_line_width ? max_line_width :
				line_width;
		}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметер фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	/*class Square :public Shape
	{
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return 4 * side;
		}
		void draw()const override
		{
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			cout << endl;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длинна стороны квадрата: " << get_side() << endl;
			Shape::info();
		}
	};*/

	class Rectangle : public Shape
	{
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		double get_area() const override
		{
			return width * height;
		}
		double get_perimeter()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();//окно консоли
			HDC hdc = GetDC(hwnd);//контекст устройства для окна консоли (device context)
			HPEN hPen = CreatePen(PS_SOLID, 5, color);//Карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);//Кисть для заливки
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);//рисуем

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Стороны: " << width << " x " << height << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle
	{
	public:
		Square(int side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::Red);
	Geometry::Square square(100, 100, 100, 1, Geometry::Color::Red);
	/*cout << "Длинна стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;
	square.draw();*/
	//cout << "\n------------------------------" << endl;
	square.info();


	Geometry::Rectangle rect(150, 100, 550, 100, 2, Geometry::Color::Orange);
	rect.info();
	while (true)
	{
		square.draw();
		rect.draw();
	}
}