#!/usr/bin/env bash

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

read -p "Enter flag: "
echo "$REPLY" > decrypted_flag.txt

docker rm $(docker stop $(docker ps -a -q --filter ancestor=greeter --format="{{.ID}}")) 2> /dev/null || true
docker build -t greeter "$DIR"
docker run -d -p 2222:22 greeter