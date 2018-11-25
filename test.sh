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

mkdir $TEST_DIR 2>&-

echo -n "generate $1 random files\n"
for a in {1..$1} ; do
  cat /dev/urandom | base64 -b $(( ( RANDOM % $a ) + 1 )) | head -n $(( ( RANDOM % ( $a / 3 + 1 ) ) + 1 )) > ${TEST_DIR}f_$a
  if [ $(( $a % 10 )) -eq 0 ]; then
    echo -n "."
  fi
done
echo "\n\033[92m - - - - - - - - TEST FILE - - - - - - - - -\033[0m"
echo "\033[93mtest MD5:\033[0m" | tee ${TEST_DIR}$FILE_FT_MD5 | tee ${TEST_DIR}$FILE_OP_MD5
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

if [ "`diff -q ${TEST_DIR}$FILE_FT_MD5 ${TEST_DIR}$FILE_OP_MD5`" = "" ]; then
	echo "no Diff, greats!"
else
	echo "Diff:"
	diff ${TEST_DIR}$FILE_FT_MD5 ${TEST_DIR}$FILE_OP_MD5
fi



echo "\033[93mtest SHA\033[0m:" | tee ${TEST_DIR}$FILE_FT_SHA | tee ${TEST_DIR}$FILE_OP_SHA
a=0
for e in `ls ${TEST_DIR}f_*` ; do
  if [ $(( $a % 10 )) -eq 0 ]; then
    echo -n "."
  fi
  ((a++))
  echo "$e:" >>  ${TEST_DIR}$FILE_FT_SHA  >> ${TEST_DIR}$FILE_OP_SHA;
  ./ft_ssl sha256 -q $e >> ${TEST_DIR}$FILE_FT_SHA
  shasum -a 256 $e | cut -d' ' -f1 >> ${TEST_DIR}$FILE_OP_SHA
done
echo "\n" 

if [ "`diff -q ${TEST_DIR}$FILE_FT_SHA ${TEST_DIR}$FILE_OP_SHA`" = "" ]; then
	echo "no Diff, greats!"
else
	echo "Diff:"
	diff ${TEST_DIR}$FILE_FT_SHA ${TEST_DIR}$FILE_OP_SHA
fi


echo "\n\033[92m - - - - - - - - TEST STRING - - - - - - - -\033[0m"

echo "\033[93mtest MD5:\033[0m" | tee ${TEST_DIR}$FILE_FT_MD5 | tee ${TEST_DIR}$FILE_OP_MD5
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

if [ "`diff -q ${TEST_DIR}$FILE_FT_MD5 ${TEST_DIR}$FILE_OP_MD5`" = "" ]; then
	echo "no Diff, greats!"
else
	echo "Diff:"
	diff ${TEST_DIR}$FILE_FT_MD5 ${TEST_DIR}$FILE_OP_MD5
fi



echo "\033[93mtest SHA:\033[0m" | tee ${TEST_DIR}$FILE_FT_SHA | tee ${TEST_DIR}$FILE_OP_SHA
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


if [ "`diff -q ${TEST_DIR}$FILE_FT_SHA ${TEST_DIR}$FILE_OP_SHA`" = "" ]; then
	echo "no Diff, greats!"
else
	echo "Diff:"
	diff ${TEST_DIR}$FILE_FT_SHA ${TEST_DIR}$FILE_OP_SHA
fi


rm ${TEST_DIR}f_*
#rm $FILE_FT_MD5 ft_sslSHA  $FILE_OP_MD5 opensslSHA
#
#
#

echo "\033[92m\n\n- - - - - - SUBJECT EXAMPLE - - - - - -\033[0m"

echo "pickle rick" | ./ft_ssl md5
echo ""
echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p
echo ""
echo "Pity the living." | ./ft_ssl md5 -q -r
echo ""
echo "And above all," > file
echo ""
./ft_ssl md5 file
echo ""
./ft_ssl md5 -r file
echo ""
echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file
echo ""
echo "some of this will not make sense at first" | ./ft_ssl md5 file
echo ""
echo "but eventually you will understand" | ./ft_ssl md5 -p -r file
echo ""
echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file
echo ""
echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"
echo ""
echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file
echo ""

echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > big_smoke_order_remix
./ft_ssl sha256 -q big_smoke_order_remix
echo ""
openssl sha -sha256 big_smoke_order_remix
echo ""
./ft_ssl sha256 -s "wubba lubba dub dub"
echo ""

echo "\033[92m- - - - - - TEST ON BIG FILE - - - - - -\n\033[0m"
echo "generate one big file"
cat /dev/urandom | base64 -b 4242  | head -n4242 > big_f

echo "\033[92m\n- - - - - - - - SHA256 - - - - - - - -\033[0m"
echo "\033[94mecho -n \"\`cat big_file\`\" |  | shasum -a 256\t\t\t\t\t(__STANDARD__)\033[0m"
echo -n "`cat big_f`" | shasum -a 256

echo "\033[94m\necho -n \"\`cat big_file\`\" | ./ft_ssl sha256  -q\t\t\t\t\t(__STDIN__)\033[0m"
echo -n "`cat big_f`" | ./ft_ssl sha256 -q

echo "\033[94m\n./ft_ssl sha256 -s \"\`big_file\`\"\t\t\t\t\t\t\t(__STRING__)\033[0m"
./ft_ssl sha256 -s "`cat big_f`" -q

echo "\033[94m\nshasum -a 256 big_file\t\t\t\t\t\t\t\t(__STANDARD__)\033[0m"
shasum -a 256 big_f
echo "\033[94m\n./ft_ssl sha256 -r big_file\t\t\t\t\t\t\t(__FILE__)\033[0m"
./ft_ssl sha256 -r big_f

echo "\033[92m\n\n- - - - - - - - MD5 - - - - - - - -\033[0m"

echo "\033[94mecho -n \"\`cat big_file\`\" |  | md5\t\t\t\t\t\t(__STANDARD__)\033[0m"
echo -n "`cat big_f`" | md5

echo "\033[94m\necho -n \"\`cat big_file\`\" | ./ft_ssl md5  -q\t\t\t\t\t(__STDIN__)\033[0m"
echo -n "`cat big_f`" | ./ft_ssl md5 -q

echo "\033[94m\n./ft_ssl md5 -s \"\`big_file\`\"\t\t\t\t\t\t\t(__STRING__)\033[0m"
./ft_ssl md5 -s "`cat big_f`" -q

echo "\033[94m\nmd5 -r big_file\t\t\t\t\t\t\t\t\t(__STANDARD__)\033[0m"
md5 -r big_f
echo "\033[94m\n./ft_ssl md5 -r big_file\t\t\t\t\t\t\t(__FILE__)\033[0m"
./ft_ssl md5 -r big_f

rm file big_smoke_order_remix big_f
