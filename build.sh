cmake -B build || exit 0
cd build
make || exit 0
if [ "$1" == "-r" ]; then
	cd ..
	./Core3D || exit 0
	exit 0
	elseif [ "$1" != "" ] then
	echo "Invalid argument!\nPossible options:\n\t-r\n\t\tRun Core3D after building."
fi
