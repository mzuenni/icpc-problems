//============================================================================//
// visiualizer.h                                                              //
//============================================================================//
// This header can be used to generate svg files
//============================================================================//

#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <vector>
#include <cmath>
#include <optional>

using Real = double;

struct Color {
	std::uint8_t r, g, b;
	constexpr Color(std::uint32_t rgb = 0) :
		r((rgb >> 16) & 0xFF),
		g((rgb >> 8) & 0xFF),
		b((rgb >> 0) & 0xFF) {}

	constexpr Color(std::uint8_t r_, std::uint8_t g_, std::uint8_t b_) :
		r(r_), g(g_), b(b_) {}

	constexpr Color(std::uint8_t gray_) :
		Color(gray_, gray_, gray_) {} 

	constexpr std::uint8_t& operator[](std::size_t i) {
		switch(i) {
			case 0: return r;
			case 1: return g;
			case 2: return b;
			default: throw std::out_of_range("Index out of range");
		}
	}

	constexpr const std::uint8_t& operator[](std::size_t i) const {
		switch(i) {
			case 0: return r;
			case 1: return g;
			case 2: return b;
			default: throw std::out_of_range("Index out of range");
		}
	}
};

constexpr std::uint8_t operator "" _c(unsigned long long int value) {
	return static_cast<std::uint8_t>(value);
}

template<typename T>
constexpr std::uint8_t clamp_color(T c) = delete;

template<>
constexpr std::uint8_t clamp_color(long long int c) {
	return static_cast<std::uint8_t>(std::clamp(c, 0ll, 0xFFll));
}

template<>
constexpr std::uint8_t clamp_color(int c) {
	return static_cast<std::uint8_t>(std::clamp(c, 0, 0xFF));
}

template<>
constexpr std::uint8_t clamp_color(long double c) {
	return static_cast<std::uint8_t>(std::clamp(std::llround(c), 0ll, 0xFFll));
}

template<>
constexpr std::uint8_t clamp_color(double c) {
	return static_cast<std::uint8_t>(std::clamp(std::llround(c), 0ll, 0xFFll));
}

constexpr Color operator*(long double f, const Color& c) {
	return Color(clamp_color(c.r*f),
				 clamp_color(c.g*f),
				 clamp_color(c.b*f));
}

constexpr Color operator*(const Color& c, long double f) {
	return f*c;
}

constexpr Color& operator*=(Color& c, long double f) {
	return c=f*c;
}

constexpr Color operator+(const Color& a, const Color& b) {
	return Color(clamp_color(a.r+b.r),
				 clamp_color(a.g+b.g),
				 clamp_color(a.b+b.b));
}

constexpr Color& operator+=(Color& a, const Color& b) {
	return a=a+b;
}

constexpr Color lerp(const Color& a, const Color& b, Real f) {
	assert(f >= 0 && f <= 1);
	return a*f+b*(1-f);
}

// some default colors
constexpr Color BLACK		= Color(0x00_c);
constexpr Color DARKGRAY	= Color(0x40_c);
constexpr Color GRAY		= Color(0x80_c);
constexpr Color LIGHTGRAY	= Color(0xC0_c);
constexpr Color WHITE		= Color(0xFF_c);

constexpr Color RED			= Color(0xFF,0x00,0x00);
constexpr Color GREEN		= Color(0x00,0xFF,0x00);
constexpr Color BLUE		= Color(0x00,0x00,0xFF);


constexpr Color YELLOW		= Color(0xFF,0xFF,0x00);
constexpr Color MAGENTA		= Color(0xFF,0x00,0xFF);
constexpr Color CYAN		= Color(0x00,0xFF,0xFF);

std::ostream& operator<<(std::ostream& os, const Color& c) {
	std::ios_base::fmtflags flags(os.flags());
	os << "#" << std::hex;
	os << std::setw(2) << std::setfill('0') << static_cast<int>(c.r);
	os << std::setw(2) << std::setfill('0') << static_cast<int>(c.g);
	os << std::setw(2) << std::setfill('0') << static_cast<int>(c.b);
	os.flags(flags);
	return os;
}

template<typename K, typename V>
std::string attribute(K key, V value) {
	std::ostringstream tmp;
	tmp << key << "=\"" << value << "\" ";
	return tmp.str();
}

template<typename K, typename V>
std::string attribute(K key, std::optional<V> value) {
	std::ostringstream tmp;
	if (value) tmp << key << "=\"" << *value << "\" ";
	return tmp.str();
}

