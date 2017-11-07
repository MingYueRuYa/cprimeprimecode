#!/bin/bash

APP_NAME="${0##*[\\/]}"
APP_VERSION="1.0"

#颜色定义
iSumColor=7			#颜色总数
cRed=1				#红色
cGreen=2			#绿色
cYellow=3			#黄色
cBlue=4				#蓝色
cFuchsia=5			#紫红色
cCyan=6				#青色(蓝绿色)
cWhite=7			#白色

#位置与大小
marginLeft=3			#边框左边距
marginTop=2			#边框上边距
((mapLeft=marginLeft+2))	#棋盘左边距
((mapTop=$marginTop+1))		#棋盘上边距
mapWidth=10			#棋盘宽度
mapHeight=15			#棋盘高度

#颜色设置
cBorder=$cGreen
cScore=$cFuchsia
cScoreValue=$cCyan

#控制信号
#游戏使用两个进程，一个用于接收输入，一个用于游戏流程和显示界面;
#当前者接收到上下左右等按键时，通过向后者发送signal的方式通知后者。
sigRotate=25		#向上键
sigLeft=26
sigRight=27
sigDown=28
sigAllDown=29		#空格键
sigExit=30

#方块定义，7大类19种样式
#前8位为方块坐标，后2位为方块刚出现的时候的位置
box0_0=(0 0 0 1 1 0 1 1 0 4)

box1_0=(0 1 1 1 2 1 3 1 0 3)
box1_1=(1 0 1 1 1 2 1 3 -1 3)

box2_0=(0 0 1 0 1 1 2 1 0 4)
box2_1=(0 1 0 2 1 0 1 1 0 3)

box3_0=(0 1 1 0 1 1 2 0 0 4)
box3_1=(0 0 0 1 1 1 1 2 0 4)

box4_0=(0 2 1 0 1 1 1 2 0 3)
box4_1=(0 1 1 1 2 1 2 2 0 3)
box4_2=(1 0 1 1 1 2 2 0 -1 3)
box4_3=(0 0 0 1 1 1 2 1 0 4)

box5_0=(0 0 1 0 1 1 1 2 0 3)
box5_1=(0 1 0 2 1 1 2 1 0 3)
box5_2=(1 0 1 1 1 2 2 2 -1 3)
box5_3=(0 1 1 1 2 0 2 1 0 4)

box6_0=(0 1 1 0 1 1 1 2 0 3)
box6_1=(0 1 1 1 1 2 2 1 0 3)
box6_2=(1 0 1 1 1 2 2 1 -1 3)
box6_3=(0 1 1 0 1 1 2 1 0 4)

iSumType=7			#方块类型总数
boxStyle=(1 2 2 2 4 4 4)	#各种方块旋转后可能的样式数目

iScoreEachLevel=50	#提升一个级别需要的分数
#运行时数据
sig=0			#接收到的signal
iScore=0		#总分
iLevel=0		#速度级
boxNext=()		#下一个方块
iboxNextColor=0		#下一个方块的颜色
iboxNextType=0		#下一个方块的种类
iboxNextStyle=0		#下一个方块的样式
boxCur=()		#当前方块的位置定义
iBoxCurColor=0		#当前方块的颜色
iBoxCurType=0		#当前方块的种类
iBoxCurStyle=0		#当前方块的样式
boxCurX=-1		#当前方块的x坐标位置
boxCurY=-1		#当前方块的y坐标位置
map=()			#棋盘图表

#初始化所有背景方块为-1, 表示没有方块
for ((i = 0; i < mapHeight * mapWidth; i++))
do
	map[$i]=-1
done

