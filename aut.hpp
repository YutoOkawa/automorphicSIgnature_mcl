#ifndef INCLUDED_aut_h_
#define INCLUDED_aut_h_

#include "mclutils.hpp"

using namespace mcl::bn256;

struct Param {
    G1 G, F, K, T;
    G2 H;
};

struct VerKey {
    G1 X;
    G2 Y;
};

struct MsgSpace {
    G1 M;
    G2 N;
};

struct Signature {
    G1 A, C, R;
    G2 D, S;
};

class aut
{
    private:
        //parameter pp = {G, H, F, K, T}
        Param param;

        // verificationKey vk = {G^x, H^x}
        VerKey verKey;

        // MessageSpace (M, N) = (G^m, H^m)
        MsgSpace msgSpc;

        // Sign sig = {A, C, D, R, S}
        Signature sign;

    public:
        void init();
        void setup();
        Fr keyGen();
        Signature genSign(Fr sk, std::string msg);
        bool verify(VerKey verkey, std::string msg, Signature sign);
        void createMsg(std::string msg);
        Param getParam();
        VerKey getVerKey();
        MsgSpace getMsg();
        Signature getSig();
};

void debugParam(Param param);
void debugVerKey(VerKey verkey);
void debugSign(Signature sign);
bool checkPairing(Fp12 gt1, Fp12 gt2, std::string str);

#endif