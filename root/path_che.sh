#!/bin/bash

echo "pwd=$(pwd)"

path=$(dirname $1);

echo "path=$path"

abs_path=$(cd $path;pwd)

echo "abs_path=$abs_path"
