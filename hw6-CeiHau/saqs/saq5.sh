user_name="$1"

if [ "$#" -ne 1 ]; then
    echo "error: user name does not exist"
    exit 1
fi

printf %-10s USER 
printf "%-10s\n" "CMD"
for entry in "/proc"/*
do
    status_file="${entry}/status"
    if [ -f "$status_file" ]; then
        
        uid=$(grep --color "Uid:" "$status_file" | cut -f2)
        pid=$(grep --color "Pid:" "$status_file" | cut -f2 | head -1)
        username=$(id -nu $uid)
        if [ $user_name = $username ]; then
            printf %-10s $user_name
            printf "%-10s\n" $pid
        fi
    fi
    # echo "$username" 

done