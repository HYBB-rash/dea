#================================================================
#   Copyright (C) 2020 OIDCAT Ltd. All rights reserved.
#   
#   文件名称：createDemoUser.sh
#   创 建 者：hyong
#   创建日期：2020年12月27日
#   描    述：
#
#================================================================

for idx in $(seq 2 100)
do 
	useradd -d /home/newUser${idx} -m newUser${idx} -s /bin/bash -G commonUser
	for i in $(seq 2 200)
	do 
		ls -al / > /home/newUser${idx}/data${i}
		chown -R newUser${idx}:newUser${idx} /home/newUser${idx}
	done
done
