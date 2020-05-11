#!/bin/bash

BUILD_PATH=$(pwd)
BUILD_DIR=${BUILD_PATH}/build
BIN_DIR=${BUILD_PATH}/bin
CMAKE_OPTS="-S ${BUILD_PATH} -B ${BUILD_DIR}"
DEBUG=true

for i in "$@"
do
    case $i in 
    --clean)
        echo 'Cleaning ...'
        rm -rf ${BUILD_DIR}
        rm -rf ${BIN_DIR}
        exit 0
    ;;
    *)
        echo 'Undefined option'
    esac
done

if [ -d "${BUILD_DIR}" ]
then
    rm -rf ${BUILD_DIR}
fi

if [ -d "${BIN_DIR}" ]
then
    rm -rf ${BIN_DIR}
fi

mkdir -p ${BUILD_DIR}
mkdir -p ${BIN_DIR}

if [ ${DEBUG} = true ]
then
    echo 'Debug build'
    CMAKE_OPTS="--debug-output ${CMAKE_OPTS}"
fi

echo ${CMAKE_OPTS}
cmake ${CMAKE_OPTS}

cd ${BUILD_DIR} && make VERBOSE=1 -j"$(nproc)"

cp ${BUILD_DIR}/bin/* ${BIN_DIR}

if [ -d "${BUILD_DIR}/bin" ]
then
    rm -rf ${BUILD_DIR}/bin
fi

exit 0