cmake_minimum_required(VERSION 3.15)
project(cpptest)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpptest main.cpp derived.hpp weipai.hpp initialize_list_y.hpp rvalue.hpp constexpression.hpp getInteger.hpp smart_pointer.hpp move_operator.hpp leetcode1.hpp mutex_usage.hpp regex_usage.hpp explicit_usage.hpp cs106_1search.hpp leetcode2_supereggdrop.hpp cs106_2operator.hpp cs106_3template.hpp cs106_4inherit.hpp cs106_3templatetemplate.hpp)