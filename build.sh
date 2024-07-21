cmake -B build || exit 0
cd build
make || exit 0
mv Core3D ../
echo Build Successful
