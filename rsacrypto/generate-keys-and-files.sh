#!/bin/bash

mkdir -p keys
rm keys/*
openssl req -new -x509 -newkey rsa:2048 -days 365 -keyout keys/key.pem \
    -out keys/cert.pem -nodes \
    -subj '/C=NL/ST=Flevoland/L=Almere/CN=www.mreitsma.com' > /dev/null
openssl x509 -pubkey -noout -in keys/cert.pem  > keys/pubkey.pem

mkdir -p files
rm files/*

cat <<-EOF > files/sample.txt
This is an example file used for the crypto lib.

This file will be encrypted, decrypted, signed and verified
EOF

openssl rsautl -encrypt -pubin -inkey keys/pubkey.pem -in files/sample.txt -out files/sample.txt.enc
openssl dgst -sha256 -sign keys/key.pem -out files/sample.txt.signature files/sample.txt
