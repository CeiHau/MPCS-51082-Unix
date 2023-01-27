# cat $1 | while read line; do
clear
CUR=$(pwd)
LOG=$(echo "$CUR/LOG")
if [ $# == 0 ]; then
    exit 1
fi

# cat log.csv | cut -f2,6,7,14 -d"," 
cat log.csv | while read line; do
    deviceProduct=$(echo "$line" | cut -f2 -d",")
    name=$(echo "$line" | cut -f6 -d",")
    start=$(echo "$line" | cut -f7 -d",")
    suser=$(echo "$line" | cut -f14 -d",")
    user_folder=$(echo "$LOG/$suser")
    deviceProduct_folder=$(echo "$user_folder/$deviceProduct")
    logfile_path=$(echo "$deviceProduct_folder/logs.csv")
    # echo "$deviceProduct,$name,$start"
    if [ $suser = $1 ]; then
        echo "$user_folder"
        echo "$deviceProduct_folder"
        if [ ! -d "$user_folder" ]; then
            mkdir -p "$user_folder"
        fi
        
        if [ ! -d "$deviceProduct_folder" ]; then
            mkdir -p "$deviceProduct_folder"
        fi

        if [ ! -f "$logfile_path" ]; then
            touch "$logfile_path"
            echo "start,name" > "$logfile_path"
        fi  
        echo "$start,$name" >> "$logfile_path"
    fi

done
