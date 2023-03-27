objects = AuditFiler.o Candidate.o CPLBallot.o CPLElection.o Election.o ElectionFactory.o IRBallot.o IRElection.o Party.o
testObjects = AuditFilerTests.o CandidateTests.o CPLBallotTests.o CPLElectionTests.o ElectionFactoryTests.o IRBallotTests.o IRElectionTests.o PartyTests.o
tests = AuditFilerTests CandidateTests CPLBallotTests CPLElectionTests ElectionFactoryTests IRBallotTests IRElectionTests PartyTests

build: main.o $(objects)
	g++ main.o $(objects) -o 2-TypeElection

allTests: $(objects) $(tests)
	
%Tests: $(objects) %Tests.o
	g++ $@.o $(objects) -o $@ -lgtest -lgtest_main -lpthread

	
main.o: main.cpp
	g++ -c main.cpp
	
$(objects): %.o: %.cpp %.h
	g++ $< -c

$(testObjects): %.o: %.cpp
	g++ $< -c
	
%Tests.o: %Tests.cpp
	g++ $< -c
	
cleanOutputs:
	del *.txt

clean:
	del *.o 2-TypeElection.exe *Tests.exe