buildMain:
	g++ main.cpp -o TicTacToe
buildTest:
	g++ ./tests/TestMain.cpp -o ./tests/TestMain

main: buildMain
	./TicTacToe
test: buildTest
	./tests/TestMain

clean:
	rm ./TicTacToe
	rm ./tests/TestMain


