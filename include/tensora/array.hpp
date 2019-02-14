#ifndef TENSORA_TENSOR_H
#define TENSORA_TENSOR_H

#include <memory>
#include "type.hpp"
#include "strides.hpp"
#include "utils.hpp"

namespace tensora
{
    // The real representation of all tensors.
    template<typename T>
    class ArrayData
    {
    public:
        std::unique_ptr<T[]> data;
        idx_type len;
        ArrayData()
            :data(nullptr), len(0)
        {

        }

        void resize(idx_type size)
        {
            if(size < 0 || size == len)
                return;
            idx_type move_size = (size > len ? len: size);
            std::unique_ptr<T[]> temp(new idx_type[size]);
            std::memcpy(temp.get(), data.get(), move_size * sizeof(idx_type));
            data = std::move(temp);

            len = size;
        }

        void resize(const DimVector& dimensions)
        {
            idx_type size = 1;
            for(idx_type i = 0; i < dimensions.size(); ++i)
            {
                size *= dimensions[i];
            }

            if(size < 0 || size == len)
                return;
            idx_type move_size = (size > len ? len: size);
            std::unique_ptr<T[]> temp(new idx_type[size]);
            std::memcpy(temp.get(), data.get(), move_size * sizeof(idx_type));
            data = std::move(temp);

            len = size;
        }
    };

    enum layout_type
    {
        row_major,
        column_major
    };

    // ndarray
    template<typename T>
    class Array
    {
    private:
        std::shared_ptr<ArrayData<T>> rep;
        DimVector dimensions;
        idx_type offset;
		StrideVector strides;
        layout_type order;
    private:
        void auto_strides()
        {
            idx_type dim_num = dimensions.size();
            strides.resize(dim_num);
            size_type stride = 1;
            if(order == layout_type::column_major)
            {
                for(idx_type i = 0; i < dim_num; ++i)
                {
                    strides[i] = stride * sizeof(T);
                    stride *= dimensions[i];
                }
            }
            else
            {
                for(idx_type i = dim_num - 1; i >= 0; --i)
                {
                    strides[i] = stride * sizeof(T);
                    stride *= dimensions[i];
                }
            }
        }
    public:
        Array()
            :rep(new ArrayData<T>),
            dimensions(), offset(0), strides(), order(layout_type::column_major)
        {
        }

        explicit Array(const DimVector& dimensions)
            :rep(new ArrayData<T>),
            dimensions(dimensions), offset(0), strides(), order(layout_type::column_major)
        {
            auto_strides();
        }

        explicit Array(const DimVector& dimensions, layout_type order)
            :rep(new ArrayData<T>),
            dimensions(dimensions), offset(0), strides(), order(order)
        {

        }

        explicit Array(const DimVector& dimensions, const StrideVector& strides)
            :rep(new ArrayData<T>),
            dimensions(dimensions), offset(0), strides(strides), order(layout_type::column_major)
        {
            auto_strides();
        }

        explicit Array(const DimVector& dimensions, const StrideVector& strides, layout_type order)
            :rep(new ArrayData<T>),
            dimensions(dimensions), offset(0), strides(strides), order(order)
        {

        }

        Array(const T& t)
            :rep(new ArrayData<T>),
            dimensions(), offset(0), strides(), order(order)
        {
            dimensions.resize(1);
            auto_strides();
        }

        Array(nested_initializer_list_t<T, 1> t)
            :rep(new ArrayData<T>),
            dimensions(), offset(0), strides(), order(order)
        {
            dimensions.resize(1);
            auto_strides();
        }
        Array(nested_initializer_list_t<T, 2> t)
            :rep(new ArrayData<T>),
            dimensions(), offset(0), strides(), order(order)
        {
            dimensions.resize(2);
            auto_strides();
        }

        Array(nested_initializer_list_t<T, 3> t)
            :rep(new ArrayData<T>),
            dimensions(), offset(0), strides(), order(order)
        {
            dimensions.resize(3);
            auto_strides();
        }
        Array(nested_initializer_list_t<T, 4> t)
            :rep(new ArrayData<T>),
            dimensions(), offset(0), strides(), order(order)
        {
            dimensions.resize(4);
            auto_strides();
        }
        Array(nested_initializer_list_t<T, 5> t)
            :rep(new ArrayData<T>),
            dimensions(), offset(0), strides(), order(order)
        {
            dimensions.resize(5);
            auto_strides();
        }

        void reshape(std::initializer_list<idx_type> t)
        {

        }

        Array& operator ()(idx_type idx)
        {
            
        }

        template<class... Args>
        Array& operator ()(idx_type idx, Args... args)
        {
            
        }

        template<class... Args>
        const Array& operator ()(idx_type idx, Args... args) const
        {
            
        }
    };
}

#endif