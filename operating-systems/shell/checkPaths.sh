#!/bin/bash

# reads paths until the user writes "stop"
# if given a file, it overwrites it
# prints what percentages were files, directories, and other things

everything=""
while read X
do
    if [ $X = stop ]
    then
        break
    fi

    everything="$everything $X"
done

cntFile=0
cntDir=0
cntOther=0

for sth in $everything
do
    if [ -f $sth ]
    then
        echo Has been modified > $sth
        cntFile=`expr $cntFile + 1`
    elif [ -d $sth ]
    then
        ls -lct $sth | head -n 2 | tail -n +2 | awk '{print $9}'
        cntDir=`expr $cntDir + 1`
    else
        echo $sth
        cntOther=`expr $cntOther + 1`
    fi
done

total=`expr $cntFile + $cntDir`
total=`expr $total + $cntOther`

cntFile=`expr $cntFile \* 100`
cntDir=`expr $cntDir \* 100`
cntOther=`expr $cntOther \* 100`

expr $cntFile / $total
expr $cntDir / $total
expr $cntOther / $total

