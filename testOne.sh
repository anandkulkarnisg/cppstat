#!/bin/bash
runParam=$1
echo -e "python3"
python3 ~/temp/winsorize.py $runParam|grep -i "after"|awk -F":" '{print $2}'|sed "s/ //g"
echo -e "cpp"
./Example1.out $runParam|grep -i "after"|awk -F":" '{print $2}'|sed "s/ //g"
