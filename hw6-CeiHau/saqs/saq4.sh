search_dir="$1"
largest=0
if [ "$#" -ne 1 ]; then
    exit 1
fi

if [ ! -d "$search_dir" ]; then
    exit 1
fi

for entry in "$search_dir"/*
do  
    file_name=$(basename "$entry")
    size=$( stat "$entry" --printf=" %s")
    if [ $size -gt $largest ]; then
        largest=$size
        rslt="file name: ${file_name} $( stat "$entry" --printf=" size: %s  Inode number: %i")"
    fi
done

echo "$rslt"