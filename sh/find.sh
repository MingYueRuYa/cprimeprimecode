 find . \( -name "*.txt" -o -name "*.png" \) -print
 find . \( ! -name "*.txt" -o -name "*.png" \) -print
 find ~ -path "*/sh/*" -print
 find . -type l -print -exec ls -cal {} \;
 find . -type f -atime -7 -print
 find . -type f -mtime -7 -print
 find . -type f  -mtime -7 -print
 find . -type f -size 2k -exec ls -alh {} \;
 find . -type f -size -2k -exec ls -al {} \;
 find . -type f -size +2k -exec ls -al {} \;
 find . -name ".*" -print -delete
 find . -type f -name "*.txt" -exec printf "Text file: %s\n" {} \;
 find . \( -name "500lines" -prune -a -name ".git" -prune  \) \
    -o \( -size +2k -print \)
 find . \( -name ".git" -prune -o -type f -print \) > record.txt
