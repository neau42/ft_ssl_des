#!/bin/zsh

if [ $# -ne 1 ] ; then
  echo "usage: $0 nb_files_to_generate"
  exit 1
fi

echo -n "generate $1 random files ."
for a in {1..$1} ; do
  cat /dev/urandom | base64 -b $(( ( RANDOM % 1042 ) + $a )) | head -n $(( ( RANDOM % 12 ) + 1)) > f_$a
  if [ $(( $a % 10 )) -eq 0 ]; then
    echo -n "."
  fi
done

echo "\n" 
echo "test MD5:" | tee ft_sllMD5.out | tee opensslMD5.out
a=0

for e in `ls f_*` ; do
  echo -n "`cat $e`" | ./ft_ssl md5 -q | cut -d' ' -f2 >> ft_sllMD5.out
  echo -n "`cat $e`" | openssl md5 | cut -d' ' -f2 >> opensslMD5.out
  ((a++))
   if [ $(( $a % 10 )) -eq 0 ]; then
    echo -n "."
    fi
done
echo "\ndiff:" 
diff ft_sllMD5.out opensslMD5.out


echo "test SHA256:" | tee ft_sllSHA.out | tee opensslSHA.out
a=0
for e in `ls f_*` ; do
  echo -n "`cat $e`" | ./ft_ssl sha256 -q | cut -d' ' -f2 >> ft_sllSHA.out
  echo -n "`cat $e`" | openssl sha256 | cut -d' ' -f2 >> opensslSHA.out
  ((a++))
  if [ $(( $a % 10 )) -eq 0 ]; then
    echo -n "."
  fi
done
echo "\ndiff:" 
diff  ft_sllSHA.out opensslSHA.out
echo "" 

rm f_*
#rm ft_sllMD5.out ft_sllSHA.out  opensslMD5.out opensslSHA.out
