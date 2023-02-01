all:
	ipcrm -a
	g++ -o consumer consumer.cpp
	g++ -o producer producer.cpp

