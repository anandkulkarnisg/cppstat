#!/bin/bash
runParam=$1
echo -e "python3"
python3 $PWD/winsorize.py $runParam|grep -i "after"|awk -F":" '{print $2}'|sed "s/ //g"
echo -e "cpp"
$PWD/Example1.out $runParam|grep -i "after"|awk -F":" '{print $2}'|sed "s/ //g"
