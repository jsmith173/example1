led: gpio_led.c 
	gcc gpio_led.c -o gpio_led

all: led

clean:
	rm -rf *.o
