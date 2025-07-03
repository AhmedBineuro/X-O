buildXoeai:
	g++ main.cpp -o XOEAI
buildTest:
	g++ ./tests/TestMain.cpp -o ./tests/TestMain

runXOEAI: ./XOEAI
	./XOEAI

runTest: ./tests/TestMain
	./tests/TestMain

XOEAI: buildXoeai
	./XOEAI
test: buildTest
	./tests/TestMain

clean:
	rm ./XOEAI
	rm ./tests/TestMain


