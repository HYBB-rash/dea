#================================================================
#   Copyright (C) 2020 OIDCAT Ltd. All rights reserved.
#   
#   文件名称：UserManage.sh
#   创 建 者：hyong
#   创建日期：2020年12月27日
#   描    述：
#
#================================================================
if [ $# -lt 2 ]; then 
	echo 'Your should input 2 args!'
	exit 
fi

if [ ${1}=='-un' ]; then
	if [ "${2}" ]; then 
		addUser=${2}
	fi 
else 
	echo 'args error!'
	echo 'Please reinput your args!'
	exit 
fi

rm -rf ./tmp 
mkdir tmp

cat /etc/passwd | cut -f 1 -d : > ./tmp/allUserList 
checkRes=$(grep ${addUser} ./tmp/allUserList)
echo "${checkRes}"
echo "${addUser}"
if [ "$checkRes"x = "$addUser"x ]; then 
	echo 'Detect your account had created.'
	echo 'If you keep to continue, the old account will be deleted anyway.'
	echo 'Please enter your choice:'
	read -p "1. continue 2. break " userChoice 
	if [ $userChoice -eq 1 ]; then 
		userdel -r ${addUser}
		echo "Finish! Old account have been deleted!"
	else 
		echo 'Stop'
		exit 
	fi
else 
	echo "There are not username like ${addUser}"
fi
rm ./tmp/allUserList
useradd -d /home/${addUser} -m ${addUser} -s /bin/bash -G commonUser
passwd ${addUser}
mkdir /home/${addUser}/newdir 
userlist=$(groupmems -g commonUser -l)
for user in ${userlist}
do
	if [ "$user"x != "$addUser"x ]; then 
		#echo $(ls -al /home/${user})
		echo "coping /home/${user} to /home/${addUser}/newdir"
		cp -r /home/${user} /home/${addUser}/newdir/
		echo "change rights to new user"
		chown -R ${addUser}:${addUser} /home/${addUser}/newdir/${user}
		chmod -R 740 /home/${addUser}/newdir/${user}
	fi 
done

