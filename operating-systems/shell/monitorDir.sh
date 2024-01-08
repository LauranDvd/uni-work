#!/bin/bash

dirName=$1

oldState=initval
while true
do
    currentState=`ls -l $dirName`  # concatenation of the states of all files
    
    for file in `find $dirName -type f`
    do
        fileState=`sha1sum $file` 
        currentState+=$fileState
    done

    if test "$oldState" = initval
    then
        oldState=$currentState
    fi
    
    if ! test "$oldState" = "$currentState" 
    then
        echo Changes in the directory
    fi

    oldState=$currentState   

    sleep 1
done
