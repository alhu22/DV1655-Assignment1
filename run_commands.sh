make clean
make
python testScript.py -semantic -valid
./compiler test_files/semantic_errors/Duplicateidentifier.java
