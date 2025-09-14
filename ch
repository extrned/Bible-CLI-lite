#!/bin/bash
# A part of Bible-CLI

echo "A minimalistic Configurator for Bible-CLI"

[ "$#" -ne 2 ] && { echo "Usage: $0 <language> <translation>"; exit 1; }
file="bible.conf"
[ ! -f "$file" ] && echo -e "language=\ntranslation=" > "$file"
sed -i "s/language=.*/language=$1/" "$file"
sed -i "s/translation=.*/translation=$2/" "$file"
echo "Success"
