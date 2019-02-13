#include<iostream>

#include<tensora/tensor.hpp>
#include<tensora/index.hpp>

int main()
{
	tensora::DimVector vec;
	std::cout << vec.size()<< std::endl;
	vec.resize(1);
	vec[0] = 2;
	vec.resize(2);
	
	std::cout << vec[0] << std::endl;
	return 0;
}