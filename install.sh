#!/bin/bash

if cmake -S . -B build && cmake --build build; then
	echo "Build successful."
else
	echo "CMake not found OR build failed. Exiting..."
	exit 1
fi

echo -n "Do you want to install kbchad? [Y/n] "
read -r kbchad
echo -n "Do you want to install wordlist? [Y/n] "
read -r wordlist

if [ "$kbchad" == "n" ] || [ "$kbchad" == "N" ]; then
    echo "Install canceled."
else
    mkdir -p /usr/local/bin/
	sudo cp build/kbchad /usr/local/bin/ && echo "kbchad was installed."
fi	

if [ "$wordlist" == "n" ] || [ "$wordlist" == "N" ]; then
    echo "Warning: you declined to install the wordlist"
else
    mkdir -p $HOME/.local/share/kbchad/
	sudo cp static/english.txt $HOME/.local/share/kbchad/ && 
        echo "wordlist was installed."
fi	

kbchad
