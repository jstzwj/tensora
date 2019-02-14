#ifndef TENSORA_STRIDES_H
#define TENSORA_STRIDES_H

#include <cstdint>
#include <cstring>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <utility>
#include "type.hpp"

#define STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION 4

namespace tensora
{
    class StrideVector
    {
    private:
        std::unique_ptr<size_type[]> data;
        size_type stack_data[STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION];
        idx_type strides_size;
    public:
        StrideVector()
            :data(nullptr), strides_size(0)
        {
        }

        StrideVector(idx_type size)
        {
            if(size < 0)
                return;
            if(size > STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                data = std::make_unique<idx_type[]>(size);
            }
            
            strides_size = size;
        }

        StrideVector(const StrideVector& other)
        {
            if(other.strides_size > STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                data = std::make_unique<idx_type[]>(other.strides_size);
                std::memcpy(data.get(), other.data.get(), other.strides_size * sizeof(idx_type));
            }
            else
            {
                std::memcpy(stack_data, other.stack_data, other.strides_size * sizeof(idx_type));
            }
            strides_size = other.strides_size;
        }

        StrideVector(StrideVector&& other)
        {
            if(other.strides_size > STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                data = std::move(other.data);
            }
            else
            {
                std::memcpy(stack_data, other.stack_data, other.strides_size * sizeof(idx_type));
            }
            strides_size = other.strides_size;
        }

        StrideVector& operator=(const StrideVector& other) noexcept
        {
            if(other.strides_size > STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                data = std::make_unique<idx_type[]>(other.strides_size);
                std::memcpy(data.get(), other.data.get(), other.strides_size * sizeof(idx_type));
            }
            else
            {
                std::memcpy(stack_data, other.stack_data, other.strides_size * sizeof(idx_type));
            }
            strides_size = other.strides_size;
            return *this;
        }

        StrideVector& operator=(StrideVector&& other) noexcept
        {
            if(other.strides_size > STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                data = std::move(other.data);
            }
            else
            {
                std::memcpy(stack_data, other.stack_data, other.strides_size * sizeof(idx_type));
            }
            strides_size = other.strides_size;
            return *this;
        }

        void push_back(size_type stride)
        {
            resize(size() + 1);
            this->operator[](size() - 1) = stride;
        }

        void resize(idx_type size)
        {
            if(size < 0 || size == strides_size)
                return;
            if(size > STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION)
            {
                if(strides_size > STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION)
                {
                    idx_type move_size = (size > strides_size ? strides_size: size);
                    std::unique_ptr<idx_type[]> temp(new idx_type[size]);
                    std::memcpy(temp.get(), data.get(), move_size * sizeof(idx_type));
                    data = std::move(temp);
                }
                else
                {
                    data = std::unique_ptr<idx_type[]>(new idx_type[size]);
                    std::memcpy(data.get(), stack_data, strides_size * sizeof(idx_type));
                }
            }
            else
            {
                if(strides_size > STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION)
                {
                    data = std::unique_ptr<idx_type[]>(nullptr);
                    if (size != 0)
                        std::memcpy(stack_data, data.get(), size * sizeof(idx_type));
                }
            }
            strides_size = size;
        }

        idx_type size() const { return this->strides_size; }

        size_type& operator[](idx_type dim)
        {
            if(dim<0 || dim >= strides_size)
                throw std::runtime_error("index out of dim vector size");
            
            if(strides_size > STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION)
                return data[dim];
            else
                return stack_data[dim];
        }

        size_type operator[](idx_type dim) const
        {
            if(dim<0 || dim >= strides_size)
                throw std::runtime_error("index out of dim vector size");
            
            if(strides_size > STRIDEVECTOR_SMALL_VECTOR_OPTIMIZATION)
                return data[dim];
            else
                return stack_data[dim];
        }
    };
}

#endif