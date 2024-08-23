CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra

# Target binary name
TARGET = column80

# Source file
SOURCE = main.cpp

# Installation directory
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin


$(TARGET): main.o
	$(CXX) $(CXXFLAGS) main.o -o $(TARGET)
	rm *.o

# Install the binary to the system-wide location
install: $(TARGET)
	install -m 0755 $(TARGET) $(BINDIR) 
	rm -f $(TARGET)

# Uninstall the binary from system-wide location
uninstall:
	rm -f $(BINDIR)/$(TARGET)

# Compile the binary
main.o: $(SOURCE)
	$(CXX) $(CXXFLAGS) -c $(SOURCE)

# Clean up the build
clean: 
	rm *.o
	rm -f $(TARGET)