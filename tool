#!/bin/bash

shopt -s nullglob
set -e

_argtoyear() {
	if [[ "${#1}" == "2" ]]; then
		echo "20$1"
	elif [[ "${#1}" == "1" ]]; then
		echo "202$1"
	else
		echo "$1"
	fi
}
_argtoday() {
	if [[ "${#1}" == "1" ]]; then
		echo "0$1"
	else
		echo "$1"
	fi
}

if [[ "$1" == "build" ]]; then
	"$0" new "$2" "$3" "$4"
	"$0" clean "$2" "$3"
	cd "$(dirname "$0")"/"$(_argtoyear "$2")"/"$(_argtoday "$3")"
	if [ ! -f .lang ]; then
		printf "$(tput bold)no .lang found$(tput sgr0)\n" 1>&2
		exit 1
	fi
	if [ -z "$(cat .lang | xargs)" ]; then
		printf "$(tput bold).lang is empty$(tput sgr0)\n" 1>&2
		exit 1
	fi
	case "$(cat .lang)" in
		c++*|gnu++*)
			rm -f _tc.json
			for file in *.cpp; do
				printf "$(tput bold)building ${file%.*}:$(tput sgr0)\n" 1>&2
				echo "g++ $file -o out/${file%.*} -Wall -Wextra -Wpedantic -std=$(cat .lang)" 1>&2
				if [ ! -f compile_commands.json ]; then
					bear --append --output _tc.json -- g++ "$file" -o out/"${file%.*}" -Wall -Wextra -Wpedantic "-std=$(cat .lang)"
				else
					g++ "$file" -o out/"${file%.*}" -Wall -Wextra -Wpedantic "-std=$(cat .lang)"
				fi
			done
			if [ -f _tc.json ]; then
				mv _tc.json compile_commands.json
			fi
		;;
		c*|gnu*|iso9899*)
			rm -f _tc.json
			for file in *.c; do
				printf "$(tput bold)building ${file%.*}:$(tput sgr0)\n" 1>&2
				echo "gcc $file -o ${file%.*} -Wall -Wextra -Wpedantic -std=$(cat .lang) -lc" 1>&2
				if [ ! -f compile_commands.json ]; then
					bear --append --output _tc.json -- gcc "$file" -o out/"${file%.*}" -Wall -Wextra -Wpedantic "-std=$(cat .lang)"
				else
					gcc "$file" -o out/"${file%.*}" -Wall -Wextra -Wpedantic "-std=$(cat .lang)"
				fi
				if [ -f _tc.json ]; then
					mv _tc.json compile_commands.json
				fi
			done
		;;
		odin)
			for file in *.odin; do
				printf "$(tput bold)building ${file%.*}:$(tput sgr0)\n" 1>&2
				echo "odin build -build-mode:exe $file -file -out:out/${file%.*}" 1>&2
				odin build -build-mode:exe "$file" -file -out:out/"${file%.*}"
			done
		;;
	esac
elif [[ "$1" == "run" ]]; then
	. "$0" build "$2" "$3"
	if [ -z "$(echo inputs/*)" ]; then
		printf "$(tput bold)no inputs found!$(tput sgr0)\n"
		exit 1
	fi
	if [ ! -f .lang ] || [ -z "$(cat .lang | xargs)" ]; then
		exit 1
	fi
	if [ -f inputs/"$4" ]; then
		for file in *.cpp *.c *.odin; do
			printf "$(tput bold)running ${file%.*} with input file $4:$(tput sgr0)\n" 1>&2
			cat inputs/"$4" | ./out/"${file%.*}"
		done
	else
		for input in inputs/*.txt; do
			for file in *.cpp *.c *.odin; do
				printf "$(tput bold)running ${file%.*} with input file $input:$(tput sgr0)\n" 1>&2
				cat "$input" | ./out/"${file%.*}"
			done
		done
	fi
elif [[ "$1" == "clean" ]]; then
	rm -f "$(dirname "$0")"/"$(_argtoyear "$2")"/"$(_argtoday "$3")"/out/*
elif [[ "$1" == "new" ]] || [[ "$1" == "lang" ]]; then
	mkdir -p "$(dirname "$0")"/"$(_argtoyear "$2")"/"$(_argtoday "$3")"
	cd "$(dirname "$0")"/"$(_argtoyear "$2")"/"$(_argtoday "$3")"
	mkdir -p out
	mkdir -p inputs
	if [ -n "$(echo $4 | xargs)" ]; then
		echo "$4" | xargs > .lang
	fi
else
	printf "$(tput bold)$1: command not found!$(tput sgr0)\n" 1>&2
	exit 1
fi
