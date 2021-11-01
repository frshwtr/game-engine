//
// Created by ben on 01/11/2021.
//

#include "UnsupportedSource.h"

#include <utility>

UnsupportedSource::UnsupportedSource(std::string description) : m_description(std::move(description)) {}
