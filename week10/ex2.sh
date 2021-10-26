mkdir ../week01
touch ../week01/file.txt
echo "Bob" > ../week01/file.txt

mkdir ../week10

link ../week01/file.txt _ex2.txt

touch ex2.txt
find ../week01/file.txt -inum ${ls -i ../week01/file.txt | head -n1 | awk '{print $1;}'} -v >> ex2.txt

find ../week01/file.txt -inum ${ls -i ../week01/file.txt | head -n1 | awk '{print $1;}'} -exec rm -v >> ex2.txt

