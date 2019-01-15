#!/bin/zsh

mkdir -p test_tmp

echo "Summary: This project is a continuation of the previous encryption project. You will recode part of the OpenSSL program, specifically BASE64, DES-ECB and DES-CBC." > test_tmp/f1

for e in {0..164} ; do cat test_tmp/f1 | head -c $e > test_tmp/f_$e ; done

echo "Test encode without salted and without base64"
for e in {0..164} ; do echo "$e :"; ./ft_ssl des-ecb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 ; openssl des-ecb -in test_tmp/f_$e -out test_tmp/openssl_$e -K 10 ; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "Test encode with salted and without base64"
for e in {0..164} ; do echo "$e :"; ./ft_ssl des-ecb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 ; openssl des-ecb -in test_tmp/f_$e -out test_tmp/openssl_$e -k password -S 10 ; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "Test encode without salted and with base64"
for e in {0..164} ; do echo "$e :"; ./ft_ssl des-ecb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 ; openssl des-ecb -a -in test_tmp/f_$e -out test_tmp/openssl_$e -K 10 ; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "Test encode with salted and with base64"
for e in {0..164} ; do echo "$e :"; ./ft_ssl des-ecb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 ; openssl des-ecb -a -in test_tmp/f_$e -out test_tmp/openssl_$e -k password -S 10 ; diff test_tmp/ft_ssl_$e  test_tmp/openssl_$e; done

echo "Test decode without salted and without base64"
for e in {0..164} ; do echo "$e :"; ./ft_ssl des-ecb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 ; ./ft_ssl des-ecb -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10; openssl des-ecb -d -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -K 10 ; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo "Test decode with salted and without base64"
for e in {0..164} ; do echo "$e :"; ./ft_ssl des-ecb -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 ; ./ft_ssl des-ecb -d -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10; openssl des-ecb -d -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -k password -S 10 ; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo "Test decode without salted and with base64"
for e in {0..164} ; do echo "$e :"; ./ft_ssl des-ecb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -k 10 ; ./ft_ssl des-ecb -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -k 10; openssl des-ecb -d -a -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -K 10 ; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done

echo "Test decode with salted and with base64"
for e in {0..164} ; do echo "$e :"; ./ft_ssl des-ecb -a -i test_tmp/f_$e -o test_tmp/ft_ssl_$e -p password -s 10 ; ./ft_ssl des-ecb -d -a -i test_tmp/ft_ssl_$e -o test_tmp/ft_ssl_decode_$e -p password -s 10; openssl des-ecb -d -a -in test_tmp/ft_ssl_$e -out test_tmp/openssl_decode_$e -k password -S 10; diff test_tmp/ft_ssl_decode_$e  test_tmp/openssl_decode_$e; done
rm -Rf test_tst