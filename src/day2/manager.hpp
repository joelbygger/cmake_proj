//
// Created by joel on 2019-03-11.
//

#ifndef CMAKE_TEMPLATE_CPP_PROJ_MANAGER_HPP
#define CMAKE_TEMPLATE_CPP_PROJ_MANAGER_HPP

#include <string>
#include <tuple>
#include <vector>

namespace manager
{
    std::tuple<int, std::string> manager(const std::vector<std::string>& ids);
} // namespace manager

#endif // CMAKE_TEMPLATE_CPP_PROJ_MANAGER_HPP
