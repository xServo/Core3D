# simply clear out the build dir and exit
[ "$1" == "-c" ] && rm -rf ./build/* && echo "./Build cleaned" && exit 0

# build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug ./ -B build || exit 0
cd build
make || exit 0

# all other options
if [ "$1" == "-r" ]; then
	# run mode
	cd ..
	./Core3D || exit 0
	exit 0

	# debug mode
elif [ "$1" == "-d" ]; then
	echo "debugging"
	cd ..
	lldb ./Core3D || exit 0
	exit 0

# invalid flag
elif [[ "$1" != "" ]]; then
	echo "Invalid argument!\nPossible options:"
	echo "\t-r\tRun Core3D after building."
	echo "\t-d\tDebug Core3D after building."
	echo "\t-c\tClean the build directory."
fi
