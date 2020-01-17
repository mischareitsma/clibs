#!/bin/bash

echo "Testing rsacrypto"

echo "Running make"
make clean && make

if [ $? -ne 0 ]; then
	echo "Make returned with errors"
	exit 1
fi

echo "Generating new keys and files"
./generate-keys-and-files.sh

echo "Testing encrypt"
./bin/rsacrypto -a encrypt -k keys/pubkey.pem -i files/sample.txt -o files/test.sample.txt.enc

# Result can be different for same text, so use the openssl rsautl decrypt and compare to original file.
openssl rsautl -decrypt -inkey keys/key.pem -in files/test.sample.txt.enc | diff -q files/sample.txt -

if [ $? -ne 0 ]; then
	echo "FAILED: Result of encrypt not the same as openssl rsautl"
else
	echo "PASSED"
fi

echo "Testing decrypt"
./bin/rsacrypto -a decrypt -k keys/key.pem -i files/sample.txt.enc -o files/test.sample.txt

diff -q files/test.sample.txt files/sample.txt

if [ $? -ne 0 ]; then
	echo "FAILED Result of decrypt not the same as original"
else
	echo "PASSED"
fi

echo "Testing sign"

./bin/rsacrypto -a sign -k keys/key.pem -i files/sample.txt -o files/test.sample.txt.signature

diff -q files/test.sample.txt.signature files/sample.txt.signature

if [ $? -ne 0 ]; then
	echo "FAILED: Result of decrypt not the same as openssl dgst -sha256"
else
	echo "PASSED"
fi

echo "Testing verify"

./bin/rsacrypto -a verify -k keys/pubkey.pem -i files/sample.txt -s files/sample.txt.signature | grep "Verify OK"

if [ $? -ne 0 ]; then
	echo "FAILED: Result of verify not the same as openssl dgst -sha256"
else
	echo "PASSED"
fi

rm files/test.*
