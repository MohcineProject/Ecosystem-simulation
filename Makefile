main : main.cpp Aquarium.o Bestiole.o Milieu.o CapteurS.o CapteurV.o Camouflage.o Carapace.o Fins.o Behaviour.o Gregarious.o Fearful.o Cautious.o MultipleBehaviour.o Kamikaze.o BestioleFactory.o
	g++ -Wall -std=c++14 -o main main.cpp Aquarium.o Bestiole.o Milieu.o CapteurS.o CapteurV.o Camouflage.o Carapace.o Fins.o Behaviour.o Gregarious.o Fearful.o Cautious.o MultipleBehaviour.o Kamikaze.o BestioleFactory.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++14 -c Aquarium.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp
	g++ -Wall -std=c++14 -c Bestiole.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++14 -c Milieu.cpp -I .

CapteurS.o : CapteurS.h CapteurS.cpp ICapteur.h
	g++ -Wall -std=c++14 -c CapteurS.cpp -I .

CapteurV.o : CapteurV.h CapteurV.cpp ICapteur.h
	g++ -Wall -std=c++14 -c CapteurV.cpp -I .

Camouflage.o : Camouflage.h Camouflage.cpp
	g++ -Wall -std=c++14 -c Camouflage.cpp -I .

Carapace.o : Carapace.h Carapace.cpp
	g++ -Wall -std=c++14 -c Carapace.cpp -I .

Fins.o : Fins.h Fins.cpp
	g++ -Wall -std=c++14 -c Fins.cpp -I .

Behaviour.o : Behaviours/Behaviour.h Behaviours/Behaviour.cpp
	g++ -Wall -std=c++14 -c Behaviours/Behaviour.cpp -I .

Gregarious.o : Behaviours/Gregarious.h Behaviours/Gregarious.cpp
	g++ -Wall -std=c++14 -c Behaviours/Gregarious.cpp -I .

Fearful.o : Behaviours/Fearful.h Behaviours/Fearful.cpp
	g++ -Wall -std=c++14 -c Behaviours/Fearful.cpp -I .

Cautious.o : Behaviours/Cautious.h Behaviours/Cautious.cpp
	g++ -Wall -std=c++14 -c Behaviours/Cautious.cpp -I .

MultipleBehaviour.o : Behaviours/MultipleBehaviour.h Behaviours/MultipleBehaviour.cpp
	g++ -Wall -std=c++14 -c Behaviours/MultipleBehaviour.cpp -I .

Kamikaze.o : Behaviours/Kamikaze.cpp
	g++ -Wall -std=c++14 -c Behaviours/Kamikaze.cpp -I .

BestioleFactory.o : BestioleFactory.cpp BestioleFactory.h
	g++ -Wall -std=c++14 -c BestioleFactory.cpp -I .

clean:
	rm -rf *.o main


