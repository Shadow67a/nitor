#!/bin/bash

echo "
███╗   ██╗██╗████████╗ ██████╗ ██████╗ 
████╗  ██║██║╚══██╔══╝██╔═══██╗██╔══██╗
██╔██╗ ██║██║   ██║   ██║   ██║██████╔╝
██║╚██╗██║██║   ██║   ██║   ██║██╔══██╗
██║ ╚████║██║   ██║   ╚██████╔╝██║  ██║
╚═╝  ╚═══╝╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝
"                                     

mkdir ../examples/build

cd ../examples/build

cmake -DExamples=ON -DASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT=OFF -DASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT=OFF -DASSIMP_BUILD_OBJ_IMPORTER=ON -DASSIMP_BUILD_TESTS=OFF ../..

printf "\nBuilding examples into /examples :)\n\n"

cmake --build .

mv ./examples/clock ../

rm -rf *

cd ../

rm -rf build/
