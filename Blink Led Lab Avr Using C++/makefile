# Define the source file
SRS = $(TARGET).cpp

# Rule for compiling the target
compile: $(SRS)
	avr-g++ -mmcu=atmega32 -Os -o $(TARGET).o $(SRS)
	avr-objcopy -j .text -j .data -O ihex $(TARGET).o $(TARGET).hex
	@echo "Success Compile"

# Rule for cleaning up files
clean:
	@rm $(TARGET).hex $(TARGET).o
	@echo "done"
