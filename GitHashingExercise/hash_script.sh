#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <4-digit-integer>"
    exit 1
fi

echo -n "$1" | sha256sum | awk '{print $1}'
