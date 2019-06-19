# FT_SSL
An introduction to cryptographic hashing algorithms and symmetric encoding and encryption

#### hasing:
md5 - sha256

#### Encrypt:
base64 - des - des-ecb - des-cbc - des-cfb - des-ctr - des-pcbc


#### Usage:
```
usage:
./ft_ssl <md5|sha256|des|des-ecb|des-cbc|des-cfb|des-ctr|des-pcbc> [options] file ...
Standard commands:

Standard options:
 -h: help.

Message Digest commands:
 md5: to use the md5 message digest algorithm.
 sha256: to use the sha256 message digest algorithm.

Message Digest options:
 -D: debug, print chuck.
 -p: echo STDIN to STDOUT and append the checksum to STDOUT.
 -q: quiet mode.
 -r: reverse the format of the output.
 -s: print the sum of the given string.

Cipher commands:
 base64
 des (des-cbc)
 des-ecb (Electronic Code Book)
 des-cbc (Cipher Block Chaining)
 des-cfb (Cipher Feedback)
 des-ctr (CounTeR)
 des-pcbc (Propagating Cipher Block Chaining)

Cipher options:
base64:
 -d: decode mode.
 -e: encode mode.
 -i: input file.
 -o: output file.
des*:
 -a: decode/encode the input/output in base64,depending on the encrypt mode.
 -d: decrypt mode.
 -e: encrypt mode (default).
 -i: input file for message.
 -k: key in hex is the next arguement.
 -o: output file for message.
 -p: password in ascii is the next argument.
 -P: print the Vector/Key/Salt/Pass
 -s: the salt in hex is the next argument.
 -v: initialization vector in hex is the next argument.
```


works like standard OPENSSL
```
~/ft_ssl_des(master) » cat my_file
Hello world

~/ft_ssl_des(master) » ./ft_ssl des-ecb -p coucou -s 123 -i my_file -o encrypted_file

~/ft_ssl_des(master*) » cat encrypted_file
Salted__0M�C���,:&s<*ϰ%

~/ft_ssl_des(master*) » openssl des-ecb -d -k coucou -S 123 -in encrypted_file
Hello world

```