struct Fill {
	Color color;
};

std::ostream& operator<<(std::ostream& os, const Fill& fill) {
	return os << attribute("fill", fill.color);
}

enum class Linecap {
	BUTT,
	ROUND,
	SQUARE,
};

std::ostream& operator<<(std::ostream& os, const Linecap& linecap) {
	switch (linecap) {
		case Linecap::BUTT: return os << "butt";
		case Linecap::ROUND: return os << "round";
		case Linecap::SQUARE: return os << "square";
		default: return os;
	}
}

enum class Linejoin {
	ROUND,
	BEVEL,
	MITER,
};

std::ostream& operator<<(std::ostream& os, const Linejoin& linejoin) {
	switch (linejoin) {
		case Linejoin::ROUND: return os << "round";
		case Linejoin::BEVEL: return os << "bevel";
		case Linejoin::MITER: return os << "miter";
		default: return os;
	}
}

struct Stroke {
	Color color;
	Real width;
	std::optional<Linecap> linecap;
	std::optional<Linejoin> linejoin;
	bool scale;
	constexpr Stroke(const Color& color_, Real width_, bool scale_ = true) :
		color(color_), width(width_), scale(scale_) {}
};

std::ostream& operator<<(std::ostream& os, const Stroke& stroke) {
	os << attribute("stroke", stroke.color);
	os << attribute("stroke-width", stroke.width);
	os << attribute("stroke-linecap", stroke.linecap);
	os << attribute("stroke-linejoin", stroke.linejoin);
	if (!stroke.scale) os << attribute("vector-effect", "non-scaling-stroke");
	return os;
}

struct Rotation {
	Real angle;
};

std::ostream& operator<<(std::ostream& os, const Rotation& rotation) {
	os << attribute("transform", "rotation(" + std::to_string(rotation.angle) + ")");
	return os;
}

struct Dimension {
	Real width, height;
	constexpr Dimension(Real width_, Real height_) :
		width(width_), height(height_) {}
};

struct Point {
	Real x, y;
	constexpr Point(Real x_, Real y_) :
		x(x_), y(y_) {}
};

struct Shape {
	std::optional<Rotation> rotation;
	std::optional<Stroke> stroke;
	std::optional<Fill> fill;
	//std::vector<std::pair<std::string, std::string>> raw;
	protected:
		constexpr Shape() {}
};

std::ostream& operator<<(std::ostream& os, const Shape& shape) {
	if (shape.rotation) os << shape.rotation.value();
	if (shape.stroke) os << shape.stroke.value();
	if (shape.fill) os << shape.fill.value();
	else os << attribute("fill", "none");
	//for (const auto e : shape.raw) os << attribute(e.first, e.second);
	return os;
}

struct Rectangle : public Shape {
	Point origin;
	Dimension dimension;
	constexpr Rectangle(Point origin_, Dimension dimension_) :
		origin(origin_), dimension(dimension_) {}
	constexpr Rectangle(Point origin_, Real width_, Real height_) :
		Rectangle(origin_, {width_, height_}) {}
	constexpr Rectangle(Real x_, Real y_, Dimension dimension_) :
		Rectangle({x_, y_}, dimension_) {}
	constexpr Rectangle(Real x_, Real y_, Real width_, Real height_) :
		Rectangle({x_, y_}, {width_, height_}) {}
};

std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle) {
	os << "<rect ";
	os << attribute("x", rectangle.origin.x);
	os << attribute("y", rectangle.origin.y);
	os << attribute("width", rectangle.dimension.width);
	os << attribute("height", rectangle.dimension.height);
	os << static_cast<const Shape&>(rectangle);
	os << "/>";
	return os;
}

struct Circle : public Shape {
	Point origin;
	Real r;
	constexpr Circle(Point origin_, Real r_) :
		origin(origin_), r(r_) {}
	constexpr Circle(Real x_, Real y_, Real r_) :
		Circle({x_, y_}, r_) {}
};

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
	os << "<circle ";
	os << attribute("r", circle.r);
	os << attribute("cx", circle.origin.x);
	os << attribute("cy", circle.origin.y);
	os << static_cast<const Shape&>(circle);
	os << "/>";
	return os;
}

struct Ellipse : public Shape {
	Point origin;
	Real rx, ry;
	constexpr Ellipse(Point origin_, Real rx_, Real ry_) :
		origin(origin_), rx(rx_), ry(ry_) {}
	constexpr Ellipse(Real x_, Real y_, Real rx_, Real ry_) :
		Ellipse({x_, y_}, rx_, ry_) {}
};

