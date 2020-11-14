#!/usr/bin/env bash

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

read -p "Enter flag: "
echo "$REPLY" > decrypted_flag.txt

docker rm $(docker stop $(docker ps -a -q --filter ancestor=secret-shell --format="{{.ID}}")) 2> /dev/null || true
docker build -t secret-shell "$DIR"
docker run -d -p 2222:22 secret-shell