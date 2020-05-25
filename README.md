# 概要
Automorphic Signatureのアルゴリズムを検証するプログラム

# 使用ライブラリ
[mcl]{https://github.com/herumi/mcl} - C++ pairing library

# Usage
```
g++ main.cpp mclutils.cpp aut.cpp -I{mclのインクルードパス} -L{mclのライブラリパス} -lmcl -lgmp
./a.out
```