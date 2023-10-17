# Hashes a file, ignoring all whitespace and comments. Use for
# verifying that code was correctly typed.
# Usage:
#   To make executable, run the command: chmod +x hash.sh
#   To execute: ./hash.sh < file.cpp
cpp -dD -P -fpreprocessed | tr -d '[:space:]'| md5sum |cut -c-6
