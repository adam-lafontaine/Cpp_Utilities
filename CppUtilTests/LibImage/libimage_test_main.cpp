#include "../../libimage/libimage.hpp"

#include <iostream>

namespace fs = std::filesystem;
namespace img = libimage;

constexpr auto SRC_IMAGE_PATH = "D:/repos/Cpp_Utilities/CppUtilTests/LibImage/in_files/png/cadillac.png";


int main()
{
	auto image = img::read_image_from_file(fs::path(SRC_IMAGE_PATH));
	auto view = img::make_view(image);

	auto w = view.width();
	auto h = view.height();

	std::cout << "width: " << w << " height: " << h << "\n";
}