#!/bin/zsh

for a in {001..300} ; do
  cat /dev/urandom | base64 -b $a  | head -n1 > f_$a
done

for e in `ls f_*` ; do
  echo "$e:"
  echo -n "`cat $e`" | ./ft_ssl md5 -s "`cat $e`" | cut -d' ' -f2
 #echo -n "`cat $e`" | ./ft_ssl md5 -s "`cat $e`"
  echo -n "`cat $e`" | openssl md5 | cut -d' ' -f2
# echo -n "`cat $e`" | openssl md5 
done

rm f_*

