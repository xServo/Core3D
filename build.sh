[ "$1" == "-c" ] && rm -rf ./build/* && echo "./Build cleaned" && exit 0
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ./ -B build || exit 0
cd build
make || exit 0
if [ "$1" == "-r" ]; then
	cd ..
	./Core3D || exit 0
	exit 0
	elseif [ "$1" != "" ] then
	echo "Invalid argument!\nPossible options:\n\t-r\n\t\tRun Core3D after building."
fi
