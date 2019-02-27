#!/bin/bash

testCaseInputs="0.01 0.02 0.03 0.04 0.05 0.09 0.10 0.12 0.14 0.15 0.19 0.20 0.25 0.28 0.30 0.32 0.34 0.35 0.38 0.39 0.40 0.41 0.42 0.45 0.48 0.49 0.5"
for testCaseItem in $testCaseInputs
do
  pythonResult=$(python3 $HOME/temp/winsorize.py $testCaseItem|grep -i "after : " | awk -F":" '{print $2}'|sed "s/ //g")
  cppWinsorResult=$($HOME/git/cppstat/Example1.out $testCaseItem|grep -i "after " | awk -F":" '{print $2}'|sed "s/ //g")
  if [ "$pythonResult" != "$cppWinsorResult" ]; then
      echo -e "The result failed for testing with winsor parameter = $testCaseItem"
  else
      echo -e "The comparison is successfull at parameter = $testCaseItem"
  fi
done

exit 0
