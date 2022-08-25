cd ~/

echo "Enter file name(path from default directory)"
read filepath

if [ ! -f "$filepath" ]; then
	echo "file does not exist"
	exit 1
fi

echo "Enter string for replacement"
read original_string

if [ -z "$original_string" ]; then
	echo "string for replacement can not be empty!"
	exit 1
fi

echo "Enter new string" read new_string
read new_string

if [ -z "$new_string" ]; then
        echo "Warning: entered strings will be deleted instead of replacement!"
fi

sed -i '' "s/$original_string/$new_string/g" $filepath

if [ $? != 0 ]; then
	echo "Replacement failed!"
	exit 1
fi

echo "Replacement was successful!"
d=`date +'%Y-%m-%d %H:%M'`
result="${filepath#*/} - $(wc -c "$filepath" | awk '{print $1}') - $d - $(shasum -a 256 $filepath | awk '{print $1}') - 256"
echo "$result"	
echo "$result" >> T02D02-0/src/files.log

