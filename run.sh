echo -e "\n*** BUILDING ***\n"
export CLEAN_BUILD_DIR=1
./build.sh
echo -e "\n*** RUNNING ***\n"
./build/keepit_app
echo -e "\n*** DONE ***\n"
