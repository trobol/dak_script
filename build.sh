#!/bin/bash

GREEN='\033[0;32m'
NC='\033[0m' # No Color
BASEDIR=$(dirname "$0")

if [ ! -d "./build" ]; then 
    mkdir build
    printf "[dak-script] ${GREEN}Creating build directory${NC}\n"
fi

RUN_CMAKE=0



cd ${BASEDIR}/build


printf "[dak-script] ${GREEN}Running Cmake${NC}\n"
cmake ..

make 

