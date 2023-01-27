clear
CUR=$(pwd)
HOME=$(echo "$CUR/home")
echo "$HOME"
if [ $# == 0 ]; then
    exit 1
fi
cat $1 | while read line; do
    STUDENT=$(echo "$line" | cut -f1 -d" ") 
    COURSE_TYPE=$(echo "$line" | cut -f2 -d" ")
    COURSE=$(echo "$line" | cut -f3 -d" ")
    GRADE=$(echo "$line" | cut -f4 -d" ")
    
    STUDENT_FOLDER=$(echo "$HOME/$STUDENT")
    COURSE_TYPE_FOLDER=$(echo "$STUDENT_FOLDER/$COURSE_TYPE")
    COURSE_FILE=$(echo "$COURSE_TYPE_FOLDER/$COURSE.txt")
    

    # echo "$COURSE_TYPE_FOLDER"
    if [ ! -d "$STUDENT_FOLDER" ]; then
        # echo "$STUDENT_FOLDER doesn't exist"
        mkdir -pv "$STUDENT_FOLDER"
    fi

    if [ ! -d "$COURSE_TYPE_FOLDER" ]; then
        # echo "$COURSE_TYPE_FOLDER doesn't exist"
        mkdir -pv "$COURSE_TYPE_FOLDER"
    fi

    if [ ! -f "$COURSE_FILE" ]; then
        # echo "$COURSE_FILE doesn't exist"
        touch "$COURSE_FILE"
    fi
    echo "$GRADE" > "$COURSE_FILE"
done