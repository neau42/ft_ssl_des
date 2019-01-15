#!/bin/zsh

mkdir -p test_tmp

echo "Summary: This project is a continuation of the previous encryption project. You will recode part of the OpenSSL program, specifically BASE64, DES-ECB and DES-CBC." > test_tmp/f1

for e in {1..164} ; do cat test_tmp/f1 | head -c $e > test_tmp/f_$e ; done

for e in {1..164} ; do   ; echo "\n\033[95m[$e] ------------\033[0m" ; ./ft_ssl des-ecb -a -i test_tmp/f_$e  -p coucou -s 123 | ./ft_ssl des-ecb -a -p coucou -s 123 -d 2>&- ; done

# rm -Rf test_tst
