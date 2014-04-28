SRC = .
DOC = doc
BINARY = laesa
GXX = g++
FLAGS = -Wall -pedantic -Wno-long-long -g -O0
OBJECTS =\
	$(SRC)/main.o\
	$(SRC)/laesa.o\
	$(SRC)/vector.o\
	$(SRC)/exceptions.o\
	$(SRC)/result.o


all: compile

compile: $(BINARY)

run:
	./$(BINARY)

doc: $(SRC)/*.cpp $(SRC)/*.h
	rm -Rf $(DOC)
	mkdir $(DOC)
	doxygen Doxyfile

count:
	\wc -l $(SRC)/*.cpp $(SRC)/*.h

clean:
	rm -Rf $(DOC) $(BINARY) $(OBJECTS)


$(BINARY): $(OBJECTS)
	$(GXX) -o $(BINARY) $(OBJECTS) $(CLIBS)
$(BIN): $(OBJECTS)
	$(GXX) $(FLAGS) $(OBJECTS) -o $(BIN) $(CLIBS)
$(SRC)/main.o: $(SRC)/main.cpp
	$(GXX) $(FLAGS) -c $(SRC)/main.cpp -o $(SRC)/main.o $(CLIBS)
$(SRC)/laesa.o: $(SRC)/laesa.cpp
	$(GXX) $(FLAGS) -c $(SRC)/laesa.cpp -o $(SRC)/laesa.o $(CLIBS)
$(SRC)/vector.o: $(SRC)/vector.cpp
	$(GXX) $(FLAGS) -c $(SRC)/vector.cpp -o $(SRC)/vector.o $(CLIBS)
$(SRC)/exceptions.o: $(SRC)/exceptions.cpp
	$(GXX) $(FLAGS) -c $(SRC)/exceptions.cpp -o $(SRC)/exceptions.o $(CLIBS)
$(SRC)/result.o: $(SRC)/result.cpp
	$(GXX) $(FLAGS) -c $(SRC)/result.cpp -o $(SRC)/result.o $(CLIBS)