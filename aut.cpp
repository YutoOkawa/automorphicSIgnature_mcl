#include "aut.hpp"

void aut::init()
{
    printf("\n-----Pairing Library mcl-bn256 initialize-----\n");
    initPairing();
}

void aut::setup()
{
    printf("\n-----AutomorphicSignature Setup-----\n");
    this->param.G = genG1Element();
    this->param.H = genG2Element();
    this->param.F = genG1Element();
    this->param.K = genG1Element();
    this->param.T = genG1Element();

    printf("Generate Parameters = {G, H, F, K, T}\n");
}

Fr aut::keyGen()
{
    printf("\n-----AutomorphicSingature KeyGeneration-----\n");
    // Signing Key sk = x
    Fr sk;
    sk.setByCSPRNG();

    // Verification Key vk = {G^x, G^x}
    G1::mul(this->verKey.X, this->param.G, sk);
    G2::mul(this->verKey.Y, this->param.H, sk);
    return sk;
}

Signature aut::genSign(Fr sk, std::string msg)
{
    printf("\n-----AutomorphicSingature Signing-----\n");
    Fr a, divA, c, r;
    G1 rT;
    // Message = (M,N)
    this->createMsg(msg);

    // choose c,r ← Zp
    c.setByCSPRNG();
    r.setByCSPRNG();

    // Sign = A, C, D, R, S
    // A = (1/x+c)(K + rT + M)
    Fr::add(a, sk, c);
    Fr::div(divA, 1, a);
    G1::mul(rT, this->param.T, r);
    G1::add(this->sign.A, this->param.K, rT);
    G1::add(this->sign.A, this->sign.A, this->msgSpc.M);
    G1::mul(this->sign.A, this->sign.A, divA);

    // C = cF, D = cH, R = rG, S = rH
    G1::mul(this->sign.C, this->param.F, c);
    G2::mul(this->sign.D, this->param.H, c);
    G1::mul(this->sign.R, this->param.G, r);
    G2::mul(this->sign.S, this->param.H, r);
    return this->sign;
}

bool aut::verify(VerKey verkey, std::string msg, Signature sign)
{
    printf("\n-----AutomorphicSingature Verification-----\n");
    G1 KM;
    G2 YD;
    Fp12 pairAYD, pairKMH, pairTS, pairKMHTS, pairCH, pairFD, pairRH, pairGS;

    // Message = (M,N)
    this->createMsg(msg);

    // Verification e(C,H) == e(F,D) ??
    pairing(pairCH, sign.C, this->param.H);
    pairing(pairFD, param.F, sign.D);
    if (!checkPairing(pairCH, pairFD, "e(C,H) == e(F,D)")) {
        return false;
    }

    // Verification e(R,H) == e(G,S) ??
    pairing(pairRH, sign.R, this->param.H);
    pairing(pairGS, this->param.G, sign.S);
    if (!checkPairing(pairRH, pairGS, "e(R,H) == e(G,S)")) {
        return false;
    }

    // e(A,Y+D) = e(K+M,H)e(T,S)
    G2::add(YD, verkey.Y, sign.D);
    pairing(pairAYD, sign.A, YD);
    G1::add(KM, this->param.K, this->msgSpc.M);
    pairing(pairKMH, KM, this->param.H);
    pairing(pairTS, this->param.T, sign.S);
    GT::mul(pairKMHTS, pairKMH, pairTS);
    if (!checkPairing(pairAYD, pairKMHTS, "e(A,Y+D) == e(K+M,H)e(T,S)")) {
        return false;
    }

    return true;
}

void aut::createMsg(std::string msg) {
    Fr msgHash;
    msgHash.setHashOf(msg);
    G1::mul(this->msgSpc.M, this->param.G, msgHash);
    G2::mul(this->msgSpc.N, this->param.H, msgHash);
}

Param aut::getParam()
{
    return this->param;
}

VerKey aut::getVerKey()
{
    return this->verKey;
}

Signature aut::getSig()
{
    return this->sign;
}

void debugParam(Param param) {
    debugG1("Param['G'] = ", param.G);
    debugG2("Param['H'] = ", param.H);
    debugG1("Param['F'] = ", param.F);
    debugG1("Param['K'] = ", param.K);
    debugG1("Param['T'] = ", param.T);
}

void debugVerKey(VerKey verkey) {
    debugG1("VerKey['X'] = ", verkey.X);
    debugG2("VerKey['Y'] = ", verkey.Y);
}

void debugSign(Signature sign) {
    debugG1("Sign['A'] = ", sign.A);
    debugG1("Sign['C'] = ", sign.C);
    debugG2("Sign['D'] = ", sign.D);
    debugG1("Sign['R'] = ", sign.R);
    debugG2("Sign['S'] = ", sign.S);
}

bool checkPairing(Fp12 gt1, Fp12 gt2, std::string str) {
    printf("CHECK %s ?? : ", str.c_str());
    if (gt1 != gt2) {
        printf("NG\n");
        return false;
    }
    printf("OK\n");
    return true;
}
