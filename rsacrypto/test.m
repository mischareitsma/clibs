test
	W "Running test.m",!
	S keyLocation=$P($ZCMDLINE," ",1)
	S fileLocation=$P($ZCMDLINE," ",2)

	N key,pubkey,input,enc,sign
	S key=$$loadFile(keyLocation_"/key.pem")
	S pubkey=$$loadFile(keyLocation_"/pubkey.pem")
	S input=$$loadFile(fileLocation_"/sample.txt")
	S enc=$$loadFile(fileLocation_"/sample.txt.enc")
	S sign=$$loadFile(fileLocation_"/sample.txt.signature")

	W "Testing encrypt: "
	; TODO: Implement, hardes one for the verify
	N encryptResult S encryptResult=$J("",512)
	D &rsacrypto.encrypt(pubkey,input,.encryptResult)
	D writeBinFile(fileLocation_"/mtest.sample.txt.enc",encryptResult,$L(encryptResult))
	N cmd S cmd="openssl rsautl -decrypt -inkey "_keyLocation_"/key.pem -in "_fileLocation_"/mtest.sample.txt.enc -out "_fileLocation_"/mtest.sample.txt"
	ZSYSTEM cmd
	N mtestSample S mtestSample=$$loadFile(fileLocation_"/mtest.sample.txt")
	I mtestSample=input W "PASSED",!
	E  W "FAILED",!

	W "Testing decrypt: "
	N decryptResult S decryptResult=$J("",512)
	D &rsacrypto.decrypt(key,enc,.decryptResult);
	I decryptResult=input W "PASSED",!
	E  W "FAILED",!

	W "Testing signing: "
	N signatureResult S signatureResult=$J("",512)
	D &rsacrypto.sign(key,input,.signatureResult)
	I signatureResult=sign W "PASSED",!
	E  W "FAILED",!

	W "Testing verify: "
	N verify S verify=$&rsacrypto.verify(pubkey,input,sign)
	I verify W "PASSED",!
	E  W "FAILED",!

	Q

loadFile(io)
	N content S content=""
	; Just read raw bytes, should work the best.
	O io:(readonly:FIXED:WRAP:CHSET="M")
	U io R content#(1024*1024) U $P
	C io
	Q content

writeBinFile(io,content,recordsize)
	O io:(newversion:FIXED:RECORDSIZE=recordsize:WRAP:CHSET="M")
	U io W content U $P
	C io
	Q
