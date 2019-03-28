#!/bin/bash
#This is Assignment 1 (Bash) of course Memory Structure & C++ in Ariel University.
#Code by: Liad Cohen & Timor Sharabi.

dirname=$1
exename=$2
shift 2
rest=$@
cdir=$(pwd) #so we can return to the actual shell path before exiting the script.
cd $dirname
make &>/dev/null 
lans=$? #exit code represents if make could compile/a Makefile exists.
if [[ $lans -eq 0 ]]; then
		valgrind --leak-check=full --error-exitcode=1 ./$exename $rest &>/dev/null #checking for mem leaks.
		valerr=$?
		valgrind --tool=helgrind --error-exitcode=1 ./$exename $rest &>/dev/null #checking for thread race.
		helerr=$?
else
		lans=1
		valerr=1
		helerr=1
fi
#printing output as required. added colors.
echo "Results: Compilation:  Memory Leak:  Thread Race: " 
if [[ $lans -eq 1 ]]; then
	printf "            \033[0;31mFAIL\033[0m          "
else
	printf "            \033[0;32mPASS\033[0m          "
fi

if [[ $valerr -eq 1 ]]; then
	printf "\033[0;31mFAIL\033[0m          "
else
	printf "\033[0;32mPASS\033[0m          "
fi

if [[ $helerr -eq 1 ]]; then
	printf "\033[0;31mFAIL\033[0m          \n"
else
	printf "\033[0;32mPASS\033[0m          \n"
fi

lans=$((lans*4)) #building error code from binary
valerr=$((valerr*2)) #building error code from binary
errorID=$((lans+valerr+helerr)) #building error code from binary

cd $cdir
exit $errorID