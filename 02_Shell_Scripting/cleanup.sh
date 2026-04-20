#!/bin/bash

if [ -z "$1" ]; then
    echo "nhap lai"
    exit 1
fi

mkdir -p "$1/backup"

mv "$1"/*.log "$1/backup/"