#================================================================
#   Copyright (C) 2020 OIDCAT Ltd. All rights reserved.
#   
#   文件名称：deletaDemoUser.sh
#   创 建 者：hyong
#   创建日期：2020年12月27日
#   描    述：
#
#================================================================

for idx in $(seq 2 100)
do 
	userdel -r newUser${idx}
done

