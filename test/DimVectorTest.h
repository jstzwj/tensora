#include<tensora/tensor.hpp>

TEST_CASE( "DimVector Size", "[DimVector]" ) {
    tensora::DimVector vec;

    SECTION( "not set size" ) {
        REQUIRE( vec.size() == 0 );
    }

    SECTION( "resize positive number" ) {
        vec.resize(5);
        REQUIRE( vec.size() == 5 );
    }

    SECTION( "resize zero number" ) {
        vec.resize(0);
        REQUIRE( vec.size() == 0 );
    }

    SECTION( "resize negative number" ) {
        vec.resize(-3);
        REQUIRE( vec.size() == 0 );
    }
}

TEST_CASE( "DimVector push back", "[DimVector]" ) {
    tensora::DimVector vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    SECTION( "size check" ) {
        REQUIRE( vec.size() == 3 );
    }

    SECTION( "value check" ) {
        REQUIRE( vec[2] == 3 );
        REQUIRE( vec[1] == 2 );
        REQUIRE( vec[0] == 1 );
    }
}