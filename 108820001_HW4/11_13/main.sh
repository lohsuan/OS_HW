ls -li file1.txt
ln file1.txt file2.txt
rm file1.txt
strace rm file2.txt
ln -s file3.txt file4.txt