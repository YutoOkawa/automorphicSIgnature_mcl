#include "aut.hpp"

int main() {
    aut aut;
    Fr sk;
    Param param;
    VerKey verkey;
    Signature sign;

    aut.init();
    // Setup(1^λ)
    aut.setup();
    param = aut.getParam();
    debugParam(param);

    // Key generation(pp)
    sk = aut.keyGen();
    verkey = aut.getVerKey();
    debugVerKey(verkey);

    // Sign(pp, sk, (M,N))
    sign = aut.genSign(sk, "Hello World!");
    debugSign(sign);

    // Ver(pp, (X,Y), (M,N), (A,C,D,R,S))
    printf("%s\n", aut.verify(verkey, "Hello World!", sign) ? "ok" : "ng");
}