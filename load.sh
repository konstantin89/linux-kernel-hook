#!/bin/bash

L_UID=$(id -u)

if [ "$L_UID" -ne "0" ]; then
    echo "[X] You must be root."
    exit 1
fi

echo "[ ] Checking if lkh module is already loaded."
module_loaded="$(lsmod | grep lkh)"

if [ -n "$module_loaded" ]; then
    echo "[ ] Removing lkh module."
    rmmod lkh
fi

KBASE32=$(cat /proc/kallsyms | grep " ia32_sys_call_table" | awk '{ print $1 }')
KBASE64=$(cat /proc/kallsyms | grep " sys_call_table" | awk '{ print $1 }')

insmod ./lkh.ko kbase32="$KBASE32" kbase64="$KBASE64"

check_module="$(lsmod | grep lkh)"
if [ -z "$check_module" ]; then
    echo "[X] Failed to load lkh module."
else
    echo "[V] lkh module loaded."
fi
