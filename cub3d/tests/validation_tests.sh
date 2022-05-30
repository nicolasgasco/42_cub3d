for file in ./tests/scripts/*.sh
do
    sh "$file"
    if [ "$?" = "1" ]
    then
        exit 1
    fi
done