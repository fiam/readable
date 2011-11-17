#!/bin/bash

DIFF=$$.diff
echo "Generating diff"
git diff . > ${DIFF}
echo "Reverting changes"
git checkout .
echo "Building previous implementation"
make clean readable
echo "Initial run"
cd tests
mkdir -p initial
for f in *.html
do
    ../readable ${f} > initial/${f}
done
cd -
echo "Patching"
patch -p2 < ${DIFF}
echo "Building"
make clean readable
cd tests
mkdir -p final
for f in *.html
do
    ../readable ${f} > final/${f}
done
for f in *.html
do
    val=$(diff -u initial/${f} final/${f})
    if [ ! -z "${val}" ]; then
        echo "File ${f} differs"
        diff -u initial/${f} final/${f}
    fi
done
rm ${DIFF}
