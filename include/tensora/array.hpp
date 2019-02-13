#ifndef TENSORA_TENSOR_H
#define TENSORA_TENSOR_H

#include <memory>
#include "type.hpp"

namespace tensora
{
    // The real representation of all tensors.
    template<typename T>
    class ArrayData
    {
    public:
        std::unique_ptr<T[]> data;
        idx_type len;
    };

    enum layout_type
    {
        row_major,
        column_major
    };

    // ndarray
    template<typename T, layout_type layout = layout_type::column_major>
    class Array
    {
    private:
        ArrayData rep;
        idx_type offset;
        StrideVec strides;
        layout_type order;
    public:
        Array()
        {

        }
        template<class... Args>
        T& operator ()(idx_type idx, Args... args)
        {
            
        }

        template<class... Args>
        T& operator ()(idx_type idx, Args... args) const
        {
            
        }
    };
}

#endif