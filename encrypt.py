import sys
from Crypto.Cipher import AES
from os import urandom
import hashlib


KEY='\x89\xabQ3\n\xcd27\xb4\xc6\x06.\xb8\xca';

def pad(s):
	return s + (AES.block_size - len(s) % AES.block_size) * chr(AES.block_size - len(s) % AES.block_size)

def enc(plaintext, key):

	k = hashlib.sha256(key).digest()
	iv = 16 * '\x00'
	plaintext = pad(plaintext)
	cipher = AES.new(k, AES.MODE_CBC, iv)

	return cipher.encrypt(bytes(plaintext))


try:
    plaintext = open(sys.argv[1], "rb").read()
    print("file length =%s" % len(plaintext))
except:
    print("File argument needed! %s <raw payload file>" % sys.argv[0])
    sys.exit()

ciphertext = enc(plaintext, KEY)
print('payload[] = {'+','.join("0x{:02x}".format(ord(x)) for x in ciphertext) + ' };')