#ifndef TENSORA_INDEX_H
#define TENSORA_INDEX_H

#include <cstdint>
#include <cstring>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <utility>
#include "type.hpp"

#define DIMVECTOR_SMALL_VECTOR_OPTIMIZATION 4

namespace tensora
{
    class DimVector
    {
    private:
        std::unique_ptr<idx_type[]> data;
        idx_type stack_data[DIMVECTOR_SMALL_VECTOR_OPTIMIZATION];
        idx_type dim_num;
    private:
        idx_type* get_data()
        {
            if(dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                return data.get();
            else
                return stack_data;
        }

        const idx_type* get_data() const
        {
            if(dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                return data.get();
            else
                return stack_data;
        }
    public:
        DimVector()
            :data(nullptr), dim_num(0)
        {
        }

        DimVector(idx_type size)
        {
            if(size < 0)
                return;
            if(size > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                data = std::make_unique<idx_type[]>(size);
            }
            
            dim_num = size;
        }

        void push_back(idx_type idx)
        {

        }

        void resize(idx_type size)
        {
            if(size < 0 || size == dim_num)
                return;
            if(size > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                if(dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                {
                    idx_type move_size = (size > dim_num ? dim_num: size);
                    std::unique_ptr<idx_type[]> temp(new idx_type[size]);
                    std::memcpy(temp.get(), data.get(), move_size * sizeof(idx_type));
                    data = std::move(temp);
                }
                else
                {
                    data = std::unique_ptr<idx_type[]>(new idx_type[size]);
                    std::memcpy(data.get(), stack_data, dim_num * sizeof(idx_type));
                }
            }
            else
            {
                if(dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                {
                    data = std::unique_ptr<idx_type[]>(nullptr);
                    std::memcpy(stack_data, data.get(), size * sizeof(idx_type));
                }
            }
            dim_num = size;
        }

        idx_type size() const { return this->dim_num; }

        idx_type& operator[](idx_type dim)
        {
            if(dim<0 || dim >= dim_num)
                throw std::runtime_error("index out of dim vector size");
            
            if(dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                return data[dim];
            else
                return stack_data[dim];
        }

        idx_type operator[](idx_type dim) const
        {
            if(dim<0 || dim >= dim_num)
                throw std::runtime_error("index out of dim vector size");
            
            if(dim_num > DIMVECTOR_SMALL_VECTOR_OPTIMIZATION)
                return data[dim];
            else
                return stack_data[dim];
        }
    };
}

#endif