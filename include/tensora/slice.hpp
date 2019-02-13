#ifndef TENSORA_SLICE_H
#define TENSORA_SLICE_H

#include <memory>
#include "type.hpp"

namespace tensora
{
    struct Slice
    {
        idx_type min;
        idx_type max;
        idx_type step;
    };
}

#endif