//! \file hello.h
//! \author Benjamin Navarro
//! \brief
//! \date 07-2020

#pragma once

#include <string>

//! \brief Contains functions to say hello to people
namespace hello {

//! \brief Get a greating sentence for a specific person
//!
//! \param name the name of the person to greet
//! \return std::string the greating sentense
std::string getGreeting(const std::string &name);

//! \brief Say hello to someone by printing a customized greeting sentence (see
//! getGreeting) to the console
//!
//! \param name the name of the person to greet
void sayHello(const std::string &name);

} // namespace hello