#接收输入的进程的主函数
function RunAsKeyReceiver()
{
	local pidDisplayer key aKey sig cESC sTTY

	pidDisplayer=$1
	aKey=(0 0 0)

	cESC=`echo -ne "\033"`
	cSpace=`echo -ne "\040"`

	#保存终端属性。在read -s读取终端键时，终端的属性会被暂时改变。
	#如果在read -s时程序被不幸杀掉，可能会导致终端混乱，
	#需要在程序退出时恢复终端属性。
	sTTY=`stty -g`

	#捕捉退出信号
	trap "MyExit;" INT QUIT
	trap "MyExitNoSub;" $sigExit

	#隐藏光标
	echo -ne "\033[?25l"

	while :
	do
		#读取输入。注-s不回显，-n读到一个字符立即返回
		read -s -n 1 key

		aKey[0]=${aKey[1]}
		aKey[1]=${aKey[2]}
		aKey[2]=$key
		sig=0

		#判断输入了何种键
		if [[ $key == $cESC && ${aKey[1]} == $cESC ]]
		then
			#ESC键
			MyExit
		elif [[ ${aKey[0]} == $cESC && ${aKey[1]} == "[" ]]
		then
			if [[ $key == "A" ]]; then sig=$sigRotate	#<向上键>
			elif [[ $key == "B" ]]; then sig=$sigDown	#<向下键>
			elif [[ $key == "D" ]]; then sig=$sigLeft	#<向左键>
			elif [[ $key == "C" ]]; then sig=$sigRight	#<向右键>
			fi
		elif [[ $key == "W" || $key == "w" ]]; then sig=$sigRotate	#W, w
		elif [[ $key == "S" || $key == "s" ]]; then sig=$sigDown	#S, s
		elif [[ $key == "A" || $key == "a" ]]; then sig=$sigLeft	#A, a
		elif [[ $key == "D" || $key == "d" ]]; then sig=$sigRight	#D, d
		elif [[ "[$key]" == "[]" ]]; then sig=$sigAllDown	#空格键
		elif [[ $key == "Q" || $key == "q" ]]			#Q, q
		then
			MyExit
		fi

		if [[ $sig != 0 ]]
		then
			#向另一进程发送消息
			kill -$sig $pidDisplayer
		fi
	done
}

#退出前的恢复
MyExitNoSub()
{
	local y

	#恢复终端属性
	stty $sTTY
	((y = marginTop + mapHeight + 4))

	#显示光标
	echo -e "\033[?25h\033[${y};0H"
	exit
}

MyExit()
{
	#通知显示进程需要退出
	kill -$sigExit $pidDisplayer

	MyExitNoSub
}

#处理显示和游戏流程的主函数
RunAsDisplayer()
{
	local sigThis
	InitDraw

	#挂载各种信号的处理函数
	trap "sig=$sigRotate;" $sigRotate
	trap "sig=$sigLeft;" $sigLeft
	trap "sig=$sigRight;" $sigRight
	trap "sig=$sigDown;" $sigDown
	trap "sig=$sigAllDown;" $sigAllDown
	trap "ShowExit;" $sigExit

	while :
	do
		#根据当前的速度级iLevel不同，设定相应的循环的次数
		for ((i = 0; i < 21 - iLevel; i++))
		do
			sleep 0.02
			sigThis=$sig
			sig=0

			#根据sig变量判断是否接受到相应的信号
			if ((sigThis == sigRotate)); then BoxRotate;	#旋转
			elif ((sigThis == sigLeft)); then BoxLeft;	#左移一列
			elif ((sigThis == sigRight)); then BoxRight;	#右移一列
			elif ((sigThis == sigDown)); then BoxDown;	#下落一行
			elif ((sigThis == sigAllDown)); then BoxAllDown;	#下落到底
			fi
		done
		#kill -$sigDown $$
		BoxDown	#下落一行
	done
}

#绘制当前方块，传第一个参数，0表示擦除当前方块，1表示绘制当前方块
DrawCurBox()
{
	local i x y bErase sBox
	bErase=$1
	if (( bErase == 0 ))
	then
		sBox="\040\040"		#用两个空格擦除
	else
		sBox="[]"
		echo -ne "\033[1m\033[3${iBoxCurColor}m\033[4${iBoxCurColor}m"
	fi

	for ((i = 0; i < 8; i += 2))
	do
		((y = mapTop + 1 + ${boxCur[$i]} + boxCurY))
		((x = mapLeft + 1 + 2 * (boxCurX + ${boxCur[$i + 1]})))
		echo -ne "\033[${y};${x}H${sBox}"
	done
	echo -ne "\033[0m"
}

#移动方块
#BoxMove(y, x), 测试是否可以把移动中的方块移到(y, x)的位置, 返回0则可以, 1不可以
BoxMove()
{
	local i x y xPos yPos
	yPos=$1
	xPos=$2
	for ((i = 0; i < 8; i += 2))
	do
		#方块相对于棋盘坐标
		((y = yPos + ${boxCur[$i]}))
		((x = xPos + ${boxCur[$i + 1]}))

		if (( y < 0 || y >= mapHeight || x < 0 || x >= mapWidth))
		then
			#撞到墙壁了
			return 1
		fi
		
		if (( ${map[y * mapWidth + x]} != -1 ))
		then
			#撞到其他已经存在的方块了
			return 1
		fi
	done
	return 0;
}

