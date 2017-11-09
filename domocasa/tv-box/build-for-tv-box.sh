#!/usr/bin/env bash
echo "Building..."
docker run -it -v $PWD:/domocasa google/golang /domocasa/build-within-docker.sh $1