
if [ ! -f num.txt ]; then # If file does not exist, then...
    echo 0 > num.txt #create a file
fi

counter=0
internalCounter=0

while [ $internalCounter -lt 100 ]; do
    if $(ln num.txt num.lock); then #Checking for lock on file. Created if none.
        internalCounter=$(expr $internalCounter + 1)
        counter=$(tail -1 num.txt)
        counter=$(expr $counter + 1) #incrementing counter by 1
        echo $counter >> num.txt   
        rm -f num.lock #Removing lock as critical zone is left.
    fi
done