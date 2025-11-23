DEPENDENCY = Dependencies
STATIC_LIBRAIRIES_BUILD = Build/lib
TEST_BINARY_DIRECTORY = Build/test
BINARY_DIRECTORY = Build/bin

# Object files for tests
OBJECT_FILES = Bestioles/Bestiole.o Aquarium/Milieu.o Aquarium/Aquarium.o \
               Captors/CapteurS.o Captors/CapteurV.o Accessories/Camouflage.o \
               Accessories/Carapace.o Accessories/Fins.o Behaviours/Behaviour.o \
               Behaviours/Gregarious.o Behaviours/Fearful.o Behaviours/Cautious.o \
               Behaviours/MultipleBehaviour.o Behaviours/Kamikaze.o \
               Bestioles/BestioleFactory.o

# Test source files
TEST_SOURCES = tests/test_Bestiole.cpp

# The building process

$(BINARY_DIRECTORY)/main : main.cpp $(OBJECT_FILES)
	@mkdir -p $(BINARY_DIRECTORY)
	@g++ -Wall -std=c++17 -o $(BINARY_DIRECTORY)/main main.cpp $(OBJECT_FILES) -I . -lX11 -lpthread

Aquarium/Aquarium.o : Aquarium/Aquarium.h Aquarium/Aquarium.cpp
	g++ -Wall -std=c++17 -c Aquarium/Aquarium.cpp -I . -o Aquarium/Aquarium.o

Bestioles/Bestiole.o : Bestioles/Bestiole.h Bestioles/Bestiole.cpp
	g++ -Wall -std=c++17 -c Bestioles/Bestiole.cpp -I . -o Bestioles/Bestiole.o

Aquarium/Milieu.o : Aquarium/Milieu.h Aquarium/Milieu.cpp
	g++ -Wall -std=c++17 -c Aquarium/Milieu.cpp -I . -o Aquarium/Milieu.o

Captors/CapteurS.o : Captors/CapteurS.h Captors/CapteurS.cpp Captors/ICapteur.h
	g++ -Wall -std=c++17 -c Captors/CapteurS.cpp -I . -o Captors/CapteurS.o

Captors/CapteurV.o : Captors/CapteurV.h Captors/CapteurV.cpp Captors/ICapteur.h
	g++ -Wall -std=c++17 -c Captors/CapteurV.cpp -I . -o Captors/CapteurV.o

Accessories/Camouflage.o : Accessories/Camouflage.h Accessories/Camouflage.cpp
	g++ -Wall -std=c++17 -c Accessories/Camouflage.cpp -I . -o Accessories/Camouflage.o

Accessories/Carapace.o : Accessories/Carapace.h Accessories/Carapace.cpp
	g++ -Wall -std=c++17 -c Accessories/Carapace.cpp -I . -o Accessories/Carapace.o

Accessories/Fins.o : Accessories/Fins.h Accessories/Fins.cpp
	g++ -Wall -std=c++17 -c Accessories/Fins.cpp -I . -o Accessories/Fins.o

Behaviours/Behaviour.o : Behaviours/Behaviour.h Behaviours/Behaviour.cpp
	g++ -Wall -std=c++17 -c Behaviours/Behaviour.cpp -I . -o Behaviours/Behaviour.o

Behaviours/Gregarious.o : Behaviours/Gregarious.h Behaviours/Gregarious.cpp
	g++ -Wall -std=c++17 -c Behaviours/Gregarious.cpp -I . -o Behaviours/Gregarious.o

Behaviours/Fearful.o : Behaviours/Fearful.h Behaviours/Fearful.cpp
	g++ -Wall -std=c++17 -c Behaviours/Fearful.cpp -I . -o Behaviours/Fearful.o

Behaviours/Cautious.o : Behaviours/Cautious.h Behaviours/Cautious.cpp
	g++ -Wall -std=c++17 -c Behaviours/Cautious.cpp -I . -o Behaviours/Cautious.o

Behaviours/MultipleBehaviour.o : Behaviours/MultipleBehaviour.h Behaviours/MultipleBehaviour.cpp
	g++ -Wall -std=c++17 -c Behaviours/MultipleBehaviour.cpp -I . -o Behaviours/MultipleBehaviour.o

Behaviours/Kamikaze.o : Behaviours/Kamikaze.h Behaviours/Kamikaze.cpp
	g++ -Wall -std=c++17 -c Behaviours/Kamikaze.cpp -I . -o Behaviours/Kamikaze.o

Bestioles/BestioleFactory.o : Bestioles/BestioleFactory.cpp Bestioles/BestioleFactory.h
	g++ -Wall -std=c++17 -c Bestioles/BestioleFactory.cpp -I . -o Bestioles/BestioleFactory.o

