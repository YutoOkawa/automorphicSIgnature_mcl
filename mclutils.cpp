#include "mclutils.hpp"

using namespace mcl::bn256;

G1 genG1Element() {
    G1 P;
    std::random_device rd;
    int p_init = rd();
    BN::mapToG1(P, p_init);
    return P;
}

G2 genG2Element() {
    G2 Q;
    std::random_device rd;
    int q_init = rd();
    BN::mapToG2(Q, q_init);
    return Q;
}

void debugG1(std::string str, G1 g) {
    std::cout << str << g << std::endl;
}

void debugG2(std::string str, G2 h) {
    std::cout << str << h << std::endl;
}

void debugFr(std::string str, Fr fr) {
    std::cout << str << fr << std::endl;
}

void debugGT(std::string str, Fp12 gt) {
    std::cout << str << gt << std::endl;
}
