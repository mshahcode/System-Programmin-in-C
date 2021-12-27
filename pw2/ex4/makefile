obj=main.o area.o perimeter.o

hdf=...

run:$(obj)
	gcc $^ -o $@

%.o : %.c $(hdr)
	gcc -c $< -o $@

clean:
	rm *.o run