
CC=g++
DEBUG=
CFLAGS=-c -Wall $(DEBUG)
LDFLAGS=-lncursesw $(DEBUG)
SOURCES=main.cpp Umbrella_Class.cpp blackjackDisplay.cpp blackjackMain.cpp blackjackBank.cpp blackjackCard.cpp blackjackDealer.cpp blackjackDeck.cpp blackjackHand.cpp blackjackPlayer.cpp blackjackPot.cpp BattleCards.cpp WarDisplay.cpp display.cpp Game.cpp main_war.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Casino

all: clean $(SOURCES) $(EXECUTABLE)

debug: clean
debug: DEBUG +=-g
debug: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

