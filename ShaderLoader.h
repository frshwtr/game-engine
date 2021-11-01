//
// Created by ben on 01/11/2021.
//

#ifndef GAME_ENGINE_SHADERLOADER_H
#define GAME_ENGINE_SHADERLOADER_H

#include <fstream>
#include <string>

struct ShaderLoader {
protected:
    std::string fromFileSystem(const char *location) {
        std::string buffer;
        std::string src;

        std::ifstream in_file;

        in_file.open(location);
        if (in_file.is_open()) {
            while (std::getline(in_file, buffer)) {
                src += buffer + "\n";
            }
        } else {
            std::cout << std::endl << "ERROR: Could not from source " << location << std::endl;
            in_file.close();
            throw;
        }

        in_file.close();

        return src;
    }

public:
    virtual void load(const char *location) = 0;
};


#endif //GAME_ENGINE_SHADERLOADER_H
