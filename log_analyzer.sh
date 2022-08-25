cd ~/
repos_path="T02D02-0/"

if [ "$#" != "1" ]; then
	echo "Argument count mismatch!"
	exit 1
fi

if [ ! -f $1 ]; then
	echo "file does not exist"
	exit 1
fi

unique_arr=()
shas=()
count=0

while read -r line; do
	IFS=' - '
	read -ra arr <<< $line
	unset IFS
	
	if [ ! -f "$repos_path${arr[0]}" ]; then
		#echo "File ${arr[0]} does not exist, skipping..."
		continue
	fi

	if [[ ! "${unique_arr[*]}" =~ "${arr[0]}" ]]; then
		unique_arr+=(${arr[0]})    		
	fi
	
	index=-1
	for (( i = 0; i < ${#unique_arr[@]}; i++ )); do
		if [[ ${unique_arr[$i]} == ${arr[0]} ]]; then
			index=$i
		fi
	done

	if [[ -z ${shas[$index]} ]]; then
		shas+=("${arr[6]}")
	elif [[ ! "${shas[$index]}" == *"${arr[6]}"* ]]; then
		shas[$index]+=" ${arr[6]}"
		((count+=1))
	fi
done < $1

((count+=${#shas[@]}))

# output result
echo $(wc -l $1 | awk '{print $1}') ${#unique_arr[@]} $count
