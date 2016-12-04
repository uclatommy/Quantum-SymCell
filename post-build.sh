DIR=$1
FILE=$2
DEST="/Applications/Quantum.app/Contents/Resources/.kivy/extensions/plugins/"
pushd ${DIR};
osxrelocator -r . ./Contents @executable_path/..;
popd;
cp ${DIR}/${FILE} ${DEST}
install_name_tool -id ./Contents/Resources/.kivy/extensions/plugins/${FILE} ${DEST}${FILE}
echo "Done."
