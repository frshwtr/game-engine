//
// Created by ben on 01/11/2021.
//

#ifndef GAME_ENGINE_UNSUPPORTEDSOURCE_H
#define GAME_ENGINE_UNSUPPORTEDSOURCE_H

#include <exception>
#include <string>

class UnsupportedSource : public std::exception {
private:
    std::string m_description;
public:
    explicit UnsupportedSource(std::string description);

    std::string what() {
        return this->m_description;
    }
};


#endif //GAME_ENGINE_UNSUPPORTEDSOURCE_H
