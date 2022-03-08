/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * uniform_matrix.cc
 */

#pragma once
#include <bits/c++config.h>
#include <stdexcept>
#include <ostream>
#ifndef _BRANDON_UNIFORM_MATRIX_C
#define _BRANDON_UNIFORM_MATRIX_C

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "uniform_matrix.h"
using bp::_uniform_matrix_row;
using bp::uniform_matrix;

// Defs for _uniform_matrix_row
template<typename _Tp, const std::size_t _Sz>
_uniform_matrix_row<_Tp,_Sz>::_uniform_matrix_row() 
    : elements{new _Tp[_Sz]}, current_cell_index{0} {}

template<typename _Tp, const std::size_t _Sz>
_uniform_matrix_row<_Tp,_Sz>::~_uniform_matrix_row() { delete[] elements; }

template<typename _Tp, const std::size_t _Sz>
const std::size_t _uniform_matrix_row<_Tp,_Sz>::size() const { return _Sz; }

template<typename _Tp, const std::size_t _Sz>
_Tp& _uniform_matrix_row<_Tp, _Sz>::operator[](const int& index) const 
{ return elements[index]; }

template<typename _Tp, const std::size_t _Sz>
void _uniform_matrix_row<_Tp, _Sz>::push_back(const _Tp& new_element) {
    try {
        elements[current_cell_index] = new_element;
    }
    catch (const std::out_of_range&) {
        std::cerr << "_uniform_matrix_row range error: push_back cannot assign "
            "cell index " << current_cell_index << "; out_of_range of size " <<
                int(_Sz) << std::endl;
        
        return;
    }
    catch (...) {
        std::cerr << "_uniform_matrix_row unexpected error" << std::endl;
        
        return;
    }

    ++current_cell_index;
}

// Defs for uniform_matrix
template<typename _Tp, const std::size_t _Sz>
uniform_matrix<_Tp, _Sz>::uniform_matrix() 
    : inner_rows{new _uniform_matrix_row<_Tp, _Sz>[_Sz]}, 
        current_row_index{0} {}

template<typename _Tp, const std::size_t _Sz>
uniform_matrix<_Tp, _Sz>::~uniform_matrix() = default;

template<typename _Tp, const std::size_t _Sz>
const std::size_t uniform_matrix<_Tp, _Sz>::size() const { return _Sz; }

template<typename _Tp, const std::size_t _Sz>
_uniform_matrix_row<_Tp, _Sz>& uniform_matrix<_Tp, _Sz>::operator[](
    const int& index) const { return inner_rows[index]; }




#endif // _BRANDON_UNIFORM_MATRIX_C