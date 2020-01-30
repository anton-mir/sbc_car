#!/bin/bash

CARCLUSTER_PATH=$(pwd)
CARCLUSTER_BUILD_DIR=${CARCLUSTER_PATH}/build
INSTALL_CARCLUSTER=false
CMAKE_OPTS=".."
release_not_specified=true

for i in "$@"
do
        case $i in
        --clean)
                echo 'Car cluster cleaning ...'
                rm -rf ${CARCLUSTER_BUILD_DIR}
                exit 0
        ;;
        --install)
                echo 'Install process included'
                echo 'Sudo required'
                INSTALL_CARCLUSTER=true
        ;;
        --pits)
                echo 'Build for pits on road demo'
                CMAKE_OPTS="\
                        -DCMAKE_XLGYRO_OPTION=XLGYRO_ENABLED \
                        ${CMAKE_OPTS}"
                release_not_specified=false
        ;;
        *)
                echo "Undefined options"

        esac
done

mkdir -p ${CARCLUSTER_BUILD_DIR}
cd ${CARCLUSTER_BUILD_DIR}


if [ ${release_not_specified} = true ]
then
        echo "Debug build by default"
        CMAKE_OPTS="\
                -DCMAKE_BUILD_TYPE=Debug \
                ${CMAKE_OPTS}"
fi

echo ${CMAKE_OPTS}

cmake ${CMAKE_OPTS}
make VERBOSE=1

if [ ${INSTALL_CARCLUSTER} = true ]
then
        sudo make install
        sudo ldconfig
fi

