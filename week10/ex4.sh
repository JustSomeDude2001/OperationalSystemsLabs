mkdir tmp
touch tmp/file1
ln tmp/file1 tmp/file2
./ex4 > ex4.txt
find tmp -inum ${ls -i tmp/file1 | head -n1 | awk '{print $1;}'} >> ex4.txt
find tmp -inum ${ls -i tmp/file2 | head -n1 | awk '{print $1;}'} >> ex4.txt