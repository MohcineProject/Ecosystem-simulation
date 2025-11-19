main : main.cpp Aquarium/Aquarium.o Bestioles/Bestiole.o Aquarium/Milieu.o Captors/CapteurS.o Captors/CapteurV.o Accessories/Camouflage.o Accessories/Carapace.o Accessories/Fins.o Behaviours/Behaviour.o Behaviours/Gregarious.o Behaviours/Fearful.o Behaviours/Cautious.o Behaviours/MultipleBehaviour.o Behaviours/Kamikaze.o Bestioles/BestioleFactory.o
	g++ -Wall -std=c++14 -o main main.cpp Aquarium/Aquarium.o Bestioles/Bestiole.o Aquarium/Milieu.o Captors/CapteurS.o Captors/CapteurV.o Accessories/Camouflage.o Accessories/Carapace.o Accessories/Fins.o Behaviours/Behaviour.o Behaviours/Gregarious.o Behaviours/Fearful.o Behaviours/Cautious.o Behaviours/MultipleBehaviour.o Behaviours/Kamikaze.o Bestioles/BestioleFactory.o -I . -lX11 -lpthread

Aquarium/Aquarium.o : Aquarium/Aquarium.h Aquarium/Aquarium.cpp
	g++ -Wall -std=c++14 -c Aquarium/Aquarium.cpp -I . -o Aquarium/Aquarium.o

Bestioles/Bestiole.o : Bestioles/Bestiole.h Bestioles/Bestiole.cpp
	g++ -Wall -std=c++14 -c Bestioles/Bestiole.cpp -I . -o Bestioles/Bestiole.o

Aquarium/Milieu.o : Aquarium/Milieu.h Aquarium/Milieu.cpp
	g++ -Wall -std=c++14 -c Aquarium/Milieu.cpp -I . -o Aquarium/Milieu.o

Captors/CapteurS.o : Captors/CapteurS.h Captors/CapteurS.cpp Captors/ICapteur.h
	g++ -Wall -std=c++14 -c Captors/CapteurS.cpp -I . -o Captors/CapteurS.o

Captors/CapteurV.o : Captors/CapteurV.h Captors/CapteurV.cpp Captors/ICapteur.h
	g++ -Wall -std=c++14 -c Captors/CapteurV.cpp -I . -o Captors/CapteurV.o

Accessories/Camouflage.o : Accessories/Camouflage.h Accessories/Camouflage.cpp
	g++ -Wall -std=c++14 -c Accessories/Camouflage.cpp -I . -o Accessories/Camouflage.o

Accessories/Carapace.o : Accessories/Carapace.h Accessories/Carapace.cpp
	g++ -Wall -std=c++14 -c Accessories/Carapace.cpp -I . -o Accessories/Carapace.o

Accessories/Fins.o : Accessories/Fins.h Accessories/Fins.cpp
	g++ -Wall -std=c++14 -c Accessories/Fins.cpp -I . -o Accessories/Fins.o

Behaviours/Behaviour.o : Behaviours/Behaviour.h Behaviours/Behaviour.cpp
	g++ -Wall -std=c++14 -c Behaviours/Behaviour.cpp -I . -o Behaviours/Behaviour.o

Behaviours/Gregarious.o : Behaviours/Gregarious.h Behaviours/Gregarious.cpp
	g++ -Wall -std=c++14 -c Behaviours/Gregarious.cpp -I . -o Behaviours/Gregarious.o

Behaviours/Fearful.o : Behaviours/Fearful.h Behaviours/Fearful.cpp
	g++ -Wall -std=c++14 -c Behaviours/Fearful.cpp -I . -o Behaviours/Fearful.o

Behaviours/Cautious.o : Behaviours/Cautious.h Behaviours/Cautious.cpp
	g++ -Wall -std=c++14 -c Behaviours/Cautious.cpp -I . -o Behaviours/Cautious.o

Behaviours/MultipleBehaviour.o : Behaviours/MultipleBehaviour.h Behaviours/MultipleBehaviour.cpp
	g++ -Wall -std=c++14 -c Behaviours/MultipleBehaviour.cpp -I . -o Behaviours/MultipleBehaviour.o

Behaviours/Kamikaze.o : Behaviours/Kamikaze.h Behaviours/Kamikaze.cpp
	g++ -Wall -std=c++14 -c Behaviours/Kamikaze.cpp -I . -o Behaviours/Kamikaze.o

Bestioles/BestioleFactory.o : Bestioles/BestioleFactory.cpp Bestioles/BestioleFactory.h
	g++ -Wall -std=c++14 -c Bestioles/BestioleFactory.cpp -I . -o Bestioles/BestioleFactory.o

clean:
	rm -rf *.o main Aquarium/*.o Bestioles/*.o Captors/*.o Accessories/*.o Behaviours/*.o


