#include <boost/property_tree/ptree.hpp>                                                                                                
#include <boost/property_tree/detail/file_parser_error.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>                                                                         
#include <string>

using namespace std;

namespace pt = boost::property_tree;

int check(const string& name_file) { //функция проверяет на наличие нужного файла проверка на путь. Функция которая будет проверять путь.
    try {
        if (std::ifstream(name_file)) {
            return 0;
        }
        else {
            cout << "File not find!!!";
            return -1;
        }
    }
    catch (...) {
        std::cout << "Failed !!!";
        return -1;
    }
}

int output_key_value(const string& name_file) {
    pt::ptree jsontree;
    read_json(name_file, jsontree);
    pt::ptree::const_assoc_iterator it;
    it = jsontree.find("product");
    if (it != jsontree.not_found()) {
        string version = jsontree.get<string>("version");  //read and save the roll no in *roll*
        string  product = jsontree.get<string>("product");  //read and save the name in *name*
        cout << "key:" << " " << "product" << "  " << "value:" << " " << product << endl;      //getting the output of all
        cout << "key:" << " " << "version" << "  " << "value:" << " " << version << endl;
        pt::ptree::const_assoc_iterator iterator;
        iterator = jsontree.find("LPR");
        if (iterator != jsontree.not_found()) {
            for (pt::ptree::value_type& v : jsontree.get_child("LPR"))
            {
                cout << "key:" << " " << v.first << "  " << "value:" << " " << v.second.data() << endl;
            }
            return 0;
        }
        else {
            cout << "LPR not find";
        }
    }
    else {
        cout << "product not find";
        return -1;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 1 || argc > 2) {
        cout << "Error!";
        return -1;
    }
    else {
        const string name_file(argv[1]);
        if (check(name_file) == -1) {
            return -1;
        }
        else {
            return output_key_value(name_file);
        }
    }
}