#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi
}

print_header "RUN cppcheck"
check_log "cppcheck main.c database/*.c database/*.h task/*.c task/*.h --enable=all --inconclusive --error-exitcode=1 -I database -I task --suppress=missingIncludeSystem" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy main.c database/*.c database/*.h task/*.c task/*.h -extra-arg=-std=c99 -- -I database -I task" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=c main.c database/*.c database/*.h task/*.c task/*.h" "Can't open for reading"

print_header "SUCCESS"
