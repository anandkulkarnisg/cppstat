#!/bin/bash

startSeed="0.00"
bumpFactor="0.01"
endLimit="0.50"
currVal="$startSeed+$bumpFactor"
winsorParam=$(python3 -c "a=$startSeed+$bumpFactor; print(\"%.2f\" % a, ',',a<=$endLimit)")
retVal=$(echo $winsorParam|awk -F"," '{print $1}' | sed "s/ //g")
retStatus=$(echo $winsorParam|awk -F"," '{print $2}'| sed "s/ //g")

while [ "$retStatus" = "True" ]; do
  pythonResult=$(python3 $PWD/winsorize.py $retVal|grep -i "after : " | awk -F":" '{print $2}'|sed "s/ //g")
  cppWinsorResult=$($PWD/Example1.out $retVal|grep -i "after " | awk -F":" '{print $2}'|sed "s/ //g")

  if [ "$pythonResult" != "$cppWinsorResult" ]; then
      echo -e "The result failed for testing with winsor parameter = $retVal"
  else
      echo -e "The comparison is successfull at parameter = $retVal"
  fi

  winsorParam=$(python3 -c "a=$retVal+$bumpFactor; print(\"%.2f\" % a, ',',a<=$endLimit)")
  retVal=$(echo $winsorParam|awk -F"," '{print $1}'|sed "s/ //g")
  retStatus=$(echo $winsorParam|awk -F"," '{print $2}'|sed "s/ //g")
done

exit 0
