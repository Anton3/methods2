# Флаги gcc
CC_FLAGS    := -O3 -masm=intel -Werror -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -std=gnu99 -c
LD_FLAGS    :=

# Списки требуемых объектных файлов
C_SOURCES   := $(shell find src -type f -iname '*.c')
C_TARGETS   := $(shell find src/main -type f -iname '*.c')

OBJECTS     := $(C_SOURCES:.c=.o)
O_TARGETS   := $(C_TARGETS:.c=.o)
O_SOURCES   := $(filter-out $(O_TARGETS), $(OBJECTS))
TARGETS     := bin/main

MAIN_FILES.bin/main := src/main/main.o

# Не нужно вызывать `make clean; make` при компиляции заново
all: clean_bin $(TARGETS) clean_obj

# Сборка целей
$(TARGETS): $(OBJECTS)
	gcc $(LD_FLAGS) $(O_SOURCES) $(MAIN_FILES.$@) -o $@ -lm

# Компиляция
%.o: %.c
	gcc $(CC_FLAGS) -o $@ $<

# Очистка
.PHONY: clean_bin clean_obj clean
	
clean_bin:
	rm -f $(TARGETS)

clean_obj:
	rm -f $(OBJECTS)

clean:
	rm -f $(TARGETS) $(OBJECTS)