#将方块贴到棋盘上
Box2Map()
{
	local i j x y line
	#将当前移动中的方块贴到棋盘对应的区域
	for ((i = 0; i < 8; i += 2))
	do
		#计算方块相对于棋盘的坐标
		((y = ${boxCur[$i]} + boxCurY))
		((x = ${boxCur[$i + 1]} + boxCurX))
		map[y*mapWidth+x]=$iBoxCurColor	#将方块颜色赋给地图
	done

	line=0
	for ((i = 0; i < mapHeight; i++))
	do
		for ((j = 0; j < mapWidth; j++))
		do
			#如果棋盘上有空隙，跳出循环
			[[ ${map[i*mapWidth+j]} -eq -1 ]] && break
		done

		[ $j -lt $mapWidth ] && continue
		#说明当前行可消去，可消去行数加一
		(( line++ ))

		#第i行可被消除，将0行至第i-1行全部下移一行，从第i-1行开始移动
		for ((j = i*mapWidth-1; j >= 0; j--))
		do
			((x = j + mapWidth))
			map[$x]=${map[$j]}
		done

		#因为下移一行，第0行置空
		for ((i = 0; i < mapWidth; i++))
		do
			map[$i]=-1
		done
	done
	
	[ $line -eq 0 ] && return

	#根据消去的行数line计算分数和速度级
	((x = marginLeft + mapWidth * 2 + 7))
	((y = marginTop + 11))
	((iScore += line * 2 - 1))
	#显示新的分数
	echo -ne "\033[1m\033[3${cScoreValue}m\033[${y};${x}H${iScore}         "
	if ((iScore % iScoreEachLevel < line * 2 - 1))
	then
		if ((iLevel < 20))
		then
			((iLevel++))
			((y = marginTop + 14))
			#显示新的速度级
			echo -ne "\033[3${cScoreValue}m\033[${y};${x}H${iLevel}        "
		fi
	fi
	echo -ne "\033[0m"

	#重新显示背景方块
	for ((i = 0; i < mapHeight; i++))
	do
		#棋盘相对于屏幕的坐标
		((y = i + mapTop + 1))
		((x = mapLeft + 1))
		echo -ne "\033[${y};${x}H"
		for ((j = 0; j < mapWidth; j++))
		do
			((tmp = i * mapWidth + j))
			if ((${map[$tmp]} == -1))
			then
				echo -ne "  "
			else
				echo -ne "\033[1m\033[3${map[$tmp]}m\033[4${map[$tmp]}m[]\033[0m"
			fi
		done
	done
}

#左移一格
BoxLeft()
{
	local x
	((x = boxCurX - 1))
	if BoxMove $boxCurY $x
	then
		DrawCurBox 0
		((boxCurX = x))
		DrawCurBox 1
	fi
}

#右移一格
BoxRight()
{
	local x
	((x = boxCurX + 1))
	if BoxMove $boxCurY $x
	then
		DrawCurBox 0
		((boxCurX = x))
		DrawCurBox 1
	fi
}

#向下移一格
BoxDown()
{
	local y
	((y = boxCurY + 1))	#新的y坐标
	if BoxMove $y $boxCurX	#测试是否可以下落一行
	then
		DrawCurBox 0	#将旧的方块抹去
		((boxCurY = y))
		DrawCurBox 1	#显示新的下落后方块
	else
		#走到这儿, 如果不能下落了
		Box2Map		#将当前移动中的方块贴到背景方块中
		CreateBox	#产生新的方块
	fi
}

#下落到底
BoxAllDown()
{
	local y iDown

	#计算能够下落的行数
	iDown=0
	(( y = boxCurY + 1 ))
	while BoxMove $y $boxCurX
	do
		(( y++ ))
		(( iDown++ ))
	done

	DrawCurBox 0	#将旧的方块抹去
	((boxCurY += iDown))
	DrawCurBox 1	#显示新的下落后的方块
	Box2Map		#将当前移动中的方块贴到背景方块中
	CreateBox	#产生新的方块
}

#翻转
BoxRotate()
{
	[ ${boxStyle[$iBoxCurType]} -eq 1 ] && return
	((rotateStyle = (iBoxCurStyle + 1) % ${boxStyle[$iBoxCurType]}))
	#将当前方块保存到boxTmp
	boxTmp=( `eval 'echo ${boxCur[@]}'` )
	boxCur=( `eval 'echo ${box'$iBoxCurType'_'$rotateStyle'[@]}'` )

	if BoxMove $boxCurY $boxCurX	#测试旋转后是否有空间放的下
	then
		#抹去旧的方块
		boxCur=( `eval 'echo ${boxTmp[@]}'` )
		DrawCurBox 0

		boxCur=( `eval 'echo ${box'$iBoxCurType'_'$rotateStyle'[@]}'` )
		DrawCurBox 1
		iBoxCurStyle=$rotateStyle
	else
		#不能旋转，还是继续使用老的样式
		boxCur=( `eval 'echo ${boxTmp[@]}'` )
	fi
}

