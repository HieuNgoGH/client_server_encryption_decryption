This program encrypts and decrypts plaintext into ciphertext by the method of One-Time-Pads with 27 allowable characters. It gave me practice multi-processing code with socket-based inter-process communication.
It starts with a keygen program that creates a key file of a specified length. The encryption client will receive a plaintext file and keygen code then sends it to the encryption server. The encryption server
then encrypts the plaintext into ciphertext and sends it back to the client. The decryption client then sends the deciphertext to the decryption server where it will decrypt the ciphertext back to plaintext using the keygen.
Then decryption server then sends the plaintext back to the client. All plaintext and decipher text are created in its own file after sent back from the servers.
