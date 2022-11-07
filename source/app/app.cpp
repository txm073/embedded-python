#include <stdio.h>

#include <pybind11/embed.h>
#include <pybind11/stl_bind.h>
namespace py = pybind11;

#define PY_LEN(ob) ob.attr("__len__")().cast<size_t>()

int main(const int argc, const char** argv)
{
    py::scoped_interpreter guard{};

    py::exec("print('Hello from embedded Python!')");
    py::module_ sys = py::module_::import("sys");
    std::vector<std::string> li = { 
        "C:/Users/User/Projects/assistant",
        "C:/Users/User/Projects/assistant/deps/python38",
        "C:/Users/User/Projects/assistant/deps/python38/scripts",
        "C:/Users/User/Projects/assistant/deps/python38/lib/site-packages"
    };
    for (std::string s : li) {
        sys.attr("path").attr("append")(s);
    }
    py::print(sys.attr("path"));

    py::module_ assistant = py::module_::import("assistant");
    py::list result = assistant.attr("test_cpython_api")();
    for (int i = 0; i < PY_LEN(result); ++i) {
        printf("%d, ", result[i].cast<int>());
    }

    return 0;
}