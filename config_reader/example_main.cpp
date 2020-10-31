#include "config_reader.hpp"

#include <iostream>

namespace cr = config_reader;

void print_config(cr::config_t const& config)
{
    for (auto const& pair : config)
    {
        std::cout << pair.first << " : " << pair.second << '\n';
    }
    std::cout<<'\n';
}


int main()
{
    const auto file_path = "config_file.txt";

    auto config = cr::read_config(file_path);
    print_config(config);

    cr::key_list_t required = { "ALPHA_PATH", "PROJECT_ROOT", "MODEL_ROOT" };
    config = cr::read_config(file_path, required);
    print_config(config);

    required = { "ALPHA_PATH", "PROJECT_ROOT", "MODEL_ROOT", "ANOTHER_KEY" };
    config = cr::read_config(file_path, required);
    print_config(config);    
}