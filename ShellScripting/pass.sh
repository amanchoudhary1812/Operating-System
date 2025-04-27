#!/bin/bash
pass=""
while [ "$pass" != "12345" ]; do
    echo "Enter password:"
    read -s pass
done
echo "Access granted!"


