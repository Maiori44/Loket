Loket is a very simple encryptor that only requires a key to work.

**NOTE: While the program is in version 1.0, it is not safe enough currently, and should be seen as a toy for learning, updates will be released to improve safety**

## How it works
Every character of the file is summed with a character of the key and the sum of all characters of the key, this sum is then also encrypted and stored in the output `*.lok` file.  
If someone will try to decrypt the file using the wrong key, it will decrypt the sum incorrectly, and will not match the sum of the incorrect key and so the program will refuse to decrypt the file (which would have resulted in a corrupted file anyway).  
Decrypting the sum correctly is also necessary to decrypt the rest of the file since, as stated previously, the sum is added to each character in the original file.  
The sum stored in the file cannot be examined to obtain the correct key since it too is encrypted, thus only who already has the correct key can decrypt the sum correctly and with it the rest of the file.

## How to compile (with GCC)
Run `build.sh` on Linux or `build.bat` on Windows.  
To compile for Windows *on Linux*, run `build.sh -win`
