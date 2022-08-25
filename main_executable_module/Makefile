CC=gcc
FLAGS=-Wall -Werror -Wextra

TARGET = ../../build/Quest_3

STATIC_TARGET = data_stat

DYNAMIC_TARGET = data_process

SRCS = \
		../data_libs/data_io.c \
		../data_libs/data_stat.c \
		../data_module/data_process.c \
		../yet_another_decision_module/decision.c \
		main_executable_module.c

INCLUDED = \
			../data_libs/ \
			../data_module/ \
			../yet_another_decision_module/

.PHONY: all clean rebuild

rebuild:
	$(CC) $(FLAGS) $(addprefix -I,$(INCLUDED)) $(SRCS) -o $(TARGET)

clean:
	rm -rf $(TARGET)

all: clean rebuild

build_with_macro:
	$(CC) $(FLAGS) $(addprefix -I,$(INCLUDED)) \
    ../data_module/data_process.c ../yet_another_decision_module/decision.c \
     main_executable_module.c ../data_libs/data_io_macro.c  ../data_libs/data_stat.c \
    -o ../../build/Quest_4 -D MACRO

data_stat.a:
	$(CC) -c ../data_libs/$(STATIC_TARGET).c
	ar -r lib$(STATIC_TARGET).a $(STATIC_TARGET).o
	rm $(STATIC_TARGET).o

build_with_static:
	$(CC) $(FLAGS) $(addprefix -I,$(INCLUDED)) \
 	../data_libs/data_io.c ../data_module/data_process.c \
 	 ../yet_another_decision_module/decision.c main_executable_module.c \
 	  -L. -l$(STATIC_TARGET) -o ../../build/Quest_5

data_process.so:
	$(CC) -c -fPIC -I ../data_libs ../data_libs/data_stat.c ../data_module/$(DYNAMIC_TARGET).c
	$(CC) -shared -o lib$(DYNAMIC_TARGET).so $(DYNAMIC_TARGET).o data_stat.o
	rm $(DYNAMIC_TARGET).o data_stat.o

build_with_dynamic:
	$(CC) $(FLAGS) $(addprefix -I,$(INCLUDED)) \
	../data_libs/data_io.c ../data_libs/data_stat.c ../yet_another_decision_module/decision.c main_executable_module.c \
	-o ../../build/Quest_6 -D DIN
