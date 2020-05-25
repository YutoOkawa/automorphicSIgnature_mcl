#ifndef INCLUDED_aut_h_
#define INCLUDED_aut_h_

#include "mclutils.hpp"

struct Param {
    mcl::bn256::G1 G, F, K, T;
    mcl::bn256::G2 H;
};

struct VerKey {
    mcl::bn256::G1 X;
    mcl::bn256::G2 Y;
};

struct MsgSpace {
    mcl::bn256::G1 M;
    mcl::bn256::G2 N;
};

struct Signature {
    mcl::bn256::G1 A, C, R;
    mcl::bn256::G2 D, S;
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
        mcl::bn256::Fr keyGen();
        Signature genSign(mcl::bn256::Fr sk, std::string msg);
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
bool checkPairing(mcl::bn256::Fp12 gt1, mcl::bn256::Fp12 gt2, std::string str);

#endif