#!/bin/bash
BUILD_PATH=${BUILD_PATH:=build}
CLEAN_BUILD_DIR=${CLEAN_BUILD_DIR:=0}

echo "BUILD_PATH = ${BUILD_PATH}"
echo "CLEAN_BUILD_DIR = ${CLEAN_BUILD_DIR} | Remove BUILD_PATH before build project"
echo -e ""

# break script running if help argument presents
if [ "$1" == "--help" ] || [ "$1" == "-h" ]
then
    exit 0
fi

if [[ $CLEAN_BUILD_DIR -eq 1 ]]
then
    echo "Remove build directory [${BUILD_PATH}]"
    rm -rf ${BUILD_PATH}
fi


# set Home and Binary directories:
cmake -H. -B${BUILD_PATH}
# compile project:
cd ${BUILD_PATH}
cmake --build . --target all
