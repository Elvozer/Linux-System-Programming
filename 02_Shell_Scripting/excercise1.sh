#!/bin/bash

fileCount=$(find "$1" -maxdepth 1 -type f | wc -l)
dirCount=$(find "$1" -maxdepth 1 -type d | wc -l)

echo "Files: $fileCount"
echo "Directories: $dirCount"
echo "File list (sorted by size):" 

ls "$1" -lS | grep "^-" | awk '{print "- " $9, "(" $5 " bytes)"}'