#!/bin/bash

echo "Testing gtmrsacrypto external call"

if [ -z ${gtm_dist} ]; then
	echo "Cannot test GT.M locally, \$gmt_dist undefined"
	exit 1
fi

which mumps > /dev/null

if [ $? -ne 0 ]; then
	echo "Cannot test GT.M locally, cannot found mumps binary"
	exit 1
fi

echo "Running make"
make clean && make gtmlib

if [ $? -ne 0 ]; then
	echo "Make returned with errors"
	exit 1
fi

echo "Generating new keys and files"
./generate-keys-and-files.sh

# TODO: Needs to be some more input driven, for now is fine"
export GTMXC_rsacrypto="/home/mreitsma/Workspace/clibs/rsacrypto/rsacrypto.xc"
export gtmroutines="."
mumps -run test $(pwd)/keys $(pwd)/files


