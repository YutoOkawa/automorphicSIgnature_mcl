#ifndef INCLUDE_mclutils_h
#define INCLUDE_mclutils_h

#include <mcl/bn256.hpp>
#include <random>
#include <iostream>

using namespace mcl::bn256;

G1 genG1Element();
G2 genG2Element();
void debugG1(std::string str, G1 g);
void debugG2(std::string str, G2 h);
void debugFr(std::string str, Fr fr);
void debugGT(std::string str, Fp12 gt);

#endif