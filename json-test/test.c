#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include "picojson.h"

int main(void)
{
    // JSONデータの読み込み。
    std::ifstream ifs("test.json", std::ios::in);
    if (ifs.fail()) {
        std::cerr << "failed to read test.json" << std::endl;
        return 1;
    }
    const std::string json((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    ifs.close();

    // JSONデータを解析する。
    picojson::value v;
    const std::string err = picojson::parse(v, json);
    if (err.empty() == false) {
        std::cerr << err << std::endl;
        return 2;
    }

    std::cout << "All out" << std::endl;
    std::cout << v << std::endl;
    std::cout << std::endl;

    std::cout << "Look parsed" << std::endl;
    picojson::object& obj = v.get<picojson::object>();
    std::cout << "string: "                         << obj["string"].get<std::string>()       << std::endl;
    std::cout << "number_double: "                  << obj["number_double"].get<double>()     << std::endl;
    std::cout << "number_integer: "                 << obj["number_integer"].get<double>()    << std::endl;
    std::cout << "boolean_true: " << std::boolalpha << obj["boolean_true"].get<bool>()        << std::endl;
    std::cout << "boolean_false: "<< std::boolalpha << obj["boolean_false"].get<bool>()       << std::endl;
    std::cout << "array: ";
    picojson::array& ary = obj["array"].get<picojson::array>();
    for (const auto& e : ary) {  // vectorをrange-based-forでまわしている。
        std::cout << e.get<std::string>() << " ";
    }
    std::cout << "\n\n";

    std::cout << "Loop" << std::endl;
    for (const auto& p : obj) { // mapをrange-based-forでまわしている。
        std::cout << p.first << ": " << p.second.to_str() << std::endl;
    }

    return 0;
}