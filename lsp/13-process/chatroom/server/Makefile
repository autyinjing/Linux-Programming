#!Makefile
#
# ----------------------------------------
#  
#
#  	Makefile 2015/8/22
#
#
# ----------------------------------------
#

C_SOURCES = $(shell find . -name "*.c") 	#寻找当前目录下所有的.c文件
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES)) 	#目标文件名为.c文件把.c后缀改为.o后缀

C_FLAGS = -c -g -Wall 
C_LINKFLAGS = -lrt

TARGET = ser_main 	#最终目标为服务端主程序

CC = gcc

$(TARGET): $(C_OBJECTS)
	@echo 链接 ...
	$(CC) -o $(TARGET) $(C_OBJECTS) $(C_LINKFLAGS)

$(C_OBJECTS): %.o: %.c
	@echo 编译 ...
	$(CC) $(C_FLAGS) $< -o $@

.PHONY: clean

clean:
	@echo 删除中间文件 ...
	rm -f $(C_OBJECTS)

#.PHONY: print

print:
	@echo $(C_SOURCES)
	@echo $(C_OBJECTS)
	@echo $(TARGET)

#end of Makefile
