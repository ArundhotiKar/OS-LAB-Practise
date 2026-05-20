#!/bin/bash

file="contacts.txt"

add_contact() {
    echo "Enter Name:"
    read name
    echo "Enter Number:"
    read number
    echo "$name - $number" >> "$file"
    echo "Contact added."
}

search_contact() {
    echo "Enter name to search:"
    read name
    grep -i "$name" "$file"
}

show_all() {
    if [ -f "$file" ]; then
        cat "$file"
    else
        echo "No contacts found."
    fi
}

while true
do
    echo "------ PHONEBOOK ------"
    echo "1. Add Contact"
    echo "2. Search Contact"
    echo "3. Show All Contacts"
    echo "4. Quit"
    echo "Choose an option:"
    read choice

    case $choice in
        1) add_contact ;;
        2) search_contact ;;
        3) show_all ;;
        4) echo "Goodbye!"; break ;;
        *) echo "Invalid option" ;;
    esac
done

