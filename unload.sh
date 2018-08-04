#!/bin/bash

L_UID=$(id -u)

if [ "$L_UID" -ne "0" ]; then
    echo "[X] You must be root"
    exit 1
fi

rmmod lkh