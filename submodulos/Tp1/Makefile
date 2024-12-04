# Variables
CC = gcc
CFLAGS = -Iinclude -I/usr/local/include -I../include
LDFLAGS = -L/usr/local/lib -lpthread -lmicrohttpd -lpromhttp -lprom

# Objetivos
TARGET = metrics
OBJS = src/main.o src/expose_metrics.o src/metrics.o

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compilación de objetos
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) 