#准备下一个方块
PrepareNextBox()
{
	local i x y
	#清除右边预显示的方块
	if (( ${#boxNext[@]} != 0 )); then
		for ((i = 0; i < 8; i += 2))
		do
			((y = marginTop + 1 + ${boxNext[$i]}))
			((x = marginLeft + 2 * mapWidth + 7 + 2 * ${boxNext[$i + 1]}))
			echo -ne "\033[${y};${x}H\040\040"
		done
	fi

	#随机生成预显式方块
	(( iBoxNextType = RANDOM % iSumType ))
	(( iBoxNextStyle = RANDOM % ${boxStyle[$iBoxNextType]} ))
	(( iBoxNextColor = RANDOM % $iSumColor + 1 ))

	boxNext=( `eval 'echo ${box'$iBoxNextType'_'$iBoxNextStyle'[@]}'` )


	#显示右边预显示的方块
	echo -ne "\033[1m\033[3${iBoxNextColor}m\033[4${iBoxNextColor}m"
	for ((i = 0; i < 8; i += 2))
	do
		((y = marginTop + 1 + ${boxNext[$i]}))
		((x = marginLeft + 2 * mapWidth + 7 + 2 * ${boxNext[$i + 1]}))
		echo -ne "\033[${y};${x}H[]"
	done

	echo -ne "\033[0m"

}

#显示新方块
CreateBox()
{
	if (( ${#boxCur[@]} == 0 )); then
		#当前方块不存在
		(( iBoxCurType = RANDOM % iSumType ))
		(( iBoxCurStyle = RANDOM % ${boxStyle[$iBoxCurType]} ))
		(( iBoxCurColor = RANDOM % $iSumColor + 1 ))
	else
		#当前方块已存在, 将下一个方块赋给当前方块
		iBoxCurType=$iBoxNextType;
		iBoxCurStyle=$iBoxNextStyle;
		iBoxCurColor=$iBoxNextColor
	fi

	#当前方块数组
	boxCur=( `eval 'echo ${box'$iBoxCurType'_'$iBoxCurStyle'[@]}'` )
	#初始化方块起始坐标
	boxCurY=boxCur[8];
	boxCurX=boxCur[9];

	DrawCurBox 1		#绘制当前方块
	if ! BoxMove $boxCurY $boxCurX
	then
		kill -$sigExit $PPID
		ShowExit
	fi

	PrepareNextBox
	
}

#绘制边框
DrawBorder()
{
	clear

	local i y x1 x2
	#显示边框
	echo -ne "\033[1m\033[3${cBorder}m\033[4${cBorder}m"

	((x1 = marginLeft + 1))				#左边框x坐标
	((x2 = x1 + 2 + mapWidth * 2))			#右边框x坐标
	for ((i = 0; i < mapHeight; i++))
	do
		((y = i + marginTop + 2))
		echo -ne "\033[${y};${x1}H||"		#绘制左边框
		echo -ne "\033[${y};${x2}H||"		#绘制右边框
	done

	((x1 = marginTop + mapHeight + 2))
	for ((i = 0; i < mapWidth + 2; i++))
	do
		((y = i * 2 + marginLeft + 1))
		echo -ne "\033[${mapTop};${y}H=="	#绘制上边框
		echo -ne "\033[${x1};${y}H=="		#绘制下边框
	done
	echo -ne "\033[0m"

	#显示"Score"和"Level"字样
	echo -ne "\033[1m"
	((y = marginLeft + mapWidth * 2 + 7))
	((x1 = marginTop + 10))
	echo -ne "\033[3${cScore}m\033[${x1};${y}HScore"
	((x1 = marginTop + 11))
	echo -ne "\033[3${cScoreValue}m\033[${x1};${y}H${iScore}"
	((x1 = marginTop + 13))
	echo -ne "\033[3${cScore}m\033[${x1};${y}HLevel"
	((x1 = marginTop + 14))
	echo -ne "\033[3${cScoreValue}m\033[${x1};${y}H${iLevel}"
	echo -ne "\033[0m"
}

InitDraw()
{
	clear			#清屏
	DrawBorder		#绘制边框
	CreateBox		#创建方块
}

#退出时显示GameOVer!
ShowExit()
{
	local y
	((y = mapHeight + mapTop + 3))
	echo -e "\033[${y};1HGameOver!\033[0m"
	exit
}

#游戏主程序在这儿开始.
if [[ "$1" == "--version" ]]; then
	echo "$APP_NAME $APP_VERSION"
elif [[ "$1" == "--show" ]]; then
	#当发现具有参数--show时，运行显示函数
	RunAsDisplayer
else
	bash $0 --show&	#以参数--show将本程序再运行一遍
	RunAsKeyReceiver $!	#以上一行产生的进程的进程号作为参数
fi
