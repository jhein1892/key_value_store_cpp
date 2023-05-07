#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

class KeyPair {
    public:
        KeyPair(std::string filename, std::map<std::string, std::string>& my_map): filename(filename), map(my_map) 
        {
            // When we start a new KeyPair class, we are going to automatically insert the map into a file.
            std::ofstream file(filename);
            if (!file.is_open()){
                std::cerr << "Error could not open file " << filename << std::endl;
                return;                
            }
            
            for (const auto& p : my_map){
                file << p.first << "," << p.second << std::endl;
            }

            file.close();
        }
    private:
        std::string filename;
        std::map<std::string, std::string> map;
};

int main()
{
    std::map<std::string, std::string> user_map;
    user_map["Key1"] = "Val1";
    user_map["Key2"] = "val2";
    user_map["Key3"] = "val3";

    KeyPair newKeyPair("TestFile.txt", user_map);
}