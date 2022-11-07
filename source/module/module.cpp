#include <iostream>
#include <string>
#include <pybind11/pybind11.h>

void say_hello()
{
	std::cout << "Hello World!\n";
}

struct Point 
{
	float x, y;
	Point() : x(0.0f), y(0.0f) {};
	Point(float x, float y) : x(x), y(y) {};
	std::string __repr__()
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}
};

PYBIND11_MODULE(pybind11module, mod)
{
	mod.doc() = "PyBind11Module";
	mod.def("say_hello", &say_hello);
	pybind11::class_<Point>(mod, "Point")
	.def(pybind11::init<>(), "constructor 1")
	.def(pybind11::init<float, float>(), "constructor 2", pybind11::arg("x"), pybind11::arg("y"))
	.def("__repr__", &Point::__repr__)
	.def_readwrite("x", &Point::x)
	.def_readwrite("y", &Point::y)
	;
}