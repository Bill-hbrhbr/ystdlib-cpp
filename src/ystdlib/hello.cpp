#include <iostream>
#include <string>
#include <vector>
#include <ystdlib/array/Array.hpp>
#include <ystdlib/hello/hello.hpp>

[[nodiscard]] auto main() -> int {
    ystdlib::Array<std::string> a{4};
    std::vector<std::string> const
            std_vector{"yscope", "clp", "clp::Array", "default_initializable"};
    std::copy(std_vector.cbegin(), std_vector.cend(), a.begin());
    for (auto const& item : a) {
        std::cout << item << '\n';
    }

    std::cout << ystdlib::hello() << '\n';
    return 0;
}
