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

echo -n "generate $1 random files\n."
for a in {1..$1} ; do
	cat /dev/urandom | base64 -b $(( ( RANDOM % $a ) + 1 )) | head -n $(( ( RANDOM % ( $a / 6 + 1 ) ) + 1 )) > ${TEST_DIR}f_$a
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
	echo "no Diff in $1 md5 hash"
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
	echo "no Diff in $1 sha256 hash"
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
	echo "no Diff in $1 md5 hash"
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
	echo "no Diff in $1 sha256 hash"
else
	echo "Diff:"
	diff ${TEST_DIR}$FILE_FT_SHA ${TEST_DIR}$FILE_OP_SHA
fi

echo "\033[92m\n\n- - - - - - SUBJECT EXAMPLE - - - - - -\033[0m"

echo "\techo \"pickle rick\" | ./ft_ssl md5"
echo "pickle rick" | ./ft_ssl md5
echo ""

echo "\techo \"Do not pity the dead, Harry.\" | ./ft_ssl md5 -p"
echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p
echo ""

echo "\techo \"Pity the living.\" | ./ft_ssl md5 -q -r"
echo "Pity the living." | ./ft_ssl md5 -q -r
echo ""

echo "\t\"And above all,\" > file"
echo "And above all," > file
echo ""

echo "\t./ft_ssl md5 file"
./ft_ssl md5 file
echo ""
echo "\t./ft_ssl md5 -r file"
./ft_ssl md5 -r file
echo ""

echo "\techo \"be sure to handle edge cases carefully\" | ./ft_ssl md5 -p file"
echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file
echo ""

echo "\techo \"some of this will not make sense at first\" | ./ft_ssl md5 file"
echo "some of this will not make sense at first" | ./ft_ssl md5 file
echo ""

echo "\techo \"but eventually you will understand\" | ./ft_ssl md5 -p -r file"
echo "but eventually you will understand" | ./ft_ssl md5 -p -r file
echo ""

echo "\techo \"GL HF let's go\" | ./ft_ssl md5 -p -s \"foo\" file"
echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file
echo ""

echo "\techo \"one more thing\" | ./ft_ssl md5 -r -p -s \"foo\" file -s \"bar\""
echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"
echo ""

echo "\techo \"just to be extra clear\" | ./ft_ssl md5 -r -q -p -s \"foo\" file"
echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file
echo ""


echo "\techo \"https://www.youtube.com/watch?v=w-5yAtMtrSM\" > big_smoke_order_remix"
echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > big_smoke_order_remix
echo "\t./ft_ssl sha256 -q big_smoke_order_remix"
./ft_ssl sha256 -q big_smoke_order_remix
echo ""

echo "\topenssl sha -sha256 big_smoke_order_remix"
openssl sha -sha256 big_smoke_order_remix
echo ""

echo "\t./ft_ssl sha256 -s \"wubba lubba dub dub\""
./ft_ssl sha256 -s "wubba lubba dub dub"
echo ""

rm -f file big_smoke_order_remix big_f
rm ${TEST_DIR}*