clean:
	rm -rf *.o main Aquarium/*.o Bestioles/*.o Captors/*.o Accessories/*.o Behaviours/*.o $(BINARY_DIRECTORY)/main

clean-all: clean
	rm -rf Build/* Dependencies/*

# Download the dependencies

get-deps: get-CImg
	@echo "All dependencies have been downloaded and set up."


## Get the CImg dependecy
get-CImg:
	@if [ ! -f "$(DEPENDENCY)/CImg.h" ]; then \
		mkdir -p "$(DEPENDENCY)"; \
		cd "$(DEPENDENCY)"; \
		curl -L https://raw.githubusercontent.com/dtschump/CImg/v.3.1.6/CImg.h -o CImg.h || \
		wget https://raw.githubusercontent.com/dtschump/CImg/v.3.1.6/CImg.h -O CImg.h || \
		(echo "Couldn't download the CImg dependency, check if curl or wget is installed"; exit 1); \
	fi
	@if [ ! -f "$(DEPENDENCY)/UImg.h" ]; then \
		echo "Creating UImg.h wrapper..."; \
		echo '#ifndef _UIMG_H_' > $(DEPENDENCY)/UImg.h; \
		echo '#define _UIMG_H_' >> $(DEPENDENCY)/UImg.h; \
		echo '' >> $(DEPENDENCY)/UImg.h; \
		echo '#include "CImg.h"' >> $(DEPENDENCY)/UImg.h; \
		echo '' >> $(DEPENDENCY)/UImg.h; \
		echo 'using namespace cimg_library;' >> $(DEPENDENCY)/UImg.h; \
		echo '' >> $(DEPENDENCY)/UImg.h; \
		echo 'typedef unsigned char      T;' >> $(DEPENDENCY)/UImg.h; \
		echo 'typedef CImg<T>            UImg;' >> $(DEPENDENCY)/UImg.h; \
		echo '' >> $(DEPENDENCY)/UImg.h; \
		echo '#endif' >> $(DEPENDENCY)/UImg.h; \
	fi
	@echo "Setup of CImg is done"

# Launching the application

launch: $(BINARY_DIRECTORY)/main
	$(BINARY_DIRECTORY)/main

# The testing process

# A quick command to download and setup the required gtest static library
setup-gtest:
	@echo "Setting up gtest..."
	@if [ ! -d "$(DEPENDENCY)/gtest/googletest" ]; then \
		mkdir -p $(DEPENDENCY)/gtest; \
		cd $(DEPENDENCY) ; \
		git clone https://github.com/google/googletest.git gtest; \
	fi
	@if [ ! -f "$(STATIC_LIBRAIRIES_BUILD)/libgtest.a" ]; then \
		mkdir -p $(STATIC_LIBRAIRIES_BUILD); \
		g++ -Wall -std=c++17 -isystem $(DEPENDENCY)/gtest/googletest/include \
		    -I$(DEPENDENCY)/gtest/googletest -pthread \
		    -c $(DEPENDENCY)/gtest/googletest/src/gtest-all.cc \
		    -o $(STATIC_LIBRAIRIES_BUILD)/gtest-all.o; \
		g++ -Wall -std=c++17 -isystem $(DEPENDENCY)/gtest/googletest/include \
			-I$(DEPENDENCY)/gtest/googletest -pthread \
			-c $(DEPENDENCY)/gtest/googletest/src/gtest_main.cc \
			-o $(STATIC_LIBRAIRIES_BUILD)/gtest_main.o; \
		ar -rv $(STATIC_LIBRAIRIES_BUILD)/libgtest.a \
			$(STATIC_LIBRAIRIES_BUILD)/gtest-all.o $(STATIC_LIBRAIRIES_BUILD)/gtest_main.o; \
		rm $(STATIC_LIBRAIRIES_BUILD)/gtest-all.o; \
		rm $(STATIC_LIBRAIRIES_BUILD)/gtest_main.o; \
	fi
	@echo "Setup of gtest was successful"

test: setup-gtest $(OBJECT_FILES)
	@mkdir -p $(TEST_BINARY_DIRECTORY)
	@g++ -Wall -std=c++17 \
	    -I. \
	    -isystem $(DEPENDENCY)/gtest/googletest/include \
	    -I$(DEPENDENCY)/gtest/googletest \
	    $(TEST_SOURCES) $(OBJECT_FILES) \
	    -L$(STATIC_LIBRAIRIES_BUILD) -lgtest -lX11 -lpthread \
	    -o $(TEST_BINARY_DIRECTORY)/test_runner;
	@./$(TEST_BINARY_DIRECTORY)/test_runner

.PHONY: clean clean-all test setup-gtest get-deps get-CImg