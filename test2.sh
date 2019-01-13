#!/bin/zsh

mkdir -p test_tmp

echo "Summary: This project is a continuation of the previous encryption project. You will recode part of the OpenSSL program, specifically BASE64, DES-ECB and DES-CBC." > test_tmp/f1

for e in {1..100} ; do cat test_tmp/f1 | head -c $e > test_tmp/f_$e ; done

for e in {1..100} ; do ./ft_ssl des-ecb -a -i test_tmp/f_$e  -p coucou -s 123 | ./ft_ssl des-ecb -a -p coucou -s 123 -d  ; echo "\n$e --------" ; done

rm -Rf test_tst