std::ostream& operator<<(std::ostream& os, const Ellipse& ellipse) {
	os << "<ellipse ";
	os << attribute("rx", ellipse.rx);
	os << attribute("ry", ellipse.ry);
	os << attribute("cx", ellipse.origin.x);
	os << attribute("cy", ellipse.origin.y);
	os << static_cast<const Shape&>(ellipse);
	os << "/>";
	return os;
}

struct Polygon : public Shape {
	std::vector<Point> points;
	Polygon(std::initializer_list<Point> points_) :
		points(points_) {}
	Polygon(std::vector<Point> points_) :
		points(points_) {}
};

std::ostream& operator<<(std::ostream& os, const Polygon& polygon) {
	os << "<polygon ";
	os << "points=\"";
	for (const Point& p : polygon.points) os << p.x << "," << p.y << " ";
	os << "\" ";
	os << static_cast<const Shape&>(polygon);
	os << "/>";
	return os;
}

struct Line : public Shape {
	Point p1, p2;
	constexpr Line(Point p1_, Point p2_) :
		p1(p1_), p2(p2_) {}
	constexpr Line(Real x1_, Real y1_, Real x2_, Real y2_) :
		p1({x1_, y1_}), p2({x2_, y2_}) {}
};

std::ostream& operator<<(std::ostream& os, const Line& line) {
	os << "<line ";
	os << attribute("x1", line.p1.x);
	os << attribute("y1", line.p1.y);
	os << attribute("x2", line.p2.x);
	os << attribute("y2", line.p2.y);
	os << static_cast<const Shape&>(line);
	os << "/>";
	return os;
}

struct Polyline : public Shape {
	std::vector<Point> points;
	Polyline(std::initializer_list<Point> points_) :
		points(points_) {}
	Polyline(std::vector<Point> points_) :
		points(points_) {}
};

std::ostream& operator<<(std::ostream& os, const Polyline& polyline) {
	os << "<polyline ";
	os << "points=\"";
	for (const Point& p : polyline.points) os << p.x << "," << p.y << " ";
	os << "\" ";
	os << static_cast<const Shape&>(polyline);
	os << "/>";
	return os;
}

struct Comment {
	std::string comment;
};

std::ostream& operator<<(std::ostream& os, const Comment& comment) {
	return os << "<!-- " << comment.comment << " -->";
}

class SVG : public std::ostream {
	std::ostringstream out;
public:
	Point origin;
	Dimension dimension;
	SVG(Point origin_, Dimension dimension_) :
		origin(origin_), dimension(dimension_) {
		init(out.rdbuf());
	}
	SVG(Point origin_, Real width_, Real height_) :
		SVG(origin_, {width_, height_}) {}
	SVG(Real x_, Real y_, Dimension dimension_) :
		SVG({x_, y_}, dimension_) {}
	SVG(Real x_, Real y_, Real width_, Real height_) :
		SVG({x_, y_}, {width_, height_}) {}
	SVG(Dimension dimension_) :
		SVG({0, 0}, dimension_) {}
	SVG(Real width_, Real height_) :
		SVG(Dimension{width_, height_}) {}
	friend std::ostream& operator<<(std::ostream& os, const SVG& svg);
};

std::ostream& operator<<(std::ostream& os, const SVG& svg) {
	os << "<?xml " << attribute("version", "1.0") << attribute("encoding", "UTF8")<< "?>" << std::endl;
	os << "<svg " << attribute("xmlns", "http://www.w3.org/2000/svg")
				  << attribute("version", "1.0")
				  << attribute("baseProfile", "full")
				  << attribute("viewBox", std::to_string(svg.origin.x) + " " +
				  						  std::to_string(svg.origin.y) + " " +
				  						  std::to_string(svg.dimension.width) + " " +
				  						  std::to_string(svg.dimension.height)) << ">" << std::endl;
	os << svg.out.str();
	os << "</svg>";
	return os;
}

class Visualizer {
	std::ofstream file;
public:
	std::ifstream testIn;
	std::ifstream testAns;
	SVG image;

	Visualizer(int argc, char** argv) : image(0, 0, 1, 1) {
		assert(argc > 1);
		std::string name = argv[1];
		file.open(name + ".svg");
		testIn.open(name + ".in");
		testAns.open(name + ".ans");
	}

	~Visualizer() {
		if (file.is_open()) {
			file << image;
		}
	}
};

#endif
