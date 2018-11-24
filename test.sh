#!/bin/zsh

FILE_FT_MD5="ft_sslMD5.out"
FILE_OP_MD5="opensslMD5.out"
FILE_FT_SHA="ft_sslSHA.out"
FILE_OP_SHA="opensslSHA.out"
TEST_DIR="test/"

if [ $# -ne 1 ] ; then
  echo "usage: $0 nb_files_to_generate"
  exit 1
fi

echo -n "generate $1 random files\n"
for a in {1..$1} ; do
  cat /dev/urandom | base64 -b $(( ( RANDOM % $a ) + 1 )) | head -n $(( ( RANDOM % ( $a / 3 + 1 ) ) + 1 )) > ${TEST_DIR}f_$a
  if [ $(( $a % 10 )) -eq 0 ]; then
    echo -n "."
  fi
done

echo "\n" 
echo "\n - - - - - - - - TEST FILE - - - - - - - - -"
echo "test MD5:" | tee ${TEST_DIR}$FILE_FT_MD5 | tee ${TEST_DIR}$FILE_OP_MD5
a=0

for e in `ls ${TEST_DIR}f_*` ; do
   if [ $(( $a % 10 )) -eq 0 ]; then
    echo -n "."
    fi
  ((a++))
  echo "$e:" >>  ${TEST_DIR}$FILE_FT_MD5  >> ${TEST_DIR}$FILE_OP_MD5;  
  ./ft_ssl md5 -q $e >> ${TEST_DIR}$FILE_FT_MD5
  openssl md5 $e | cut -d' ' -f2 >> ${TEST_DIR}$FILE_OP_MD5
done
echo "\n" 
diff ${TEST_DIR}$FILE_FT_MD5 ${TEST_DIR}$FILE_OP_MD5


echo "test SHA256:" | tee ${TEST_DIR}$FILE_FT_SHA | tee ${TEST_DIR}$FILE_OP_SHA
a=0
for e in `ls ${TEST_DIR}f_*` ; do
  if [ $(( $a % 10 )) -eq 0 ]; then
    echo -n "."
  fi
  ((a++))
  echo "$e:" >>  ${TEST_DIR}$FILE_FT_SHA  >> ${TEST_DIR}$FILE_OP_SHA;
  ./ft_ssl sha256 -q $e >> ${TEST_DIR}$FILE_FT_SHA
  openssl sha256 $e | cut -d' ' -f2 >> ${TEST_DIR}$FILE_OP_SHA
done
echo "\n" 
diff ${TEST_DIR}$FILE_FT_SHA ${TEST_DIR}$FILE_OP_SHA
echo "\n - - - - - - - - TEST STRING - - - - - - - -"

echo "test MD5:" | tee ${TEST_DIR}$FILE_FT_MD5 | tee ${TEST_DIR}$FILE_OP_MD5
a=0
for e in  `ls ${TEST_DIR}f_*` ; do
  if [ $(( $a % 10 )) -eq 0 ]; then
    echo -n "."
  fi
  ((a++))
  str="`cat $e`";
  echo "$e:" >>  ${TEST_DIR}$FILE_FT_MD5  >> ${TEST_DIR}$FILE_OP_MD5 2>&1;
  ./ft_ssl md5 -q -s $str >> ${TEST_DIR}$FILE_FT_MD5 2>&1;
  md5 -q -s $str >> ${TEST_DIR}$FILE_OP_MD5 2>&1;
done
echo "\n" 
diff ${TEST_DIR}$FILE_FT_MD5 ${TEST_DIR}$FILE_OP_MD5


echo "test SHA:" | tee ${TEST_DIR}$FILE_FT_SHA | tee ${TEST_DIR}$FILE_OP_SHA
a=0
for e in  `ls ${TEST_DIR}f_*` ; do
  if [ $(( $a % 10 )) -eq 0 ]; then
    echo -n "."
  fi
  ((a++))
  str="`cat $e`";
  echo "$e:" >>  ${TEST_DIR}$FILE_FT_SHA  >> ${TEST_DIR}$FILE_OP_SHA 2>&1;
  ./ft_ssl sha256 -q -s $str >> ${TEST_DIR}$FILE_FT_SHA 2>&1;
  echo -n "`cat $e`" | shasum -a 256 | cut -d' ' -f1 >> ${TEST_DIR}$FILE_OP_SHA 2>&1;
done
echo "\n" 
diff ${TEST_DIR}$FILE_FT_SHA ${TEST_DIR}$FILE_OP_SHA

#rm ${TEST_DIR}f_*
#rm $FILE_FT_MD5 ft_sslSHA  $FILE_OP_MD5 opensslSHA
