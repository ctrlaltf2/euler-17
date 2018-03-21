#include <functional>
#include <iostream>
#include <map>
#include <string>

#include <boost/program_options.hpp>

#include "Problems.h"

#define P(D) \
    { #D, D }

int main(int argc, char** argv) {
    using namespace boost;
    const std::map<std::string, std::function<void(std::ostream&)>> funcMap = {
        P(p1),  P(p1l), P(p2),  P(p2l), P(p3),  P(p4),  P(p5),
        P(p6),  P(p7),  P(p8),  P(p9),  P(p10), P(p11), P(p12),
        P(p13), P(p14), P(p15), P(p16), P(p17)};
    try {
        program_options::options_description desc{"Options"};
        desc.add_options()("help,h", "Help")("problem,p",
                                             program_options::value<int>(),
                                             "Problem")("lazy,l", "Lazy");

        program_options::variables_map vm;
        program_options::store(
            program_options::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            std::cout << desc << '\n';
            return 0;
        }

        std::string mapkey = "p";
        if (vm.count("problem"))
            mapkey += std::to_string(vm["problem"].as<int>());
        else {
            std::cout << "A problem number is required" << '\n';
            return -1;
        }

        if (vm.count("lazy")) mapkey += 'l';

        try {
            (funcMap.at(mapkey))(std::cout);
        } catch (const std::out_of_range& e) {
            std::cout << "Problem hasn't been implemented yet " << '\n';
            std::cout << desc << '\n';
            return -1;
        }
    } catch (const program_options::error& e) {
        std::cout << e.what() << '\n';
    }
}
